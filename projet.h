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
