#ifndef PROJET_H
#define PROJET_H

typedef struct ethernet{
	char mac_source[13] ;
	char mac_dest[13] ;
	char type[5];
} Ethernet;

typedef struct option{
	char op[3];
	int octet; // pour L'option 0x07
	struct option * suiv; 
}Option; 

typedef struct optionTCP{
	char type[3]; 
	char longueur[3]; 
	char valeur[17]; 
	struct optionTCP* tete; 
	struct optionTCP* suiv; 
}OptionTCP;

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

typedef struct tcp{
	char sourcePort[5]; 
	char destPort[5]; 
	char sn[9]; 
	char an[9]; 
	int tHL; 
	char flags[4]; 
	char window[5]; 
	char checksum[5]; 
	char urgentPointer[5]; 
	OptionTCP* options; 
}TCP; 

typedef struct ligneEntete{
	struct ligneEntete* tete; 
	char* nomchamp; 
	char* valeurchamp; 
	struct ligneEntete *suiv; 
}LigneEntete; 

typedef struct http{
	char* methode; 
	char* URL; 
	char* version; 
	LigneEntete* lig; 
	char* corpsreq; 
}HTTP; 

typedef struct trame{
	Ethernet* eth; 
	IPV4* ipv4; 
	TCP* tcp; 
	HTTP* http; 
	struct trame * suiv; 
}Trame; 

char* motsansespace(char*x ); 
int hexa_int(char* s);
void afficheoption(Option * option); 

// Ethernet 
Ethernet* lectureEthernet(char* chaine); 
void afficheEthernet(Ethernet* ether);  
void freeEthernet(Ethernet* ether); 

//IPV4
int lectureIPV4(char* chaine, IPV4* ipv4); 
void afficheIPV4(IPV4* ipv4); 
void freeIPV4(IPV4* ipv4 ); 

//TCP
void freeTCP(TCP* tcp);
void freeOptionsTCP(OptionTCP * op); 
LigneEntete* ajoutfin(char* ch);
void afficheOptionTCP(OptionTCP* op); 
void afficheTCP(TCP* tcp); 
int lecturetcp(char* chaine, TCP* tcp); 

//HTTP
void freeLig(LigneEntete* lig); 
void freeHTTP(HTTP* http); 
void afficheLig(LigneEntete* lig); 
void afficheHTTP(HTTP* http); 
LigneEntete*  inserer_elem_fin(LigneEntete* lig, LigneEntete* l);  
void lecturehttp(char* chaine,HTTP* http); 
void hextoAscii(char* ch); 

//Trame
void afficheTrame(Trame* trame); 
void freeTrame(Trame* trame); 
Trame* lecture(char *name); 

#endif
