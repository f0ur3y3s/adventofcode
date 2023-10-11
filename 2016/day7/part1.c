#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int
contains_abba(char *str, size_t length)
{
    for (int idx = 0; idx < length-3; idx++)
    {
        if (str[idx] == str[idx+3] && str[idx+1] == str[idx+2] && str[idx] != str[idx+1])
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

    int count_tls = 0;
    char line[256];

    int hypernet = 0;
    int has_abba = 0;
    char *token;


    while (fscanf(p_input_file, "%s\n", line) != EOF)
    {

        hypernet = 0;
        token = strtok(line, "[]");

        while (token != NULL)
        {
            int abba_found = contains_abba(token, strlen(token));
            if (abba_found)
            {
                has_abba = 1;
                if (hypernet)
                {
                    has_abba = 0;
                    token = NULL;
                    break;
                }
            }
            hypernet = !hypernet;
            token = strtok(NULL, "[]");
        }
       
        if (has_abba == 1)
        {
            count_tls++;
            has_abba = 0;
        }
    }
    printf("TLS count: %d\n", count_tls);
}