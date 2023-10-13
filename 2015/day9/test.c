#include <stdio.h>
#include <string.h>
#include "array/array.h"

#define MAX_LINE_LENGTH 100

int main() {
    FILE *file = fopen("test.txt", "r");
    if (!file) {
        printf("Failed to open the file.\n");
        return 1;
    }

    str_array *city_names = safe_malloc_str_array();

    if (!city_names) {
        printf("Failed to initialize the city names array.\n");
        fclose(file);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char city1[MAX_LINE_LENGTH];
        char city2[MAX_LINE_LENGTH];
        int distance;

        if (sscanf(line, "%s to %s = %d", city1, city2, &distance) != 3) {
            printf("Invalid line: %s\n", line);
            continue;
        }

        // Check if city1 is already in the array, and add it if not
        int found = 0;
        for (size_t i = 0; i < city_names->size; i++) {
            if (strcmp(city_names->pp_strings[i], city1) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (!append_str(city_names, city1)) {
                printf("Failed to append city name to array.\n");
                break;
            }
        }

        // Check if city2 is already in the array, and add it if not
        found = 0;
        for (size_t i = 0; i < city_names->size; i++) {
            if (strcmp(city_names->pp_strings[i], city2) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (!append_str(city_names, city2)) {
                printf("Failed to append city name to array.\n");
                break;
            }
        }
    }

    fclose(file);

    // Print the city names in the array
    printf("City Names:\n");
    print_str_array(city_names);

    // Free the memory used by the city_names array
    free_str_array(city_names);

    return 0;
}
