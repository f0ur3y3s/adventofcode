#include <stdio.h>
#include <stdlib.h>
#include "intarr/intarr.h"
#include <sys/types.h>
#include <string.h>
#include <limits.h>
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

int literal_or_parameter (int n)
{
    if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
    if (n < 100) return 1;
    return 2;
}

int number_length(int n)
{
    if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    /*      2147483647 is 2^31-1 - add more ifs as needed
       and adjust this final return as well. */
    return 10;
}

void program_run(intarr_t *program_arr)
{
    // start at zero
    int instr = 0;
    int instr_idx = 0;
    int num1 = 0;
    int num2 = 0;
    int num_len = 0;
    instr = program_arr->values[instr_idx];
    int instr_type = literal_or_parameter(instr); // 1 being positional, 2 being parameter
    printf("Instr\tIdx\tType\n");
    while (instr != 99)
    {
        switch (instr_type)
        {
            case 1:
                printf("%d\t%d\t%s\n", instr, instr_idx, instr_type == 1 ? "literal" : "parameter");
                switch (instr)
                {
                    case 1:
                        num1 = program_arr->values[program_arr->values[instr_idx + 1]];
                        num2 = program_arr->values[program_arr->values[instr_idx + 2]];
                        program_arr->values[program_arr->values[instr_idx + 3]] = num1 + num2;
                        instr_idx += 4;

                        break;
                    case 2:
                        num1 = program_arr->values[program_arr->values[instr_idx + 1]];
                        num2 = program_arr->values[program_arr->values[instr_idx + 2]];
                        program_arr->values[program_arr->values[instr_idx + 3]] = num1 * num2;
                        instr_idx += 4;

                        break;
                    case 3:
                        num1 = program_arr->values[program_arr->values[instr_idx + 1]];
                        instr_idx += 2;

                        break;
                    case 4:
                        num1 = program_arr->values[program_arr->values[instr_idx + 1]];
                        printf("%d\n", num1);
                        instr_idx += 2;

                        break;
                    case 99:
                        printf("Somehow end of program found inside while\n");
                        break;
                    default:
                        printf("Unknown instruction, exiting...\n");
                        return;
                }
                break;

            case 2:
                num_len = number_length(instr);
                printf("%d\t%d\t%s\n", instr, instr_idx, instr_type == 1 ? "literal" : "parameter");
                instr_idx += 5;
                break;
        }
        instr = program_arr->values[instr_idx];
        instr_type = literal_or_parameter(instr); // 1 being positional, 2 being parameter
    }
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