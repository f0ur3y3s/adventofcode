#include <stdio.h>
#include <stdlib.h>
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
    p_input_file = fopen(argv[1],"r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    char c; // to store the character read from the file
    int floor = 0;
    int count = 0;
    while ((c = fgetc(p_input_file)) != EOF)
    {
        if ('(' == c)
        {
            floor++;
        }
        else
        {
            floor--;
        }
        if (-1 == floor)
        {
            printf("Index of basement enter: %d\n", count);
        }
        count ++;
    }
    printf("Final floor: %d\n", floor);
}