#include "projet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAILLE_MAX 56

int hexa_int(char* s){
    int x= 0; 
    unsigned char c= 0;
    while(*s!='\0'){
        if(*s>= '0' && *s <='9') c= *s-'0'; 
        else if(*s>= 'a' && *s <='f') c= *s-'a'+10; 
        else if(*s>= 'A' && *s <='F') c= *s-'A'+10; 
        else break; 
        x=x*16+c; 
        s++; 
    }

    return x; 
}
char* motsansespace(char*x ){
    char* s= malloc(strlen(x)*sizeof(char)); 
    int j=0; 
    for(int i=0; i<strlen(x);i++){
        if((x[i]!= ' ')&&(x[i]!='\n')){
            s[j]=x[i]; 
            j++; 
        }
    }
    s[j]='\0'; 
    //printf("Apres la suppression des espaces : %s", s); 
    //free(x); 
    return s; 
}
void afficheoption(Option * option){
    if(option==NULL) return; 
    while(option !=NULL){
        printf(" Option : %s %d \t", option->op, option->octet);
        option= option->suiv; 
        printf("vrai" ); 
    }
}

//Lecture de l'ensemble du fichier texte 
Ethernet* lecture(char *name){
    //lecture d'une trame à partir d'un fichier 
    FILE* file= fopen(name, "r"); 
    if(file==NULL){
        return NULL; 
    }
    //int currentchar=0; 
    //int indice =0; 
    Ethernet* ethernet; 
    //char* ligne_suiv= malloc(TAILLE_MAX*sizeof(char)); 

    char* chainetot = malloc(1000*sizeof(char)); 
    char* chaine= malloc(36*sizeof(char)); 
    // lecture intégrale du fichier texte
    while(fgets(chaine, TAILLE_MAX, file)!=NULL){
        chainetot= strcat(chainetot,chaine); 
    }
    chainetot=motsansespace(chainetot); 
    //un ligne fait 36 caractère sans espace et avec offset
    // sans offset elle en fait 32
    printf("chainetot : %s\n", chainetot); 
    int indice =7; 
    // lecture d'un trame ethernet 
    //Trame ethernet fait au maximum sans le préambule et seulement avec les adresses Mac et le type
    //: 28
    char* ch= malloc(36*sizeof(char)); 
    ch[35]='\0'; 
    while(indice<35){
        ch[indice-7]=chainetot[indice]; 
        indice++; 
    }
    //printf("\n chaine : %s", ch); 
    ethernet=lectureEthernet(ch); 
    afficheEthernet(ethernet); 
    free(ch); 

    //lecture de IPV4 
    if(strcmp(ethernet->type,"0800")==0){
        printf("La couche reseau est IPV4\n");
        IPV4* ipv4= malloc(sizeof(IPV4));  

        // intialisation du champs tos et de IHL
        ipv4->iHL[0]=chainetot[36];
        ipv4->iHL[1]='\0'; 
        //tos est pas défaut toujours à 0x00

        //Chaine pour ipv4
        //taille max =60 sans les data + 2 offset 
        indice=43; 
        char* ch= malloc(68*sizeof(char)); 
        ch[67]='\0'; 
        while(indice-43<68){
            ch[indice-43]=chainetot[indice];
            indice++;  
        } 

        //printf("\n chaine : %s", ch); 
        indice=43+lectureIPV4(ch,ipv4); 
        printf(" indice : %d\n", indice); 
        afficheIPV4(ipv4); 

        /*if(strcmp(ipv4->Protocol,"01")==0){
            //Protocole ICMP
        }*/
        if(strcmp(ipv4->Protocol,"06")==0){
            //Protocole TCP 
            char* ch= malloc(140*sizeof(char)); 
            
            int constante=indice; 
            while(indice-constante<140 && chainetot[indice]!='\0'){
                ch[indice-constante]=chainetot[indice];
                indice++;  
            } 
            ch[indice-constante]='\0'; 

            int reste=(constante-3)%36; 
            printf("reste: %d", reste); // on est à la reste ième case du début d'une ligne. 
            reste=reste-4; // on enlève le offset
            int findeligneds= 32-reste; // on est en fin de ligne dans 32-reste 

            TCP* tcp= malloc(sizeof(TCP)); 
            printf("\n chaine : %s", ch);
            indice= indice + lecturetcp(ch,tcp,findeligneds); 
            afficheTCP(tcp); 
            
        }
        /*if(strcmp(ipv4->Protocol,"11")==0){
            //Protocole UDP
        }*/ 
        
    
    }
    free(chaine); 
    free(ch); 
    free(chainetot); 
    fclose(file); 
    return ethernet; 
}
