#include <projet.h>
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

Ethernet* lectureEthernet(char* chaine){
    Ethernet* ethernet = malloc(sizeof(Ethernet));
    chaine= motsansespace(chaine); 
    for(int i=0; chaine[i]!='\0'; i++){
        if((i<18)&&(i>=4)){
            ethernet->mac_source[i-4]=chaine[i]; 
        }
        if((i<30)&&(i>=18)){
            ethernet->mac_dest[i-18]=chaine[i]; 
        }
        if((i<34)&&(i>=30)){
            ethernet->type[i-30]=chaine[i]; 
        }
    }
    return ethernet; 
}
void afficheEthernet(Ethernet* ether){
    printf("Mac source : %s , Mac dest : %s , type : %s ", ether->mac_source, ether->mac_dest, ether->type);  
}

Ethernet* lecture(char *name){
    //lecture d'une trame à partir d'un fichier 
    FILE* file= fopen(name, "r"); 
    //int currentchar=0; 
    //int indice =0; 
    Ethernet* ethernet; 
    char chaine[TAILLE_MAX]=""; 


    if(file==NULL){
        return NULL; 
    }
    //do{
       fgets(chaine, TAILLE_MAX, file); 

        // lecture d'un trame ethernet 
        ethernet=lectureEthernet(chaine); 
        printf(" chaine : %s\n", chaine ); 
        afficheEthernet(ethernet); 


    fclose(file); 
    return ethernet; 
}
