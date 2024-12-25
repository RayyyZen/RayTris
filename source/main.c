#include "library.h"
#include "grid.h"
#include "player.h"

int main(){
    setlocale(LC_ALL, "");
    initscr();
    //cbreak();
    curs_set(0);
    //To remove the mark of the cursor
    clear();
    //To reset the display, and it is essential before every display
    keypad(stdscr, TRUE);
    //To activate the special keys as KEY_DOWN, KEY_UP ....
    noecho();
    srand(time(NULL));
    initializeColor();

    WINDOW *win =newwin(BOXLINES,BOXCOLUMNS,0,0);
    //To create a new window
    wbkgd(win, COLOR_PAIR(1));

    keypad(win,TRUE);

    echo();

    Grid grid=createGrid(win);
    Form form=createForms();
    Timer timer;
    Player player;
    noecho();
    timer.speed=100;
    do{
        playerMovement(&grid,&timer,&player,form,win);
        grid=deleteLine(grid);
    }while(loseCondition(grid)==0);

    wtimeout(win,-1);
    wgetch(win);
    wclear(win);
    clear();
    delwin(win);
    endwin();
    return 0;
}