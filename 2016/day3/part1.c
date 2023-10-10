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

    int first = 0;
    int second = 0;
    int third = 0;
    int total_possible = 0;
    int max = 0;
    while (fscanf(p_input_file, "%d %d %d", &first, &second, &third) != EOF)
    {
        if(first+second>third && first+third>second && second+third>first){
            total_possible++;
        }

        // find the max of first, second, third

        // if (first + second > third)
        // {
        //     printf("%d\t%d\t%d\n", first, second, third);
        //     total_possible++;
        // }
    }

    printf("Total possible: %d\n", total_possible);
}