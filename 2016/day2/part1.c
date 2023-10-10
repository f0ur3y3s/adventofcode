#include <stdio.h>
#include <stdlib.h>

enum Direction
{
    Up,
    Right,
    Down,
    Left,
};

void
calculateResult(int *row, int *col)
{
    int result = *row * 3 + *col + 1;
    printf("%d\n", result);
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

    char direction;
    int current_row = 1; // Starting row
    int current_col = 1; // Starting column

    for (;;)
    {
        int ret = fscanf(p_input_file, "%c", &direction);
        if (ret == EOF)
        {
            calculateResult(&current_row, &current_col);
            break;
        }
        else if (direction == '\n')
        {
            calculateResult(&current_row, &current_col);
            continue;
        }
        switch (direction)
        {
            case 'U':
                if (current_row > 0)
                    current_row--;
                break;
            case 'R':
                if (current_col < 2)
                    current_col++;
                break;
            case 'D':
                if (current_row < 2)
                    current_row++;
                break;
            case 'L':
                if (current_col > 0)
                    current_col--;
                break;
            default:
                printf("Ran into unexpected input.\n");
                fclose(p_input_file);
                exit(EXIT_FAILURE);
                break;
        }
    }

    fclose(p_input_file);
    return 1;
}