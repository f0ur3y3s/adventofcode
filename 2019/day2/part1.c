#include <stdio.h>
#include <stdlib.h>
#include "intarr/intarr.h"
#include <sys/types.h>
#include <string.h>
// 1,9,10,3,2,3,11,0,99,30,40,50

void program_print(intarr_t *program_arr)
{
    for (int idx = 0; idx < program_arr->size; idx++)
    {
        printf("%d,", program_arr->values[idx]);
    }
    printf("\n");
}

int program_load(FILE *p_input_file, intarr_t *program_arr)
{
    char *program = NULL;
    size_t size = 0;
    ssize_t read = 0;
    read = getline(&program, &size, p_input_file);
    if (read == 0)
    {
        return 0;
    }
    program[strcspn(program, "\n")] = '\0';

    int instruction = 0;
    char *token;
    token = strtok(program, ",");
    while (token != NULL)
    {
        sscanf(token, "%d", &instruction);
        intarr_add(program_arr, instruction);
        token = strtok(NULL, ",");
    }

    program_print(program_arr);
    rewind(p_input_file);
    free(program);
    return 1;
}

void program_run(intarr_t *program_arr)
{
    // start at zero
    int instruction = 0;
    int instruction_idx = 0;
    int num1 = 0;
    int num2 = 0;
    instruction = program_arr->values[instruction_idx];
    while (instruction != 99)
    {
        switch (instruction)
        {
            case 1:
                num1 = program_arr->values[program_arr->values[instruction_idx + 1]];
                num2 = program_arr->values[program_arr->values[instruction_idx + 2]];
                program_arr->values[program_arr->values[instruction_idx + 3]] = num1 + num2;
                break;
            case 2:
                num1 = program_arr->values[program_arr->values[instruction_idx + 1]];
                num2 = program_arr->values[program_arr->values[instruction_idx + 2]];
                program_arr->values[program_arr->values[instruction_idx + 3]] = num1 * num2;
                break;
            case 99:
                printf("Somehow end of program found inside while\n");
                break;
            default:
                printf("Unknown instruction, exiting...\n");
                return;
        }
        instruction_idx += 4;
        instruction = program_arr->values[instruction_idx];
    }
    printf("End of program found.\n");
}

int
main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s [file]\n", argv[0]);

    }

    FILE *p_input_file;
    p_input_file = fopen(argv[1],"r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    intarr_t *program_arr = intarr_create();
    program_load(p_input_file, program_arr);
    // load the program into an array
    program_run(program_arr);
    program_print(program_arr);

    fclose(p_input_file);
    intarr_free(program_arr);
}