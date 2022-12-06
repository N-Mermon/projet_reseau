#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "projet.h"

int main(){
    Trame* trame= lecture("trame1.txt"); 
    Trame* trame1= lecture("trame2.txt"); 
    trame->suiv=trame1; 
    freeTrame(trame);  
    return 0; 
}
