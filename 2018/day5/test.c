#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LENGTH  50000

int react(char *polymer)
{
    int reaction = 1;
    while (reaction) {
        reaction = 0;
        for (int i = 0; i < LENGTH - 1; i++)
            if (polymer[i] != ' ') {
                int j = i + 1;
                while (polymer[j] == ' ' && j < LENGTH)
                    j++;
                if (abs(polymer[i] - polymer[j]) == 'a' - 'A') {
                    polymer[i] = polymer[j] = ' ';
                    reaction = 1;
                }
            }
    }

    int count = 0;
    for (int i = 0; i < LENGTH; i++)
        if (polymer[i] != ' ')
                count ++;
    return count;
}

int main()
{
    char *polymer;
    char initpolymer[LENGTH + 1];

    FILE *fp = fopen("./input.txt", "r");
    fgets(initpolymer, sizeof(initpolymer), fp);

    polymer = strndup((char *)initpolymer, LENGTH);
    printf("%d\n", react(polymer));
    free(polymer);

    int min = LENGTH;
    for (int c = 'a'; c <= 'z'; c++) {
        polymer = strndup((char *)initpolymer, LENGTH);
        for (int i = 0 ; i < LENGTH; i++)
            if (polymer[i] == c || polymer[i] == c - ('a' - 'A'))
                polymer[i] = ' ';
        int len = react(polymer);
        if (len < min)
            min = len;
        free(polymer);
    }

    printf("%d\n", min);

    return 0;
}