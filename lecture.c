#include "projet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAILLE_MAX 55

char* motsansespace(char*x ){
    char* s= malloc(strlen(x)*sizeof(char)); 
    int j=0; 
    for(int i=0; i<strlen(x);i++){
        if(x[i]!= ' '){
            s[j]=x[i]; 
            j++; 
        }
    }
    s[j]='\0'; 
    printf("Après la suppression des espaces : %s", s); 
    //free(x); 
    return s; 
}
//Couche Liaison 
//Ethernet
Ethernet* lectureEthernet(char* chaine){
    Ethernet* ethernet = malloc(sizeof(Ethernet));
    for(int i=0; chaine[i]!='\0'; i++){
        if((i<16)&&(i>=4)){
            ethernet->mac_source[i-4]=chaine[i]; 
        
        }
        
        if((i<28)&&(i>=16)){
            ethernet->mac_dest[i-16]=chaine[i]; 
        }
        if((i<32)&&(i>=28)){
            
            ethernet->type[i-28]=chaine[i]; 
        }
    }
    ethernet->mac_dest[12]='\0'; 
    ethernet->mac_source[12]='\0'; 
    ethernet->type[4]='\0'; 
    return ethernet; 
}
void afficheEthernet(Ethernet* ether){
    printf("Mac source : %s , Mac dest : %s , type : %s ", ether->mac_source, ether->mac_dest, ether->type);  
}
void freeEthernet(Ethernet* ether){
    free(ether->mac_dest); 
    free(ether->mac_source); 
    free(ether); 
}
// Couche Réseau 
//IPV4
void lectureIPV4(char* chaine, IPV4* ipv4){
    int fragmentoffset=0; 
    ipv4->fragmentOffset[0]=0; 
    for(int i=0; chaine[i]!='\0'; i++){
        if((i<10)&&(i>=6)){
            ipv4->totalLength[i-6]=chaine[i];      
        }
        if((i<15)&&(i>=10)){
            ipv4->identifier[i-10]=chaine[i]; 
        }
        if((i<20)&&(i>=15)){
            ipv4->flags[i-15]=chaine[i];
            fragmentoffset= fragmentoffset+chaine[i];
        }
        if(fragmentoffset>0){
            if((i<24)&&(i>=20)){
                ipv4->fragmentOffset[i-20]=chaine[i];
            }
            if((i<27)&&(i>=24)){
                ipv4->ttl[i-24]=chaine[i];
            }
            if((i<30)&&(i>=27)){
                ipv4->Protocol[i-27]=chaine[i];
            }
            if((i<35)&&(i>=30)){
                ipv4->headerChecksum[i-30]=chaine[i];
            }
            if(i>=35){
                ipv4->destAddress[i-35]=chaine[i]; 
            }
        }else{
            if((i<23)&&(i>=20)){
                ipv4->ttl[i-20]=chaine[i];
            }
            if((i<26)&&(i>=23)){
                ipv4->Protocol[i-27]=chaine[i];
            }
            if((i<31)&&(i>=26)){
                ipv4->headerChecksum[i-30]=chaine[i];
            }
            if(i>=31){
                ipv4->destAddress[i-31]=chaine[i]; 
                //6 caractères dans destAddress
            }
        }
    ipv4->iHL[4]='\0'; 
    ipv4->identifier[4]='\0'; 
    ipv4->flags[4]='\0'; 
    ipv4->fragmentOffset[3]='\0'; 
    ipv4->ttl[2]='\0'; 
    ipv4->Protocol[2]='\0'; 
    ipv4->headerChecksum[4]='\0'; 
    ipv4->destAddress[8]='\0'; 
    ipv4->sourceAddress[8]='\0'; 

    }
}
void afficheIPV4(IPV4* ipv4){
    if(strcmp(ipv4->fragmentOffset,'0')){
        printf("4 IHL: %s TOS: 00, TotalLenght : %s , Identifier : %s , flags: %s ", ipv4->iHL, ipv4->totalLength, ipv4->identifier, ipv4->flags); 
    }else{
        printf("4 IHL: %s TOS: 00, TotalLenght : %s , Identifier : %s , flags: %s, FragmentOffset : %s ", ipv4->iHL, ipv4->totalLength, ipv4->identifier, ipv4->flags, ipv4->fragmentOffset); 
    }
    printf("TTL: %s Protocole: %s , HeaderChecksum: %s ", ipv4->ttl,ipv4->Protocol, ipv4->headerChecksum );
    printf("DestAddress: %s sourceAddress: %s \n", ipv4->destAddress, ipv4->sourceAddress); 
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
}
//Lecture de l'ensemble du fichier texte 
Ethernet* lecture(char *name){
    //lecture d'une trame à partir d'un fichier 
    FILE* file= fopen(name, "r"); 
    //int currentchar=0; 
    //int indice =0; 
    Ethernet* ethernet; 
    char* chaine= malloc(TAILLE_MAX*sizeof(char)); 


    if(file==NULL){
        return NULL; 
    }
    printf("coucou"); 
    //do{
       fgets(chaine, TAILLE_MAX, file); 

        // lecture d'un trame ethernet 
        chaine = motsansespace(chaine);
        //Taille max d'une ligne sans espace = 36  
        ethernet=lectureEthernet(chaine); 
        printf(" chaine : %s\n", chaine); 
        afficheEthernet(ethernet); 

        //lecture de IPV4 
        if(strcmp(ethernet->type,"0800")==0){
            printf("La couche réseau est IPV4\n");
            IPV4* ipv4= malloc(sizeof(IPV4));  

            //initialisation du champ IHL
            ipv4->iHL[0]= chaine[33]; 
            ipv4->iHL[1]= '\0'; 

            //On parcours une nouvelle ligne
            fgets(chaine, TAILLE_MAX, file);
            chaine = motsansespace(chaine);
            lectureIPV4(chaine,ipv4); 

            afficheIPV4(ipv4); 

            /*if(strcmp(ipv4->Protocol,"01")==0){
                //Protocole ICMP
                //pas besoin de le faire selon le sujet 
            }
            */
            if(strcmp(ipv4->Protocol,"06")==0){
                //Protocole TCP 
            }
            /*if(strcmp(ipv4->Protocol,"11")==0){
                //Protocole UDP
            }*/ //Pas besoin de le faire selon le sujet 
        }

    fclose(file); 
    return ethernet; 
}
