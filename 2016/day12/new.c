#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char line[16];
} instruction_t;

typedef struct {
    instruction_t *data;
    size_t size;
    size_t capacity;
} instruction_stack_t;

void initStack(instruction_stack_t* stack, size_t capacity)
{
    stack->data = (instruction_t*)malloc(capacity * sizeof(instruction_t));
    if (!stack->data)
    {
        printf("Alloc failed!\n");
        exit(1);
    }
    stack->size = 0;
    stack->capacity = capacity;
}

void freeStack(instruction_stack_t *stack)
{
    free(stack->data);
}

void push(instruction_stack_t *stack, char *line)
{
    if (stack->size < stack->capacity)
    {
        strncpy(stack->data[stack->size].line, line, sizeof(stack->data[stack->size].line));
        stack->size++;
    }
    else
    {
        int new_capacity = stack->capacity * 2;
        stack->data = (instruction_t*)realloc(stack->data, new_capacity * sizeof(instruction_t));

        if (stack->data == NULL) {
            printf("Realloc failed!\n");
            exit(1);
        }
        stack->capacity = new_capacity;
        strncpy(stack->data[stack->size].line, line, sizeof(stack->data[stack->size].line));
        stack->size++;
    }
}

void readFile(FILE *p_input_file, instruction_stack_t *stack)
{
    char buffer[16];
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        push(stack, buffer);
    }
}

void printStack(instruction_stack_t *stack)
{
    for (int idx = 0; idx < stack->size; idx ++)
    {
        printf("Stack line: %s\n", stack->data[idx].line);
    }
}

typedef struct {
    int value;
    char cid;
} reg_t;

void initRegs(reg_t bunny_reg[4], size_t size)
{
    for (int idx = 0; idx < size; idx++)
    {
        bunny_reg[idx].cid = 'a' + idx;
        bunny_reg[idx].value = 0;
    }
}

void printRegs(reg_t bunny_reg[4], size_t size)
{
    for (int idx = 0; idx < size; idx++)
    {
        printf("REG %c: %d\n", bunny_reg[idx].cid, bunny_reg[idx].value);
    }
}

void copyReg(reg_t *bunny_reg, int new_value)
{
    bunny_reg->value = new_value;
}

void incReg(reg_t *bunny_reg, int new_value)
{
    bunny_reg->value += new_value;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *p_input_file = NULL;
    p_input_file = fopen(argv[1],"r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    instruction_stack_t instr_stack;
    initStack(&instr_stack, 2);
    readFile(p_input_file, &instr_stack);
    printStack(&instr_stack);

    reg_t bunny_reg[4];
    size_t bunny_length = sizeof(bunny_reg)/sizeof(reg_t);
    initRegs(bunny_reg, bunny_length);
    // printRegs(bunny_reg, bunny_length);
    int idx = 0;


    fclose(p_input_file);
    freeStack(&instr_stack);
    exit(0);
}