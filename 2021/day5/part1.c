#include <stdio.h>
#include <stdlib.h>
#include "grid/grid.h"

int
max(int a, int b)
{
    return a > b ? a : b;
}

void
scan_file_max(FILE *p_input_file, int* p_min_x, int* p_min_y)
{
    int grid_x1 = 0;
    int grid_y1 = 0;
    int grid_x2 = 0;
    int grid_y2 = 0;
    char buffer[20];
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        sscanf(buffer, "%d,%d -> %d,%d", &grid_x1, &grid_y1, &grid_x2, &grid_y2);
        *p_min_x = max(*p_min_x, grid_x1);
        *p_min_x = max(*p_min_x, grid_x2);
        *p_min_y = max(*p_min_y, grid_y1);
        *p_min_y = max(*p_min_y, grid_y2);
    }
    rewind(p_input_file);
}

int
count_dangerous(grid_t *p_grid)
{
    int dangerous = 0;
    for (int i = 0; i < p_grid->capacity; i++)
    {
        for (int j = 0; j < p_grid->capacity; j++)
        {
            if (p_grid->points[i][j].value >= 2)
            {
                dangerous++;
            }
        }
    }
    return dangerous;
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

    int min_x = 0;
    int min_y = 0;
    scan_file_max(p_input_file, &min_x, &min_y);
    grid_t *p_grid = grid_create(min_x+1);

    char buffer[20];
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        int grid_x1 = 0;
        int grid_y1 = 0;
        int grid_x2 = 0;
        int grid_y2 = 0;
        sscanf(buffer, "%d,%d -> %d,%d", &grid_x1, &grid_y1, &grid_x2, &grid_y2);
        if (grid_x1 == grid_x2)
        {
            int increment = (grid_y1 < grid_y2) ? 1 : -1;
            for (int i = grid_y1; i != grid_y2 + increment; i += increment)
            {
                p_grid->points[i][grid_x1].value += 1;
            }
        }
        else if (grid_y1 == grid_y2)
        {
            int increment = (grid_x1 < grid_x2) ? 1 : -1;
            for (int i = grid_x1; i != grid_x2 + increment; i += increment)
            {
                p_grid->points[grid_y1][i].value += 1;
            }
        }
    }
    printf("Dangerous: %d\n", count_dangerous(p_grid));

    grid_free(p_grid);
    fclose(p_input_file);
    exit(EXIT_SUCCESS);
}