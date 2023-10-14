#ifndef GRAPH_H
#define GRAPH_H

void graph_init(int size, int graph[size][size]);
int * graph_create(int size);
// void graph_print(int size, int graph[size][size]);
void graph_print(int size, int graph[size][size], wordlist_t* map);

#endif