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
    int idx = 0;
    int group[9] = {0,0,0,0,0,0,0,0,0};
    while (fscanf(p_input_file, "%d %d %d", &group[idx], &group[idx+1], &group[idx+2]) != EOF)
    {
        idx += 3;
        if(idx == 9)
        {
            for(int j = 0; j < 3; j ++){
                if(group[j]+group[j+3]>group[j+6] &&
                   group[j]+group[j+6]>group[j+3] &&
                   group[j+3]+group[j+6]>group[j]){
                    total_possible++;
                }
            }
            idx = 0;
        }

    }

    printf("Total possible: %d\n", total_possible);
}