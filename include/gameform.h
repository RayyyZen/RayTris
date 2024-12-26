#ifndef GAMEFORM_H
#define GAMEFORM_H

#include "library.h"

#define NUMBERFORMS 7
#define DIMENSION 4

#define IFORM 1
#define JFORM 2
#define LFORM 3
#define OFORM 4
#define SFORM 5
#define ZFORM 6
#define TFORM 7

typedef struct{
    int tab[NUMBERFORMS][DIMENSION][DIMENSION];
    int currentForm;
    int height;
    int width;
}Form;

Form createForms();
void rotateForm(int tab[DIMENSION][DIMENSION]);
void shiftFormLeftUp(int tab[DIMENSION][DIMENSION]);
void getFormDimensions(int tab[DIMENSION][DIMENSION], int *height, int *width);
Form generateNewForm(Form form);

#endif