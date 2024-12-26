#ifndef PLAYER_H
#define PLAYER_H

#include "library.h"
#include "grid.h"
#include "gametime.h"
#include <time.h>

typedef struct{
    char username[30];
    int clearedLines;
    int numberForms;
    int points[4];
    int score;
}Player;

Player createPlayer(WINDOW *win, int points[4]);
void displayScreen(Grid grid, Timer *timer, Player player, Form currentform, Form nextform, WINDOW **win);
void getFormCoordinates(Grid *grid, Form currentform);
int playerMovement(Grid *grid, Timer *timer, Player *player, Form currentform, Form nextform, WINDOW *win);

#endif