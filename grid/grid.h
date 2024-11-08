#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <sys/types.h>

typedef struct
{
    int value;
} grid_point_t;

typedef struct
{
    grid_point_t **points;
    size_t     capacity;
} grid_t;


grid_t* grid_create(size_t capacity);
// void grid_grow(grid_t *grid);
// void grid_add_point(grid_t *grid, grid_point_t point);
// int grid_check_point(grid_t *grid, grid_point_t point);

void grid_print(grid_t *grid);
void grid_free(grid_t *grid);
#endif  // GRID_H