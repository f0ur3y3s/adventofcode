#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int curr_x;
    int curr_y;
    int prev_x;
    int prev_y;
    int visited;
} knot_t;

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

knot_t *knot_create(void);
int knot_check(knot_t *head, knot_t *tail);
void knot_free(knot_t *knot);
void knot_move(knot_t *knot, int x_step, int y_step);

knot_t *
knot_create(void)
{
    knot_t *p_knot = (knot_t *)malloc(sizeof(knot_t));
    if (!p_knot)
    {
        return NULL;
    }
    p_knot->curr_x = 0;
    p_knot->curr_y = 0;
    p_knot->prev_x = 0;
    p_knot->prev_y = 0;
    p_knot->visited = 0;
    return p_knot;
}

int
knot_check(knot_t *head, knot_t *tail)
{
    // check all squares around the tail grid to see if the head grid is within 1 square
    int tail_current_x = tail->curr_x;
    int tail_current_y = tail->curr_y;
    for (int x_step = -1; x_step <= 1; x_step++)
    {
        for (int y_step = -1; y_step <= 1; y_step++)
        {
            if (head->curr_x == tail_current_x + x_step && head->curr_y == tail_current_y + y_step)
            {
                return 1;
            }
        }
    }
    return 0;
}

void
knot_free(knot_t *knot)
{
    free(knot);
}

void
knot_move(knot_t *knot, int x_step, int y_step)
{
    knot->prev_x = knot->curr_x;
    knot->prev_y = knot->curr_y;
    knot->curr_x += x_step;
    knot->curr_y += y_step;
    knot->visited++;   
}

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

void grid_free(grid_t *grid)
{
    for (int i = 0; i < grid->size; i++)
    {
        free(grid->points[i]);
    }
    free(grid->points);
    free(grid);
}

int grid_add_point(grid_t *grid, int x, int y)
{
    // printf("adding point\n");
    if (grid->capacity == grid->size)
    {
        points_t **tmp = realloc(grid->points, grid->capacity * 2 * sizeof(grid->points));
        if (!tmp)
        {
            return 0 ;
        }
        grid->points = tmp;
        grid->capacity *= 2;
    }

    grid->points[grid->size] = malloc(sizeof(points_t));
    if (!grid->points[grid->size])
    {
        return 0;
    }

    grid->points[grid->size]->x = x;
    grid->points[grid->size]->y = y;
    grid->size++;
    return 1;
}

int grid_check_point(grid_t *grid, int x, int y)
{
    for (int i = 0; i < grid->size; i++)
    {
        if (grid->points[i]->x == x && grid->points[i]->y == y)
        {
            return 1;
        }
    }
    return 0;
}

void execute_move(knot_t *head_knot, knot_t *tail_knot, grid_t *tail_grid, int x_step, int y_step)
{
    knot_move(head_knot, x_step, y_step);
    if (!knot_check(head_knot, tail_knot))
    {
        int x_diff = head_knot->prev_x - tail_knot->curr_x;
        int y_diff = head_knot->prev_y - tail_knot->curr_y;
        knot_move(tail_knot, x_diff, y_diff);
        if (!grid_check_point(tail_grid, tail_knot->curr_x, tail_knot->curr_y))
        {
            grid_add_point(tail_grid, tail_knot->curr_x, tail_knot->curr_y);
        }
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

    knot_t *head_knot = knot_create();
    knot_t *tail_knot = knot_create();
    grid_t *tail_grid = grid_create(2);

    char move;
    int distance = 0;
    int x_diff = 0;
    int y_diff = 0;
    while (fscanf(p_input_file, "%c %d\n", &move, &distance) != EOF)
    {
        // printf("%c %d\n", move, distance);
        switch (move)
        {
            case 'U':
                for (int y_step = distance; y_step > 0; y_step--)
                {
                    execute_move(head_knot, tail_knot, tail_grid, 0, -1);
                    // printf("Head: (%d, %d)\tTail: (%d, %d)\n", head_knot->curr_x, head_knot->curr_y, tail_knot->curr_x, tail_knot->curr_y);
                }
                break;

            case 'D':
                for (int y_step = 0; y_step < distance; y_step++)
                {
                    execute_move(head_knot, tail_knot, tail_grid, 0, 1);
                    // printf("Head: (%d, %d)\tTail: (%d, %d)\n", head_knot->curr_x, head_knot->curr_y, tail_knot->curr_x, tail_knot->curr_y);
                }
                break;

            case 'L':
                for (int x_step = 0; x_step > -distance; x_step--)
                {
                    execute_move(head_knot, tail_knot, tail_grid, -1, 0);
                    // printf("Head: (%d, %d)\tTail: (%d, %d)\n", head_knot->curr_x, head_knot->curr_y, tail_knot->curr_x, tail_knot->curr_y);
                }
                break;

            case 'R':
                for (int x_step = 0; x_step < distance; x_step++)
                {
                    execute_move(head_knot, tail_knot, tail_grid, 1, 0);
                    // printf("Head: (%d, %d)\tTail: (%d, %d)\n", head_knot->curr_x, head_knot->curr_y, tail_knot->curr_x, tail_knot->curr_y);
                }
                break;
            default:
                printf("Error: invalid move.\n");
                exit(EXIT_FAILURE);
        }
    }

    printf("Tail visited %d\n", tail_knot->visited);
    printf("Tail visited %ld unique\n", tail_grid->size + 1);


    knot_free(head_knot);
    knot_free(tail_knot);
    grid_free(tail_grid);
    fclose(p_input_file);
}