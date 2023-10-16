#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "grid/grid.h"

int calculate_perimeter(const int side)
{
    return ((2 * side) + (2 * (side - 2)));
}

int get_perimeter(FILE *p_input_file)
{
    char *buffer;
    size_t len = 0;
    ssize_t read = 0;
    read = getline(&buffer, &len, p_input_file);
    rewind(p_input_file);
    free(buffer);
    return (int) read - 1;
}

void
load_tree_arr(FILE *p_input_file, grid_t *tree_grid)
{
    int x = 0;
    int y = 0;
    int num = 0;
    while (fscanf(p_input_file, "%1d", &num) == 1)
    {
        tree_grid->points[y][x].value = num;
        x++;
        if (x % tree_grid->capacity == 0)
        {
            y++;
            x = 0;
        }
    }
    rewind(p_input_file);
}

void
scan_scenic(grid_t *tree_grid, grid_t *scenic_grid)
{
    // for each x and y index, scan in each cardinal direction to see how far the point can see without being blocked.
    for (int y_idx = 1; y_idx < tree_grid->capacity - 1; y_idx ++)
    {
        int current_tree_value = 0;
        int count_visible = 0;
        for (int x_idx = 1; x_idx < tree_grid->capacity - 1; x_idx++)
        {
            current_tree_value = tree_grid->points[y_idx][x_idx].value;
            // shoot in each direction
            int x_dir = 0;
            int y_dir = 1;
            int tmp = 0;
            for (int dir_itr = 0; dir_itr < 4; dir_itr++)
            {
                int direction_view = 0;
                for (int step = 0; step < tree_grid->capacity; step++)
                {
                    int extend_x = x_dir * step;
                    int extend_y = y_dir * step;
                    int next_x = (extend_x + x_idx);
                    int next_y = (extend_y + y_idx);
                    if (next_x != x_idx || next_y != y_idx)
                    {
                        if (-1 < next_x && next_x < tree_grid->capacity && -1 < next_y && next_y < tree_grid->capacity)
                        {
                            if (tree_grid->points[next_y][next_x].value >= current_tree_value)
                            {
                                direction_view++;
                                break;
                            }
                            if (tree_grid->points[next_y][next_x].value < current_tree_value)
                            {
                                direction_view++;
                            }
                        }
                    }
                }
                scenic_grid->points[y_idx][x_idx].value = scenic_grid->points[y_idx][x_idx].value * direction_view;
                tmp = x_dir;
                x_dir = -y_dir;
                y_dir = tmp;
            }
        }
    }
}

int
get_highest_scenic(grid_t *scenic_grid)
{
    int max = 0;
    for (int i = 0; i < scenic_grid->capacity; i++)
    {
        for (int j = 0; j < scenic_grid->capacity; j++)
        {
            if (scenic_grid->points[i][j].value > max)
            {
                max = scenic_grid->points[i][j].value;
            }
        }
    }
    return max;
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

    int side = get_perimeter(p_input_file);

    grid_t *tree_grid = grid_create(side);
    grid_t *scenic_grid = grid_create(side);

    // load the initial tree arr
    load_tree_arr(p_input_file, tree_grid);
    grid_print(tree_grid);

    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            scenic_grid->points[i][j].value = 1;
        }
    }

    scan_scenic(tree_grid, scenic_grid);
    grid_print(scenic_grid);
    int max = get_highest_scenic(scenic_grid);
    printf("%d is the max\n", max);


    grid_free(tree_grid);
    grid_free(scenic_grid);
    fclose(p_input_file);
}