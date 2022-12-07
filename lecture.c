#include "projet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void hextoAscii(char* ch){
    char c[3]; 
    c[3]='\0'; 
    int i; 
    for( i=0; i<(strlen(ch)/2); i++){
        c[0]=ch[i]; 
        c[1]=ch[i+1]; 
        ch[i]=(char) hexa_int(c); 
        i=i+1; 
    }
    printf(" %s",ch); 
    ch[i]='\0'; 
}
void freeLig(LigneEntete* lig){
    while(lig){
        free(lig->nomchamp); 
        free(lig->valeurchamp); 
        lig=lig->suiv; 
    }
}
void freeHTTP(HTTP* http){
    free(http->methode); 
    free(http->URL); 
    free(http->version); 
    freeLig(http->lig); 
    free(http->corpsreq); 
}
void afficheLig(LigneEntete* lig){
    
     while(lig!=NULL){ 
        printf("Entete ligne : nom champ %s valeur champ %s \n", lig->nomchamp, lig->valeurchamp); 
        lig=lig->suiv; 
    }
}
void afficheHTTP(HTTP* http){
    printf("HTTP: methode : %s URL: %s Version:  %s ", http->methode, http->URL, http->version); 
    afficheLig(http->lig->tete); 
    printf("Corps Requete : %s\n ",http->corpsreq); 
}
LigneEntete*  inserer_elem_fin(LigneEntete* lig, LigneEntete* l){
    if(lig==NULL){
        l->tete=l; 
        return l; 
    } 
    while(lig->suiv!=NULL) lig=lig->suiv; 
    l->tete=lig->tete; 
    lig->suiv=l;  
    return lig; 
}
LigneEntete* ajoutfin(char* ch){

    int j=0;  
    int compt=0; 
    LigneEntete* l= malloc(sizeof(LigneEntete));
    char* chaine = malloc(strlen(ch)*sizeof(char)); 
    for(int i=0; i<strlen(ch); i++){
        if(ch[i]=='2' && ch[i+1]=='0' && compt==0){
            chaine[j]='\0'; 
            l->nomchamp=strdup(chaine); 
            j=0; 
            compt++; 
            i=i+2; 
        }
        if(compt>0 && ch[i]=='2' && ch[i+1]=='0'){
            i=i+2; 
        }
        else{
            chaine[j]=ch[i]; 
            j++; 
        }
    }
    chaine[j]='\0'; 
    l->valeurchamp=strdup(chaine); 
    l->suiv=NULL; 
    //printf("valeur champ %s\n", l->valeurchamp); 
    //printf("nom champ %s\n", l->nomchamp); 
    //afficheLig(lig); 
    //printf(" %d %d\t",lig==NULL, NULL==NULL); 
    free(chaine); 
    //printf("je passe \n"); 
    return l; 
}
void lecturehttp(char* chaine, HTTP* http){
    http->methode=NULL; 
    http->URL=NULL; 
    http->version=NULL; 
    http->lig=NULL;  
    http->corpsreq=NULL; 

    char*ch= malloc(strlen(chaine)*sizeof(char)); 
    int j=0; 
    for(int i=0; i<strlen(chaine); i++){
        if(chaine[i]=='2' && chaine[i+1]=='0'){
            if(http->methode==NULL){
                ch[j]='\0'; 
                http->methode=strdup(ch); 
                //printf("methode : %s", http->methode); 
                j=0; 
                i=i+2; 
            }
            else{
                if(http->URL==NULL){
                    ch[j]='\0'; 
                    http->URL=strdup(ch); 
                    j=0; 
                    i=i+2; 
                    //printf("URL : %s", http->URL); 
                     
                }
            }
        }
        if(chaine[i]=='0' && (chaine[i+1]=='d'||chaine[i+1]=='D') && chaine[i+2]=='0' && (chaine[i+3]=='a'|| chaine[i+3]=='A')){
            i=i+3; 
            if(http->version==NULL){
                ch[j]='\0'; 
                http->version=strdup(ch); 
                j=0; 
                //printf("version : %s\n", http->version); 
            }
            else{
                //printf(" %c %c %c %c \t", chaine[i+1],chaine[i+2], chaine[i+3], chaine[i+4]); 
                if(chaine[i+1]=='0' && (chaine[i+2]=='d'||chaine[i+2]=='D') && chaine[i+3]=='0' && (chaine[i+4]=='a'|| chaine[i+4]=='A')){
                    //Alors on commence le corps
                    ch[j]='\0'; 
                    //printf("ligne de fin 1 : %s\n", ch); 
                    http->lig=inserer_elem_fin(http->lig,ajoutfin(ch)); 
                    j=0; 
                    i=i+4; 
                }
                else{
                    ch[j]='\0'; 
                    //printf("ligne de fin  : %s\n", ch); 
                    http->lig=inserer_elem_fin(http->lig,ajoutfin(ch)); 
                    //afficheLig(http->lig);  
                    j=0; 
                }

            }
            
        }
        else{
            //printf("  %c ", chaine[i]); 
            ch[j]=chaine[i]; 
            j++; 
        }
    }
    ch[j]='\0'; 
    http->corpsreq=strdup(ch); 
    free(ch); 
    free(chaine); 
}#include "projet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void hextoAscii(char* ch){
    char c[3]; 
    c[3]='\0'; 
    int i; 
    for( i=0; i<(strlen(ch)/2); i++){
        c[0]=ch[i]; 
        c[1]=ch[i+1]; 
        ch[i]=(char) hexa_int(c); 
        i=i+1; 
    }
    printf(" %s",ch); 
    ch[i]='\0'; 
}
void freeLig(LigneEntete* lig){
    while(lig){
        free(lig->nomchamp); 
        free(lig->valeurchamp); 
        lig=lig->suiv; 
    }
}
void freeHTTP(HTTP* http){
    free(http->methode); 
    free(http->URL); 
    free(http->version); 
    freeLig(http->lig); 
    free(http->corpsreq); 
}
void afficheLig(LigneEntete* lig){
    
     while(lig!=NULL){ 
        printf("Entete ligne : nom champ %s valeur champ %s \n", lig->nomchamp, lig->valeurchamp); 
        lig=lig->suiv; 
    }
}
void afficheHTTP(HTTP* http){
    printf("HTTP: methode : %s URL: %s Version:  %s ", http->methode, http->URL, http->version); 
    afficheLig(http->lig->tete); 
    printf("Corps Requete : %s\n ",http->corpsreq); 
}
LigneEntete*  inserer_elem_fin(LigneEntete* lig, LigneEntete* l){
    if(lig==NULL){
        l->tete=l; 
        return l; 
    } 
    while(lig->suiv!=NULL) lig=lig->suiv; 
    l->tete=lig->tete; 
    lig->suiv=l;  
    return lig; 
}
LigneEntete* ajoutfin(char* ch){

    int j=0;  
    int compt=0; 
    LigneEntete* l= malloc(sizeof(LigneEntete));
    char* chaine = malloc(strlen(ch)*sizeof(char)); 
    for(int i=0; i<strlen(ch); i++){
        if(ch[i]=='2' && ch[i+1]=='0' && compt==0){
            chaine[j]='\0'; 
            l->nomchamp=strdup(chaine); 
            j=0; 
            compt++; 
            i=i+2; 
        }
        if(compt>0 && ch[i]=='2' && ch[i+1]=='0'){
            i=i+2; 
        }
        else{
            chaine[j]=ch[i]; 
            j++; 
        }
    }
    chaine[j]='\0'; 
    l->valeurchamp=strdup(chaine); 
    l->suiv=NULL; 
    //printf("valeur champ %s\n", l->valeurchamp); 
    //printf("nom champ %s\n", l->nomchamp); 
    //afficheLig(lig); 
    //printf(" %d %d\t",lig==NULL, NULL==NULL); 
    free(chaine); 
    //printf("je passe \n"); 
    return l; 
}
void lecturehttp(char* chaine, HTTP* http){
    http->methode=NULL; 
    http->URL=NULL; 
    http->version=NULL; 
    http->lig=NULL;  
    http->corpsreq=NULL; 

    char*ch= malloc(strlen(chaine)*sizeof(char)); 
    int j=0; 
    for(int i=0; i<strlen(chaine); i++){
        if(chaine[i]=='2' && chaine[i+1]=='0'){
            if(http->methode==NULL){
                ch[j]='\0'; 
                http->methode=strdup(ch); 
                //printf("methode : %s", http->methode); 
                j=0; 
                i=i+2; 
            }
            else{
                if(http->URL==NULL){
                    ch[j]='\0'; 
                    http->URL=strdup(ch); 
                    j=0; 
                    i=i+2; 
                    //printf("URL : %s", http->URL); 
                     
                }
            }
        }
        if(chaine[i]=='0' && (chaine[i+1]=='d'||chaine[i+1]=='D') && chaine[i+2]=='0' && (chaine[i+3]=='a'|| chaine[i+3]=='A')){
            i=i+3; 
            if(http->version==NULL){
                ch[j]='\0'; 
                http->version=strdup(ch); 
                j=0; 
                //printf("version : %s\n", http->version); 
            }
            else{
                //printf(" %c %c %c %c \t", chaine[i+1],chaine[i+2], chaine[i+3], chaine[i+4]); 
                if(chaine[i+1]=='0' && (chaine[i+2]=='d'||chaine[i+2]=='D') && chaine[i+3]=='0' && (chaine[i+4]=='a'|| chaine[i+4]=='A')){
                    //Alors on commence le corps
                    ch[j]='\0'; 
                    //printf("ligne de fin 1 : %s\n", ch); 
                    http->lig=inserer_elem_fin(http->lig,ajoutfin(ch)); 
                    j=0; 
                    i=i+4; 
                }
                else{
                    ch[j]='\0'; 
                    //printf("ligne de fin  : %s\n", ch); 
                    http->lig=inserer_elem_fin(http->lig,ajoutfin(ch)); 
                    //afficheLig(http->lig);  
                    j=0; 
                }

            }
            
        }
        else{
            //printf("  %c ", chaine[i]); 
            ch[j]=chaine[i]; 
            j++; 
        }
    }
    ch[j]='\0'; 
    http->corpsreq=strdup(ch); 
    free(ch); 
    free(chaine); 
}
