#include <stdio.h>
#include <stdlib.h>



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

    int count_double = 0;
    int count_triple = 0;
    char buffer[100];
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        int letters[27] = {0};
        int idx = 0;
        int local_double = 0;
        int local_triple = 0;
        while (buffer[idx] != '\0')
        {
            // printf("%d\n", buffer[idx] - 'a');
            letters[buffer[idx] - 'a'] += 1;
            idx++;
        }
        for (int lidx = 0; lidx < 27; lidx++)
        {
            if (0 == local_double && 2 == letters[lidx])
            {
                local_double = 1;
            }
            if (0 == local_triple && 3 == letters[lidx])
            {
                local_triple = 1;
            }
        }
        count_double += local_double;
        count_triple += local_triple;
    }
    printf("Count double: %d\n", count_double);
    printf("Count triple: %d\n", count_triple);
    printf("Checksum: %d\n", count_double * count_triple);
}