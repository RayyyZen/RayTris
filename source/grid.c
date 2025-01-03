#include "grid.h"

//This function returns the absolute value of a number
int absoluteValue(int value){
    return value>0 ? value : -value;
}

//This function transforms a string to an integer with a value between a min and a max given as arguments
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

//This function creates the array that will contain the forms
int** createArray(int height, int width){
    int **tab=NULL;
    int i=0;

    tab=calloc(height,sizeof(int*));
    if(tab==NULL){
        exit(10);
    }

    for(i=0;i<height;i++){
        tab[i]=calloc(width,sizeof(int));
        if(tab[i]==NULL){
            exit(11);
        }
    }

    return tab;
}

//This function creates a grid according to the player's input
Grid createGrid(WINDOW *win){
    Grid grid={NULL,0,0,-1,-1,-1,-1};
    char string[3];

    box(win,0,0);
    mvwprintw(win,12,2,"Choose the height of the grid between %d and %d :",MINHEIGHT,MAXHEIGHT);
    wrefresh(win);
    mvwgetnstr(win,12,52,string,2);
    grid.M=stringToInteger(string,MINHEIGHT,MAXHEIGHT)+5;

    box(win,0,0);
    mvwprintw(win,14,2,"Choose the width of the grid between %d and %d :",MINWIDTH,MAXWIDTH);
    wrefresh(win);
    mvwgetnstr(win,14,51,string,2);
    grid.N=stringToInteger(string,MINWIDTH,MAXWIDTH);

    grid.tab=createArray(grid.M,grid.N);

    werase(win);

    return grid;
}

//This function displays emojis according to the form type
void displayEmoji(WINDOW *win, int x, int y, int form){
    switch(form){
        case IFORM :
            mvwprintw(win,x,y,"🟦");
            break;
        case JFORM :
            mvwprintw(win,x,y,"🟫");
            break;
        case LFORM :
            mvwprintw(win,x,y,"🟧");
            break;
        case OFORM :
            mvwprintw(win,x,y,"🟨");
            break;
        case SFORM :
            mvwprintw(win,x,y,"🟩");
            break;
        case ZFORM :
            mvwprintw(win,x,y,"🟥");
            break;
        case TFORM :
            mvwprintw(win,x,y,"🟪");
            break;
        default :
            mvwprintw(win,x,y,"  ");
    }
}

//This function displays the grid containing the forms
void displayGrid(Grid grid, Form form, WINDOW *win){
    int i=0,j=0,line=BOXLINES/2-grid.M/2,column=(11*BOXCOLUMNS)/20-grid.N/2;
    for(i=0;i<grid.M;i++){
        for(j=0;j<grid.N;j++){
            if(i==4 && grid.tab[i][j]==0 && (i<grid.x1 || i>grid.x2 || j<grid.y1 || j>grid.y2 || form.tab[form.currentForm][i-grid.x1][j-grid.y1]==0)){
                mvwprintw(win,line+i,column+2*j,"🌫 ");
                //🕸🕳🌫
            }
            else if(i>=grid.x1 && i<=grid.x2 && j>=grid.y1 && j<=grid.y2 && form.tab[form.currentForm][i-grid.x1][j-grid.y1]!=0){
                displayEmoji(win,line+i,column+2*j,form.currentForm+1);
            }
            else{
                displayEmoji(win,line+i,column+2*j,grid.tab[i][j]);
            }
            
        }
        mvwprintw(win,line+i,column-2,"🔲");
        mvwprintw(win,line+i,column+2*grid.N,"🔲");
    }
    for(j=-1;j<=grid.N;j++){
        mvwprintw(win,line-1,column+2*j,"🔲");
        mvwprintw(win,line+i,column+2*j,"🔲");
    }
}

//This function simulates the gravity effect after deleting a line
Grid gravityEffect(Grid grid, int line){
    int i=0,j=0;

    for(i=line;i>0;i--){
        for(j=0;j<grid.N;j++){
            grid.tab[i][j]=grid.tab[i-1][j];
            grid.tab[i-1][j]=0;
        }
    }

    return grid;
}

//This function deletes a complete line and simulates the gravity effect
int deleteLine(Grid *grid){
    int i=0,j=0,completeLine=0;
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
            return 1;
        }
    }
    return 0;
}

//This function checks if the player lost
int loseCondition(Grid grid){
    int i=0,j=0;
    for(i=0;i<5;i++){
        for(j=0;j<grid.N;j++){
            if(grid.tab[i][j]!=0){
                return 1;
            }
        }
    }
    return 0;
}