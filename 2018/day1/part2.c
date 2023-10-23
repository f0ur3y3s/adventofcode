#include <stdio.h>
#include <stdlib.h>
#include "intarr/intarr.h"

int
intarr_find(intarr_t *seen, int num)
{
    for (int idx = 0; idx < seen->size; idx++)
    {
        if (seen->values[idx] == num)
        {
            return 1;
        }
    }
    return 0;
}


int
scan_file(FILE *p_input_file, intarr_t *seen, int curr_freq)
{
    int change = 0;
    while (fscanf(p_input_file, "%d\n", &change) != EOF)
    {
        curr_freq += change;
        // printf("curr_freq: %d\n", curr_freq);
        if (intarr_find(seen, curr_freq))
        {
            printf("Frequency found twice: %d\n", curr_freq);
            return 1;
        }
        else
        {
            intarr_add(seen, curr_freq);
        }
    }
    // printf("Repeating file...\n");
    rewind(p_input_file);
    // intarr_print(seen);
    return scan_file(p_input_file, seen, curr_freq);
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

    intarr_t *seen = intarr_create();
    int ret = scan_file(p_input_file, seen, 0);
    printf("Return code: %d\n", ret);
    // while (!scan_file(p_input_file, seen));
    intarr_free(seen);
    fclose(p_input_file);
}