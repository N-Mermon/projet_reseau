#ifndef PROJET_H
#define PROJET_H

typedef struct ethernet{
	char mac_source[12] ;
	char mac_dest[12] ;
	char type[2];
} Ethernet;

// Lecture.c 
char* motsansespace(char*x ); 
Ethernet* lectureEthernet(char* chaine); 
void afficheEthernet(Ethernet* ether); 
Ethernet* lecture(char *name); 

/*typedef struct ip_hx{
	char IHL;
	//char ToS[2]; initialiser à 0 en général
	char total_lenght[4];
	char Identifier[4];
	char 0_DF_MF_Frangmentoffset[4];
	char TTL[2];
	char protocole[2];
	char Header_Checksum[4];
	char Source_adresse[8];
	char Destination_adresse[8];
	char options_padding[16]
	} IP_hx;

typedef struct ip_dc{
	int IHL; //taille de l'entête IP (header+options) /4
	int total_lenght; // IP+ datas associées (data= lenght-4*IHL)
	int Identifier; //code d'identification (identique pour les fragment d'un même ensemble)
	int DF; //1 ou 0 Don't fragment
	int MF; //1 ou 0 More fragment
	int fragment_offset; //positionnement du fragment
	int TTL; //68 en général je crois, max 255
	char protocole[2];
	int Header_Checksum; //1 checksum : OK, 0 problème 
	int Source_adresse[4];
	int Destination_adresse[4];
	char options_padding[16]
	} IP_dc;
	
	
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
