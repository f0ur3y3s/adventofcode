#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char * word;
    int    digit;
} word_digit_t;

word_digit_t word_digit_map[] = {
    { "one", 1 }, { "two", 2 },   { "three", 3 }, { "four", 4 }, { "five", 5 },
    { "six", 6 }, { "seven", 7 }, { "eight", 8 }, { "nine", 9 },
};

// return -1 if the word is not found
int get_digit_from_word (const char * word)
{
    int size = sizeof(word_digit_map) / sizeof(word_digit_map[0]);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(word_digit_map[i].word, word) == 0)
        {
            return word_digit_map[i].digit;
        }
    }
    return -1;
}

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

        // scan the string with a sliding window
        // the window starts at the beginning of the string
        // eightwothree
        // e
        // ei
        // eig
        // eigh
        // eight
        // here we know that eight is a digit
        // so we set first_digit to 8
        // and last_digit to 8
        // then we slide the window to the right

        char substring_buffer[64] = { 0 };
        for (int start_index = 0; start_index <= strlen(buffer); start_index++)
        {
            for (int end_index = start_index; end_index <= strlen(buffer); end_index++)
            {
                memcpy(substring_buffer, buffer + start_index, end_index - start_index);
                int word_digit = get_digit_from_word(substring_buffer);
                if (word_digit != -1)
                {
                    if (first_digit == -1)
                    {
                        first_digit = word_digit;
                    }
                    last_digit = word_digit;
                }
                if (isdigit(substring_buffer[0]))
                {
                    if (first_digit == -1)
                    {
                        first_digit = substring_buffer[0] - '0';
                    }
                    last_digit = substring_buffer[0] - '0';
                }
            }
            memset(substring_buffer, 0, sizeof(substring_buffer));
        }


        // create a 2 digit number
        int line_number = (first_digit * 10) + last_digit;
        printf("%d\n", line_number);
        sum += line_number;
    }
    printf("Sum: %d\n", sum);
    printf("\n");
    free(p_input_file);
    free(buffer);
}