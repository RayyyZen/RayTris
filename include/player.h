#ifndef PLAYER_H
#define PLAYER_H

#include "grid.h"
#include "gametime.h"

typedef struct{
    char username[22];
    int clearedLines;
    int numberForms;
    int points[4];
    int score;
}Player;

Player createPlayer(WINDOW *win, int points[4]);
void displayGameKeys(WINDOW *win);
void displayScreen(Grid grid, Timer *timer, Player player, Form currentform, Form nextform, WINDOW **win);
void getFormCoordinates(Grid *grid, Form currentform);
int playerMovement(Grid *grid, Timer *timer, Player *player, Form *currentform, Form nextform, WINDOW *win);
void displayRanking(WINDOW *win, int line, int column);
void displayEndScreen(Grid grid, Timer timer, Player player, Form currentform, Form nextform, WINDOW **win, int ranking);

#endif