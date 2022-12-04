#ifndef PROJET_H
#define PROJET_H

typedef struct ethernet{
	char mac_source[13] ;
	char mac_dest[13] ;
	char type[4];
} Ethernet;

typedef struct option{
	char op[3];
	int octet; // pour L'option 0x07
	struct option * suiv; 
}Option; 

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
	Option* option;  
} IPV4; 

char* motsansespace(char*x ); 
int hexa_int(char* s);
void afficheoption(Option * option); 

// Ethernet 
Ethernet* lectureEthernet(char* chaine); 
void afficheEthernet(Ethernet* ether); 
Ethernet* lecture(char *name); 
void freeEthernet(Ethernet* ether); 

//IPV4
int lectureIPV4(char* chaine, IPV4* ipv4); 
void afficheIPV4(IPV4* ipv4); 
void freeIPV4(IPV4* ipv4 ); 

#endif
