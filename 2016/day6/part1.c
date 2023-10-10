#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 8

typedef struct {
    char letter;
    int count;
} letter_count;

typedef struct {
    letter_count letters[26];
} message;

void
initLetters(message *message_letters)
{
    for (int i = 0; i < MAX_LINE_LENGTH; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            message_letters[i].letters[j].letter = 'a' + j;
            message_letters[i].letters[j].count = 0;
        }
    }
}

int
compare(const void *a, const void *b)
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
countLetters(char *name, message *message_letters)
{
    for (int i = 0; i < MAX_LINE_LENGTH; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (name[i] == message_letters[i].letters[j].letter)
            {
                message_letters[i].letters[j].count++;
            }
        }
    }
    for (int i = 0; i < MAX_LINE_LENGTH; i++)
    {
        qsort(message_letters[i].letters, 26, sizeof(letter_count), compare);
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

    message message_letters[MAX_LINE_LENGTH];
    initLetters(message_letters);

    char line[MAX_LINE_LENGTH];

    while (fscanf(p_input_file, "%s\n", line) != EOF)
    {
        countLetters(line, message_letters);
        // printf("%s\n", line);
    }
    for (int idx = 0; idx < MAX_LINE_LENGTH; idx++)
    {
        printf("%c", message_letters[idx].letters[0].letter);
    }
    printf("\n");
}