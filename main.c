#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "projet.h"

int main(){
    //Trame* trame= lecture("trame1.txt"); 
    //Trame* trame1= lecture("trame2.txt"); 
    //httptoAscii(trame->http); 
    //afficheTrame(trame); 
    //printf(" je suis : %c", 73);
    //trame->suiv=trame1; 
    //printf("affiche HTTP corps : %s", trame->http->corpsreq); */

    Trame**t = lirefichier("trame1.txt"); 
    printf("Je passe "); 
    afficheTrame(t[0]); 
    //hextoAscii("73207475"); 
    //freeTrame(trame);  
    return 0; 
}
