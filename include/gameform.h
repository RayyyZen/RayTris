#ifndef GAMEFORM_H
#define GAMEFORM_H

#include "library.h"

#define NUMBERFORMS 7
#define DIMENSION 4

typedef struct{
    int tab[NUMBERFORMS][DIMENSION][DIMENSION];
    int currentForm;
}Form;

Form createForms();
void rotateForm(int tab[DIMENSION][DIMENSION]);
void shiftFormLeftUp(int tab[DIMENSION][DIMENSION]);
void getFormDimensions(int tab[DIMENSION][DIMENSION], int *height, int *width);
Form generateNewForm(Form form, int *height, int *width);

#endif