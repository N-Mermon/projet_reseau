#include "projet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void freeTCP(TCP* tcp){
    free(tcp->sourcePort); 
	free(tcp->destPort); 
	free(tcp->sn); 
	free(tcp->an); 
	free(tcp->flags); 
	free(tcp->window); 
	free(tcp->checksum); 
	free(tcp->urgentPointer); 
	free(tcp->options); 
    free(tcp);
}
void afficheOptionTCP(OptionTCP* op){
    if(op==NULL) return; 
    while(op!=NULL){
        printf("Type: %s, longueur: %s, valeur : %s\t", op->type, op->longueur, op->valeur); 
        op=op->suiv; 
    }
}
void afficheTCP(TCP* tcp){
    printf("TCP NportS : %s, NportD : %s, SN: %s, AN: %s, ", tcp->sourcePort, tcp->destPort, tcp->sn, tcp->an); 
    printf("THL %d, flags: %s, fenetre : %s, checksum : %s, URG : %s ", tcp->tHL, tcp->flags, tcp->window, tcp->checksum,tcp->urgentPointer); 
    afficheOptionTCP(tcp->options); 
    printf("\n"); 
}
int lecturetcp(char* chaine, TCP* tcp){
    int m = strlen(chaine); 

    tcp->sourcePort[4]='\0';
    tcp->destPort[4]='\0';
    tcp->sn[8]='\0'; 
    tcp->an[8]='\0'; 
    tcp->flags[3]='\0'; 
    tcp->window[4]='\0'; 
    tcp->checksum[4]='\0'; 
    tcp->urgentPointer[4]='\0'; 

    OptionTCP* tete=tcp->options; 
    for(int i=0; i<m; i++ ){
        if(i<4 && i>=0) tcp->sourcePort[i]=chaine[i]; 
        if(i<8 && i>=4) tcp->destPort[i-4]=chaine[i]; 
        if(i<16 && i>=8) tcp->sn[i-8]=chaine[i]; 
        if(i<24 && i>=16) tcp->an[i-16]=chaine[i]; 
        if(i==24) {
            char c[1]; c[0]=chaine[i]; 
            tcp->tHL=hexa_int(c)*4; 
        }
        if(i<28 && i>=25) tcp->flags[i-25]=chaine[i]; 
        if(i<32 && i>=28) tcp->window[i-28]=chaine[i]; 
        if(i<36 && i>=32) tcp->checksum[i-32]=chaine[i]; 
        if(i<40 && i>=36) tcp->urgentPointer[i-36]= chaine[i]; 
        //Les options TCP
        if(i>=40 && (tcp->tHL-20>0)){
            if(chaine[i]=='0' && chaine[i+1]=='0'){
                tete= malloc(sizeof(OptionTCP)); 
                tete->type[0]= chaine[i]; 
                tete->type[1]= chaine[i+1]; 
                tete->type[2]= '\0'; 
                i++; 
                return i; 
            }
            if(chaine[i]=='0' && chaine[i+1]=='2'){
                //MSS
                tete= malloc(sizeof(OptionTCP)); 
                tete->type[0]= chaine[i]; 
                tete->type[0]= chaine[i+1]; 
                tete->type[2]= '\0'; 
                tete->longueur[0]= chaine[i+2]; 
                tete->longueur[1]= chaine[i+3]; 
                tete->longueur[2]= '\0'; 
                i=i+4; 
                int j=hexa_int(tete->longueur); 
                int k=0; 
                while(j!=0){
                    tete->valeur[k]=chaine[i]; 
                    j--; 
                    k++; 
                    i++; 
                }
                tete->type[k]= '\0'; 
                tete=tete->suiv; 
            }
            if(chaine[i]=='0' && chaine[i+1]=='4'){
                //SACK
                tete= malloc(sizeof(OptionTCP)); 
                tete->type[0]= chaine[i]; 
                tete->type[0]= chaine[i+1]; 
                tete->type[2]= '\0'; 
                tete->longueur[0]= chaine[i+2]; 
                tete->longueur[1]= chaine[i+3]; 
                tete->longueur[2]= '\0'; 
                tete->valeur[0]= '\0'; 
                i=i+3; 
                tete=tete->suiv; 
            }
            if(chaine[i]=='0' && chaine[i+1]=='8'){
                //Timestamp
                tete= malloc(sizeof(OptionTCP)); 
                tete->type[0]= chaine[i]; 
                tete->type[0]= chaine[i+1];
                tete->type[2]= '\0';  
                tete->longueur[0]= chaine[i+2]; 
                tete->longueur[1]= chaine[i+3]; 
                tete->longueur[2]= '\0'; 
                i=i+4; 
                int k=0; 
                while(k!=16){
                    tete->valeur[k]=chaine[i]; 
                    k++; 
                    i++; 
                }
                tete->valeur[k]= '\0'; 
                tete=tete->suiv; 
            }
            if(chaine[i]=='0' && chaine[i+1]=='1'){
                //NOP
                tete= malloc(sizeof(OptionTCP)); 
                tete->type[0]= chaine[i]; 
                tete->type[0]= chaine[i+1]; 
                tete->type[2]= '\0'; 
                tete->longueur[0]= 0; 
                tete->longueur[1]= 0; 
                tete->longueur[2]= '\0'; 
                tete->valeur[0]= '\0'; 
                i++; 
                tete=tete->suiv; 
            }
            if(chaine[i]=='0' && chaine[i+1]=='2'){
                //MSS
                tete= malloc(sizeof(OptionTCP)); 
                tete->type[0]= chaine[i]; 
                tete->type[0]= chaine[i+1]; 
                tete->type[2]= '\0'; 
                tete->longueur[0]= '0'; 
                tete->longueur[1]= '3'; 
                tete->longueur[2]= '\0'; 
                i=i+3; 
                tete->valeur[0]=chaine[i+1]; 
                tete->valeur[1]=chaine[i+2]; 
                tete->valeur[2]= '\0'; 
                i=i+2; 
                tete=tete->suiv; 
            }

        }
    }
    return m; 
    
}
