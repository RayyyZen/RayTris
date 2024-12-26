#include "library.h"
#include "grid.h"
#include "player.h"
#include "gamemenu.h"

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
    int choice=-1,mode=-1;
    menu(&choice,&mode,&grid,&player,&timer,form,&currentform,&nextform);
    noecho();

    char fileNameGame[20],fileNameArray[20];

    if(choice==EXIT){
        clear();
        endwin();
        return 0;
    }
    else if(choice==NEWGAME){
        getFormCoordinates(&grid,currentform);
    }

    if(mode==NORMALMODE){
        strcpy(fileNameGame,"normalGame.bin");
        strcpy(fileNameArray,"normalArray.bin");
    }
    else if(mode==CUSTOMMODE){
        strcpy(fileNameGame,"customGame.bin");
        strcpy(fileNameArray,"customArray.bin");
    }

    WINDOW *win =newwin(BOXLINES,BOXCOLUMNS,0,0);
    //To create a new window
    wbkgd(win, COLOR_PAIR(1));

    keypad(win,TRUE);

    int delete=0,movement=0;

    do{
        movement=playerMovement(&grid,&timer,&player,currentform,nextform,win);
        if(movement==-1){
            break;
        }
        player.numberForms++;
        grid.x1=-1;
        grid.x2=-1;
        grid.y1=-1;
        grid.y2=-1;
        delete=deleteLine(&grid,player,&timer,currentform,nextform,win);
        player.clearedLines+=delete;
        if(delete!=0){
            player.score+=player.points[delete-1];
        }

        if(loseCondition(grid)!=0){
            break;
        }
        currentform=nextform;
        getFormCoordinates(&grid,currentform);
        nextform=generateNewForm(form);
    }while(loseCondition(grid)==0);

    //Faut que je change cette ligne de sorte a ce que le currentform ne se voit pas car sinon il y a un petit bug d affichage
    displayScreen(grid,&timer,player,currentform,nextform,&win);
    wtimeout(win,-1);
    wgetch(win);

    if(movement!=-1){
        if(existFile("topScores.txt")==0){
            FILE *file=fopen("topScores.txt","w");
            if(file==NULL){
                exit(204);
            }
            fclose(file);
        }
        addFileScore("topScores.txt",player);
        removeSaves(fileNameGame,fileNameArray);
    }
    else{
        saveArray(grid,fileNameArray);
        destroyGrid(&grid);
        saveGame(grid,player,timer,currentform,nextform,fileNameGame);
    }

    wclear(win);
    clear();
    delwin(win);
    endwin();
    return 0;
}