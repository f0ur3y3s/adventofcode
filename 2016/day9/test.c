#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// void
// parseMarker(char *p_line, int idx, long *num_repeat, long *num_chars)
// {
//     char *endptr;
//     *num_chars = strtol(p_line + idx + 1, &endptr, 10);
//     idx++;
//     idx++;
//     *num_repeat = strtol(p_line + idx + 1, &endptr, 10);
//     printf("%ldx%ld\n", num_chars, num_repeat);
// }

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

    char line[256];
    char *token;
    long num_repeat;
    long num_chars;
    size_t string_length = 0;

    while (fscanf(p_input_file, "%s\n", line) != EOF)
    {
        int result = 0;
        char *p_line = line;
        string_length = strlen(line);
        while ((p_line - line) < string_length)
        {
        // for (int idx = 0; idx < string_length; idx ++)
        // {
            if (*p_line == '(')
            {
                // parseMarker(p_line, idx, &num_repeat, &num_chars);
                p_line++; // skip the (
                num_chars = strtol(p_line, &p_line, 10);
                p_line++; // skip x
                num_repeat = strtol(p_line, &p_line, 10);
                p_line++; // move to )
                result += num_chars * num_repeat;
                p_line += num_chars;
                printf("%ldx%ld\n", num_chars, num_repeat);
                // parse marker
            }
            else
            {
                p_line++;
                result++;
            }
            // printf("%c\n", *(p_line+idx));
        }
        printf("Result: %d\n", result);
    }
    // while (fscanf(p_input_file, "%s\n", line) != EOF)
    // {
    //     token = strtok(line, "()");
    //     while (token != NULL)
    //     {
    //         if (sscanf(token, "%dx%d", &num_chars, &num_repeat))
    //         {
    //             // scan the next token
    //             // if the next token is a marker, skip until you get to a non-marker
    //             // once the non-marker is found, apply the first marker operation
    //             result += num_chars * num_repeat;
    //         }
    //         else
    //         {
    //         }
    //         // printf("%s", token);

    //         token = strtok(NULL, "()");
    //     }
    //     printf("Result: %d\n", result);
    //     result = 0;
    // }
}

