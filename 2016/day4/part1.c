#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char letter;
    int count;
} letter_count;



void
breakApart(char *str, char *name, int *sector_id, char *checksum)
{
    char *token;
    token = strtok(str, "-");
    while (token != NULL)
    {
        if (strchr(token, '[') != NULL)
        {
            sscanf(token, "%d[%[^]]]", sector_id, checksum);
            break;
        }
        else
        {
            strcat(name, token);
        }
        token = strtok(NULL, "-");
    }
}

int compare(const void *a, const void *b)
{
    letter_count *letter_a = (letter_count *)a;
    letter_count *letter_b = (letter_count *)b;
    if (letter_a->count == letter_b->count)
    {
        return letter_a->letter - letter_b->letter;
    }
    else
    {
        return letter_b->count - letter_a->count;
    }
}

void
countLetters(char *name, char *result)
{
    letter_count letters[26];
    for (int i = 0; i < 26; i++)
    {
        letters[i].letter = 'a' + i;
        letters[i].count = 0;
    }

    for (int i = 0; i < strlen(name); i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (name[i] == letters[j].letter)
            {
                letters[j].count++;
            }
        }
    }
    qsort(letters, 26, sizeof(letter_count), compare);
    for (int idx = 0; idx < 5; idx++)
    {
        result[idx] = letters[idx].letter;
    }
    result[5] = '\0';
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

    char name[256];
    int sector_id;
    char checksum[256];
    char str[256];
    char *token;
    int total_rooms = 0;
    char result[6];

    for (;;)
    {
        int ret = fscanf(p_input_file, "%s\n", str);
        if (ret == EOF)
        {
            break;
        }

        breakApart(str, name, &sector_id, checksum);
        countLetters(name, result);
        if (strcmp(checksum, result) == 0)
        {
            total_rooms += sector_id;
        }
        // printf("Calculated checksum: %s\n", result);
        // printf("%s\t%s\n", name, checksum);
        // printf("Digit: %d\n", sector_id);
        memset(str, 0, sizeof(str));
        memset(name, 0, sizeof(name));
        memset(result, 0, sizeof(result));
    }
    printf("Total rooms: %d\n", total_rooms);
}