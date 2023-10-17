#include <stdio.h>
#include <stdlib.h>
#include "grid/grid.h"

int
count_visited(grid_t *tail_grid)
{
    int count = 1;
    for (int i = 0; i < tail_grid->capacity; i++)
    {
        for (int j = 0; j < tail_grid->capacity; j++)
        {
            if (tail_grid->points[i][j].value > 0)
            {
                count++;
            }
        }
    }
    return count;
}

int
grid_check_head_tail(grid_t *head_grid, grid_t *tail_grid)
{
    // check all squares around the tail grid to see if the head grid is within 1 square
    int tail_current_x = tail_grid->current_x;
    int tail_current_y = tail_grid->current_y;
    for (int x_step = -1; x_step <= 1; x_step++)
    {
        for (int y_step = -1; y_step <= 1; y_step++)
        {
            if (head_grid->current_x == tail_current_x + x_step && head_grid->current_y == tail_current_y + y_step)
            {
                printf("Head and tail are within 1 square.\n");
                return 1;
            }
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
    p_input_file = fopen(argv[1],"r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    grid_t *head_grid = grid_create(2);
    grid_t *tail_grid = grid_create(2);

    char move;
    int distance;
    while (fscanf(p_input_file, "%c %d\n", &move, &distance) != EOF)
    {
        // printf("%c %d\n", move, distance);
        switch (move)
        {
            case 'U':
                for (int y_step = distance; y_step > 0; y_step--)
                {
                    // printf("y_step: %d\n", y_step);
                    grid_step(head_grid, 0, 1, 1);
                    grid_print(head_grid);
                    if (!grid_check_head_tail(head_grid, tail_grid))
                    {
                        // calculate the difference between the head last and tail current
                        int x_diff = head_grid->last_x - tail_grid->current_x;
                        int y_diff = head_grid->last_y - tail_grid->current_y;
                        grid_step(tail_grid, x_diff, y_diff, 2);
                        grid_print(tail_grid);
                    }
                }
                break;

            case 'D':
                for (int y_step = 0; y_step < distance; y_step++)
                {
                    // printf("y_step: %d\n", y_step);
                    grid_step(head_grid, 0, -1, 1);
                    grid_print(head_grid);
                    if (!grid_check_head_tail(head_grid, tail_grid))
                    {
                        // calculate the difference between the head last and tail current
                        int x_diff = head_grid->last_x - tail_grid->current_x;
                        int y_diff = head_grid->last_y - tail_grid->current_y;
                        grid_step(tail_grid, x_diff, y_diff, 2);
                        grid_print(tail_grid);
                    }
                }
                break;

            case 'L':
                for (int x_step = 0; x_step > -distance; x_step--)
                {
                    // printf("x_step: %d\n", x_step);
                    grid_step(head_grid, -1, 0, 1);
                    grid_print(head_grid);
                    if (!grid_check_head_tail(head_grid, tail_grid))
                    {
                        // calculate the difference between the head last and tail current
                        int x_diff = head_grid->last_x - tail_grid->current_x;
                        int y_diff = head_grid->last_y - tail_grid->current_y;
                        grid_step(tail_grid, x_diff, y_diff, 2);
                        grid_print(tail_grid);
                    }
                }
                break;

            case 'R':
                for (int x_step = 0; x_step < distance; x_step++)
                {
                    // printf("x_step: %d\tmove: %d\n", x_step, distance);
                    grid_step(head_grid, 1, 0, 1);
                    grid_print(head_grid);
                    if (!grid_check_head_tail(head_grid, tail_grid))
                    {
                        // calculate the difference between the head last and tail current
                        int x_diff = head_grid->last_x - tail_grid->current_x;
                        int y_diff = head_grid->last_y - tail_grid->current_y;
                        grid_step(tail_grid, x_diff, y_diff, 2);
                        grid_print(tail_grid);
                    }
                }
                break;
            default:
                printf("Error: invalid move.\n");
                exit(EXIT_FAILURE);
        }
    }

    printf("Number of squares visited: %d\n", count_visited(tail_grid));

    grid_free(head_grid);
    grid_free(tail_grid);
    fclose(p_input_file);
}