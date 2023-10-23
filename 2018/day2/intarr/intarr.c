#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t size;
    size_t capacity;
} intarr_t;

intarr_t* intarr_create(void)
{
    intarr_t *p_intarr = malloc(sizeof(intarr_t));
    if (!p_intarr) {
        return NULL;
    }

    p_intarr->size = 0;
    p_intarr->capacity = 2;

    p_intarr->values = malloc(p_intarr->capacity * sizeof(p_intarr->values));
    if (!p_intarr->values) {
        free(p_intarr);
        return NULL;
    }

    return p_intarr;
}

void intarr_add(intarr_t *intarr, int new_value)
{
    if (intarr->size == intarr->capacity)
    {
        intarr->values = realloc(intarr->values, 2 * intarr->capacity * sizeof(intarr->values));
        if (!intarr->values) {
            free(intarr);
            return;
        }
        intarr->capacity *= 2;
    }
    intarr->values[intarr->size] = new_value;
    intarr->size++;
}

void intarr_print(intarr_t *intarr)
{
    for (int i = 0; i < intarr->size; i++)
    {
        printf("%d,", intarr->values[i]);
    }
    printf("\n");
    printf("Size: \t\t%ld\nCapacity: \t%ld\n", intarr->size, intarr->capacity);
}

void intarr_free(intarr_t *intarr)
{
    printf("Size: \t\t%ld\nCapacity: \t%ld\n", intarr->size, intarr->capacity);
    free(intarr->values);
    free(intarr);
}