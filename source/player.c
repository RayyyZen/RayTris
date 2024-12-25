#include "player.h"

void playerMovement(Grid *grid, Timer *timer, Player *player, Form form, WINDOW *win){
    struct timespec current;
    long start=0,final=0,passedTime=0;
    int i=0,j=0,height=0,width=0,right=0,left=0,down=0;
    int movement=0;
    Form newform=generateNewForm(form,&height,&width);
    grid->x1=0;
    grid->y1=rand()%(grid->N-width+1);
    grid->x2=height-1;
    grid->y2=grid->y1+width-1;

    clock_gettime(CLOCK_REALTIME,&current);
    start=current.tv_sec*1000+current.tv_nsec/1000000;
    do{
        werase(win);
        win =newwin(BOXLINES,BOXCOLUMNS,0,0);
        wbkgd(win, COLOR_PAIR(1));
        keypad(win,TRUE);
        box(win,ACS_VLINE, ACS_HLINE);
        wtimeout(win,timer->speed);
        displayGrid(*grid,newform,win);
        movement=wgetch(win);
        wrefresh(win);
        clock_gettime(CLOCK_REALTIME,&current);
        final=current.tv_sec*1000+current.tv_nsec/1000000;
        passedTime+=final-start;
        clock_gettime(CLOCK_REALTIME,&current);
        start=current.tv_sec*1000+current.tv_nsec/1000000;

        if(passedTime>=timer->speed){
            down=1;
            for(i=grid->x1;i<=grid->x2;i++){
                for(j=grid->y1;j<=grid->y2;j++){
                    if(grid->x2==grid->M-1 || (newform.tab[newform.currentForm][i-grid->x1][j-grid->y1]!=0 && (i-grid->x1==DIMENSION-1 || newform.tab[newform.currentForm][i-grid->x1+1][j-grid->y1]==0) && grid->tab[i+1][j]!=0)){
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
                    if(grid->y2==grid->N-1 || (newform.tab[newform.currentForm][i-grid->x1][j-grid->y1]!=0 && (j-grid->y1==DIMENSION-1 || newform.tab[newform.currentForm][i-grid->x1][j-grid->y1+1]==0) && grid->tab[i][j+1]!=0)){
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
                    if(grid->y1==0 || (newform.tab[newform.currentForm][i-grid->x1][j-grid->y1]!=0 && (j-grid->y1==0 || newform.tab[newform.currentForm][i-grid->x1][j-grid->y1-1]==0) && grid->tab[i][j-1]!=0)){
                        left=0;
                    }
                }
            }
            if(left==1){
                grid->y1--;
                grid->y2--;
            }
        }
    }while(1);

    for(i=grid->x1;i<=grid->x2;i++){
        for(j=grid->y1;j<=grid->y2;j++){
            if(newform.tab[newform.currentForm][i-grid->x1][j-grid->y1]!=0){
                grid->tab[i][j]=newform.currentForm+1;
            }
        }
    }
}