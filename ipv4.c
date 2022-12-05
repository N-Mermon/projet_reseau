#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "projet.h"

// Couche Réseau 
//IPV4
int lectureIPV4(char* chaine, IPV4* ipv4){
    ipv4->totalLength[4]='\0';
    ipv4->identifier[4]='\0'; 
    ipv4->flags[4]='\0'; 
    ipv4->fragmentOffset[3]='\0'; 
    ipv4->ttl[2]='\0'; 
    ipv4->Protocol[2]='\0'; 
    ipv4->headerChecksum[4]='\0'; 
    ipv4->destAddress[8]='\0'; 
    ipv4->sourceAddress[8]='\0'; 

    int fragmentoffset=0; 
    
    int option =(hexa_int(ipv4->iHL))*4-20;
    printf("option : %d \n", option); 

    Option * tete= ipv4->option;  

    
    ipv4->fragmentOffset[0]=0; 
    //remplissage de ipv4
    for(int i=0; chaine[i]!='\0'; i++){
        if((i<4)&&(i>=0)) ipv4->totalLength[i]=chaine[i];   
        if((i<8)&&(i>=4)) ipv4->identifier[i-4]=chaine[i]; 
        if((i<12)&&(i>=8)){
            ipv4->flags[i-8]=chaine[i];
            if(chaine[i]!='0'){
                fragmentoffset=0; 
                printf("chaine : %c ", chaine [i]); 
            }
        }
        if(fragmentoffset!=0){
            //printf("fragmentoffset %d\t",fragmentoffset);
            if((i<16)&&(i>=12)) ipv4->fragmentOffset[i-12]=chaine[i];
            if((i<19)&&(i>=16)) ipv4->ttl[i-16]=chaine[i];
            if((i<21)&&(i>=19)) ipv4->Protocol[i-19]=chaine[i];
            if((i<25)&&(i>=21)) ipv4->headerChecksum[i-21]=chaine[i];
            if((i>=25 && i<32) ) ipv4->destAddress[i-25]=chaine[i];
            if(i==36) ipv4->destAddress[7]=chaine[i];
            if((i>=37)&&(i<45)) ipv4->sourceAddress[i-37]=chaine[i]; 
            if((option==0)&&(i>=45)){
                printf("Il n'y a pas d'option \n"); 
                free(tete); 
                ipv4->option=NULL; 
                return i; 
            }
            if((i>=45)&&(option!=0)){
                if(chaine[i]=='0' && chaine[i+1]=='\0'){
                    //End of Option List
                    tete= malloc(sizeof(Option)); 
                    tete->op[0]='0';
                    tete->op[1]='0';
                    tete->op[2]='\0';
                    tete->octet= 0; 
                    tete= tete; 
                    return i++; 
                }
                else {
                    if(chaine[i]=='0'&& chaine[i+1]=='1'){
                    //No Operation : aligner le debut de l'option suivante sur 32bits 
                    tete= malloc(sizeof(Option)); 
                    tete->op[0]='0';
                    tete->op[1]='1';
                    tete->op[2]='\0';
                    tete->octet= 0; 
                    tete= tete->suiv;
                    
                    continue; 
                    } 
                    else if(chaine[i]=='0'&& chaine[i+1]=='7'){
                    //Record Route : Permet d'enregistrer l'adesse IP de cahque passerelle traversée
                    tete= malloc(sizeof(Option)); 
                    tete->op[0]='0';
                    tete->op[1]='7';
                    tete->op[2]='\0';
                    char c[3]; 
                    c[0]=chaine[i+2]; 
                    c[1]=chaine[i+3]; 
                    c[2]='\0'; 
                    tete->octet= hexa_int(c); 
                    tete= tete->suiv;
                    i=i+3; 
                    continue; 
                    } 
                    else {
                        tete= malloc(sizeof(Option)); 
                        tete->op[0]=chaine[i];
                        tete->op[1]=chaine[i+1];
                        tete->op[2]='\0';
                        tete->octet= 0; 
                        tete= tete->suiv;
                        i=i+1; 
                        continue; 
                    }
                }
            }
        }else{
            if((i<14)&&(i>=12)) ipv4->ttl[i-12]=chaine[i];
            if((i<16)&&(i>=14)) ipv4->Protocol[i-14]=chaine[i];
            if((i<20)&&(i>=16)) ipv4->headerChecksum[i-16]=chaine[i];
            if((i>=20)&&(i<28)) ipv4->destAddress[i-20]=chaine[i]; 
            //8 caractères dans destAddress
            if(i>=28 && i<32) ipv4->sourceAddress[i-28]=chaine[i]; 
            if((i>=36 && i<40)) ipv4->sourceAddress[i-36+4]=chaine[i]; 
            if((option==0)&&(i>=40)){
                printf("Il n'y a pas d'option \n"); 
                free(tete); 
                ipv4->option=NULL; 
                return i; 
            }
            if((i>=40)&&(option!=0)){
                if(chaine[i]=='0' && chaine[i+1]=='0'){
                    //End of Option List
                    tete= malloc(sizeof(Option)); 
                    tete->op[0]='0';
                    tete->op[1]='0';
                    tete->op[2]='\0';
                    tete->octet= 0; 
                    tete= tete;  
                    return i++; 
                }
                else {
                    if(chaine[i]=='0'&& chaine[i+1]=='1'){
                    //No Operation : aligner le debut de l'option suivante sur 32bits 
                    tete= malloc(sizeof(Option)); 
                    tete->op[0]='0';
                    tete->op[1]='1';
                    tete->op[2]='\0';
                    tete->octet= 0; 
                    tete= tete->suiv;
                    continue; 
                    } 
                    else if(chaine[i]=='0'&& chaine[i+1]=='7'){
                        //Record Route : Permet d'enregistrer l'adesse IP de cahque passerelle traversée
                        tete= malloc(sizeof(Option)); 
                        tete->op[0]='0';
                        tete->op[1]='7';
                        tete->op[2]='\0';
                        char c[3]; 
                        c[0]=chaine[i+2]; 
                        //printf(" i = %d i+2: %c", i,  chaine[i+2]); 
                        c[1]=chaine[i+3]; 
                        c[2]='\0'; 
                        //printf(" c: %s",  c); 
                        tete->octet= hexa_int(c); 
                        //afficheoption(ipv4->option); 
                        tete= tete->suiv;
                        i=i+3; 
                        //printf(" tout va bien %c", chaine[i]); 
                        continue; 
                    } 
                    else {
                        //printf(" tout va bien "); 
                        tete= malloc(sizeof(Option)); 
                        tete->op[0]=chaine[i];
                        tete->op[1]=chaine[i+1];
                        tete->op[2]='\0';
                        tete->octet= 0; 
                        afficheoption(tete); 
                        tete= tete->suiv;
                        i=i+1; 
                        continue; 
                    }

                }//fin du else si l'option n'est pas 0x00
            }//Fin du if option 

        }//fin du else
    
    } // fin de la boucle for
    return strlen(chaine); 
}//fin de lectureIPV4
void afficheIPV4(IPV4* ipv4){
    if(strcmp(ipv4->flags,"00")==0){
        printf("IPV4 IHL: %s TOS: 00, TotalLenght : %s , Identifier : %s , flags: %s ", ipv4->iHL, ipv4->totalLength, ipv4->identifier, ipv4->flags); 
    }else{
        printf("IPV4 IHL: %s TOS: 00, TotalLenght : %s , Identifier : %s , flags: %s, FragmentOffset : %s ", ipv4->iHL, ipv4->totalLength, ipv4->identifier, ipv4->flags, ipv4->fragmentOffset); 
    }
    printf("TTL: %s Protocole: %s , HeaderChecksum: %s ", ipv4->ttl,ipv4->Protocol, ipv4->headerChecksum );
    printf("DestAddress: %s sourceAddress: %s ", ipv4->destAddress, ipv4->sourceAddress); 
    afficheoption(ipv4->option); 

}
void freeIPV4(IPV4* ipv4 ){
    free(ipv4->iHL); 
    free(ipv4->totalLength); 
    free(ipv4->identifier); 
    free(ipv4->flags); 
    free(ipv4->fragmentOffset); 
    free(ipv4->ttl); 
    free(ipv4->Protocol); 
    free(ipv4->headerChecksum); 
    free(ipv4->destAddress); 
    free(ipv4->sourceAddress); 
    free(ipv4); 
}
