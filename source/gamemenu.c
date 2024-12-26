#include "gamemenu.h"

void displayLeftArrow(WINDOW *win){
    int line=BOXLINES/2-4,column=3;
    wattron(win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(win,line,column,"   $$\\  $$\\");                                 
    mvwprintw(win,line+1,column,"  $$  |$$  |");                                   
    mvwprintw(win,line+2,column," $$  /$$  /");  
    mvwprintw(win,line+3,column,"$$  /$$  /"); 
    mvwprintw(win,line+4,column,"\\$$< \\$$<");
    mvwprintw(win,line+5,column," \\$$\\ \\$$\\");
    mvwprintw(win,line+6,column,"  \\$$\\ \\$$\\");
    mvwprintw(win,line+7,column,"   \\__| \\__|");
    wattroff(win,COLOR_PAIR(7) | A_BOLD);
}

void displayRightArrow(WINDOW *win){
    int line=BOXLINES/2-4,column=BOXCOLUMNS-14;
    wattron(win,COLOR_PAIR(7) | A_BOLD);
    mvwprintw(win,line,column,"$$\\  $$\\");                                 
    mvwprintw(win,line+1,column,"\\$$\\ \\$$\\");                                   
    mvwprintw(win,line+2,column," \\$$\\ \\$$\\");  
    mvwprintw(win,line+3,column,"  \\$$\\ \\$$\\"); 
    mvwprintw(win,line+4,column,"  $$  |$$  |");
    mvwprintw(win,line+5,column," $$  /$$  /");
    mvwprintw(win,line+6,column,"$$  /$$  /");
    mvwprintw(win,line+7,column,"\\__/ \\__/");
    wattroff(win,COLOR_PAIR(7) | A_BOLD);
}

void displayNewGame(WINDOW *win){
    int line=BOXLINES/2-4,column=BOXCOLUMNS/2-15;
    mvwprintw(win,line,column,"$$\\   $$\\");                                 
    mvwprintw(win,line+1,column,"$$$\\  $$ |");                                   
    mvwprintw(win,line+2,column,"$$$$\\ $$ | $$$$$$\\  $$\\  $$\\  $$\\");  
    mvwprintw(win,line+3,column,"$$ $$\\$$ |$$  __$$\\ $$ | $$ | $$ |"); 
    mvwprintw(win,line+4,column,"$$ \\$$$$ |$$$$$$$$ |$$ | $$ | $$ |");
    mvwprintw(win,line+5,column,"$$ |\\$$$ |$$   ____|$$ | $$ | $$ |");
    mvwprintw(win,line+6,column,"$$ | \\$$ |\\$$$$$$$\\ \\$$$$$\\$$$$  |");
    mvwprintw(win,line+7,column,"\\__|  \\__| \\_______| \\_____\\____/");
}

void displayResumeGame(WINDOW *win){
    int line=BOXLINES/2-4,column=BOXCOLUMNS/2-31;
    mvwprintw(win,line,column,"$$$$$$$\\");                                 
    mvwprintw(win,line+1,column,"$$  __$$");                                   
    mvwprintw(win,line+2,column,"$$ |  $$ | $$$$$$\\   $$$$$$$\\ $$\\   $$\\ $$$$$$\\$$$$\\   $$$$$$\\");  
    mvwprintw(win,line+3,column,"$$$$$$$  |$$  __$$\\ $$  _____|$$ |  $$ |$$  _$$  _$$\\ $$  __$$\\"); 
    mvwprintw(win,line+4,column,"$$  __$$< $$$$$$$$ |\\$$$$$$\\  $$ |  $$ |$$ / $$ / $$ |$$$$$$$$ |");
    mvwprintw(win,line+5,column,"$$ |  $$ |$$   ____| \\____$$\\ $$ |  $$ |$$ | $$ | $$ |$$   ____|");
    mvwprintw(win,line+6,column,"$$ |  $$ |\\$$$$$$$\\ $$$$$$$  |\\$$$$$$  |$$ | $$ | $$ |\\$$$$$$$\\");
    mvwprintw(win,line+7,column,"\\__|  \\__| \\_______|\\_______/  \\______/ \\__| \\__| \\__| \\_______|");
}

void displayExit(WINDOW *win){
    int line=BOXLINES/2-4,column=BOXCOLUMNS/2-15;
    mvwprintw(win,line,column,"$$$$$$$$\\           $$\\   $$\\");                                 
    mvwprintw(win,line+1,column,"$$  _____|          \\__|  $$ |");                                   
    mvwprintw(win,line+2,column,"$$ |      $$\\   $$\\ $$\\ $$$$$$\\");  
    mvwprintw(win,line+3,column,"$$$$$\\    \\$$\\ $$  |$$ |\\_$$  _|"); 
    mvwprintw(win,line+4,column,"$$  __|    \\$$$$  / $$ |  $$ |");
    mvwprintw(win,line+5,column,"$$ |       $$  $$<  $$ |  $$ |$$\\");
    mvwprintw(win,line+6,column,"$$$$$$$$\\ $$  /\\$$\\ $$ |  \\$$$$  |");
    mvwprintw(win,line+7,column,"\\________|\\__/  \\__|\\__|   \\____/");
}

void displayMenu(WINDOW *win, int choice[CHOICES], int cursor){
    if(choice[cursor]==0){
        displayNewGame(win);
    }
    else if(choice[cursor]==1){
        displayResumeGame(win);
    }
    else{
        displayExit(win);
    }

    if(choice[cursor]!=CHOICES-1){
        displayRightArrow(win);
    }
    if(choice[cursor]!=0){
        displayLeftArrow(win);
    }
}

int movementMenu(WINDOW *win, int *cursor, int size, int mode){
    int movement=wgetch(win);
    if((movement==KEY_LEFT || movement=='q') && *cursor>0){
        (*cursor)--;
        return 0;
    }
    else if((movement==KEY_RIGHT || movement=='d') && *cursor<size-1){
        (*cursor)++;
        return 0;
    }
    else if(movement=='\n'){
        return 1;
    }
    else if(mode==1 && movement=='b'){
        return 2;
    }
    return 0;
}

void displayNormalMode(WINDOW *win){
    int line=BOXLINES-7,column=BOXCOLUMNS/2-34;
    mvwprintw(win,line,column,"   _  __                    __");                                 
    mvwprintw(win,line+1,column,"  / |/ /__  ______ _  ___ _/ /");                                   
    mvwprintw(win,line+2,column," /    / _ \\/ __/  ' \\/ _ `/ /");  
    mvwprintw(win,line+3,column,"/_/|_/\\___/_/ /_/_/_/\\_,_/_/"); 
}

void displayCustomMode(WINDOW *win){
    int line=BOXLINES-7,column=BOXCOLUMNS/2+8;
    mvwprintw(win,line,column,"  _____         __");                                 
    mvwprintw(win,line+1,column," / ___/_ _____ / /____  __ _");                                   
    mvwprintw(win,line+2,column,"/ /__/ // (_-</ __/ _ \\/  ' \\");  
    mvwprintw(win,line+3,column,"\\___/\\_,_/___/\\__/\\___/_/_/_/"); 
}

void choiceMenu(int *menuchoice, int *gamemode){
    int choice[CHOICES]={NEWGAME,RESUMEGAME,EXIT};
    int mode[MODES]={NORMALMODE,CUSTOMMODE};
    WINDOW *win=newwin(BOXLINES,BOXCOLUMNS,0,0);
    int cursor=0,userchoice=-1,cursormode=-1,usermodechoice=0;
    do{
        do{
            werase(win);
            win=newwin(BOXLINES,BOXCOLUMNS,0,0);
            wbkgd(win,COLOR_PAIR(1));
            keypad(win,TRUE);
            box(win,0,0);

            displayMenu(win,choice,cursor);
            userchoice=movementMenu(win,&cursor,CHOICES,0);
            wrefresh(win);
        }while(userchoice==0);

        if(choice[cursor]!=EXIT){
            cursormode=0;
            do{
                werase(win);
                win=newwin(BOXLINES,BOXCOLUMNS,0,0);
                wbkgd(win,COLOR_PAIR(1));
                keypad(win,TRUE);
                box(win,0,0);

                displayMenu(win,choice,cursor);
                wattron(win,COLOR_PAIR(7) | A_BOLD);
                if(cursormode==0){
                    displayNormalMode(win);
                    wattroff(win,COLOR_PAIR(7) | A_BOLD);
                    displayCustomMode(win);
                }
                else{
                    displayCustomMode(win);
                    wattroff(win,COLOR_PAIR(7) | A_BOLD);
                    displayNormalMode(win);
                }
                usermodechoice=movementMenu(win,&cursormode,MODES,1);
                wrefresh(win);
            }while(usermodechoice==0);
        }
        else{
            break;
        }
    }while(usermodechoice==2);

    *menuchoice=choice[cursor];
    *gamemode=mode[cursormode];
}

int menu(Grid *grid, Player *player, Timer *timer, Form form, Form *currentform, Form *nextform){
    int choice=0,mode=0;
    choiceMenu(&choice,&mode);
    WINDOW *win=newwin(BOXLINES,BOXCOLUMNS,0,0);
    echo();
    switch(choice){
        case EXIT :
            wclear(win);
            delwin(win);
            return -1;

        case NEWGAME :
            int points[4]={100,300,500,800};
            int emptypoints[4]={-1,-1,-1,-1};
            
            timer->start=time(NULL);
            timer->elapsedTime=0;
            timer->speed=MINSPEED;
            *currentform=generateNewForm(form);
            *nextform=generateNewForm(form);
            if(mode==NORMALMODE){
                *player=createPlayer(win,points);
                grid->M=20;
                grid->N=10;
                grid->tab=createArray(grid->M,grid->N);
                werase(win);
            }
            else{
                *player=createPlayer(win,emptypoints);
                *grid=createGrid(win);
            }
            break;

        case RESUMEGAME :
            if(mode==NORMALMODE){

            }
            else{
                
            }
            break;
    }
    noecho();
    return 0;
}