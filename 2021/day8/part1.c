#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

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

    char *buffer = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char junk[100];
    char digits[100];
    char *token = NULL;
    int length = 0;
    int count1478 = 0;
    while((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        // printf("%s\n", buffer);
        sscanf(buffer, "%[^|]|%[^\n]\n", junk, digits);
        // printf("%s\t%s\n", junk, digits);
        token = strtok(digits, " ");
        while (token)
        {
            length = strlen(token);
            switch (length)
            {
                case 2: // 1
                    count1478++;
                break;
                case 4: // 4
                    count1478++;
                break;
                case 3: // 7
                    count1478++;
                break;
                case 7: // 8
                    count1478++;
                break;
            }
            // printf("%s\n", token);
            token = strtok(NULL, " ");
        }
    }

    printf("Count of 1,4,7,8: %d\n", count1478);

    free(buffer);
    fclose(p_input_file);
}