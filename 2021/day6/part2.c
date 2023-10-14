#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "intarr/intarr.h"

void simulate_lanternfish(intarr_t *intarr)
{
    // running into not enough memory errors
    for (int day = 1; day < 81; day++)
    {
        // iterate through each lantern fish
        // if lantern fish value is 0, add a new lanternfish at value 8
        // else, decrement value by 1
        for (int i = 0; i < intarr->size; i++)
        {
            unsigned char value = (unsigned char) intarr->values[i];
            if (value == 0)
            {
                intarr_add(intarr, 9);
                intarr->values[i] = (char) 6;
            }
            else
            {
                intarr->values[i] = (char) (value - 1);
            }
        }
    }
}
int
main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *p_input_file;
    p_input_file = fopen(argv[1],"r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    // get line from file
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    getline(&line, &len, p_input_file);
    line[strcspn(line, "\n")] = 0;  // Remove trailing newline
    printf("%s\n", line);

    // create intarr
    intarr_t *intarr;
    intarr = intarr_create();

    // parse line
    size_t size = strlen(line);
    char *token = strtok(line, ",");

    while (token != NULL)
    {
        intarr_add(intarr, *token);
        // printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    // simulate
    simulate_lanternfish(intarr);

    printf("There are %ld lanternfish in the lake.\n", intarr->size);

    intarr_free(intarr);
    free(line);
    fclose(p_input_file);
    exit(EXIT_SUCCESS);
}