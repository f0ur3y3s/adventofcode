#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[4];
    int value;
} wire_t;

typedef struct {
    wire_t *wires;
    size_t size;
    size_t capacity;
} collection_t;

void createCollection(collection_t *collection, size_t capacity)
{
    collection->wires = (wire_t *)malloc(capacity * sizeof(wire_t));
    if (!collection->wires)
    {
        printf("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    collection->capacity = capacity;
    collection->size = 0;
}

void addWire(collection_t *collection, wire_t wire)
{
    if (collection->size == collection->capacity)
    {
        collection->wires = (wire_t *)realloc(collection->wires, collection->capacity * 2 * sizeof(wire_t));
        if (!collection->wires)
        {
            printf("Error allocating memory.\n");
            exit(EXIT_FAILURE);
        }
        collection->capacity *= 2;
    }
    collection->wires[collection->size] = wire;
    collection->size++;
}

int findWire(collection_t *collection, char *name)
/*
* Returns the index of the wire with the given name, or -1 if not found.
*/
{
    for (int i = 0; i < collection->size; i++)
    {
        if (strcmp(collection->wires[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
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

    char buffer[64];
    collection_t collection;
    createCollection(&collection, 2);

    char wire1;
    char wire2;
    int value;
    char operation;

    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        if (2 == sscanf(buffer, "%d -> %s"))
        printf("%s\n", buffer);
    }

}