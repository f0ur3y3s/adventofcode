#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include "../aoc/shared.h"

int main (int argc, char * argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE * p_input_file;
    p_input_file = fopen(argv[1], "r");

    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    char *  buffer = NULL;
    int     sum    = 0;
    size_t  len    = 0;
    ssize_t read   = 0;

    while ((read = getline(&buffer, &len, p_input_file)) > 0)
    {
    }

    free(p_input_file);
    free(buffer);
}