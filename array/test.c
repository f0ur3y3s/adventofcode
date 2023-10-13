#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include <string.h>
#include <sys/types.h>

int
main(int argc, char *argv[])
{
    FILE *p_input_file;
    p_input_file = fopen("test.txt","r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    str_array *str_arr = safe_malloc_str_array();
    printf("Size: %ld, Capacity: %ld\n", str_arr->size, str_arr->capacity);
    if (!str_arr) {
        exit(EXIT_FAILURE);
    }

    // char* buffer = NULL;
    // size_t len = 0;
    // ssize_t read;
    // while ((read = getline(&buffer, &len, p_input_file)) != -1)
    // {
    //     // copy the buffer into a line
    //     buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
    //     printf("%ld\t%s\n", read, buffer);
    //     buffer = NULL;
    // }
    // free(buffer);

    char* buffer;
    while (fscanf(p_input_file, "%[^\n]\n", buffer) != EOF)
    {
        size_t str_length = strlen(buffer) + 1; // + 1 for null terminator
        printf("%ld\t%s\n", str_length, buffer);
        append_str(str_arr, buffer);
    }

    print_str_array(str_arr);

    fclose(p_input_file);
    free_str_array(str_arr);
}