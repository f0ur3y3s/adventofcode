#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "grid/grid.h"
#include <string.h>

void
get_basin_mask(grid_t *basin_mask_grid, grid_t *file_grid, int curr_x, int curr_y)
{
    basin_mask_grid->points[curr_y][curr_x].value = 1;
    int size = 0;
    int x_dirs[] = {0, 1, 0, -1};
    int y_dirs[] = {1, 0, -1, 0};

    for (int dir_itr = 0; dir_itr < 4; dir_itr++)
    {
        int next_x = curr_x + x_dirs[dir_itr];
        int next_y = curr_y + y_dirs[dir_itr];
        if (next_y >= 0 && next_y < file_grid->rows && next_x >= 0 && next_x < file_grid->columns)
        {
            if (file_grid->points[curr_y][curr_x].value < file_grid->points[next_y][next_x].value && file_grid->points[next_y][next_x].value < 9)
            {
                // here, update the basin mask
                basin_mask_grid->points[next_y][next_x].value = 1;
                get_basin_mask(basin_mask_grid, file_grid, next_x, next_y);
                // basin_mask_grid[next_y][next_x]
            }
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
    p_input_file = fopen(argv[1], "r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    // scan through file to get size
    char   *buffer       = NULL;
    size_t  len          = 0;
    ssize_t read         = 0;
    int     file_rows    = 0;
    int     file_columns = 0;

    while ((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        // printf("%s\n", buffer);
        file_columns = read;
        file_rows++;
    }

    printf("%d rows by %d columns\n", file_rows, file_columns);
    // create capacity of grid based on y and x
    grid_t *file_grid = grid_create(file_rows, file_columns);
    grid_print(file_grid);
    // rewind
    rewind(p_input_file);
    // scan through and populate grid with input
    int pop_row = 0;
    int pop_col = 0;
    while ((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        while (buffer[pop_col] != '\0')
        {
            file_grid->points[pop_row][pop_col].value = (buffer[pop_col] - '0');
            pop_col++;
        }
        pop_row++;
        pop_col = 0;
    }
    grid_print(file_grid);
    // copy capacity of grid for basin points

    grid_t *basin_grid = grid_create(file_rows, file_columns);
    // look for basin
    int risk_level = 0;
    int basin_points = 0;
    for (int curr_y = 0; curr_y < file_grid->rows; curr_y++)
    {
        for (int curr_x = 0; curr_x < file_grid->columns; curr_x++)
        {
            int x_dirs[] = {0, 1, 0, -1};
            int y_dirs[] = {1, 0, -1, 0};
            int set_basin = 0;

            for (int dir_itr = 0; dir_itr < 4; dir_itr++)
            {
                int next_x = curr_x + x_dirs[dir_itr];
                int next_y = curr_y + y_dirs[dir_itr];
                if (next_y >= 0 && next_y < file_grid->rows && next_x >= 0 && next_x < file_grid->columns)
                {
                    if (file_grid->points[curr_y][curr_x].value < file_grid->points[next_y][next_x].value)
                    {
                        set_basin = 1;
                    }
                    else
                    {
                        set_basin = 0;
                        break;
                    }
                }
            }
            if (set_basin)
            {
                risk_level += (1 + file_grid->points[curr_y][curr_x].value);
                basin_grid->points[curr_y][curr_x].value = 1;
                basin_points++;
            }
        }
    }

    grid_print(basin_grid);
    printf("Risk level: %d\n", risk_level);

    // part 2 start here
    // at every basin point, scan adjacent
    // if adjacent is not 9, scan adjacent to that point
    // use recursion

    int *basin_sizes = malloc(sizeof(int) * basin_points);

    grid_t * basin_mask_grid = NULL;
    int count_basin = 0;
    for (int curr_y = 0; curr_y < file_grid->rows; curr_y++)
    {
        for (int curr_x = 0; curr_x < file_grid->columns; curr_x++)
        {
            if (basin_grid->points[curr_y][curr_x].value)
            {
                // printf("Found basin center: %d, %d\n", curr_x, curr_y);
                basin_mask_grid = grid_create(file_rows, file_columns);
                get_basin_mask(basin_mask_grid, file_grid, curr_x, curr_y);
                int basin_size = 0;
                for (int basin_y = 0; basin_y < file_grid->rows; basin_y++)
                {
                    for (int basin_x = 0; basin_x < file_grid->columns; basin_x++)
                    {
                        if (basin_mask_grid->points[basin_y][basin_x].value)
                        {
                            basin_size++;
                        }
                    }
                }
                printf("Size: %d\tBasin mask grid:\n", basin_size);
                basin_sizes[count_basin] = basin_size;
                // printf("%d\n", basin_sizes[count_basin]);
                count_basin++;
                grid_print(basin_mask_grid);
                grid_free(basin_mask_grid);
            }
        }
    }

    for (int idx = 0; idx < basin_points; idx++)
    {
        printf("%d ", basin_sizes[idx]);
    }
    printf("\n");

    // multiply the three largest basins
    int largest_basins[3] = {0};
    for (int idx = 0; idx < basin_points; idx++)
    {
        if (basin_sizes[idx] > largest_basins[0])
        {
            largest_basins[2] = largest_basins[1];
            largest_basins[1] = largest_basins[0];
            largest_basins[0] = basin_sizes[idx];
        }
        else if (basin_sizes[idx] > largest_basins[1])
        {
            largest_basins[2] = largest_basins[1];
            largest_basins[1] = basin_sizes[idx];
        }
        else if (basin_sizes[idx] > largest_basins[2])
        {
            largest_basins[2] = basin_sizes[idx];
        }
    }

    printf("Largest basins: %d, %d, %d: %d\n", largest_basins[0], largest_basins[1], largest_basins[2], largest_basins[0] * largest_basins[1] * largest_basins[2]);

    grid_free(file_grid);
    grid_free(basin_grid);
    fclose(p_input_file);
    free(buffer);
    free(basin_sizes);
    return 0;
}