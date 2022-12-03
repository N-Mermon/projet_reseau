#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "projet.h"

int main(){
    Ethernet* ether= lecture("trame1.txt"); 
    free(ether->mac_dest); 
    free(ether->mac_source); 
    free(ether); 
    return 0; 
}
