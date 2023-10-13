#include <stdio.h>
#include <stdlib.h>
#include "wordlist.h"
#include <string.h>
#include <sys/types.h>

int
main(int argc, char *argv[])
{
    FILE *p_input_file;
    p_input_file = fopen("test.txt","r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    wordlist_t *wordlist = wordlist_create();
    printf("Size: %ld, Capacity: %ld\n", wordlist->size, wordlist->capacity);
    if (!wordlist) {
        exit(EXIT_FAILURE);
    }

    char buffer[64];
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        size_t str_length = strlen(buffer) + 1; // + 1 for null terminator
        printf("%ld\t%s\n", str_length, buffer);
        wordlist_append(wordlist, buffer);
    }

    wordlist_print(wordlist);

    fclose(p_input_file);
    wordlist_free(wordlist);
}