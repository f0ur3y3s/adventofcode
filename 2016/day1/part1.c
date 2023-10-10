#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum CardinalDirection
{
    North,
    East,
    South,
    West,
};


const char* getDirection(enum CardinalDirection direction)
{
    switch (direction)
    {
        case North: return "North";
        case East: return "East";
        case South: return "South";
        case West: return "West";
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
    p_input_file = fopen(argv[1],"r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    enum CardinalDirection current_direction = North;
    char direction = 0;
    int distance = 0;
    char junk;

    int x = 0;
    int y = 0;

    while (fscanf(p_input_file, "%c%d", &direction, &distance) != EOF)
    {
        printf("%c\t%d\n", direction, distance);

        switch (direction)
        {
            case 'R':
                current_direction = (current_direction + 1) % 4;
                break;
            case 'L':
                current_direction = (current_direction - 1) % 4;
                break;
            default:
                printf("Ran into unexpected input.\n");
                exit(EXIT_FAILURE);
                break;
        }

        switch (current_direction)
        {
            case North:
                y += distance;
                break;
            case East:
                x += distance;
                break;
            case South:
                y -= distance;
                break;
            case West:
                x -= distance;
                break;
        }

        printf("%s\tX: %d\tY: %d\n", getDirection(current_direction), x, y);
        // consume the comma and space
        fscanf(p_input_file, "%c%c", &junk, &junk);
    }
    int total_distance = abs(x) + abs(y);
    printf("Total distance traveled: %d\n", total_distance);
    fclose(p_input_file);
    return 0;
}
