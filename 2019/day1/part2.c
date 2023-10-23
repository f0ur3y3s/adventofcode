#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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

    size_t len = 0;
    char *buffer = NULL;
    ssize_t read;
    int fuel_sum = 0;

    while((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        int mass = 0;
        sscanf(buffer, "%d\n", &mass);
        fuel_sum += ((mass/3) - 2);
        printf("%d\n", mass);
    }

    free(p_input_file);
    free(buffer);
}