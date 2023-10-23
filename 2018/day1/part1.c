#include <stdio.h>
#include <stdlib.h>

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

    int curr_freq = 0;
    int change = 0;
    while (fscanf(p_input_file, "%d\n", &change) != EOF)
    {
        curr_freq += change;
        // printf("%d\n", change);
    }
    printf("Current frequency: %d\n", curr_freq);
    fclose(p_input_file);
}