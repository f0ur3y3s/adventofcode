#include <stdio.h>
#include <stdlib.h>
#include "array/array.h"
#include <string.h>

int
is_in_arr(str_array* map, char* name)
{
    // printf("Looking for %s\n", name);
    for (int idx = 0; idx < map->size; idx++)
    {
        // printf("%s\t%s\n", name, map->pp_strings[idx]);
        if (strcmp(map->pp_strings[idx], name) == 0)
        {
            // printf("Found! %s\n", name);
            return 1;
        }
    }
    return 0;
}

void
scan_file_locations(FILE* p_input_file, str_array* map)
{
    char city1;
    char city2;
    int distance = 0;
    while (fscanf(p_input_file, "%s to %s = %d\n", city1, city2, &distance) != EOF)
    {
        // printf("%s\t%s\n", city1, city2);
        if (!is_in_arr(map, city1))
        {
            append_str(map, city1);
        }
        if (!is_in_arr(map, city2))
        {
            append_str(map, city2);
        }
    }
    rewind(p_input_file);
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

    str_array *map = safe_malloc_str_array();
    if (!map)
    {
        exit(EXIT_FAILURE);
    }

    char buffer[64];
    char city1[64];
    char city2[64];
    int distance = 0;

    scan_file_locations(p_input_file, map);
    print_str_array(map);
    // while (fscanf(p_input_file, "%s to %s = %d\n", city1, city2, &distance) != EOF)
    // {
    //     printf("%s\t%s\t%d\n", city1, city2, distance);
    // }
    printf("%ld\t%ld\n", map->capacity, map->size);

    free_str_array(map);
    fclose(p_input_file);
    exit(EXIT_SUCCESS);
}