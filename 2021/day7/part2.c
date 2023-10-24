#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "intarr/intarr.h"
#include <math.h>

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

    intarr_t *crab_locations = intarr_create();
    if (!crab_locations)
    {
        printf("Error creating intarr.\n");
        exit(EXIT_FAILURE);
    }

    int min = INT_MAX;
    int max = INT_MIN;
    int num = 0;
    while(fscanf(p_input_file, "%d,", &num) != EOF)
    {
        if (num < min)
            min = num;
        if (num > max)
            max = num;
        intarr_add(crab_locations, num);
    }
    printf("min: %d\n", min);
    printf("max: %d\n", max);
    // intarr_print(crab_locations);
    // create an array of max
    int fuel_arr[max+1];
    for (int i = 0; i < max+1; i++)
    {
        fuel_arr[i] = 0;
    }



    // iterate through fuel_arr, each index of fuel_arr represents a position that
    // crabs can go to

    for (int fuel_idx = 0; fuel_idx < max+1; fuel_idx++)
    {
        for (int crab_idx = 0; crab_idx < crab_locations->size; crab_idx++)
        {
            int n = abs(crab_locations->values[crab_idx] - fuel_idx);
            fuel_arr[fuel_idx] += ((n * (n + 1))/2);
        }
    }

    // for (int i = 0; i < max+1; i++)
    // {
    //     printf("%d,", fuel_arr[i]);
    // }
    // printf("\n");

    int fuel_min = INT_MAX;
    int min_idx = 0;
    for (int idx = 0; idx < max+1; idx++)
    {
        if (fuel_arr[idx] < fuel_min)
        {
            fuel_min = fuel_arr[idx];
            min_idx = idx;
        }
    }

    printf("Min fuel: %d at idx %d\n", fuel_min, min_idx);
    printf("\n");
    fclose(p_input_file);
    intarr_free(crab_locations);
    return 0;
}