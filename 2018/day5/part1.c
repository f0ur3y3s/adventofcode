#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void
scan_polymer(char *p_polymer, size_t *polymer_size)
{
    for (int idx = 0; idx < *polymer_size - 1; idx++)
    {
        char current_char = p_polymer[idx];
        char next_char = p_polymer[idx + 1];
        if (current_char == next_char)
        {
            continue;
        }
        else if (current_char == next_char + 32 || current_char == next_char - 32)
        {
            for (int jdx = idx; jdx < *polymer_size - 2; jdx++)
            {
                p_polymer[jdx] = p_polymer[jdx + 2];
            }
            p_polymer[*polymer_size - 2] = '\0';
            *polymer_size -= 2;
            scan_polymer(p_polymer, polymer_size);
            return;
        }
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

    char *p_polymer;
    size_t polymer_size = 0;
    ssize_t read = 0;
    read = getline(&p_polymer, &polymer_size, p_input_file);
    if (read == -1)
    {
        printf("Error reading file.\n");
        exit(EXIT_FAILURE);
    }

    scan_polymer(p_polymer, &read);
    printf("%s\t%ld\n", p_polymer, read);

    fclose(p_input_file);
    free(p_polymer);
}