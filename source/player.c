#include "player.h"

//This function creates a player
Player createPlayer(WINDOW *win, int points[4]){
    Player player;
    char string[6];
    int i=0;

    box(win,0,0);
    mvwprintw(win,2,2,"Choose a username :");
    wrefresh(win);
    mvwgetnstr(win,2,22,player.username,10);
    player.score=0;
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

//This function displays the useful keys to play the game
void displayGameKeys(WINDOW *win){
    mvwprintw(win,1,2,"Press ");
    mvwprintw(win,2,2,"Press ");
    mvwprintw(win,3,2,"Press ");
    mvwprintw(win,4,2,"Press ");
    mvwprintw(win,5,2,"Press ");

    wattron(win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(win,1,8,"'l'");
    mvwprintw(win,2,8,"'SPACE'");
    mvwprintw(win,3,8,"'←' ");
    mvwprintw(win,5,8,"'↓' ");
    mvwprintw(win,4,8,"'→' ");
    wattroff(win,COLOR_PAIR(7) | A_BOLD);

    mvwprintw(win,3,12,"or ");
    mvwprintw(win,5,12,"or ");
    mvwprintw(win,4,12,"or ");

    wattron(win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(win,3,15,"'q'");
    mvwprintw(win,5,15,"'s'");
    mvwprintw(win,4,15,"'d'");
    wattroff(win,COLOR_PAIR(7) | A_BOLD);

    mvwprintw(win,1,11," to stop the game");
    mvwprintw(win,2,15," to rotate the form");
    mvwprintw(win,3,18," to move left");
    mvwprintw(win,4,18," to move right");
    mvwprintw(win,5,18," to move down");
}

//This function displays the screen containing the grid and some other informations related to the player and the game keys
void displayScreen(Grid grid, Timer *timer, Player player, Form currentform, Form nextform, WINDOW **win){
    int i=0,j=0;
    
    werase(*win);
    *win=newwin(BOXLINES,BOXCOLUMNS,0,0);
    wbkgd(*win,COLOR_PAIR(1));
    //To keep the background black
    keypad(*win,TRUE);
    //To activate the special keys as KEY_UP ...
    box(*win,0,0);
    wtimeout(*win,timer->speed);

    displayGameKeys(*win);

    mvwprintw(*win,7,2,"%s : %d points",player.username,player.score);
    mvwprintw(*win,8,2,"%d placed forms and %d complete lines",player.numberForms,player.clearedLines);
    
    timer->elapsedTime=time(NULL)-timer->start;
    wattron(*win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(*win,10,2,"Time passed : %d seconds",timer->elapsedTime);
    mvwprintw(*win,11,2,"Drop speed : %d milliseconds",timer->speed);
    wattroff(*win,COLOR_PAIR(7) | A_BOLD);

    mvwprintw(*win,13,2,"Simple line : %d points",player.points[0]);
    mvwprintw(*win,14,2,"Double line : %d points",player.points[1]);
    mvwprintw(*win,15,2,"Triple line : %d points",player.points[2]);
    mvwprintw(*win,16,2,"Tetris line : %d points",player.points[3]);

    wattron(*win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(*win,18,2,"Next form : ");
    wattroff(*win,COLOR_PAIR(7) | A_BOLD);
    int column=7-nextform.width;
    for(i=0;i<DIMENSION;i++){
        for(j=0;j<DIMENSION;j++){
            if(nextform.tab[nextform.currentForm][i][j]!=0){
                displayEmoji(*win,20+i,column+2*j,nextform.currentForm+1);
            }
        }
    }

    displayGrid(grid,currentform,*win);
    wrefresh(*win);
}

//This function gets the coordinates of a new form in the grid
void getFormCoordinates(Grid *grid, Form currentform){
    grid->x1=0;
    grid->y1=grid->N/2-currentform.width/2;
    grid->x2=currentform.height-1;
    grid->y2=grid->y1+currentform.width-1;
}

//This function allows the player to control the movement of the form dropping until it hits another form or the bottom of the grid
int playerMovement(Grid *grid, Timer *timer, Player *player, Form *currentform, Form nextform, WINDOW *win){
    struct timespec current;
    long start=0,final=0,passedTime=0;
    int i=0,j=0,right=0,left=0,down=0;
    int movement=0,validRotation;
    Form tmpform;

    timer->speed=MINSPEED-25*(timer->elapsedTime/30);
    //Increases the speed by 25 ms every 30 seconds
    if(timer->speed<MAXSPEED){
        timer->speed=MAXSPEED;
    }

    clock_gettime(CLOCK_REALTIME,&current);
    start=current.tv_sec*1000+current.tv_nsec/1000000;
    do{
        displayScreen(*grid,timer,*player,*currentform,nextform,&win);
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
                    if(grid->x2==grid->M-1 || (currentform->tab[currentform->currentForm][i-grid->x1][j-grid->y1]!=0 && (i-grid->x1==DIMENSION-1 || currentform->tab[currentform->currentForm][i-grid->x1+1][j-grid->y1]==0) && grid->tab[i+1][j]!=0)){
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
                    if(grid->y2==grid->N-1 || (currentform->tab[currentform->currentForm][i-grid->x1][j-grid->y1]!=0 && (j-grid->y1==DIMENSION-1 || currentform->tab[currentform->currentForm][i-grid->x1][j-grid->y1+1]==0) && grid->tab[i][j+1]!=0)){
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
                    if(grid->y1==0 || (currentform->tab[currentform->currentForm][i-grid->x1][j-grid->y1]!=0 && (j-grid->y1==0 || currentform->tab[currentform->currentForm][i-grid->x1][j-grid->y1-1]==0) && grid->tab[i][j-1]!=0)){
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
            tmpform=(*currentform);
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
                (*currentform)=tmpform;
            }
            else{
                grid->x2=grid->x1+currentform->height-1;
                grid->y2=grid->y1+currentform->width-1;
            }
        }
    }while(1);

    for(i=grid->x1;i<=grid->x2;i++){
        for(j=grid->y1;j<=grid->y2;j++){
            if(currentform->tab[currentform->currentForm][i-grid->x1][j-grid->y1]!=0){
                grid->tab[i][j]=currentform->currentForm+1;
            }
        }
    }

    return 0;
}

//This function displays the ranking of the top 3 scores in the normal mode
void displayRanking(WINDOW *win, int line, int column){
    int counter=0;
    FILE *file=fopen("topScores.txt","r");
    int score=0;
    char username[15];
    if(file==NULL){
        return;
    }
    while(fscanf(file,"%s %d",username,&score)!=EOF){
        if(counter==0){
            mvwprintw(win,line+counter,column,"🥇 %s %d points",username,score);
        }
        else if(counter==1){
            mvwprintw(win,line+counter,column,"🥈 %s %d points",username,score);
        }
        else{
            mvwprintw(win,line+counter,column,"🥉 %s %d points",username,score);
        }
        counter++;
    }
    fclose(file);
}

//This function displays the end screen
void displayEndScreen(Grid grid, Timer timer, Player player, Form currentform, Form nextform, WINDOW **win, int ranking){
    int i=0,j=0;
    
    werase(*win);
    *win=newwin(BOXLINES,BOXCOLUMNS,0,0);
    wbkgd(*win,COLOR_PAIR(1));
    keypad(*win,TRUE);
    box(*win,0,0);
    wtimeout(*win,-1);

    mvwprintw(*win,1,2,"Press ");
    wattron(*win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(*win,1,8,"'l'");
    wattroff(*win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(*win,1,11," to leave");

    mvwprintw(*win,2,2,"Press ");
    wattron(*win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(*win,2,8,"'m'");
    wattroff(*win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(*win,2,11," to return to menu");

    mvwprintw(*win,4,2,"%s : %d points",player.username,player.score);
    mvwprintw(*win,5,2,"%d placed forms and %d complete lines",player.numberForms,player.clearedLines);
    
    wattron(*win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(*win,7,2,"Time passed : %d seconds",timer.elapsedTime);
    mvwprintw(*win,8,2,"Drop speed : %d milliseconds",timer.speed);
    wattroff(*win,COLOR_PAIR(7) | A_BOLD);

    mvwprintw(*win,10,2,"Simple line : %d points",player.points[0]);
    mvwprintw(*win,11,2,"Double line : %d points",player.points[1]);
    mvwprintw(*win,12,2,"Triple line : %d points",player.points[2]);
    mvwprintw(*win,13,2,"Tetris line : %d points",player.points[3]);

    wattron(*win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(*win,15,2,"Next form : ");
    wattroff(*win,COLOR_PAIR(7) | A_BOLD);
    int column=7-nextform.width;
    for(i=0;i<DIMENSION;i++){
        for(j=0;j<DIMENSION;j++){
            if(nextform.tab[nextform.currentForm][i][j]!=0){
                displayEmoji(*win,17+i,column+2*j,nextform.currentForm+1);
            }
        }
    }

    displayGrid(grid,currentform,*win);
    if(ranking==1){
        wattron(*win,COLOR_PAIR(7) | A_BOLD);
        mvwprintw(*win,22,2,"Ranking :");
        wattroff(*win,COLOR_PAIR(7) | A_BOLD);
        displayRanking(*win,24,2);
    }
    wrefresh(*win);
}