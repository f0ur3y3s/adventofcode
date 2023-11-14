#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* safe_malloc(size_t num_bytes, char *var_name, int line_num, const char *func_name)
{
    void *p_malloc_location = NULL;
    p_malloc_location = malloc(num_bytes);
    if (!p_malloc_location)
    {
        printf("Fatal: failed to allocate %ld bytes for variable '%s' on line '%d' in function '%s': Cannot allocate memory\n", num_bytes, var_name, line_num, func_name);
        free(p_malloc_location);
        return NULL;
    }
    return p_malloc_location;
}

void* safe_realloc(void *ptr, size_t num_bytes, char *var_name, int line_num, const char *func_name)
{
    void *p_realloc_location = NULL;
    p_realloc_location = realloc(ptr, num_bytes);
    if (!p_realloc_location)
    {
        printf("Fatal: failed to reallocate %ld bytes for variable '%s' on line '%d' in function '%s': Cannot allocate memory\n", num_bytes, var_name, line_num, func_name);
        free(p_realloc_location);
        return NULL;
    }
    return p_realloc_location;
}

typedef struct {
    int *values;
    size_t size;
    size_t capacity;
} intarr_t;

intarr_t* intarr_create(void)
{
    intarr_t *p_intarr = (intarr_t *)safe_malloc(sizeof(intarr_t), "new_array", __LINE__, __func__);
    if (!p_intarr) {
        return NULL;
    }

    p_intarr->size = 0;
    p_intarr->capacity = 2;
    p_intarr->values = (int *)safe_malloc(4 * sizeof(p_intarr->values), "p_intarr->values", __LINE__, __func__);
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
        intarr->capacity += 1;
        intarr->values = (int *)safe_realloc(intarr->values, intarr->capacity * sizeof(intarr->values), "intarr->values", __LINE__, __func__);
        if (!intarr->values) {
            free(intarr);
            return;
        }
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
}

void intarr_free(intarr_t *intarr)
{
    free(intarr->values);
    free(intarr);
}