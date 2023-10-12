#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkVowels(char *string, int length)
{
    int count_vowels = 0;
    for (int idx = 0; idx < length; idx++)
    {
        if (string[idx] == 'a' || string[idx] == 'e' || string[idx] == 'i' || string[idx] == 'o' || string[idx] == 'u')
        count_vowels++;
    }
    return count_vowels;
}

int checkTwice(char *string, int length)
{
    for (int idx = 0; idx < length-1; idx++)
    {
        if (string[idx] == string[idx+1])
        {
            return 1;
        }
    }
    return 0;
}

int checkDisallowed(char *string, int length)
{
    // ab, cd, pq, or xy
    for (int idx = 0; idx < length-1; idx++)
    {
        if (!strstr(string, "ab") && !strstr(string, "cd") && !strstr(string, "pq") && !strstr(string, "xy"))
        {
            return 1;
        }
    }
    return 0;
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

    char buffer[64];
    int count_nice = 0;
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        size_t length = strlen(buffer);
        if (checkVowels(buffer, length) >= 3)
        {
            if (checkTwice(buffer, length))
            {
                if (checkDisallowed(buffer, length))
                {
                    count_nice++;
                    // printf("%s\n", buffer);
                }
            }
        }
    }
    printf("%d\n", count_nice);
}