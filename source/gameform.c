#include "gameform.h"

Form createForms(){
    Form form={{
        {
            {1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}
        },
        {
            {1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}
        },
        {
            {0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}
        },
        {
            {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}
        },
        {
            {0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}
        },
        {
            {1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}
        },
        {
            {0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}
        },
    },-1,-1,-1};
    return form;
}

void rotateForm(int tab[DIMENSION][DIMENSION]){
    int tmp1[DIMENSION],tmp2[DIMENSION],tmp3[DIMENSION],tmp4[DIMENSION];
    int i=0,k=0;
    for(k=0;k<DIMENSION/2;k++){
        for(i=k;i<DIMENSION-k;i++){
            tmp1[i]=tab[DIMENSION-1-i][k];
            tmp2[i]=tab[k][i];
            tmp3[i]=tab[DIMENSION-1-i][DIMENSION-1-k];
            tmp4[i]=tab[DIMENSION-1-k][i];
        }
        for(i=k;i<DIMENSION-k;i++){
            tab[k][i]=tmp1[i];
            tab[i][DIMENSION-1-k]=tmp2[i];
            tab[DIMENSION-1-k][i]=tmp3[i];
            tab[i][k]=tmp4[i];
        }
    }
}

void shiftFormLeftUp(int tab[DIMENSION][DIMENSION]){
    int left[DIMENSION]={1,1,1,1},up[DIMENSION]={1,1,1,1};
    int i=0,j=0,k=0;
    for(i=0;i<DIMENSION;i++){
        for(j=0;j<DIMENSION;j++){
            if(tab[i][j]!=0){
                left[j]=0;
            }
        }
    }
    for(k=0;k<DIMENSION;k++){
        if(left[k]==0){
            break;
        }
        else{
            for(i=0;i<DIMENSION;i++){
                for(j=0;j<DIMENSION-1;j++){
                    tab[i][j]=tab[i][j+1];
                    tab[i][j+1]=0;
                }
            }
        }
    }
    
    for(i=0;i<DIMENSION;i++){
        for(j=0;j<DIMENSION;j++){
            if(tab[i][j]!=0){
                up[i]=0;
            }
        }
    }
    for(k=0;k<DIMENSION;k++){
        if(up[k]==0){
            break;
        }
        else{
            for(i=0;i<DIMENSION-1;i++){
                for(j=0;j<DIMENSION;j++){
                    tab[i][j]=tab[i+1][j];
                    tab[i+1][j]=0;
                }
            }
        }
    }
}

void getFormDimensions(int tab[DIMENSION][DIMENSION], int *height, int *width){
    int i=0,j=0;
    *height=0;
    *width=0;
    for(i=DIMENSION-1;i>=0;i--){
        for(j=DIMENSION-1;j>=0;j--){
            if(tab[i][j]!=0){
                if(i+1>*height){
                    *height=i+1;
                }
                if(j+1>*width){
                    *width=j+1;
                }
            }
        }
    }
}

Form generateNewForm(Form form){
    form.currentForm=rand()%NUMBERFORMS;
    shiftFormLeftUp(form.tab[form.currentForm]);
    getFormDimensions(form.tab[form.currentForm],&form.height,&form.width);
    return form;
}