#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// Santa's list is a file that contains many double-quoted string literals, one on each line.
// The only escape sequences used are
// \\ (which represents a single backslash)
// \" (which represents a lone double-quote character)
// and \x plus two hexadecimal characters (which represents a single character with that ASCII code).

int
countChar(char *string, int orig_length)
{
    int char_count = 6;
    int idx = 0;
    char current_char;
    while (string[idx] != '\0' && idx < orig_length)
    {
        current_char = string[idx];
        switch (current_char)
        {
            case '\\':
            // look at the next char
                current_char = string[idx+1];
                switch (current_char)
                {
                    case '\\':
                        char_count++;
                        char_count++;
                        idx++;
                        break;
                    case '\"':
                        char_count++;
                        char_count++;
                        idx++;
                        break;
                    case 'x':
                        // hex stuff, add two to index
                        char_count++;
                        char_count++;
                        idx+=2;
                        break;
                    default:
                        printf("Unknown character\n");
                        break;
                }
                char_count++;
                char_count++;
                break;
            default: // normal char
                char_count++;
                break;
        }
        // printf("%c\n", string[idx]);
        idx++;
    }
    // printf("%d\n", char_count);
    return char_count;
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

    int code_len = 0;
    int escaped_len = 0;
    int total_string = 0;
    int total_char = 0;

    char *buffer;
    size_t len;
    ssize_t read;
    while((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        size_t newlinePos = strcspn(buffer, "\n");
        buffer[newlinePos] = '\0';
        if (newlinePos == read)
        {
            memmove(buffer, buffer + 1, read - 2);
            buffer[read - 2] = '\0';
            code_len = read;
        }
        else
        {
            memmove(buffer, buffer + 1, read - 3);
            buffer[read - 3] = '\0';
            code_len = read - 1;
        }
        escaped_len = countChar(buffer, strlen(buffer));
        total_string += code_len;
        total_char += escaped_len;
        printf("Original length: %d\tScanned length: %d\tString: %s\n", code_len, escaped_len, buffer);
    }
    printf("total: %d\n", total_char - total_string);
}