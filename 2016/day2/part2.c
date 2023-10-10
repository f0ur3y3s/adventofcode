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
calculateResult(char keypad[5][5], int row, int col)
{
    printf("%c\n", keypad[row][col]);
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
    int current_row = 2; // Starting row
    int current_col = 0; // Starting column

    char keypad[5][5] = {
        {'0', '0', '1', '0', '0'},
        {'0', '2', '3', '4', '0'},
        {'5', '6', '7', '8', '9'},
        {'0', 'A', 'B', 'C', '0'},
        {'0', '0', 'D', '0', '0'}
    };

    for (;;)
    {
        int ret = fscanf(p_input_file, "%c", &direction);
        if (ret == EOF)
        {
            calculateResult(keypad, current_row, current_col);
            break;
        }
        else if (direction == '\n')
        {
            calculateResult(keypad, current_row, current_col);
            continue;
        }
        switch (direction)
        {
            case 'U':
                if (current_row > 0 && keypad[current_row - 1][current_col] != '0')
                {
                    current_row--;
                }
                break;
            case 'D':
                if (current_row < 4 && keypad[current_row + 1][current_col] != '0')
                {
                    current_row++;
                }
                break;
            case 'R':
                if (current_col < 4 && keypad[current_row][current_col + 1] != '0')
                {
                    current_col++;
                }
                break;
            case 'L':
                if (current_col > 0 && keypad[current_row][current_col - 1] != '0')
                {
                    current_col--;
                }
                break;
            default:
                printf("Ran into unexpected input.\n");
                fclose(p_input_file);
                exit(EXIT_FAILURE);
                break;
        }
        // printf("%c\t%d, %d\n", direction, current_row, current_col);
    }

    fclose(p_input_file);
    return 1;
}