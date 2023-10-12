#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char line[16];
    int line_number;
} instruction_t;

typedef struct node {
    instruction_t data;
    struct node* prev;
    struct node* next;
} node_t;

typedef struct {
    node_t* head;
    node_t* tail;
} instruction_list_t;

void initList(instruction_list_t* list) {
    list->head = NULL;
    list->tail = NULL;
}

void appendToList(instruction_list_t *list, char *line, int line_number)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strncpy(new_node->data.line, line, sizeof(new_node->data.line));
    new_node->data.line_number = line_number;
    new_node->prev = list->tail;
    new_node->next = NULL;

    if (list->tail) {
        list->tail->next = new_node;
    }

    if (!list->head) {
        list->head = new_node;
    }

    list->tail = new_node;
}

void freeList(instruction_list_t *list)
{
    node_t* current = list->head;
    while (current != NULL)
    {
        node_t *next = current->next;
        free(current);
        current = next;
    }
}

void printList(instruction_list_t* list)
{
    node_t* current = list->head;
    while (current != NULL)
    {
        printf("List line: %s\n", current->data.line);
        current = current->next;
    }
}

void readFile(FILE *p_input_file, instruction_list_t *list)
{
    char buffer[16];
    int line_number = 1;
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        appendToList(list, buffer, line_number);
        line_number ++;
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
        if (2 == idx)
        {
            bunny_reg[idx].value = 1;
        }
        else{
            bunny_reg[idx].value = 0;
        }
    }
}

void printRegs(reg_t bunny_reg[4])
{
    for (int idx = 0; idx < 4; idx++)
    {
        printf("REG %c: %d\n", bunny_reg[idx].cid, bunny_reg[idx].value);
    }
}

reg_t *findReg(reg_t bunny_reg[4], char target)
{
    for (int idx = 0; idx < 4; idx++)
    {
        if (bunny_reg[idx].cid == target)
        {
            return &bunny_reg[idx];
        }
    }
    return NULL; // Return NULL if the target register is not found.
}

void copyReg(reg_t *bunny_reg, int new_value)
{
    bunny_reg->value = new_value;
}

void incReg(reg_t *bunny_reg, int new_value)
{
    bunny_reg->value += new_value;
}

void executeProgram(reg_t bunny_reg[4], instruction_list_t *program)
{
    char buffer[16];
    int val;
    int val2;
    char reg;
    char reg2;
    node_t* current = program->head;
    int programCounter = 0; // Initialize program counter

    while (current != NULL)
    {
        // programCounter = 0;
        // printf("LINE %d: %s\n", current->data.line_number, current->data.line);
        if (sscanf(current->data.line, "jnz %d %d", &val, &val2) == 2)
        {
            if (val != 0)
            {
                programCounter += val2;
            }
            else
            {
                programCounter++; // If val is zero, move to the next instruction
            }
        }
        else if (sscanf(current->data.line, "jnz %c %d", &reg, &val) == 2)
        {
            if (findReg(bunny_reg, reg)->value != 0)
            {
                programCounter += val;
            }
            else
            {
                programCounter++;
            }
        }
        else
        {
            // Handle other instructions (cpy, inc, dec) as before
            if (sscanf(current->data.line, "cpy %d %c", &val, &reg) == 2)
            {
                copyReg(findReg(bunny_reg, reg), val);
            }
            else if (sscanf(current->data.line, "cpy %c %c", &reg, &reg2) == 2)
            {
                copyReg(findReg(bunny_reg, reg2), findReg(bunny_reg, reg)->value);
            }
            else if (sscanf(current->data.line, "inc %c", &reg) == 1)
            {
                incReg(findReg(bunny_reg, reg), 1);
            }
            else if (sscanf(current->data.line, "dec %c", &reg) == 1)
            {
                incReg(findReg(bunny_reg, reg), -1);
            }
            else
            {
                printf("Unknown instruction");
                exit(1);
            }
            programCounter++; // Move to the next instruction
        }
        // Update current to the appropriate instruction based on programCounter
        current = program->head;
        // printf("programCounter: %d\n", programCounter);
        for (int i = 0; i < programCounter; i++)
        {
            current = current->next;
        }
        // printRegs(bunny_reg);
    }
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

    instruction_list_t program;
    initList(&program);
    readFile(p_input_file, &program);

    reg_t bunny_reg[4];
    size_t bunny_length = sizeof(bunny_reg)/sizeof(reg_t);
    initRegs(bunny_reg, bunny_length);
    // printRegs(bunny_reg);
    executeProgram(bunny_reg, &program);
    printRegs(bunny_reg);

    freeList(&program);
    fclose(p_input_file);
    exit(0);
}