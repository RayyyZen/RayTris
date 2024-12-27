#ifndef GAMEFILE_H
#define GAMEFILE_H

#include "player.h"

typedef struct{
    Grid grid;
    Player player;
    Timer timer;
    Form currentform;
    Form nextform;
}Game;

void saveArray(Grid grid, char *fileName);
void destroyGrid(Grid *grid);
void saveGame(Grid grid, Player player, Timer timer, Form currentform, Form nextform, char *fileName);
void recoverArray(Grid *grid, char *fileName);
void recoverGame(Grid *grid, Player *player, Timer *timer, Form *currentform, Form *nextform, char *fileName);
void removeSaves(char *fileName1, char *fileName2);
int existFile(char *fileName);
void addFileScore(char *fileName, Player player);

#endif