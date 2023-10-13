#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
        char **words;
        size_t size;
        size_t capacity;
} wordlist;

wordlist *wordlist_create(void)
{
        wordlist *wl = malloc(sizeof(*wl));
        if (!wl) {
                return NULL;
        }

        // 8 seems like a reasonable starting capacity
        wl->capacity = 8;
        wl->size = 0;

        wl->words = malloc(wl->capacity * sizeof(*wl->words));
        if (!wl->words) {
                // Remember to free any partial allocations
                free(wl);
                return NULL;
        }

        return wl;
}


bool wordlist_append(wordlist *wl, const char *s)
{
        if (!wl) {
                return false;
        }
        if (wl->size == wl->capacity) {
                char **tmp = realloc(wl->words, 2 * wl->capacity * (strlen(s)+1));
                if (!tmp) {
                        return false;
                }

                wl->words = tmp;
                wl->capacity *= 2;
        }

        wl->words[wl->size] = strdup(s);
        // Confirm that `strdup` succeeded
        if (!wl->words[wl->size]) {
                return false;
        }

        wl->size++;
        return true;
}

void wordlist_print(const wordlist *wl)
{
    if (!wl) {
            return;
    }

    for (size_t n=0; n < wl->size; ++n) {
            printf("%s\n", wl->words[n]);
    }
}

void wordlist_destroy(wordlist *wl)
{
    if (!wl) {
            return;
    }

    for (size_t n=0; n < wl->size; ++n) {
            free(wl->words[n]);
    }

    free(wl->words);
    free(wl);
}


void main(void)
{
    wordlist* list = wordlist_create();
    FILE *p_input_file;
    p_input_file = fopen("test.txt","r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    char* buffer;
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        wordlist_append(list, buffer);
    }


    fclose(p_input_file);
    wordlist_print(list);
    wordlist_destroy(list);
}
