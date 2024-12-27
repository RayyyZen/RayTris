#ifndef GRID_H
#define GRID_H

#include "gameform.h"

#define MINHEIGHT 10
#define MAXHEIGHT 18
#define MINWIDTH 10
#define MAXWIDTH 25

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
int** createArray(int height, int width);
Grid createGrid(WINDOW *win);
void displayEmoji(WINDOW *win, int x, int y, int form);
void displayGrid(Grid grid, Form form, WINDOW *win);
Grid gravityEffect(Grid grid, int line);
int deleteLine(Grid *grid);
int loseCondition(Grid grid);

#endif