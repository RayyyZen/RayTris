#include "player.h"

Player createPlayer(WINDOW *win, int points[4]){
    Player player;
    char string[6];
    int i=0;

    box(win,0,0);
    mvwprintw(win,2,2,"Choose a username :");
    wrefresh(win);
    mvwgetnstr(win,2,22,player.username,10);
    player.clearedLines=0;
    player.numberForms=0;

    if(points[0]>=0){
        for(i=0;i<4;i++){
            player.points[i]=points[i];
        }
        return player;
    }

    box(win,0,0);
    mvwprintw(win,4,2,"Choose the number of points gained from a complete line between 0 and 10000 :");
    wrefresh(win);
    mvwgetnstr(win,4,80,string,5);
    player.points[0]=stringToInteger(string,0,10000);

    box(win,0,0);
    mvwprintw(win,6,2,"Choose the number of points gained from two complete lines between 0 and 10000 :");
    wrefresh(win);
    mvwgetnstr(win,6,83,string,5);
    player.points[1]=stringToInteger(string,0,10000);

    box(win,0,0);
    mvwprintw(win,8,2,"Choose the number of points gained from three complete lines between 0 and 10000 :");
    wrefresh(win);
    mvwgetnstr(win,8,85,string,5);
    player.points[2]=stringToInteger(string,0,10000);

    box(win,0,0);
    mvwprintw(win,10,2,"Choose the number of points gained from four complete lines between 0 and 10000 :");
    wrefresh(win);
    mvwgetnstr(win,10,84,string,5);
    player.points[3]=stringToInteger(string,0,10000);

    return player;
}

void displayScreen(Grid grid, Timer *timer, Player player, Form currentform, Form nextform, WINDOW **win){
    int i=0,j=0;
    
    werase(*win);
    *win=newwin(BOXLINES,BOXCOLUMNS,0,0);
    wbkgd(*win,COLOR_PAIR(1));
    keypad(*win,TRUE);
    box(*win,0,0);
    wtimeout(*win,timer->speed);
    
    mvwprintw(*win,1,2,"%s",player.username);
    mvwprintw(*win,3,2,"Number of placed forms : %d",player.numberForms);
    mvwprintw(*win,5,2,"Number of cleared lines : %d",player.clearedLines);
    mvwprintw(*win,7,2,"Score : %d points",player.score);
    wattron(*win,COLOR_PAIR(2) | A_BOLD);
    timer->elapsedTime=time(NULL)-timer->start;
    mvwprintw(*win,9,2,"Time passed : %d",timer->elapsedTime);
    mvwprintw(*win,11,2,"Drop speed : %d",timer->speed);
    wattroff(*win,COLOR_PAIR(2) | A_BOLD);
    mvwprintw(*win,13,2,"Simple line : %d points",player.points[0]);
    mvwprintw(*win,15,2,"Double line : %d points",player.points[1]);
    mvwprintw(*win,17,2,"Triple line : %d points",player.points[2]);
    mvwprintw(*win,19,2,"Tetris line : %d points",player.points[3]);
    mvwprintw(*win,21,2,"Next form : ");
    for(i=0;i<DIMENSION;i++){
        for(j=0;j<DIMENSION;j++){
            if(nextform.tab[nextform.currentForm][i][j]!=0){
                displayEmoji(*win,23+i,3+2*j,nextform.currentForm+1);
            }
        }
    }

    displayGrid(grid,currentform,*win);
    wrefresh(*win);
}

void getFormCoordinates(Grid *grid, Form currentform){
    grid->x1=0;
    grid->y1=rand()%(grid->N-currentform.width+1);
    grid->x2=currentform.height-1;
    grid->y2=grid->y1+currentform.width-1;
}

