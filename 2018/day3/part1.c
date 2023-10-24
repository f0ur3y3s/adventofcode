#include <stdio.h>
#include <stdlib.h>
#include "grid/grid.h"

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

    // grid_t *grid = grid_create(10); // for testing only 
    grid_t *grid = grid_create(1000); // use in production

    int id = 0;
    int claimx = 0;
    int claimy = 0;
    int claimw = 0;
    int claimh = 0;
    while (fscanf(p_input_file, "#%d @ %d,%d: %dx%d\n", &id, &claimx, &claimy, &claimw, &claimh) != EOF)
    {
        // printf("id: %d, x: %d, y: %d, w: %d, h: %d\n", id, claimx, claimy, claimw, claimh);
        for (int j = claimy; j < claimy + claimh; j++)
        {
            for (int i = claimx; i < claimx + claimw; i++)
            {
                if (grid->points[j][i].value != 0)
                {
                    grid->points[j][i].value = -1;
                }
                else
                {
                    grid->points[j][i].value = id;
                }
            }
        }
    }

    // count the number of overlapping claims
    int count = 0;
    for (int j = 0; j < grid->capacity; j++)
    {
        for (int i = 0; i < grid->capacity; i++)
        {
            if (grid->points[j][i].value == -1)
            {
                count++;
            }
        }
    }

    printf("Count: %d\n", count);

    // grid_print(grid);
    grid_free(grid);
    fclose(p_input_file);
}