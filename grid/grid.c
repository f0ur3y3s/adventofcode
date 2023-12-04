#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

typedef struct
{
    char value;
} grid_point_t;

typedef struct
{
    grid_point_t ** points;
    size_t          capacity;
} grid_t;

grid_t * grid_create (size_t capacity)
{
    grid_t * p_grid = (grid_t *)malloc(sizeof(grid_t));
    if (!p_grid)
    {
        return NULL;
    }
    p_grid->points = (grid_point_t **)malloc(capacity * sizeof(grid_point_t *));
    if (p_grid->points == NULL)
    {
        // Handle memory allocation error here if needed
        exit(1);
    }
    for (int i = 0; i < capacity; i++)
    {
        p_grid->points[i]
            = (grid_point_t *)malloc(capacity * sizeof(grid_point_t));
    }

    for (int i = 0; i < capacity; i++)
    {
        for (int j = 0; j < capacity; j++)
        {
            p_grid->points[i][j].value = '0';
        }
    }
    p_grid->capacity = capacity;
    return p_grid;
}

// void
// grid_grow(grid_t *grid)
// {
//     size_t     new_capacity = grid->capacity * 2; // Double the capacity
//     grid_point_t *new_points
//         = (grid_point_t *)realloc(grid->points, new_capacity *
//         sizeof(grid_point_t));
//     if (new_points == NULL)
//     {
//         // Handle memory reallocation error here if needed
//         exit(1);
//     }
//     grid->points   = new_points;
//     grid->capacity = new_capacity;
// }

// void
// grid_add_point(grid_t *grid, grid_point_t point)
// {
//     if (grid->size >= grid->capacity)
//     {
//         grow_grid(grid);
//     }
//     grid->points[grid->size] = point;
//     grid->size++;
// }

// int
// grid_check_point(grid_t *grid, grid_point_t point)
// {
//     for (int idx = 0; idx < grid->size; idx++)
//     {
//         if (grid->points[idx].x == point.x && grid->points[idx].y == point.y)
//         {
//             return 1;
//         }
//     }
//     return 0;
// }

void grid_print (grid_t * grid)
{
    for (int i = 0; i < grid->capacity; i++)
    {
        for (int j = 0; j < grid->capacity; j++)
        {
            printf("%c ", grid->points[i][j].value);
        }
        printf("\n");
    }
    printf("\n");
}

void grid_free (grid_t * grid)
{
    for (int i = 0; i < grid->capacity; i++)
    {
        free(grid->points[i]);
    }
    free(grid->points);
    free(grid);
}