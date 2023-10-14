#include <stdio.h>
#include <stdlib.h>
#include "../../../wordlist/wordlist.h"

int* graph_create(int size)
{
    int *graph = (int *)malloc(size * size * sizeof(int));
    if (!graph)
    {
        printf("Fatal: failed to allocate %ld bytes for variable '%s' on line '%d' in function '%s': Cannot allocate memory\n", size * size * sizeof(int), "graph", __LINE__, __func__);
        free(graph);
        return NULL;
    }
    return graph;
}

void graph_init(int size, int graph[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            graph[i][j] = 0;
        }
    }
}

void graph_print(int size, int graph[size][size], wordlist_t* map)
{
    for (int i = 0; i < size; i++)
    {
        printf("%20s\t", map->words[i]);
        for (int j = 0; j < size; j++)
        {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

int tsp(int graph[NUM_LOCATIONS][NUM_LOCATIONS], int* path, int visited, int current, int n) {
    if (visited == (1 << n) - 1) {
        return graph[current][0];
    }

    int min_distance = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!(visited & (1 << i)) && graph[current][i] != 0) {
            int new_distance = graph[current][i] + tsp(graph, path, visited | (1 << i), i, n);
            
            if (new_distance < min_distance) {
                min_distance = new_distance;
                path[i] = current;
            }
        }
    }
    return min_distance;
}

