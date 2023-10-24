#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "intarr/intarr.h"

// intarr_t *intarr_create_n(int n)
// {
//     intarr_t *p_intarr = malloc(sizeof(intarr_t));
//     if (!p_intarr) {
//         return NULL;
//     }

//     p_intarr->size = n;
//     p_intarr->capacity = n;

//     p_intarr->values = malloc(p_intarr->capacity * sizeof(p_intarr->values));
//     if (!p_intarr->values) {
//         free(p_intarr);
//         return NULL;
//     }

//     // initialize all values to 0
//     for (int i = 0; i < p_intarr->capacity; i++)
//     {
//         p_intarr->values[i] = 0;
//     }
//     return p_intarr;
// }

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
    if (!fuel_arr)
    {
        printf("Error creating intarr.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < max+1; i++)
    {
        fuel_arr[i] = 0;
    }

    // for (int i = 0; i < max+1; i++)
    // {
    //     printf("%d,", fuel_arr[i]);
    // }
    // printf("\n");

    

    fclose(p_input_file);
    intarr_free(crab_locations);
    return 0;
    
}