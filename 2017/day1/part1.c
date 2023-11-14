#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "intarr/intarr.h"

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

    // create a stack of numbers based on the size of read characters
    size_t len = 0;
    ssize_t read = 0;
    char *buffer;

    read = getline(&buffer, &len, p_input_file);
    printf("%s\n", buffer);

    intarr_t *captcha_arr = intarr_create();
    for (int idx = 0; idx < read; idx++)
    {
        intarr_add(captcha_arr, buffer[idx] - '0');
    }

    // when we have reached the end, compare the first to last
    int sum = 0;

    for (int idx = 0; idx < captcha_arr->size; idx++)
    {
        if (idx == captcha_arr->size - 1)
        {
            if (captcha_arr->values[idx] == captcha_arr->values[0])
            {
                sum += captcha_arr->values[idx];
            }
            // compare to the first
            // dont compare to the next at the end
        }
        else
        {
            if (captcha_arr->values[idx] == captcha_arr->values[idx + 1])
            {
                sum += captcha_arr->values[idx];
            }
        }
    }

    printf("Sum: %d\n", sum);

    free(buffer);
    fclose(p_input_file);
}