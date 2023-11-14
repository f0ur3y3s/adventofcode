#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "intarr/intarr.h"
#include <limits.h>
#include <string.h>

void
find_min_max(intarr_t *row, int *min, int *max)
{
    int local_min = INT_MAX;
    int local_max = INT_MIN;

    for (int idx = 0; idx < row->size; idx++)
    {
        if (row->values[idx] < local_min)
        {
            local_min = row->values[idx];
        }
        if (row->values[idx] > local_max)
        {
            local_max = row->values[idx];
        }
    }
    *min = local_min;
    *max = local_max;
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
    p_input_file = fopen(argv[1], "r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    // scan each row of the spreadsheet
    size_t    len        = 0;
    ssize_t   read       = 0;
    char     *buffer     = 0;
    intarr_t *row        = NULL;
    char     *token      = NULL;
    int       min        = 0;
    int       max        = 0;
    int       difference = 0;
    int       checksum   = 0;
    while ((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        row                           = intarr_create();
        token                         = strtok(buffer, "\t");
        while (token)
        {
            // printf("%s\n", token);
            intarr_add(row, atoi(token));
            token = strtok(NULL, "\t");
        }
        intarr_print(row);
        difference = max - min;
        checksum += difference;
        intarr_free(row);
    }
    printf("checksum: %d\n", checksum);

    // populate the inarr with each row of the spreadsheet
    // get min and max from the intarr
    // find difference, add to checksum
}