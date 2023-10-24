#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

typedef struct
{
    int value;
} grid_point_t;

typedef struct
{
    grid_point_t **points;
    int            rows;
    int            columns;
} grid_t;

grid_t *
grid_create(int rows, int columns)
{
    grid_t *new_grid  = malloc(sizeof(grid_t));
    new_grid->rows    = rows;
    new_grid->columns = columns;
    new_grid->points = malloc(rows * sizeof(grid_point_t *));

    for (int idx = 0; idx < new_grid->rows; idx++)
    {
        new_grid->points[idx] = malloc(new_grid->columns * sizeof(grid_point_t));
    }

    for (int i = 0; i < new_grid->rows; i++)
    {
        for (int j = 0; j < new_grid->columns; j++)
        {
            new_grid->points[i][j].value = 0;
        }
    }

    return new_grid;
}

void
grid_print(grid_t *grid)
{
    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->columns; j++)
        {
            printf("%d ", grid->points[i][j].value);
        }
        printf("\n");
    }
    printf("\n");
}

void
grid_free(grid_t *grid)
{
    for (int i = 0; i < grid->rows; i++)
    {
        free(grid->points[i]);
    }
    free(grid->points);
    free(grid);
}