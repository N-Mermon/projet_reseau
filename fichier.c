#include "projet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

char* supprimeoffset(char* ch){
    char* chaine = malloc(strlen(ch)*sizeof(char)); 
    int i=4; 
    while(i<strlen(ch)){
        chaine[i-4]=ch[i];
        i++; 
    }
    free(ch); 
    chaine[i-4]='\0'; 
    return chaine; 
}

Trame** lirefichier(char * name ){
    FILE* file= fopen(name, "r"); 
    if(file==NULL){
        return NULL; 
    }

    char* chainetot = malloc(12000*sizeof(char)); 
    chainetot[0]='\0'; 
    char* chaine= malloc(55*sizeof(char)); 

    Trame** t= malloc(10*sizeof(Trame*)); 
    int i=0; 
    //printf("Je passe "); 
    int j=0; 
    while(fgets(chaine, 56, file)!=NULL){
        //printf("chaine %s \n",chaine); 
        //printf(" %c %c %c %c \t",chaine[0],chaine[1], chaine[2], chaine[3]); 
        if(chaine[0]=='0' && chaine[1]=='0' && chaine[2]=='0' && chaine[3]=='0' && j!=0){
            //printf("Je passe "); 
            t[i]=lecture(chainetot); 
            j=0; 
            i++; 
        }
        //printf("chaine :%s\n",chaine); 
        chaine = supprimeoffset(chaine); 
        if(j==0) chainetot=strcpy(chainetot,chaine); 
        else{chainetot=strcat(chainetot,chaine); }
        j++; 
    } 
    //printf(" %s\n",chainetot); 
    t[i]=lecture(chainetot); 
    fclose(file); 
    free(chaine); 
    free(chainetot); 
    return t; 
}
