#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include "../aoc/shared.h"
#include "../aoc/intarr.h"

#define CARD_OFFSET 10
#define NUM_OFFSET  3
#define SEP_OFFSET  2

// #define NUM_OFFSET 10

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

    char *  buffer = NULL;
    size_t  len    = 0;
    ssize_t read   = 0;
    int     sum    = 0;

    while ((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        intarr_t * p_winning = intarr_create();
        intarr_t * p_card    = intarr_create();

        int card_number;

        strsnl(buffer);
        char * p_line       = strdup(buffer);
        char * p_line_start = p_line;
        p_line              = p_line + CARD_OFFSET;
        // printf("%s\n", p_line);
        while (sscanf(p_line, "%d ", &card_number) == 1)
        {
            p_line = p_line + NUM_OFFSET;
            intarr_add(p_winning, card_number);
        }

        p_line = p_line + SEP_OFFSET; // skip |
        // printf("-----\n");

        while (sscanf(p_line, "%d ", &card_number) == 1)
        {
            p_line = p_line + NUM_OFFSET;
            intarr_add(p_card, card_number);
        }
        // intarr_print(p_winning);
        // intarr_print(p_card);

        // check if each num in p_card is in p_winning
        // if sum is 0, make sum 1
        // else double sum

        int card_points = 0;
        for (int p_card_idx = 0; p_card_idx < p_card->size; p_card_idx++)
        {
            for (int p_winning_idx = 0; p_winning_idx < p_winning->size;
                 p_winning_idx++)
            {
                if (p_card->values[p_card_idx]
                    == p_winning->values[p_winning_idx])
                {
                    if (card_points == 0)
                    {
                        card_points = 1;
                    }
                    else
                    {
                        card_points *= 2;
                    }
                    // sum += p_card->values[p_card_idx];
                }
            }
        }

        sum += card_points;
        intarr_destroy(p_winning);
        intarr_destroy(p_card);
        free(p_line_start);
    }
    printf("Sum: %d\n", sum);
    fclose(p_input_file);
    free(buffer);
}
