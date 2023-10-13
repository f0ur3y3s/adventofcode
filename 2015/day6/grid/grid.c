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

void
createGrid(Grid *grid, size_t capacity)
{
    grid->points = (GridPoint **)malloc(capacity * sizeof(GridPoint *));
    for (int i = 0; i < capacity; i++)
    {
        grid->points[i] = (GridPoint *)malloc(capacity * sizeof(GridPoint));
    }
    grid->capacity = capacity;
}

void initLights(Grid *grid)
{
    for (int x = 0; x < grid->capacity; x++)
    {
        for (int y = 0; y < grid->capacity; y++)
        {
            grid->points[x][y].brightness = 0;
        }
    }
}

void changeBrightness(GridPoint *point, int change)
{
    if (point->brightness + change < 0)
    {
        return;
    }
    else
    {
        point->brightness += change;
    }
}

void toggleLight(Grid *grid, int x, int y)
{
    // increase brightness by 2
    changeBrightness(&(grid->points[x][y]), 2);
    // grid->points[x][y].brightness = !grid->points[x][y].brightness;
}

void turnOn(Grid *grid, int x, int y)
{
    // increase brightness by 1
    changeBrightness(&(grid->points[x][y]), 1);
    // grid->points[x][y].brightness = 1;
}

void turnOff(Grid *grid, int x, int y)
{
    // decrease brightness by 1
    changeBrightness(&(grid->points[x][y]), -1);
    // grid->points[x][y].brightness = 0;
}

int countLightsOn(Grid *grid)
{
    int count = 0;
    for (int x = 0; x < grid->capacity; x++)
    {
        for (int y = 0; y < grid->capacity; y++)
        {
            if (grid->points[x][y].brightness)
            {
                count++;
            }
        }
    }
    return count;
}

int totalBrightness(Grid *grid)
{
    int brightness = 0;
    for (int x = 0; x < grid->capacity; x++)
    {
        for (int y = 0; y < grid->capacity; y++)
        {
            brightness += grid->points[x][y].brightness;
        }
    }
    return brightness;
}

void freeGrid(Grid *grid)
{
    for (int i = 0; i < grid->capacity; i++)
    {
        free(grid->points[i]);
    }
    free(grid->points);
}