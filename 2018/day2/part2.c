#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
    char **words;
    size_t size;
    size_t capacity;
} wordlist_t;

wordlist_t *wordlist_create()
{
    wordlist_t *new_wordlist = malloc(sizeof(wordlist_t));
    new_wordlist->size = 0;
    new_wordlist->capacity = 2;
    new_wordlist->words = malloc(new_wordlist->capacity * sizeof(char *));
    return new_wordlist;
}

int wordlist_add(wordlist_t *wordlist, char *word, size_t wordlen)
{
    if (wordlist->size == wordlist->capacity)
    {
        char **tmp = realloc(wordlist->words, wordlist->capacity * 2 * sizeof(char *));
        wordlist->words = tmp;
        wordlist->capacity *= 2;
    }

    // memcpy(wordlist->words[wordlist->size], word, wordlen);
    wordlist->words[wordlist->size] = strdup(word);
    wordlist->size++;
    return 1;
}

void wordlist_print(wordlist_t* wordlist)
{
    for (size_t idx = 0; idx < wordlist->size; idx++)
    {
        printf("Location: %p\t%s\n", &(wordlist->words[idx]), wordlist->words[idx]);
    }
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

    wordlist_t *wordlist;
    wordlist = wordlist_create();
    printf("Created wordlist\n");

    char *buffer = NULL;
    size_t size;
    ssize_t read;

    while ((read = getline(&buffer, &size, p_input_file)) > 0)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        // printf("Buffer: %s\n", buffer);
        // printf("Appending: %ld\t%s\n", strlen(buffer), buffer);
        wordlist_add(wordlist, buffer, strlen(buffer));
    }

    wordlist_print(wordlist);

    for (int widx = 0; widx < wordlist->size; widx++)
    {
        char *p_word = wordlist->words[widx];
        for (int idx = 0; idx < wordlist->size; idx++)
        {
            int difference = 0;
            char *b_word = wordlist->words[idx];
            for (int cidx = 0; cidx < strlen(p_word); cidx++)
            {
                if (p_word[cidx] != b_word[cidx])
                {
                    difference++;
                }
            }
            // printf("Difference: %d\n%s\n%s\n", difference, p_word, b_word);
            // wordlist_compare(wordlist->words[idx]);
            if (difference == 1)
            {
                printf("Found one letter difference\n%s\n%s\n", p_word, b_word);
            }
        }
    }
}

nvosmkcdtdbfhyxsphzgrraljq
nvosmkcdtdbfhyxsphzgraljq