#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void *
safe_malloc(size_t num_bytes, char *var_name, int line_num, const char *func_name)
{
    void *p_malloc_location = NULL;
    p_malloc_location = malloc(num_bytes);
    if (!p_malloc_location)
    {
        printf("Fatal: failed to allocate %ld bytes for variable '%s' on line '%d' in function '%s': Cannot allocate memory\n", num_bytes, var_name, line_num, func_name);
        return NULL;
    }
    return p_malloc_location;
}

void *
safe_realloc(void *ptr, size_t num_bytes, char *var_name, int line_num, const char *func_name)
{
    void *p_realloc_location = NULL;
    p_realloc_location = realloc(ptr, num_bytes);
    if (!p_realloc_location)
    {
        printf("Fatal: failed to reallocate %ld bytes for variable '%s' on line '%d' in function '%s': Cannot allocate memory\n", num_bytes, var_name, line_num, func_name);
        return NULL;
    }
    return p_realloc_location;
}

typedef struct {
    char **pp_strings;
    size_t size;
    size_t capacity;
} str_array;

str_array *
safe_malloc_str_array(void)
{
    str_array *p_new_array = (str_array *)safe_malloc(sizeof(str_array), "new_array", __LINE__, __func__);
    if (!p_new_array) {
        return NULL;
    }

    p_new_array->pp_strings = (char **)safe_malloc(sizeof(char *), "p_new_array->pp_strings", __LINE__, __func__);
    if (!p_new_array->pp_strings) {
        return NULL;
    }

    p_new_array->size = 0;
    p_new_array->capacity = 2;

    return p_new_array;
}

int
append_str(str_array *str_arr, char *new_string)
{
    if (!str_arr) {
        return 0;
    }
    printf("Adding: %s\n", new_string);
    if (str_arr->size == str_arr->capacity) {
        // printf("\nReallocing...\n\n");
        char **tmp = (char **)safe_realloc(str_arr->pp_strings, 2 * str_arr->capacity * sizeof(char *), "tmp", __LINE__, __func__);
        if (!tmp) {
            return 0;
        }

        str_arr->pp_strings = tmp;
        str_arr->capacity *= 2;
    }

    // Allocate memory for the new string on the heap
    char *new_str = (char *)safe_malloc(strlen(new_string) + 1, "new_str", __LINE__, __func__);
    if (!new_str) {
        return 0;
    }

    // Copy the new string to the allocated memory
    strcpy(new_str, new_string);

    // Store the pointer to the new string in the array
    str_arr->pp_strings[str_arr->size++] = new_str;

    // str_arr->pp_strings[str_arr->size++] = new_string;
    return 1;
}

void
print_str_array(str_array* str_arr)
{
    for (int idx = 0; idx < str_arr->size; idx++)
    {
        printf("%s\n", str_arr->pp_strings[idx]);
    }
}

void free_str_array(str_array *str_arr)
{
    if (!str_arr)
        return;

    // Free each individual string in the array
    for (size_t i = 0; i < str_arr->size; i++) {
        free(str_arr->pp_strings[i]);
    }

    // Free the array of pointers to strings
    free(str_arr->pp_strings);

    // Free the str_array structure itself
    free(str_arr);
}