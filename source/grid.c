#include "grid.h"

int absoluteValue(int value){
    return value>0 ? value : -value;
}

int stringToInteger(char string[3], int min, int max){
    int value=0;
    if(string[1]=='\0'){
        value=absoluteValue(string[0]-'0');
    }
    else{
        value=absoluteValue((string[0]-'0')*10+(string[1]-'0'));
    }
    if(value>=min && value<=max){
        return value;
    }
    else{
        return value%(max-min+1)+min;
    }
}

Grid createGrid(WINDOW *win){
    Grid grid={NULL,0,0,-1,-1,-1,-1};
    char string[3];
    int i=0;

    box(win,0,0);
    mvwprintw(win,2,2,"Choose the height of the grid between %d and %d :",MINHEIGHT,MAXHEIGHT);
    wrefresh(win);
    mvwgetnstr(win,2,52,string,2);
    grid.M=stringToInteger(string,MINHEIGHT,MAXHEIGHT)+5;

    box(win,0,0);
    mvwprintw(win,4,2,"Choose the width of the grid between %d and %d :",MINWIDTH,MAXWIDTH);
    wrefresh(win);
    mvwgetnstr(win,4,51,string,2);
    grid.N=stringToInteger(string,MINWIDTH,MAXWIDTH);

    grid.tab=calloc(grid.M,sizeof(int*));
    if(grid.tab==NULL){
        exit(10);
    }

    for(i=0;i<grid.M;i++){
        grid.tab[i]=calloc(grid.N,sizeof(int));
        if(grid.tab[i]==NULL){
            exit(11);
        }
    }

    werase(win);

    return grid;
}

void displayGrid(Grid grid, Form form, WINDOW *win){
    int i=0,j=0,line=BOXLINES/2-grid.M/2,column=(13*BOXCOLUMNS)/20-grid.N/2;
    box(win,0,0);
    for(i=0;i<grid.M;i++){
        if(i>4){
            mvwprintw(win,line+i,column-1,"|");
            mvwprintw(win,line+i,column+grid.N,"|");
        }
        for(j=0;j<grid.N;j++){
            if(i>=grid.x1 && i<=grid.x2 && j>=grid.y1 && j<=grid.y2){
                if(form.tab[form.currentForm][i-grid.x1][j-grid.y1]!=0){
                    wattron(win,COLOR_PAIR(form.currentForm+1) | A_BOLD);
                    mvwprintw(win,line+i,column+j,"*");
                    wattroff(win,COLOR_PAIR(form.currentForm+1) | A_BOLD);
                }
                else{
                    mvwprintw(win,line+i,column+j," ");
                }
            }
            else{
                if(grid.tab[i][j]==0){
                    mvwprintw(win,line+i,column+j," ");
                }
                else{
                    wattron(win,COLOR_PAIR(grid.tab[i][j]) | A_BOLD);
                    mvwprintw(win,line+i,column+j,"*");
                    wattroff(win,COLOR_PAIR(grid.tab[i][j]) | A_BOLD);
                }
            }
        }
    }
    for(j=0;j<grid.N;j++){
        mvwprintw(win,line+i,column+j,"-");
    }

    wrefresh(win);
}