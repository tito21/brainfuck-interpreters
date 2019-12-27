#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

#ifndef VERBOSE
#define VERBOSE 0
#endif
#ifndef S
#define S 500000
#endif
#ifndef C
#define C 500000
#endif
#ifndef STACKWIDTH
#define STACKWIDTH 15
#endif


typedef enum
{
    JUMP,
    LOOP,
    CNT,
    HALT
} signal;

#define JUMP 1
#define LOOP 2
#define CNT 3
#define HALT 4

#include <stdio.h>
#include <string.h>


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
    // char str_pointer[STACKWIDTH*5];
    // memset(str_pointer, ' ', NELEMS(str_pointer));
    // str_pointer[(pointer*4)] = '^';
    printf("%d\n", pointer);
}

unsigned int matchLoop(char* code, unsigned int inst) {
    unsigned int i = inst-1;
    // if (VERBOSE) printf("%d\n", i);
    int nested = 1;
    while (i > 0)
    {
        // printf("%d\n", i);
        if (nested == 0)
        {
            return i+1;
        }
        if (code[i] == '[')
        {
            nested-=1;
        }
        if (code[i] == ']')
        {
            nested+=1;
        }
        i--;
    }
    return 0;
}

unsigned int matchJump(char* code, unsigned int inst) {
    unsigned int i = inst+1;
    int nested = 1;
    while (code[i])
    {
        // if (VERBOSE) printf("%d\n", i);
        if (nested == 0)
        {
            return i;
        }
        if (code[i] == ']')
        {
            nested-=1;
        }
        if (code[i] == '[')
        {
            nested+=1;
        }
        i++;
    }
    return 0;
}

signal runInstruction(char* stack, unsigned int * pointer, char inst)
{
    switch (inst)
    {
    case '+':
        stack[*pointer]++;
        return CNT;
        break;
    case '-':
        stack[*pointer]--;
        return CNT;
        break;
    case '>':
        (*pointer)++;
        return CNT;
        break;
    case '<':
        (*pointer)--;
        return CNT;
        break;
    case '[':
        if (VERBOSE) printf("%d",stack[ *pointer]);
        if (stack[*pointer] == 0) return JUMP;
        else return CNT;
        break;
    case ']':
        return LOOP;
        break;
    case '.':
        if (VERBOSE) printf("printing ");
        printf("%c", stack[*pointer]);
        if (VERBOSE) printf("\n");
        return CNT;
        break;
    case ',':
        scanf("%c", &stack[*pointer]);
        return CNT;
        break;
    default:
        return HALT;
        break;
    }
}

void getCode(FILE *file, char code[], int *code_len)
{

    int c;
    int i = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if (strchr("<>+-[],.", c))
        {
            code[i] = c;
            i++;
        }
    }
    *code_len = i;
    fclose(file);
}


int main(int argc, char const *argv[])
{
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


    // Create a str with the code
    char code[C];
    memset(code, '\0', NELEMS(code));
    int lastInst;
    getCode(file, code, &lastInst);

    printf("Executing: \n%s\n", code);
    char stack[S];
    memset(stack, 0, NELEMS(stack));
    unsigned int stackPointer = 0;
    unsigned int insPointer = 0;

    while (insPointer < lastInst)
    {
        if (VERBOSE) printf("%x, %d, %c\n", stackPointer, insPointer, code[insPointer]);
        if (VERBOSE) printStack(stack, NELEMS(stack));
        // int acc = runInstruction(stack, &stackPointer, code[insPointer]);
        switch (runInstruction(stack, &stackPointer, code[insPointer]))
        {
        case CNT:
            insPointer++;
            break;
        case JUMP:
            if (VERBOSE) printf("matching jump: ");
            insPointer = matchJump(code, insPointer);
            if (VERBOSE) printf("%d\n", insPointer);
            break;
        case LOOP:
            if (VERBOSE) printf("matching loop: ");
            insPointer = matchLoop(code, insPointer);
            if (VERBOSE) printf("%d\n", insPointer);
            break;
        case HALT:
            insPointer = 1+lastInst;
            break;
        default:
            break;
        }
    }

    dispState(stack, NELEMS(stack), stackPointer);

    return 0;
}
