#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include "../aoc/shared.h"

#define MAX_COLS 12
#define MAX_ROWS 12

char schematic[MAX_COLS][MAX_ROWS] = { 0 };

int get_number (int x, int y)
{
    int result = 0;

    while (isdigit(schematic[x][y]))
    {
        y--;
    }

    result = strtol(schematic[x] + (++y), NULL, 10);

    while (isdigit(schematic[x][y]))
    {
        schematic[x][y++] = '.';
    }
    return result;
}

int get_parts (int x, int y)
{
    int sum = 0;
    for (int j = x - 1; j < x + 2; j++)
    {
        for (int k = y - 1; k < y + 2; k++)
        {
            if (isdigit(schematic[j][k]))
            {
                sum += get_number(j, k);
            }
        }
    }

    return sum;
}

void print_schematic (void)
{
    for (int i = 0; i < MAX_COLS; i++)
    {
        for (int j = 0; j < MAX_ROWS; j++)
        {
            printf("%c", schematic[i][j]);
        }
        printf("\n");
    }
}

int main (int argc, char * argv[])
{
    long   result = 0;
    int    x      = 0;
    FILE * p_input_file;
    if (2 != argc)
    {
        printf("Usage: %s [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((p_input_file = fopen(argv[1], "r")) == NULL)
    {
        printf("error opening file %s\n", argv[1]);
        return 1;
    }
    int     y_index = 0;
    char *  buffer  = NULL;
    size_t  len     = 0;
    ssize_t read    = 0;

    while ((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        strsnl(buffer);
        strcpy(schematic[y_index++] + 1, buffer);
    }

    print_schematic();

    for (x = 1; x < MAX_COLS; x++)
    {
        for (int y = 1; y < MAX_ROWS; y++)
        {
            if (schematic[x][y] != '\0' && schematic[x][y] != '.'
                && !isdigit(schematic[x][y]))
            {
                result += get_parts(x, y);
            }
        }
    }
    print_schematic();

    printf("%ld\n", result);
    return 0;
}
