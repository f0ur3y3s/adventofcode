#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int low;
    int high;
    int id;
} bot_t;


int
hasBoth(bot_t *bot)
{
    return (bot->low != 0 && bot->high != 0);
}

void
initBots(bot_t *bots, size_t size)
{
    for (int idx = 0; idx < size; idx ++)
    {
        bots[idx].low = 0;
        bots[idx].high = 0;
        bots[idx].id = idx;
    }
}

void
checkSpecial(bot_t *bot)
{
    if (bot->low == 17 && bot->high == 61)
    {
        printf("Special bot found: %d\n", bot->id);
        exit(EXIT_SUCCESS);
    }
}

void
addChip(bot_t *bot, int chip_value)
{
    if (bot->low != 0)
    {
        if (bot->low < chip_value)
        {
            bot->high = chip_value;
        }
        else
        {
            bot->high = bot->low;
            bot->low = chip_value;
        }
    }
    else
    {
        bot->low = chip_value;
    }
}

void
populateChips(FILE *p_input_file, bot_t *all_bots)
{
    char line[64];
    while(fscanf(p_input_file, "%[^\n]\n", line) != EOF)
    {
        char junk[64];
        int chip_value;
        int bot_id;
        if (sscanf(line, "%s %d %s %s %s %d", junk, &chip_value, junk, junk, junk, &bot_id) == 6)
        {
            addChip(&(all_bots[bot_id]), chip_value);
        }
    }
    rewind(p_input_file);
}

int
getRemoveLow(bot_t *bot)
{
    int value = bot->low;
    bot->low = 0;
    return value;
}

int
getRemoveHigh(bot_t *bot)
{
    int value = bot->high;
    bot->high = 0;
    return value;
}

void
scanFile(FILE *p_input_file, bot_t all_bots[256], size_t all_bots_length)
{
    char line[64];

    while(fscanf(p_input_file, "%[^\n]\n", line) != EOF)
    {
        char junk[64];
        int from_bot_id;
        int low_to;
        int high_to;
        char low_dest[8];
        char high_dest[8];
        // bot 2 gives low to bot 1 and high to bot 0
        if (sscanf(line, "%s %d %s %s %s %s %d %s %s %s %s %d", junk, &from_bot_id, junk, junk, junk, low_dest, &low_to, junk, junk, junk, high_dest, &high_to) == 12)
        {
            // printf("From %d \tLow to %s\tValue %d\tHigh to %s\tValue %d\n", from_bot_id, low_dest, low_to, high_dest, high_to);
            if (!hasBoth(&(all_bots[from_bot_id])))
            {
                continue;
            }
            int low = getRemoveLow(&(all_bots[from_bot_id]));
            int high = getRemoveHigh(&(all_bots[from_bot_id]));
            // printf("Low: %d\tHigh: %d\n", low, high);
            if (low == 17 && high == 61)
            {
                printf("Found special: %d\n", from_bot_id);
                exit(EXIT_SUCCESS);
            }
            if (strcmp(low_dest, "bot") == 0)
            {
                addChip(&(all_bots[low_to]), low);
            }
            if (strcmp(high_dest, "bot") == 0)
            {
                addChip(&(all_bots[high_to]), high);
            }
            else
            {
                // else for outputs, no action. remove and throw away value.
            }
        }
    }
    rewind(p_input_file);
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

    bot_t all_bots[256];
    size_t all_bots_length = sizeof(all_bots)/sizeof(bot_t);
    initBots(all_bots, all_bots_length);
    populateChips(p_input_file, all_bots);
    // for (int idx = 0; idx < all_bots_length; idx ++)
    // {
    //     printf("bot %d: %d\t%d\n", idx, all_bots[idx].low, all_bots[idx].high);
    // }

    for (;;)
    {
        scanFile(p_input_file, all_bots, all_bots_length);
    }
}