#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

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

void remove_unit(char *p_polymer, size_t *polymer_size, char *removal_char)
{
    int idx_to_remove = 0;
    while (idx_to_remove < *polymer_size) {
        if (p_polymer[idx_to_remove] == *removal_char || p_polymer[idx_to_remove] == *removal_char - 32) {
            memmove(&p_polymer[idx_to_remove], &p_polymer[idx_to_remove + 1], *polymer_size - idx_to_remove);
            (*polymer_size)--;
        } 
        else {
            idx_to_remove++;
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

    char letter_arr[27] = {0};
    char *p_copy_polymer = NULL;
    ssize_t copy_read = 0;
    for (int idx = 'a'; idx <= 'z'; idx++)
    {
        copy_read = read;
        p_copy_polymer = strdup(p_polymer);
        char removal = idx;
        // printf("Before removal: %c\t%ld\n", removal, copy_read);
        remove_unit(p_copy_polymer, &copy_read, &removal);
        // printf("After removal: %c\t%ld\n", removal, copy_read);
        scan_polymer(p_copy_polymer, &copy_read);
        printf("%c\t%ld\n", removal, copy_read);
        letter_arr[idx] = copy_read;
        free(p_copy_polymer);
    }

    fclose(p_input_file);
    free(p_polymer);
}


// 4992