int playerMovement(Grid *grid, Timer *timer, Player *player, Form currentform, Form nextform, WINDOW *win){
    struct timespec current;
    long start=0,final=0,passedTime=0;
    int i=0,j=0,right=0,left=0,down=0;
    int movement=0,validRotation;
    Form tmpform;

    timer->speed=MINSPEED-25*(timer->elapsedTime/30);

    clock_gettime(CLOCK_REALTIME,&current);
    start=current.tv_sec*1000+current.tv_nsec/1000000;
    do{
        displayScreen(*grid,timer,*player,currentform,nextform,&win);
        movement=wgetch(win);

        if(movement=='l'){
            return -1;
        }

        clock_gettime(CLOCK_REALTIME,&current);
        final=current.tv_sec*1000+current.tv_nsec/1000000;
        passedTime+=final-start;
        clock_gettime(CLOCK_REALTIME,&current);
        start=current.tv_sec*1000+current.tv_nsec/1000000;

        if(movement==KEY_DOWN || movement=='s' || passedTime>=timer->speed){
            down=1;
            for(i=grid->x1;i<=grid->x2;i++){
                for(j=grid->y1;j<=grid->y2;j++){
                    if(grid->x2==grid->M-1 || (currentform.tab[currentform.currentForm][i-grid->x1][j-grid->y1]!=0 && (i-grid->x1==DIMENSION-1 || currentform.tab[currentform.currentForm][i-grid->x1+1][j-grid->y1]==0) && grid->tab[i+1][j]!=0)){
                        down=0;
                    }
                }
            }
            if(down==1){
                grid->x1++;
                grid->x2++;
            }
            else{
                break;
            }
            passedTime=0;
        }

        if(movement==KEY_RIGHT || movement=='d'){
            right=1;
            for(i=grid->x1;i<=grid->x2;i++){
                for(j=grid->y1;j<=grid->y2;j++){
                    if(grid->y2==grid->N-1 || (currentform.tab[currentform.currentForm][i-grid->x1][j-grid->y1]!=0 && (j-grid->y1==DIMENSION-1 || currentform.tab[currentform.currentForm][i-grid->x1][j-grid->y1+1]==0) && grid->tab[i][j+1]!=0)){
                        right=0;
                    }
                }
            }
            if(right==1){
                grid->y1++;
                grid->y2++;
            }
        }
        else if(movement==KEY_LEFT || movement=='q'){
            left=1;
            for(i=grid->x1;i<=grid->x2;i++){
                for(j=grid->y1;j<=grid->y2;j++){
                    if(grid->y1==0 || (currentform.tab[currentform.currentForm][i-grid->x1][j-grid->y1]!=0 && (j-grid->y1==0 || currentform.tab[currentform.currentForm][i-grid->x1][j-grid->y1-1]==0) && grid->tab[i][j-1]!=0)){
                        left=0;
                    }
                }
            }
            if(left==1){
                grid->y1--;
                grid->y2--;
            }
        }
        else if(movement==' '){
            tmpform=currentform;
            rotateForm(tmpform.tab[tmpform.currentForm]);
            shiftFormLeftUp(tmpform.tab[tmpform.currentForm]);
            getFormDimensions(tmpform.tab[tmpform.currentForm],&tmpform.height,&tmpform.width);
            grid->x2=grid->x1+tmpform.height-1;
            grid->y2=grid->y1+tmpform.width-1;
            validRotation=1;
            for(i=grid->x1;i<=grid->x2;i++){
                for(j=grid->y1;j<=grid->y2;j++){
                    if(tmpform.tab[tmpform.currentForm][i-grid->x1][j-grid->y1]!=0 && (i>grid->M-1 || j>grid->N-1 || i<0 || j<0 || grid->tab[i][j]!=0)){
                        validRotation=0;
                    }                    
                }
            }
            if(validRotation==1){
                currentform=tmpform;
            }
            else{
                grid->x2=grid->x1+currentform.height-1;
                grid->y2=grid->y1+currentform.width-1;
            }
        }
    }while(1);

    for(i=grid->x1;i<=grid->x2;i++){
        for(j=grid->y1;j<=grid->y2;j++){
            if(currentform.tab[currentform.currentForm][i-grid->x1][j-grid->y1]!=0){
                grid->tab[i][j]=currentform.currentForm+1;
            }
        }
    }

    return 0;
}

Grid gravityEffect(Grid grid, int line){
    int i=0,j=0,k=0;

    for(i=line;i>0;i--){
        for(j=0;j<grid.N;j++){
            grid.tab[i][j]=grid.tab[i-1][j];
            grid.tab[i-1][j]=0;
        }
    }

    return grid;
}

int deleteLine(Grid *grid, Player player, Timer *timer, Form currentform, Form nextform, WINDOW *win){
    int i=0,j=0,completeLine=0,counter=0;
    for(i=5;i<grid->M;i++){
        completeLine=1;
        for(j=0;j<grid->N;j++){
            if(grid->tab[i][j]==0){
                completeLine=0;
            }
        }
        if(completeLine==1){
            for(j=0;j<grid->N;j++){
                grid->tab[i][j]=0;
            }
            *grid=gravityEffect(*grid,i);
            displayScreen(*grid,timer,player,currentform,nextform,&win);
            usleep(500000);
            counter++;
        }
    }
    return counter;
}