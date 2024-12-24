#ifndef GRID_H
#define GRID_H

#include "library.h"
#include "gameform.h"

#define MINHEIGHT 10
#define MAXHEIGHT 18
#define MINWIDTH 30
#define MAXWIDTH 60

typedef struct{
    int **tab;
    int M;
    int N;
    int x1;
    int y1;
    int x2;
    int y2;
}Grid;

int absoluteValue(int value);
int stringToInteger(char string[3], int min, int max);
Grid createGrid(WINDOW *win);
void displayGrid(Grid grid, Form form, WINDOW *win);

#endif