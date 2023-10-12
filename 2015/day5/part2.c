#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkPairTwice(char *string, int length)
{
    char test[2];
    char substring[length+1]; // +1 for null terminator
    for (int idx = 0; idx < length-3; idx++)
    {
        strncpy(substring, string+idx+2, length-idx);
        substring[length-idx] = '\0';
        test[0] = string[idx];
        test[1] = string[idx+1];
        if (strstr(substring, test) != NULL) {
            return 1;
        }
    }
    return 0;
}

int checkPalindrome(char *string, int length)
{
    char substring[3];
    for (int idx = 0; idx < length-2; idx++)
    {
        strncpy(substring, string+idx, 3);
        if (substring[0] == substring[2] && substring[0] != substring[1])
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
        if (checkPairTwice(buffer, length))
        {
            if (checkPalindrome(buffer, length))
            {
                count_nice++;
            }
        }

    }
    printf("%d\n", count_nice);
}