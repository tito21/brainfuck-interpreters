// Copyright (C) 2019  Alberto Di Biase
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

#ifndef VERBOSE
#define VERBOSE 0
#endif
#ifndef TAPE_SIZE
#define TAPE_SIZE 5000000
#endif

#ifndef CODE_SIZE
#define CODE_SIZE 100000
#endif

#ifndef STACKWIDTH
#define STACKWIDTH 10
#endif


typedef enum
{
    PNT,
    JMP,
    BRZ,
    INC_TP,
    INC,
    DCN,
    DCN_TP
} signal;

typedef struct
{
    signal inst;
    int nex_pc; // for BRZ and JUMP indicate where to jump the PC
} Instruction;

char *signalf(signal c) {
    switch (c)
    {
    case DCN_TP:
        return "DCN_TP";
    case INC:
        return "INC";
    case DCN:
        return "DCN";
    case JMP:
        return "JMP";
    case PNT:
        return "PNT";
    case BRZ:
        return "BRZ";
    case INC_TP:
        return "INC_TP";
    default:
        break;
    }
}

void printStack(char* stack, const size_t n)
{
    int i = 0;
    printf("\n ");
    for (; i < n-1; ++i)
        printf("%3i, ", stack[i]);
    printf("%3i\n", stack[i+1]);
}

void dispState(char* stack, const size_t n, int pointer) {
    printf("\nStack state:\n");
    printStack(stack, STACKWIDTH);
    char * str_pointer = malloc(3*pointer*sizeof(char));
    memset(str_pointer, ' ', 3*pointer*sizeof(char));
    str_pointer[3*pointer] = '^';
    printf(" %s", str_pointer);
    printf("\nPointer at: %d", pointer);
    printf("\nValue: %d\n", stack[pointer]);
    free(str_pointer);
}

void execInstruction(Instruction inst, int *inst_pointer, char tape[], int *tape_pointer) {
    switch (inst.inst)
    {
    case JMP:
        *inst_pointer = inst.nex_pc;
        break;

    case BRZ:
        if (tape[*tape_pointer] == 0) {
            *inst_pointer = inst.nex_pc;
        }
        else {
            *inst_pointer += 1;
        }
        break;
    case INC_TP:
        *tape_pointer += 1;
        *inst_pointer += 1;
        break;
    case INC:
        tape[*tape_pointer] += 1;
        *inst_pointer += 1;
        break;
    case DCN:
        tape[*tape_pointer] -= 1;
        *inst_pointer += 1;
        break;
    case DCN_TP:
        *tape_pointer -= 1;
        *inst_pointer += 1;
        break;
    case PNT:
        if (VERBOSE) {
            printf("%d", tape[*tape_pointer]);
        }
        else {
            printf("%c", tape[*tape_pointer]);
        }
        *inst_pointer += 1;
        break;
    default:
        // Nothing to do
        break;
    }
}

int getByteCode(FILE *file, Instruction code[]) {
    int c;
    int i = 0;
    Node *loop_stack = newEmptyQueue();
    // loop_stack->next = NULL;
    int zero = 0;
    loop_stack->value = &zero;

    while ((c = fgetc(file)) != EOF) {
        if ( !strchr("[]<>+-.", c)) {
            continue;
        }
        printf("%i, %c\n", i, c);
        dispList(loop_stack);

        switch (c) {
            case '<':
                code[i].inst = DCN_TP;
                code[i].nex_pc = 1;
                break;
            case '>':
                code[i].inst = INC_TP;
                code[i].nex_pc = 1;
                break;
            case '+':
                code[i].inst = INC;
                code[i].nex_pc = 1;
                break;
            case '-':
                code[i].inst = DCN;
                code[i].nex_pc = 1;
                break;
            case '.':
                code[i].inst = PNT;
                code[i].nex_pc = 1;
                break;
            case '[':
                code[i].inst = BRZ;
                { // make sure value is reintialize
                    int *v = malloc(sizeof(int));
                    *v = i;
                    printf("value %d @:%p\n", *v, v);
                    loop_stack = pushQueue(loop_stack, v);
                }
                // printf("loopstack: \n");
                // dispList(loop_stack);
                // printf("i: %d\n", i);
                code[i].nex_pc = 1;
                break;
            case ']':
                code[i].inst = JMP;
                // dispList(loop_stack);
                int s = *(int *)loop_stack->value;
                // printf("loop to %d\n", s);
                // int s = 11;
                code[i].nex_pc = s;
                code[s].nex_pc = i+1;
                loop_stack = shiftQueue(loop_stack);
                break;
            default:
                // don't increment i
                i--;
                break;
        }
        i++;
    }
    // freeQueue(loop_stack);
    fclose(file);
    return i;
}

int main(int argc, char const *argv[]) {
    FILE *file;
    if (argc < 2) {
        printf("No input file specified, reading from stdin\n");
        file = stdin;
    }
    else
    {
        file = fopen(argv[1], "r");
        if (file==NULL)
        {
            printf("File %s not found\n", argv[1]);
            return 1;
        }
    }
    Instruction *code = malloc(sizeof(Instruction)*CODE_SIZE);
    int code_length = getByteCode(file, code);
    char tape[TAPE_SIZE];
    int tape_pointer = 0;
    int inst_pointer = 0;
    for (int i = 0; i < code_length; i++)
    {
        printf("%i: %s, %d\n", i, signalf(code[i].inst), code[i].nex_pc);
    }
    // return 0;

    while (inst_pointer < code_length) {
        if (VERBOSE) dispState(tape, TAPE_SIZE, tape_pointer);
        execInstruction(code[inst_pointer], &inst_pointer, tape, &tape_pointer);
    }

    printf("\n-------End of program-------\n");
    dispState(tape, TAPE_SIZE, tape_pointer);
    free(code);
    return 0;

}
