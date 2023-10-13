#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <sys/types.h>

typedef struct
{
    int brightness;
} GridPoint;

typedef struct
{
    GridPoint **points;
    size_t     capacity;
} Grid;


void createGrid(Grid *grid, size_t capacity);
void initLights(Grid *grid);
void toggleLight(Grid *grid, int x, int y);
void turnOn(Grid *grid, int x, int y);
void turnOff(Grid *grid, int x, int y);
int countLightsOn(Grid *grid);
int totalBrightness(Grid *grid);
void freeGrid(Grid *grid);

#endif  // GRID_H