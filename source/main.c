#include "library.h"
#include "grid.h"
#include "player.h"
#include "menu.h"

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

    Player player;
    Grid grid;
    Form form=createForms(),nextform,currentform;
    Timer timer;

    if(menu(&grid,&player,&timer,form,&currentform,&nextform)==-1){
        clear();
        endwin();
        return 0;
    }

    WINDOW *win =newwin(BOXLINES,BOXCOLUMNS,0,0);
    //To create a new window
    wbkgd(win, COLOR_PAIR(1));

    keypad(win,TRUE);

    int delete=0;

    do{
        playerMovement(&grid,&timer,&player,currentform,nextform,win);
        player.numberForms++;
        delete=deleteLine(&grid);
        player.clearedLines+=delete;
        if(delete!=0){
            player.score+=player.points[delete-1];
        }

        if(loseCondition(grid)!=0){
            break;
        }
        currentform=nextform;
        nextform=generateNewForm(form);
    }while(loseCondition(grid)==0);

    //Faut que je change cette ligne de sorte a ce que le currentform ne se voit pas car sinon il y a un petit bug d affichage
    displayScreen(grid,&timer,player,currentform,nextform,&win);
    wtimeout(win,-1);
    wgetch(win);
    wclear(win);
    clear();
    delwin(win);
    endwin();
    return 0;
}