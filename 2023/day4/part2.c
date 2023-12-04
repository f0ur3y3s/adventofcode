#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include "../aoc/shared.h"
#include "../aoc/intarr.h"

#define CARD_OFFSET 5
#define NUM_OFFSET  3
#define SEP_OFFSET  2

void process_winning_cards (intarr_t * p_winning,
                            intarr_t * p_card,
                            intarr_t * p_won_cards,
                            int        curr_card_number);

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

        p_line = p_line + CARD_OFFSET;
        sscanf(p_line, "%d :", &curr_card_number);
        p_line = p_line + 3;
        printf("-----\n");
        printf("%s\n", p_line);
        printf("curr_card_number: %d\n", curr_card_number);

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
        // if yes, process winning cards
        process_winning_cards(p_winning, p_card, p_won_cards, curr_card_number);

        intarr_destroy(p_winning);
        intarr_destroy(p_card);
        free(p_line_start);
    }
    fclose(p_input_file);
    free(buffer);

    // Print the final result
    printf("Total number of scratchcards: %ld\n", p_won_cards->size);

    // Cleanup
    intarr_destroy(p_won_cards);

    return 0;
}

void process_winning_cards (intarr_t * p_winning,
                            intarr_t * p_card,
                            intarr_t * p_won_cards,
                            int        curr_card_number)
{
    int card_copy = 0;

    for (int p_card_idx = 0; p_card_idx < p_card->size; p_card_idx++)
    {
        for (int p_winning_idx = 0; p_winning_idx < p_winning->size;
             p_winning_idx++)
        {
            // printf("%d\t?= %d\n",
            //        p_card->values[p_card_idx],
            //        p_winning->values[p_winning_idx]);
            if (p_card->values[p_card_idx] == p_winning->values[p_winning_idx])
            {
                // printf("Found match\n");
                card_copy++;
            }
        }
    }

    for (int idx = 1; idx <= card_copy; idx++)
    {
        intarr_add(p_won_cards, curr_card_number + idx);
    }

    intarr_print(p_won_cards);
    printf("won %d cards\n", card_copy);
}



// Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
// Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
// Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
// Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
// Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
// Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11

// Card 1 has four matching numbers, so you win one copy each of the next four cards: cards 2, 3, 4, and 5.
// Your original card 2 has two matching numbers, so you win one copy each of cards 3 and 4.
// Your copy of card 2 also wins one copy each of cards 3 and 4.
// Your four instances of card 3 (one original and three copies) have two matching numbers, so you win four copies each of cards 4 and 5.
// Your eight instances of card 4 (one original and seven copies) have one matching number, so you win eight copies of card 5.
// Your fourteen instances of card 5 (one original and thirteen copies) have no matching numbers and win no more cards.
// Your one instance of card 6 (one original) has no matching numbers and wins no more cards.