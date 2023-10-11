#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    long num_repeat;
    long num_chars;
    size_t string_length = 0;
    char *line = NULL;
    getline(&line, &string_length, p_input_file);

    sscanf(line, "%s\n", line);
    int result = 0;
    char *p_line = line;
    string_length = strlen(line);
    while ((p_line - line) < string_length)
    {
        if (*p_line == '(')
        {
            p_line++; // skip the (
            num_chars = strtol(p_line, &p_line, 10);
            p_line++; // skip x
            num_repeat = strtol(p_line, &p_line, 10);
            p_line++; // skip to )
            result += num_chars * num_repeat;
            p_line += num_chars;
            // printf("%ldx%ld\n", num_chars, num_repeat);
        }
        else
        {
            p_line++;
            result++;
        }
    }
    printf("Result: %d\n", result);
    // }
}

