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
createGrid(Grid *grid, size_t capacity)
{
    grid->points = (GridPoint *)malloc(capacity * sizeof(GridPoint));
    if (grid->points == NULL)
    {
        // Handle memory allocation error here if needed
        exit(1);
    }
    grid->size     = 0;
    grid->capacity = capacity;
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