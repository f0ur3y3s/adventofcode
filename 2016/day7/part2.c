#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char a;
    char b;
} aba;

typedef struct {
    aba *subnet;
    aba *hypernet;
    size_t subnet_size;
    size_t subnet_capacity;
    size_t hypernet_size;
    size_t hypernet_capacity;
} abas;

void
createABAs(abas *abas)
{
    abas->subnet = (aba *)malloc(2 * sizeof(aba));
    if (abas->subnet == NULL)
    {
        printf("Error allocating memory for subnet aba.\n");
        exit(EXIT_FAILURE);
    }
    abas->hypernet = (aba *)malloc(2 * sizeof(aba));
    if (abas->hypernet == NULL)
    {
        printf("Error allocating memory for hypernet aba.\n");
        exit(EXIT_FAILURE);
    }
    abas->subnet_size = 0;
    abas->subnet_capacity = 2;
    abas->hypernet_size = 0;
    abas->hypernet_capacity = 2;
}

void
resetABAs(abas *abas)
{
    free(abas->subnet);
    free(abas->hypernet);
    createABAs(abas);
}

void
addHypernetABA(abas *abas, char a, char b)
{
    if (abas->hypernet_size == abas->hypernet_capacity)
    {
        abas->hypernet_capacity *= 2;
        abas->hypernet = (aba *)realloc(abas->hypernet, abas->hypernet_capacity * sizeof(aba));
        if (abas->hypernet == NULL)
        {
            printf("Error reallocating memory for hypernet aba.\n");
            exit(EXIT_FAILURE);
        }
    }
    abas->hypernet[abas->hypernet_size].a = a;
    abas->hypernet[abas->hypernet_size].b = b;
    abas->hypernet_size++;
}

void
addSubnetABA(abas *abas, char a, char b)
{
    if (abas->subnet_size == abas->subnet_capacity)
    {
        abas->subnet_capacity *= 2;
        abas->subnet = (aba *)realloc(abas->subnet, abas->subnet_capacity * sizeof(aba));
        if (abas->subnet == NULL)
        {
            printf("Error reallocating memory for subnet aba.\n");
            exit(EXIT_FAILURE);
        }
    }
    abas->subnet[abas->subnet_size].a = a;
    abas->subnet[abas->subnet_size].b = b;
    abas->subnet_size++;
}

void
checkAddABAHypernet(char *str, size_t length, abas *master_abas, aba *aba)
{
    for (int idx = 0; idx < length-2; idx++)
    {
        if (str[idx] == str[idx+2] && str[idx] != str[idx+1])
        {
            addHypernetABA(master_abas, str[idx], str[idx+1]);
        }
    }
}

void
checkAddABASubnet(char *str, size_t length, abas *master_abas, aba *aba)
{
    for (int idx = 0; idx < length-2; idx++)
    {
        if (str[idx] == str[idx+2] && str[idx] != str[idx+1])
        {
            addSubnetABA(master_abas, str[idx], str[idx+1]);
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

    int count_ssl = 0;
    char line[256];
    char *token;
    int hypernet = 0;

    abas abas;

    while (fscanf(p_input_file, "%s\n", line) != EOF)
    {
        resetABAs(&abas);
        hypernet = 0;
        token = strtok(line, "[]");

        while (token != NULL)
        {
            if (hypernet)
            {
                checkAddABAHypernet(token, strlen(token), &abas, abas.hypernet);
            }
            else
            {
                checkAddABASubnet(token, strlen(token), &abas, abas.subnet);
            }
            hypernet = !hypernet;
            token = strtok(NULL, "[]");
        }

        int ssl_found = 0;
        for (int idx = 0; idx < abas.hypernet_size; idx++)
        {
            for (int jdx = 0; jdx < abas.subnet_size; jdx++)
            {
                if (abas.hypernet[idx].a == abas.subnet[jdx].b && abas.hypernet[idx].b == abas.subnet[jdx].a)
                {
                    ssl_found = 1;
                    break;
                }
            }
            if (ssl_found)
            {
                break;
            }
        }
        if (ssl_found)
        {
            count_ssl++;
        }
    }
    printf("SSL count: %d\n", count_ssl);
    free(abas.subnet);
    free(abas.hypernet);
    fclose(p_input_file);
    exit(EXIT_SUCCESS);
}
