#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "gamefile.h"

#define CHOICES 3
#define MODES 2

#define NEWGAME 0
#define RESUMEGAME 1
#define EXIT 2
#define NORMALMODE 3
#define CUSTOMMODE 4

void displayLeftArrow(WINDOW *win);
void displayRightArrow(WINDOW *win);
void displayNewGame(WINDOW *win);
void displayResumeGame(WINDOW *win);
void displayExit(WINDOW *win);
void displayMenu(WINDOW *win, int choice[CHOICES], int cursor);
int movementMenu(WINDOW *win, int *cursor, int size, int choice, int mode);
void displayNormalMode(WINDOW *win);
void displayCustomMode(WINDOW *win);
void displayMenuKeys(WINDOW *win);
void choiceMenu(int *menuchoice, int *gamemode);
void menu(int *choice, int *mode, Grid *grid, Player *player, Timer *timer, Form form, Form *currentform, Form *nextform);

#endif