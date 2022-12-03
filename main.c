#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "projet.h"

int main(){
    Ethernet* ether= lecture("trame1.txt"); 
    freeEthernet(ether); 
    return 0; 
}
