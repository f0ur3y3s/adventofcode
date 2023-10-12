#include <stdio.h>
#include <stdlib.h>

int
calcSurface(int l, int w, int h)
{
    return ((2*l*w) + (2*w*h) + (2*h*l));
}

int
findSmallestSide(int l, int w, int h)
{
    int surfaceAreas[3];

    surfaceAreas[0] = (l * w);
    surfaceAreas[1] = (w * h);
    surfaceAreas[2] = (h * l);

    int minSurfaceArea = surfaceAreas[0];
    for (int i = 1; i < 3; i++) {
        if (surfaceAreas[i] < minSurfaceArea) {
            minSurfaceArea = surfaceAreas[i];
        }
    }

    return minSurfaceArea;
}

int
calcRibbon(int l, int w, int h)
{
    int min1 = 0;
    int min2 = 0;
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

    int length = 0;
    int width = 0;
    int height = 0;
    int total = 0;
    while (fscanf(p_input_file, "%dx%dx%d\n", &length, &width, &height) != EOF)
    {
        total += (calcSurface(length, width, height) + findSmallestSide(length, width, height));
    }
    printf("Total required: %d\n", total);
}