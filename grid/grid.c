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
    size_t     size;
    size_t     capacity;
} Grid;

void
createGrid(Grid *grid)
{
    grid->points = (GridPoint *)malloc(2 * sizeof(GridPoint));
    if (grid->points == NULL)
    {
        // Handle memory allocation error here if needed
        exit(1);
    }
    grid->size     = 0;
    grid->capacity = 2;
}

void
growGrid(Grid *grid)
{
    size_t     new_capacity = grid->capacity * 2; // Double the capacity
    GridPoint *new_points
        = (GridPoint *)realloc(grid->points, new_capacity * sizeof(GridPoint));
    if (new_points == NULL)
    {
        // Handle memory reallocation error here if needed
        exit(1);
    }
    grid->points   = new_points;
    grid->capacity = new_capacity;
}

void
addGridPoint(Grid *grid, GridPoint point)
{
    if (grid->size >= grid->capacity)
    {
        growGrid(grid);
    }
    grid->points[grid->size] = point;
    grid->size++;
}

int
checkGridPoint(Grid *grid, GridPoint point)
{
    for (int idx = 0; idx < grid->size; idx++)
    {
        if (grid->points[idx].x == point.x && grid->points[idx].y == point.y)
        {
            return 1;
        }
    }
    return 0;
}