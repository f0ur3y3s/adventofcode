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
    int last_x;
    int last_y;
    int current_x;
    int current_y;
} grid_t;


grid_t* grid_create(size_t capacity);
void grid_print(grid_t *grid);
void grid_free(grid_t *grid);
void grid_grow(grid_t *grid);
void grid_step(grid_t *grid, int x_step, int y_step, int value);

#endif  // GRID_H