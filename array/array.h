#include <stdlib.h>

#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
    char **pp_strings;
    size_t size;
    size_t capacity;
} str_array;

str_array *safe_malloc_str_array(void);
int append_str(str_array *str_arr, char *new_string);
void print_str_array(str_array* str_arr);
void free_str_array(str_array *str_arr);

#endif

