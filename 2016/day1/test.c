#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} GridPoint;

typedef struct {
    GridPoint *points;
    size_t size;
    size_t capacity;
} Grid;

void create_grid(Grid *grid, size_t initial_capacity) {
    grid->points = (GridPoint *)malloc(initial_capacity * sizeof(GridPoint));
    if (grid->points == NULL) {
        // Handle memory allocation error here if needed
        exit(1);
    }
    grid->size = 0;
    grid->capacity = initial_capacity;
}

void grow_grid(Grid *grid) {
    size_t new_capacity = grid->capacity * 2; // Double the capacity
    GridPoint *new_points = (GridPoint *)realloc(grid->points, new_capacity * sizeof(GridPoint));
    if (new_points == NULL) {
        // Handle memory reallocation error here if needed
        exit(1);
    }
    grid->points = new_points;
    grid->capacity = new_capacity;
}

void addGridPoint(Grid *grid, GridPoint point) {
    if (grid->size >= grid->capacity) {
        grow_grid(grid);
    }
    grid->points[grid->size] = point;
    grid->size++;
}

int checkGridPoint(Grid *grid, GridPoint point)
{
    for (int idx = 0; idx < grid->size; idx++)
    {
        if (grid->points[idx].x == point.x && grid->points[idx].y == point.y){
            return 1;
        }
    }
    return 0;
}

int main() {
    Grid grid;
    size_t initial_capacity = 10; // Initial capacity of the grid

    create_grid(&grid, initial_capacity);

    // Adding points to the grid for setup
    for (int idx = 0; idx < 20; idx ++)
    {
        GridPoint temp_point = {1, idx};
        addGridPoint(&grid, temp_point);
    }

    // Accessing points
    for (size_t i = 0; i < grid.size; i++) {
        printf("Point %zu: x = %d, y = %d\n", i, grid.points[i].x, grid.points[i].y);
    }

    for (int idx = 20; idx > 0; idx --)
    {
        GridPoint temp_point = {1, idx};
        if (checkGridPoint(&grid, temp_point))
        {
            printf("Point %d, %d already exists\n", temp_point.x, temp_point.y);
            exit(EXIT_SUCCESS);
        }
        else
        {
            addGridPoint(&grid, temp_point);
        }
    }


    // Don't forget to free the allocated memory when done
    free(grid.points);

    return 0;
}