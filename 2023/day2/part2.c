#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "../aoc/shared.h"
#include <string.h>
#include <limits.h>

typedef struct game_t
{
    int num_red;
    int num_green;
    int num_blue;
} game_t;

void print_game (game_t * game)
{
    printf("Game: %d %d %d\n", game->num_red, game->num_green, game->num_blue);
}

int process_hand (game_t * game, char * hand)
{
    char * hand_copy  = strdup(hand);
    char * hand_token = strtok(hand_copy, ",");
    while (NULL != hand_token)
    {
        char scanned_token[10] = { 0 };
        int  scanned_number    = 0;
        sscanf(hand_token, "%d %s", &scanned_number, &scanned_token);
        if (0 == strcmp(scanned_token, "red"))
        {
            game->num_red = game->num_red < scanned_number ? scanned_number
                                                           : game->num_red;
        }
        else if (0 == strcmp(scanned_token, "green"))
        {
            game->num_green = game->num_green < scanned_number
                                  ? scanned_number
                                  : game->num_green;
        }
        else if (0 == strcmp(scanned_token, "blue"))
        {
            game->num_blue = game->num_blue < scanned_number ? scanned_number
                                                             : game->num_blue;
        }
        else
        {
            printf("Error parsing hand\n");
            return -1;
        }
        hand_token = strtok(NULL, ",");
    }
}

int process_game_id (char * hand)
{
    int    retval       = -1;
    char * line_game_id = strtok(hand, ":"); // Game 1
    if (!line_game_id)
    {
        printf("Error parsing game id\n");
        return retval;
    }

    retval = atoi(line_game_id + 5);
    return retval;
}

// returns 0 on failure, non zero id if game is possible
int is_possible_game (const game_t * target_game, char * line)
{
    int      retval = 0;
    game_t * game   = malloc(sizeof(game_t));
    game->num_red   = INT_MIN;
    game->num_green = INT_MIN;
    game->num_blue  = INT_MIN;

    // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    // need to split game on : and ;
    int game_power = process_game_id(line);

    char * game_data = strtok(NULL, ":");
    if (!game_data)
    {
        printf("Error parsing game data\n");
        return retval;
    }

    // printf("Game id: %d\n", game_power);
    // printf("Game data: %s\n", game_data);
    char * saveptr;
    char * game_data_copy = strdup(game_data);
    char * game_data_hand = strtok_r(game_data_copy, ";", &saveptr);

    while (NULL != game_data_hand)
    {
        process_hand(game, game_data_hand);
        print_game(game);
        game_data_hand = strtok_r(NULL, ";", &saveptr);
    }

    retval = game->num_red * game->num_green * game->num_blue;

    return retval;
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

    char *  line = NULL;
    size_t  len  = 0;
    ssize_t read = 0;
    int     sum  = 0;

    game_t * target_game   = malloc(sizeof(game_t));
    target_game->num_red   = 12;
    target_game->num_green = 13;
    target_game->num_blue  = 14;

    while ((read = getline(&line, &len, p_input_file)) > 0)
    {
        strsnl(line);
        int game_power = -1;
        game_power     = is_possible_game(target_game, line);

        if (-1 == game_power)
        {
            printf("Error parsing game\n");
            continue;
        }

        printf("Game power: %d\n", game_power);
        sum += game_power;
    }

    printf("Sum of possible game_power: %d\n", sum);
    fclose(p_input_file);
    free(line);
}