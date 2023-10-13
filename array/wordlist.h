#include <stdlib.h>

#ifndef WORDLIST_H
#define WORDLIST_H

typedef struct {
    char **words;
    size_t size;
    size_t capacity;
} wordlist_t;

wordlist_t* wordlist_create(void);
int wordlist_append(wordlist_t *str_arr, char *new_string);
void wordlist_print(wordlist_t* str_arr);
void wordlist_free(wordlist_t *str_arr);

#endif

