#include "library.h"
#include "grid.h"

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

    echo();
    Grid grid=createGrid(win);
    Form newform,form=createForms();
    int height,width;
    form.currentForm=1;
    newform=generateNewForm(form,&height,&width);
    grid.x1=0;
    grid.y1=rand()%(grid.N-width+1);
    grid.x2=height-1;
    grid.y2=grid.y1+width-1;
    mvwprintw(win,10,5,"%d %d %d",newform.currentForm,grid.y1,grid.y2);

    displayGrid(grid,newform,win);
    noecho();

    wgetch(win);
    wclear(win);
    clear();
    delwin(win);
    endwin();
    return 0;
}