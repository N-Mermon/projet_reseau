#ifndef PROJET_H
#define PROJET_H

typedef struct ethernet{
	char mac_source[13] ;
	char mac_dest[13] ;
	char type[4];
} Ethernet;

typedef struct ipv4{
	char iHL[2]; 
	char totalLength[5]; 
	char identifier[5]; 
	char flags[5]; 
	char fragmentOffset[4]; //4 avec un pour le caratère de fin de chaine
	char ttl[3]; 
	char Protocol[3]; 
	char headerChecksum[5];
	char destAddress[9]; 
	char sourceAddress[9];
	char * option;  
} IPV4; 

char* motsansespace(char*x ); 

// Ethernet 
Ethernet* lectureEthernet(char* chaine); 
void afficheEthernet(Ethernet* ether); 
Ethernet* lecture(char *name); 
void freeEthernet(Ethernet* ether); 

//IPV4
void lectureIPV4(char* chaine, IPV4* ipv4); 
void afficheIPV4(IPV4* ipv4); 
void freeIPV4(IPV4* ipv4); 
/*typedef struct Reseau{
	Element_alignement_bar *premier_el;
	Element_alignement_bar *dernier_el;
	} Alignement_bar;

typedef struct alignement{
	Alignement_bar* x;
	Alignement_bar* y;
	} Alignement ;

typedef struct optimal{
	Alignement *al;
	int dist;
} Optimal

int Dist_Naif ( char* x, char*y, int taillex, int tailley);
int Dist_Naif_Rec (char* x, char*y, int i, int j, int c, int dist, int taillex, int tailley);
*/

#endif
