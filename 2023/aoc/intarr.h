#ifndef INTARR_H
#define INTARR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *  values;
    size_t size;
    size_t capacity;
} intarr_t;

intarr_t * intarr_create (void);
void       intarr_add (intarr_t * p_intarr, int new_value);
void       intarr_print (intarr_t * p_intarr);
void       intarr_destroy (intarr_t * p_intarr);
#endif