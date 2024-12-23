#include "library.h"

int main(){
    initscr();
    curs_set(0);
    //To remove the mark of the cursor
    clear();
    //To reset the display, and it is essential before every display
    keypad(stdscr, TRUE);
    //To activate the special keys as KEY_DOWN, KEY_UP ....
    noecho();
    initializeColor();
    srand(time(NULL));

    WINDOW *win =newwin(BOXLINES,BOXCOLUMNS,0,0);
    //To create a new window
    keypad(win,TRUE);

    wgetch(win);
    wclear(win);
    clear();
    delwin(win);
    endwin();
    return 0;
}