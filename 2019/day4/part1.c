#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int
check_increasing(int num)
{
    // check if every integer is increasing
    int prevDigit = num % 10; // extract the last digit
    num /= 10; // remove the last digit

    while (num > 0) {
        int currentDigit = num % 10;
        if (prevDigit < currentDigit) {
            return 0;
        }
        prevDigit = currentDigit;
        num /= 10;
    }
    return 1;
}

int
check_double(int num)
{
    int int_arr[10] = {0,0,0,0,0,0,0,0,0};
    int prevDigit = num % 10; // extract the last digit
    num /= 10; // remove the last digit

    while (num > 0) {
        int currentDigit = num % 10;
        if (prevDigit == currentDigit)
        {
            int_arr[currentDigit] += 1;
        }
        prevDigit = currentDigit;
        // prevDigit = currentDigit;
        num /= 10;
    }

    int return_val = 0;
    for (int idx = 0; idx < 10; idx++)
    {
        printf("%d,", int_arr[idx]);
        if (int_arr[idx] == 1)
        {
            return_val = 1;
        }
    }
    printf("\n");
    return return_val;
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

    size_t size;
    ssize_t read;
    char * buffer = 0;

    int min = 0;
    int max = 0;
    int count_valid = 0;
    while ((read = getline(&buffer, &size, p_input_file)) > 0)
    {
        sscanf(buffer, "%d-%d\n", &min, &max);
        for (int idx = min; idx < max; idx++)
        {
            if (check_increasing(idx) && check_double(idx))
            {
                printf("%d\n", idx);
                count_valid += 1;
            }
        }
    }

    printf("There are %d valid passwords.\n", count_valid);

    fclose(p_input_file);
    free(buffer);
}