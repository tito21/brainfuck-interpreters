// Copyright (C) 2019  Alberto Di Biase
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

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
    BRZ,
    INC_PC,
    INC
} signal;

typedef struct
{
    signal inst;
    int nex_pc; // for BRZ and JUMP indicate how much to increment or decrement the PC
} Instruction;


void printStack(char* stack, const size_t n)
{
    int i = 0;
    printf("\n ");
    for (; i < n-1; ++i)
        printf("%3i, ", stack[i]);
    printf("%3i\n", stack[i+1]);
}

void dispState(char* stack, const size_t n, int pointer)
{
    printf("\nStack state:\n");
    printStack(stack, STACKWIDTH);
    char * str_pointer = malloc(3*pointer*sizeof(char));
    memset(str_pointer, ' ', 3*pointer*sizeof(char));
    str_pointer[3*pointer] = '^';
    printf(" %s", str_pointer);
    printf("\nPointer at: %d\n", pointer);
}


void getByteCode(FILE *file, Instruction code[], int *code_len)
{
    int c;
    int i = 0;
    Node *loop_stack = newEmptyQueue();

    while ((c = fgetc(file)) != EOF)
    {
        if (strchr("<>+-[],.", c))
        {
            code[i].inst = c;

            if (c == '[') {
                loop_stack = pushQueue(loop_stack, &code[i]);
                ;
            }
            else if (c == ']') {
                loop_stack = popQueue(loop_stack);
            }
            else {
                code[i].nex_pc = 1;
            }
            i++;
        }
    }
    freeQueue(loop_stack);
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

}
