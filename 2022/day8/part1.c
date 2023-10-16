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

// int
// find_visible_trees(const int side, const int tree_arr[side][side])
// {
//     int count = 0;
//     int x = 1;
//     int y = 1;
//     // scan through each column and row starting from 1.
//     // in each column, if the tree is larger than the max, add to visible, update max
//     int max = 0;
//     for (int y_idx = 1; y_idx < side; y_idx++)
//     {
//         max = tree_arr[y_idx][0];
//         for (int x_idx = 1; x_idx < side - 1; x_idx++)
//         {
//             printf("Max: %d\tValue: %d\tScanning tree %d, %d\n", max, tree_arr[y_idx][x_idx], x_idx, y_idx);
//             if (tree_arr[y_idx][x_idx] > max)
//             {
//                 printf("Value exceeds max, tree is visible!\n");
//                 max = tree_arr[y_idx][x_idx];
//                 count++;
//             }
//         }
//         max = tree_arr[y_idx][side-1];
//         for (int x_idx = side-2; x_idx >= 1; x_idx--)
//         {
//             printf("Max: %d\tValue: %d\tScanning tree %d, %d\n", max, tree_arr[y_idx][x_idx], x_idx, y_idx);
//             if (tree_arr[y_idx][x_idx] > max)
//             {
//                 printf("Value exceeds max, tree is visible!\n");
//                 max = tree_arr[y_idx][x_idx];
//                 count++;
//             }
//         }
//     }
//     return count;
// }

void
scan_visible(const grid_t *tree_grid, grid_t *visible_grid)
{
    int max = 0;
    // scan through the rows
    for (int y_idx = 1; y_idx < ((tree_grid->capacity)-1); y_idx++)
    {
        max = tree_grid->points[y_idx][0].value;
        for (int x_idx = 1; x_idx < ((tree_grid->capacity)-1) - 1; x_idx++)
        {
            if (tree_grid->points[y_idx][x_idx].value > max)
            {
                // printf("Value exceeds max, tree is visible!\n");
                max = tree_grid->points[y_idx][x_idx].value;
                visible_grid->points[y_idx][x_idx].value = 1;
            }
        }
        max = tree_grid->points[y_idx][tree_grid->capacity - 1].value;
        for (int x_idx = ((tree_grid->capacity)-2); x_idx >= 1; x_idx--)
        {
            if (tree_grid->points[y_idx][x_idx].value > max)
            {
                // printf("Value exceeds max, tree is visible!\n");
                max = tree_grid->points[y_idx][x_idx].value;
                visible_grid->points[y_idx][x_idx].value = 1;
            }
        }
    }
    // scan through the columns
    for (int x_idx = 1; x_idx < ((tree_grid->capacity)-1); x_idx++)
    {
        max = tree_grid->points[0][x_idx].value;
        for (int y_idx = 1; y_idx < ((tree_grid->capacity)-1) - 1; y_idx++)
        {
            if (tree_grid->points[y_idx][x_idx].value > max)
            {
                // printf("Value exceeds max, tree is visible!\n");
                max = tree_grid->points[y_idx][x_idx].value;
                visible_grid->points[y_idx][x_idx].value = 1;
            }
        }
        max = tree_grid->points[tree_grid->capacity - 1][x_idx].value;
        for (int y_idx = ((tree_grid->capacity)-2); y_idx >= 1; y_idx--)
        {
            if (tree_grid->points[y_idx][x_idx].value > max)
            {
                // printf("Value exceeds max, tree is visible!\n");
                max = tree_grid->points[y_idx][x_idx].value;
                visible_grid->points[y_idx][x_idx].value = 1;
            }
        }
    }
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
set_perimeter_visible(grid_t *visible_grid)
{
    for (int y_idx = 0; y_idx < visible_grid->capacity; y_idx++)
    {
        for (int x_idx = 0; x_idx < visible_grid->capacity; x_idx++)
        {
            if (y_idx % (visible_grid->capacity - 1) == 0 || x_idx % (visible_grid->capacity - 1) == 0 )
            {
                visible_grid->points[y_idx][x_idx].value = 1;
            }
        }

    }
}

int
count_visible(grid_t *visible_grid)
{
    int count = 0;
    for (int y_idx = 0; y_idx < visible_grid->capacity; y_idx++)
    {
        for (int x_idx = 0; x_idx < visible_grid->capacity; x_idx++)
        {
            if (visible_grid->points[y_idx][x_idx].value == 1)
            {
                count += 1;
            }
        }
    }
    return count;
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
    // printf("The side is %d\n", side);
    // int tree_arr[side][side];

    grid_t *tree_grid = grid_create(side);
    grid_t *visible_grid = grid_create(side);

    // load the initial tree arr
    load_tree_arr(p_input_file, tree_grid);
    // print_trees(side, tree_arr);
    grid_print(tree_grid);
    set_perimeter_visible(visible_grid);

    scan_visible(tree_grid, visible_grid);

    int count = count_visible(visible_grid);
    grid_print(visible_grid);
    printf("%d trees are visible.\n", count);
    grid_free(visible_grid);
    grid_free(tree_grid);
    fclose(p_input_file);
}