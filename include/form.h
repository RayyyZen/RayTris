#ifndef FORM_H
#define FORM_H

#include "library.h"

#define FORMS 8
#define DIMENSION 4

typedef struct{
    int tab[FORMS][DIMENSION][DIMENSION];
    int currentForm;
}Form;

#endif