#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>



typedef struct {
    int x;
    int y;
} points_t;

typedef struct {
    points_t **points;
    size_t capacity;
    size_t size;
} grid_t;

// function prototypes
grid_t *grid_create(size_t capacity);
void grid_free(grid_t *grid);
int grid_add_point(grid_t *grid, int x, int y);
int grid_check_point(grid_t *grid, int x, int y);

grid_t *grid_create(size_t capacity)
{
    grid_t *p_grid = (grid_t *)malloc(sizeof(grid_t));
    if (!p_grid)
    {
        return NULL;
    }
    p_grid->size = 0;
    p_grid->capacity = capacity;
    p_grid->points = (points_t **)malloc(p_grid->capacity * sizeof(p_grid->points));
    if (!p_grid->points)
    {
        free(p_grid);
        exit(EXIT_FAILURE);
    }
    return p_grid;
}
void
grid_grow(grid_t *grid)
{
    size_t new_capacity = grid->capacity * 2;
    grid_point_t **new_points = (grid_point_t **)malloc(new_capacity * sizeof(grid_point_t *));
    if (new_points == NULL)
    {
        // Handle memory allocation error here if needed
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < new_capacity; i++)
    {
        new_points[i] = (grid_point_t *)calloc(new_capacity, sizeof(grid_point_t));
        if (new_points[i] == NULL)
        {
            // Handle memory allocation error here if needed
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < grid->capacity; i++)
    {
        memcpy(new_points[i], grid->points[i], grid->capacity * sizeof(grid_point_t));
        free(grid->points[i]);
    }
    free(grid->points);
    grid->points = new_points;
    grid->capacity = new_capacity;
}

void
grid_step(grid_t *grid, int x_step, int y_step, int value)
{
    grid->last_x = grid->current_x;
    grid->last_y = grid->current_y;
    grid->points[grid->current_y][grid->current_x].value = value;
    int new_x = grid->current_x + x_step;
    int new_y = grid->current_y + y_step;
    if (new_x >= grid->capacity || new_y >= grid->capacity)
    {
        grid_grow(grid);
    }
    grid->current_x = new_x;
    grid->current_y = new_y;
}

void
grid_print(grid_t *grid)
{
    for (int i = 0; i < grid->capacity; i++)
    {
        for (int j = 0; j < grid->capacity; j++)
        {
            printf("%d ", grid->points[i][j].value);
        }
        printf("\n");
    }
    printf("\n");
}

void
grid_free(grid_t *grid)
{
    for (int i = 0; i < grid->capacity; i++)
    {
        free(grid->points[i]);
    }
    free(grid->points);
    free(grid);
}