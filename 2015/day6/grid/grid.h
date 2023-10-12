#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <sys/types.h>

typedef struct
{
    int x;
    int y;
} GridPoint;

typedef struct
{
    GridPoint *points;
    size_t size;
    size_t capacity;
} Grid;

void createGrid(Grid *grid, size_t capacity);
void growGrid(Grid *grid);
void addGridPoint(Grid *grid, GridPoint point);
int checkGridPoint(Grid *grid, GridPoint point);

#endif  // GRID_H