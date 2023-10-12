#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

enum CardinalDirection
{
    North,
    East,
    South,
    West,
};

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


void
moveAndCheckIntersection(enum CardinalDirection current_direction,
                         Grid                  *grid,
                         int                   *x,
                         int                   *y
                         )
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
    *x+=x_step;
    *y+=y_step;
    GridPoint temp_point = { *x, *y };
    if (checkGridPoint(grid, temp_point))
    {
        // printf("Already delivered, not incrementing count\n");
        // printf("Intersection at %d, %d\n", temp_point.x, temp_point.y);
    }
    else
    {
        addGridPoint(grid, temp_point);
    }
}

void switch_direction(enum CardinalDirection *current_direction, char *current_char)
{
    switch (*current_char)
    {
        case '^':
            *current_direction = North;
            break;
        case '>':
            *current_direction = East;
            break;
        case 'v':
            *current_direction = South;
            break;
        case '<':
            *current_direction = West;
            break;
        default:
            printf("Ran into unexpected input.\n");
            exit(EXIT_FAILURE);
            break;
    }
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
    p_input_file = fopen(argv[1],"r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    enum CardinalDirection santa_direction = North;
    enum CardinalDirection robo_santa_direction = North;

    size_t len = 0;
    char *buffer = NULL;
    ssize_t read;

    while((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        Grid   grid;
        createGrid(&grid);

        int santa_x = 0;
        int santa_y = 0;
        GridPoint temp_point = {santa_x, santa_y};
        addGridPoint(&grid, temp_point);

        int robo_x = 0;
        int robo_y = 0;

        buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
        for (int idx = 0; idx < read-1; idx++) {
            char current_char = buffer[idx];
            if (idx % 2 == 0) // move santa direction
            {
                printf("moving santa\n");
                switch_direction(&santa_direction, &current_char);
                moveAndCheckIntersection(santa_direction, &grid, &santa_x, &santa_y);
            }
            else // move robo santa direction
            {
                printf("moving robo santa\n");
                switch_direction(&robo_santa_direction, &current_char);
                moveAndCheckIntersection(robo_santa_direction, &grid, &robo_x, &robo_y);
            }
        }
        printf("%ld\n", grid.size);
        free(grid.points);
    }

    free(buffer);
    fclose(p_input_file);
}