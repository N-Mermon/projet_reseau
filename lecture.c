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
    //int currentchar=0; 
    //int indice =0; 
    Ethernet* ethernet; 
    char* chaine= malloc(TAILLE_MAX*sizeof(char)); 
    char* ligne_suiv= malloc(TAILLE_MAX*sizeof(char)); 

    if(file==NULL){
        return NULL; 
    }
    printf("coucou"); 
    //do{
       fgets(chaine, TAILLE_MAX, file); 

        // lecture d'un trame ethernet 
        chaine = motsansespace(chaine);
        //Taille max d'une ligne sans espace = 36  
        printf(" chaine : %s\n", chaine); 
        ethernet=lectureEthernet(chaine); 
        
        afficheEthernet(ethernet); 

        //lecture de IPV4 
        if(strcmp(ethernet->type,"0800")==0){
            printf("La couche reseau est IPV4\n");
            IPV4* ipv4= malloc(sizeof(IPV4));  

            //initialisation du champ IHL
            ipv4->iHL[0]= chaine[33]; 
            ipv4->iHL[1]= '\0'; 

            printf("IHL : %s\n" , ipv4->iHL); 

            //On parcours une nouvelle ligne
            int marche = fseek(file, 0075, SEEK_SET); 
            //printf("marche : %d\n",marche); 
            fgets(chaine, TAILLE_MAX, file);
            //printf("Chaine : %s\n", chaine );

            marche = fseek(file, 0165, SEEK_SET); 
            printf("marche : %d\n",marche); 
            fgets(ligne_suiv, TAILLE_MAX, file);
            printf("ligne_suiv : %s\n", ligne_suiv );

            chaine = strcat(chaine, ligne_suiv); 
            chaine = motsansespace(chaine);
            printf("Chaine apres concatenation: %s\n", chaine );
            printf(" lecture IPV4 : %d \n", lectureIPV4(chaine,ipv4)); 

            afficheIPV4(ipv4); 

            if(strcmp(ipv4->Protocol,"01")==0){
                //Protocole ICMP
            }
            if(strcmp(ipv4->Protocol,"06")==0){
                //Protocole TCP 
            }
            if(strcmp(ipv4->Protocol,"11")==0){
                //Protocole UDP
            }
        }

    fclose(file); 
    return ethernet; 
}
