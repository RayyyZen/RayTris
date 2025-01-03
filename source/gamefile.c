#include "gamefile.h"

//This function saves the array that contains the grid
void saveArray(Grid grid, char *fileName){
    FILE *file=fopen(fileName,"wb");
    //If the file does not exist it will be created because I use the "wb" mode
    int i=0;
    if(file==NULL){
        exit(100);
    }
    for(i=0;i<grid.M;i++){
        fwrite(grid.tab[i],sizeof(int),grid.N,file);
    }
    fclose(file);
}

//This function frees the array that contains the grid
void destroyGrid(Grid *grid){
    int i=0;
    for(i=0;i<grid->M;i++){
        free(grid->tab[i]);
    }
    free(grid->tab);
    grid->tab=NULL;
}

//This function saves the game informations
void saveGame(Grid grid, Player player, Timer timer, Form currentform, Form nextform, char *fileName){
    FILE *file=fopen(fileName,"wb");
    //If the file does not exist it will be created because I use the "wb" mode
    Game game={grid,player,timer,currentform,nextform};
    if(file==NULL){
        exit(200);
    }
    fwrite(&game,sizeof(Game),1,file);
    fclose(file);
}

//This function recovers the array that was previously saved
void recoverArray(Grid *grid, char *fileName){
    FILE *file=fopen(fileName,"rb");
    int i=0;
    if(file==NULL){
        exit(101);
    }
    grid->tab=malloc((grid->M)*sizeof(int*));
    if(grid->tab==NULL){
        exit(11);
    }
    for(i=0;i<grid->M;i++){
        grid->tab[i]=malloc((grid->N)*sizeof(int));
        if(grid->tab[i]==NULL){
            exit(12+i);
        }
        fread(grid->tab[i],sizeof(int),grid->N,file);
    }
    fclose(file);
}

//This function recovers the game that was previously saved
void recoverGame(Grid *grid, Player *player, Timer *timer, Form *currentform, Form *nextform, char *fileName){
    FILE *file=NULL;
    Game game;
    file=fopen(fileName,"rb");
    if(file==NULL){
        exit(201);
    }
    fread(&game,sizeof(Game),1,file);
    *grid=game.grid;
    *player=game.player;
    *timer=game.timer;
    *currentform=game.currentform;
    *nextform=game.nextform;
    fclose(file);
}

//This function removes the files that contains the saves of the previous game
void removeSaves(char *fileName1, char *fileName2){
    //The remove() function must be used after the fclose() function
    FILE *file1=fopen(fileName1,"rb");
    if(file1!=NULL){
        fclose(file1);
        if(remove(fileName1)!=0){exit(55);};
    }
    FILE *file2=fopen(fileName2,"rb");
    if(file2!=NULL){
        fclose(file2);
        if(remove(fileName2)!=0){exit(56);};
    }
}

//This function checks if a file exists or not
int existFile(char *fileName){
    FILE *file=fopen(fileName,"rb");
    if(file==NULL){
        return 0;
    }
    fclose(file);
    return 1;
}

//This function adds the score of the player in a file containing the top 3 scores in the normal mode
void addFileScore(char *fileName, Player player){
    FILE *file=fopen(fileName,"r");
    char tabUserName[4][20];
    int tabScore[4]={0};
    int counter=0;

    if(file==NULL){
        exit(202);
    }
    while(fscanf(file,"%s %d",tabUserName[counter],&tabScore[counter])!=EOF){
        counter++;
    }
    strcpy(tabUserName[counter],player.username);
    tabScore[counter]=player.score;
    fclose(file);

    FILE *file2=fopen(fileName,"w");
    if(file==NULL){
        exit(203);
    }
    int i=0,j=0,tmp=0;
    char tmpname[15];

    for(i=0;i<=counter-1;i++){
        for(j=i;j<=counter;j++){
            if(tabScore[j]>tabScore[i]){
                tmp=tabScore[i];
                tabScore[i]=tabScore[j];
                tabScore[j]=tmp;

                strcpy(tmpname,tabUserName[i]);
                strcpy(tabUserName[i],tabUserName[j]);
                strcpy(tabUserName[j],tmpname);
            }
        }
    }

    for(i=0;i<=counter;i++){
        if(i<3){
            if(tabUserName[i][0]=='\0'){
                fprintf(file2,"%s %d\n","NoName",tabScore[i]);
            }
            else{
                fprintf(file2,"%s %d\n",tabUserName[i],tabScore[i]);
            }
        }
    }

    fclose(file2);
}