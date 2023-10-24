#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "grid/grid.h"
#include <string.h>

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
    // for (int curr_y = 0; curr_y < file_grid->rows; curr_y++) {
    //     for (int curr_x = 0; curr_x < file_grid->columns; curr_x++) {
    //         int x_dirs[] = {0, 1, 1, 1, 0, -1, -1, -1};
    //         int y_dirs[] = {1, 1, 0, -1, -1, -1, 0, 1};
    //         int set_basin = 0;

    //         for (int dir_itr = 0; dir_itr < 8; dir_itr++) {
    //             int next_x = curr_x + x_dirs[dir_itr];
    //             int next_y = curr_y + y_dirs[dir_itr];
    //             printf("NEXT: %d, %d\n", next_x, next_y);
    //             if (next_y >= 0 && next_y < file_grid->rows && next_x >= 0 && next_x < file_grid->columns) {
    //                 if (file_grid->points[curr_y][curr_x].value < file_grid->points[next_y][next_x].value) {
    //                     set_basin = 1;
    //                 }
    //                 else
    //                 {
    //                     set_basin = 0;
    //                     break;
    //                 }
    //             }
    //         }
    int risk_level = 0;
    for (int curr_y = 0; curr_y < file_grid->rows; curr_y++)
    {
        for (int curr_x = 0; curr_x < file_grid->columns; curr_x++)
        {
            int x_dir = 0;
            int y_dir = 1;
            int tmp = 0;
            int set_basin = 0;
            for (int dir_itr = 0; dir_itr < 4; dir_itr++)
            {
                int next_x = (curr_x + x_dir);
                int next_y = (curr_y + y_dir);
                // printf("NEXT: %d, %d\n", next_x, next_y);
                if ((next_y >= 0) && (next_y < file_grid->rows))
                {
                    if ((next_x >= 0) && (next_x < file_grid->columns))
                    {
                        // printf("Comparing %d, %d\n", next_x, next_y);
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
                tmp = x_dir;
                x_dir = -y_dir;
                y_dir = tmp;
            }
            // printf("%d, %d\tSet Basin? %s\n", curr_x, curr_y, set_basin ? "yes" : "no");
            // here, update the basin grid if the flag to set is true
            if (set_basin)
            {
                risk_level += (1 + file_grid->points[curr_y][curr_x].value);
                basin_grid->points[curr_y][curr_x].value = 1;
            }
        }
    }

    grid_print(basin_grid);
    printf("Risk level: %d\n", risk_level);

    // at point, scan in 4 adjacent directions
    // if value in adjacent directions are all larger, then basin is found
    grid_free(file_grid);
    grid_free(basin_grid);
    fclose(p_input_file);
    free(buffer);
}