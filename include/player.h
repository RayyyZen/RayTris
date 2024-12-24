#ifndef PLAYER_H
#define PLAYER_H

#include "library.h"
#include "grid.h"
#include "gametime.h"

typedef struct{
    char username[30];
    int clearedLine;
    int numberForms;
}Player;

void playerMovement(Grid *grid, Timer *timer, Player *player, Form form, WINDOW *win);

#endif