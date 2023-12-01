#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

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

    size_t  len    = 0;
    char *  buffer = NULL;
    ssize_t read;
    int     sum = 0;

    while ((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        char line_buffer[64]          = { 0 };
        int  line_ptr                 = 0;
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing '\n'
        int first_digit = -1, last_digit = -1;

        for (int index = 0; index < strlen(buffer); index++)
        {
            if (isdigit(buffer[index]))
            {
                if (first_digit == -1)
                {
                    first_digit = buffer[index] - '0';
                }
                last_digit = buffer[index] - '0';
            }
        }
        // create a 2 digit number
        int line_number = (first_digit * 10) + last_digit;
        sum += line_number;
    }
    printf("Sum: %d\n", sum);
    printf("\n");
    free(p_input_file);
    free(buffer);
}