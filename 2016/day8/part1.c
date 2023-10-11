#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COLS 50
#define MAX_ROWS 6

void
initScreen(char screen[MAX_ROWS][MAX_COLS])
{
    for (int row = 0; row < MAX_ROWS; row++)
    {
        for (int col = 0; col < MAX_COLS; col++)
        {
            screen[row][col] = '.';
        }
    }
}

void
printScreen(char screen[MAX_ROWS][MAX_COLS])
{
    for (int row = 0; row < MAX_ROWS; row++)
    {
        for (int col = 0; col < MAX_COLS; col++)
        {
            printf("%c", screen[row][col]);
        }
        printf("\n");
    }
}

void
initRect(char screen[MAX_ROWS][MAX_COLS], int width, int height)
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            screen[row][col] = '#';
        }
    }
}

void
rotate()
{

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

    char line[64];
    char *token;

    char screen[MAX_ROWS][MAX_COLS];
    initScreen(screen);
    int rect_width;
    int rect_height;

    int x;
    int y;
    char junk;
    int amount;
    char target[8];

    while (fscanf(p_input_file, "%[^\n]\n", line) != EOF)
    {
        token = strtok(line, " ");
        if (strcmp(token, "rect") == 0)
        {
            token = strtok(NULL, " ");
            sscanf(token, "%dx%d", &rect_width, &rect_height);
            printf("rect\t%d, %d\n", rect_width, rect_height);
            initRect(screen, rect_width, rect_height);
        }

        else
        {
            // rotate column x=1 by 1
            token = strtok(NULL, " ");
            sscanf(token, "%s", target);
            if (strcmp(token, "column") == 0)
            {
                token = strtok(NULL, " ");
                sscanf(token, "%c%c%d", &junk, &junk, &x);
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                sscanf(token, "%d", &amount);
                printf("rotate column\t%d\t%d\n", x, amount);
            }
            else
            {
                token = strtok(NULL, " ");
                sscanf(token, "%c%c%d", &junk, &junk, &y);
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                sscanf(token, "%d", &amount);
                printf("rotate row\t%d\t%d\n", y, amount);
            }
            token = strtok(NULL, " ");
            // printf("rotate\t%s\n", target);
        }
        token = strtok(NULL, " ");
        printScreen(screen);
    }

    fclose(p_input_file);
}