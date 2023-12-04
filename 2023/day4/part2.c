#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include "../aoc/shared.h"
#include "../aoc/intarr.h"

#define CARD_OFFSET 5
// #define CARD_OFFSET 8
#define NUM_OFFSET 3
#define SEP_OFFSET 2

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

    char *     buffer      = NULL;
    size_t     len         = 0;
    ssize_t    read        = 0;
    int        sum         = 0;
    intarr_t * p_won_cards = intarr_create();

    while ((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        intarr_t * p_winning        = intarr_create();
        intarr_t * p_card           = intarr_create();
        int        curr_card_number = 0;
        int        card_number      = 0;

        strsnl(buffer);
        char * p_line       = strdup(buffer);
        char * p_line_start = p_line;
        p_line              = p_line + CARD_OFFSET;
        sscanf(p_line, "%d :", &curr_card_number);
        printf("-----\n");
        printf("curr_card_number: %d\n", curr_card_number);
        // printf("%s\n", p_line);

        while (sscanf(p_line, "%d ", &card_number) == 1)
        {
            p_line = p_line + NUM_OFFSET;
            intarr_add(p_winning, card_number);
        }

        p_line = p_line + SEP_OFFSET; // skip |

        while (sscanf(p_line, "%d ", &card_number) == 1)
        {
            p_line = p_line + NUM_OFFSET;
            intarr_add(p_card, card_number);
        }
        intarr_print(p_winning);
        intarr_print(p_card);

        // check if each num in p_card is in p_winning
        // if sum is 0, make sum 1
        // else double sum

        int card_copy = 0;
        for (int p_card_idx = 0; p_card_idx < p_card->size; p_card_idx++)
        {
            for (int p_winning_idx = 0; p_winning_idx < p_winning->size;
                 p_winning_idx++)
            {
                if (p_card->values[p_card_idx]
                    == p_winning->values[p_winning_idx])
                {
                    card_copy++;
                    // sum += p_card->values[p_card_idx];
                }
            }
        }

        for (int idx = 1; idx <= card_copy; idx++)
        {
            intarr_add(p_won_cards, curr_card_number + idx);
        }

        intarr_print(p_won_cards);
        printf("won %d cards\n", card_copy);

        intarr_destroy(p_winning);
        intarr_destroy(p_card);
        free(p_line_start);
    }
    fclose(p_input_file);
    free(buffer);
}
