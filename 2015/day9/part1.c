#include <stdio.h>
#include <stdlib.h>
#include "../../wordlist/wordlist.h"
#include "graph/graph.h"
#include <string.h>

void
scan_file_locations(FILE* p_input_file, wordlist_t* map)
{
    char city1[64];
    char city2[64];
    int distance = 0;
    while (fscanf(p_input_file, "%s to %s = %d\n", city1, city2, &distance) != EOF)
    {
        // printf("%d\n", wordlist_find(map, city1));
        if (-1 == wordlist_find(map, city1))
        {
            // printf("Adding %s\n", city1);
            wordlist_append(map, city1);
        }
        if (-1 == wordlist_find(map, city2))
        {
            // printf("Adding %s\n", city2);
            wordlist_append(map, city2);
        }
        // printf("Map size: %ld\n", map->size);
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

    wordlist_t *map = wordlist_create();
    if (!map)
    {
        exit(EXIT_FAILURE);
    }

    scan_file_locations(p_input_file, map);
    wordlist_print(map);

    int map_size = map->size;
    // printf("%d\n", map_size);

    int graph[map_size][map_size];
    graph_init(map_size, graph);

    char buffer[64];
    char city1[64];
    char city2[64];
    int distance = 0;

    while (fscanf(p_input_file, "%s to %s = %d\n", city1, city2, &distance) != EOF)
    {
        // printf("%s\t%s\t%d\n", city1, city2, distance);
        int city1_idx = wordlist_find(map, city1);
        int city2_idx = wordlist_find(map, city2);
        graph[city1_idx][city2_idx] = distance;
        graph[city2_idx][city1_idx] = distance;
        // graph_print(map_size, graph);
    }
    // printf("%ld\t%ld\n", map->capacity, map_size);
    graph_print(map_size, graph, map);

    wordlist_free(map);
    fclose(p_input_file);
    exit(EXIT_SUCCESS);
}