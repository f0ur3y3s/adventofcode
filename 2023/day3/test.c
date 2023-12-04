#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char scheme[142][142] = { 0 };

int getparts (int x, int y);
int getgears (int x, int y);
int getnumber (int x, int y);

int main (int argc, char * argv[])
{
    char * filename = "input";
    long   result   = 0;
    int    part     = 1;
    char   buf[145];
    int    x = 0;
    FILE * p_input_file;
    if (argc > 1)
        part = atoi(argv[1]);
    if (argc > 2)
        filename = argv[2];
    if ((p_input_file = fopen(filename, "r")) == NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while (fgets(buf, 145, p_input_file) != NULL)
    {
        buf[140] = '\0';
        strcpy(scheme[++x] + 1, buf);
    }
    if (part == 1)
    {
        for (x = 1; x < 142; x++)
            for (int y = 1; y < 142; y++)
                if (scheme[x][y] != '\0' && scheme[x][y] != '.'
                    && !isdigit(scheme[x][y]))
                    result += getparts(x, y);
    }
    else
        for (x = 1; x < 142; x++)
            for (int y = 1; y < 142; y++)
                if (scheme[x][y] == '*')
                    result += getgears(x, y);
    printf("%ld\n", result);
    return 0;
}

int getparts (int x, int y)
{

    int sum = 0;
    for (int j = x - 1; j < x + 2; j++)
        for (int k = y - 1; k < y + 2; k++)
            if (isdigit(scheme[j][k]))
                sum += getnumber(j, k);
    return sum;
}

int getgears (int x, int y)
{
    int nums = 0;
    int sum  = 0;
    for (int j = x - 1; j < x + 2; j++)
        for (int k = y - 1; k < y + 2; k++)
            if (isdigit(scheme[j][k]))
            {
                if (nums == 0)
                    sum += getnumber(j, k);
                else if (nums == 1)
                    sum *= getnumber(j, k);
                else if (nums == 2)
                    return 0;
                nums++;
            }
    if (nums == 1)
        return 0;
    return sum;
}

int getnumber (int x, int y)
{
    int result;
    while (isdigit(scheme[x][y]))
        y--;
    result = strtol(scheme[x] + (++y), NULL, 10);
    while (isdigit(scheme[x][y]))
        scheme[x][y++] = '.';
    return result;
}