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
    int            rows;
    int            columns;
} grid_t;


grid_t * grid_create(int rows, int columns);
void grid_print(grid_t *grid);
void grid_free(grid_t *grid);

#endif  // GRID_H