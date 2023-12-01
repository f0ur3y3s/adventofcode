#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include "../aoc/shared.h"

typedef struct
{
    char * word;
    int    digit;
} word_digit_t;

word_digit_t g_word_digit_map[] = {
    { "one", 1 }, { "two", 2 },   { "three", 3 }, { "four", 4 }, { "five", 5 },
    { "six", 6 }, { "seven", 7 }, { "eight", 8 }, { "nine", 9 }, { "0", 0 },
    { "1", 1 },   { "2", 2 },     { "3", 3 },     { "4", 4 },    { "5", 5 },
    { "6", 6 },   { "7", 7 },     { "8", 8 },     { "9", 9 },
};

// return -1 if the word is not found
int get_digit_from_word (const char * word)
{
    int size = sizeof(g_word_digit_map) / sizeof(g_word_digit_map[0]);
    for (int i = 0; i < size; i++)
    {
        if (0 == strcmp(g_word_digit_map[i].word, word))
        {
            return g_word_digit_map[i].digit;
        }
    }
    return -1;
}

void process_line (char * line, int * first_digit, int * last_digit)
{
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
    // then we slide the window to the right by one

    char substring_line[64] = { 0 };

    int start_index = 0;
    for (; start_index <= strlen(line); start_index++)
    {
        int end_index = start_index + 1;
        int backstop  = strlen(line);
        for (; end_index <= backstop; end_index++)
        {
            memcpy(substring_line, line + start_index, end_index - start_index);
            int substring_index
                = end_index - start_index - 1; // -1 for indexing
            printf("S: %d\tE: %d\tSI: %d\tFirst:  %d\tLast:  %d\t%s\n",
                   start_index,
                   end_index,
                   substring_index,
                   *first_digit,
                   *last_digit,
                   substring_line);
            int word_digit = get_digit_from_word(substring_line);

            if (-1 != word_digit)
            {

                if (*first_digit == -1)
                {
                    *first_digit = word_digit;
                }
                *last_digit = word_digit;
                break;
            }

            int check_end
                = get_digit_from_word(&substring_line[substring_index]);

            if (-1 != check_end)
            {
                backstop = end_index;
                continue;
            }
        }
        memset(substring_line, 0, sizeof(substring_line));
    }
}

int main (int argc, char * argv[])
{
    if (2 != argc)
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

    char *  line = NULL;
    int     sum  = 0;
    size_t  len  = 0;
    ssize_t read = 0;

    while ((read = getline(&line, &len, p_input_file)) > 0)
    {
        strsnl(line);
        int first_digit = -1;
        int last_digit  = -1;
        process_line(line, &first_digit, &last_digit);
        // create a 2 digit number
        int line_number = (first_digit * 10) + last_digit;
        // printf("--------------- line sum: %d\n", line_number);
        sum += line_number;
    }

    printf("Sum: %d\n", sum);
    printf("\n");
    free(line);
    fclose(p_input_file);

    return 0;
}