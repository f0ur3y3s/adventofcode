#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t
part2(char *line, size_t length)
{
    char *p_line = line;
    size_t result = 0;
    while ((p_line - line) < length)
    {
        if (*p_line == '(')
        {
            int num_repeat;
            int num_chars;
            p_line++; // skip the (
            num_chars = strtol(p_line, &p_line, 10);
            p_line++; // skip x
            num_repeat = strtol(p_line, &p_line, 10);
            p_line++; // skip to )
            result += part2(p_line, num_chars) * num_repeat;
            p_line += num_chars;
        }
        else
        {
            p_line++;
            result++;
        }
    }
    return result;
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


    size_t string_length = 0;
    char *line = NULL;
    getline(&line, &string_length, p_input_file);
    sscanf(line, "%s\n", line);
    string_length = strlen(line);
    size_t result = part2(line, string_length);
    printf("Result: %ld\n", result);
    // }
}

