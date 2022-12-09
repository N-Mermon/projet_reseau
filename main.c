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

    decoupe("trame1.txt"); 
    Trame* t = assemble(7); 
    //afficheHTTP(t[0]->http); 
    //printf("Je passe "); 
    //printf("%s trame http dans main%d\n", t[0]->http->version, NULL==NULL); 
    afficheTrame(t); 
    sauvegardeTxt(t, "sauvegardeTrame.txt"); 
    traductionIP(t->ipv4->destAddress); 
    printf("\n%s\n",t->ipv4->destAddress); 
    //afficheTrame(t[1]); 
    //hextoAscii("73207475"); 
    freeTrame(t);
    //freeTrame(t[1]);   
    return 0; 
}
