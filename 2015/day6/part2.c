#include <stdio.h>
#include <stdlib.h>
#include "grid/grid.h"

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

    Grid grid;
    size_t capacity = 1000;
    createGrid(&grid, capacity);
    initLights(&grid);

    char buffer[64];
    int x1, y1, x2, y2 = 0;
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        if (4 == sscanf(buffer, "turn on %d,%d through %d,%d", &x1, &y1, &x2, &y2))
        {
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    turnOn(&grid, x, y);
                }
            }
        }
        else if (4 == sscanf(buffer, "turn off %d,%d through %d,%d", &x1, &y1, &x2, &y2))
        {
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    turnOff(&grid, x, y);
                }
            }
        }
        else if (4 == sscanf(buffer, "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2))
        {
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    toggleLight(&grid, x, y);
                }
            }
        }
        else
        {
            printf("Error parsing input.\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("%d total brightness\n", totalBrightness(&grid));
    freeGrid(&grid);
    fclose(p_input_file);
}