#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int *  values;
    size_t size;
    size_t capacity;
} intarr_t;

intarr_t * intarr_create (void)
{
    intarr_t * p_intarr = malloc(sizeof(intarr_t));
    if (!p_intarr)
    {
        return NULL;
    }

    p_intarr->size     = 0;
    p_intarr->capacity = 4;

    p_intarr->values = malloc(p_intarr->capacity * sizeof(p_intarr->values));
    if (!p_intarr->values)
    {
        free(p_intarr);
        return NULL;
    }

    return p_intarr;
}

void intarr_add (intarr_t * p_intarr, int new_value)
{
    if (p_intarr->size == p_intarr->capacity)
    {
        p_intarr->values
            = realloc(p_intarr->values,
                      2 * p_intarr->capacity * sizeof(p_intarr->values));
        if (!p_intarr->values)
        {
            free(p_intarr);
            return;
        }
        p_intarr->capacity *= 2;
    }
    p_intarr->values[p_intarr->size] = new_value;
    p_intarr->size++;
}

void intarr_print (intarr_t * p_intarr)
{
    for (int i = 0; i < p_intarr->size; i++)
    {
        printf("%d,", p_intarr->values[i]);
    }
    printf("\n");
    // printf(
    //     "Size: \t\t%ld\nCapacity: \t%ld\n", p_intarr->size, p_intarr->capacity);
}

void intarr_destroy (intarr_t * p_intarr)
{
    // printf(
    //     "Size: \t\t%ld\nCapacity: \t%ld\n", p_intarr->size, p_intarr->capacity);
    free(p_intarr->values);
    free(p_intarr);
}