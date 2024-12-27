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

    WINDOW *win=newwin(BOXLINES,BOXCOLUMNS,0,0);
    Player player;
    Grid grid;
    Form form=createForms(),nextform,currentform;
    Timer timer;
    int choice=-1,mode=-1,delete=0,movement=0,counter=0,car=0;
    char fileNameGame[20],fileNameArray[20];
    struct timespec ts;
    ts.tv_sec = 0;           // Secondes
    ts.tv_nsec = 200 * 1000000L; // 200 millisecondes en nanosecondes

    do{

        menu(&choice,&mode,&grid,&player,&timer,form,&currentform,&nextform);
        noecho();

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

        movement=0;

        do{
            if(playerMovement(&grid,&timer,&player,currentform,nextform,win)==-1){
                movement=-1;
                break;
            }
            player.numberForms++;
            grid.x1=-1;
            grid.x2=-1;
            grid.y1=-1;
            grid.y2=-1;
            counter=0;
            do{
                delete=deleteLine(&grid);
                displayScreen(grid,&timer,player,currentform,nextform,&win);
                nanosleep(&ts, NULL);
                counter+=delete;
            }while(delete!=0);
            player.clearedLines+=counter;
            if(counter!=0){
                player.score+=player.points[counter-1];
            }

            if(loseCondition(grid)==0){
                currentform=nextform;
                getFormCoordinates(&grid,currentform);
                nextform=generateNewForm(form);
            }

        }while(loseCondition(grid)==0);

        if(movement!=-1){
            if(mode==NORMALMODE && existFile("topScores.txt")==0){
                FILE *file=fopen("topScores.txt","w");
                if(file==NULL){
                    exit(204);
                }
                fclose(file);
            }
            addFileScore("topScores.txt",player);
            removeSaves(fileNameGame,fileNameArray);
            if(mode==NORMALMODE){
                displayEndScreen(grid,timer,player,currentform,nextform,&win,1);
            }
            else{
                displayEndScreen(grid,timer,player,currentform,nextform,&win,0);
            }
        }
        else{
            displayEndScreen(grid,timer,player,currentform,nextform,&win,0);
            saveArray(grid,fileNameArray);
            destroyGrid(&grid);
            saveGame(grid,player,timer,currentform,nextform,fileNameGame);
        }

        do{
            car=wgetch(win);
        }while(car!='r' && car!='l');

    }while(car=='r');

    wclear(win);
    clear();
    delwin(win);
    endwin();
    return 0;
}