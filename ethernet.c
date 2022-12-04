#include "projet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//Couche Liaison 
//Ethernet
Ethernet* lectureEthernet(char* chaine){
    Ethernet* ethernet = malloc(sizeof(Ethernet));
    for(int i=0; chaine[i]!='\0'; i++){
        if((i<16)&&(i>=4)) ethernet->mac_source[i-4]=chaine[i]; 
        if((i<28)&&(i>=16)) ethernet->mac_dest[i-16]=chaine[i]; 
        if((i<32)&&(i>=28)) ethernet->type[i-28]=chaine[i]; 
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
