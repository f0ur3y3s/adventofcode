#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum CardinalDirection
{
    North,
    East,
    South,
    West,
};

const char *
getDirection(enum CardinalDirection direction)
{
    switch (direction)
    {
        case North:
            return "North";
        case East:
            return "East";
        case South:
            return "South";
        case West:
            return "West";
    }
}

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
createGrid(Grid *grid, size_t initial_capacity)
{
    grid->points = (GridPoint *)malloc(initial_capacity * sizeof(GridPoint));
    if (grid->points == NULL)
    {
        // Handle memory allocation error here if needed
        exit(1);
    }
    grid->size     = 0;
    grid->capacity = initial_capacity;
}

void
grow_grid(Grid *grid)
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
        grow_grid(grid);
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

int
moveAndCheckIntersection(enum CardinalDirection current_direction,
                         int                    distance,
                         Grid                  *grid,
                         int                   *x,
                         int                   *y)
{
    int x_step = 0;
    int y_step = 0;

    switch (current_direction)
    {
        case North:
            y_step = 1;
            break;
        case East:
            x_step = 1;
            break;
        case South:
            y_step = -1;
            break;
        case West:
            x_step = -1;
            break;
    }

    for (int inc = 0; inc < distance; inc++)
    {
        *x += x_step;
        *y += y_step;

        GridPoint temp_point = { *x, *y };
        if (checkGridPoint(grid, temp_point))
        {
            printf("Intersection at %d, %d\n", temp_point.x, temp_point.y);
            return 1;
        }
        else
        {
            addGridPoint(grid, temp_point);
        }
    }
    return 0;
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
    p_input_file = fopen(argv[1], "r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    enum CardinalDirection current_direction = North;
    char                   direction         = 0;
    int                    distance          = 0;
    char                   junk;

    Grid   grid;
    size_t initial_capacity = 2; // Initial capacity of the grid

    createGrid(&grid, initial_capacity);

    int x              = 0;
    int y              = 0;
    int total_distance = 0;

    while (fscanf(p_input_file, "%c%d", &direction, &distance) != EOF)
    {
        // printf("%c\t%d\n", direction, distance);
        switch (direction)
        {
            case 'R':
                current_direction = (current_direction + 1) % 4;
                break;
            case 'L':
                current_direction = (current_direction - 1) % 4;
                break;
            default:
                printf("Ran into unexpected input.\n");
                exit(EXIT_FAILURE);
                break;
        }

        if (moveAndCheckIntersection(
                current_direction, distance, &grid, &x, &y))
        {
            goto CLEANUP;
        }

        // printf("%s\tX: %d\tY: %d\n", getDirection(current_direction), x, y);
        fscanf(p_input_file, "%c%c", &junk, &junk);
    }
    goto CLEANUP;

CLEANUP:
    total_distance = abs(x) + abs(y);
    printf("Total distance traveled: %d\n", total_distance);
    fclose(p_input_file);

    free(grid.points);

    return 0;
}