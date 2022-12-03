#ifndef TACHEA_H
#define TACHEA_H

typedef struct element_alignement_bar{
	int gap; // 0 ou 1
	char lettre; // A,G,C ou T
	struct element_alignement_bar *prec;
	struct element_alignement_bar *suiv;
} Element_alignement_bar;

typedef struct Alignement_bar{
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
} Optimal;

int Dist_Naif ( char* x, char*y, int taillex, int tailley);
int Dist_Naif_Rec (char* x, char*y, int i, int j, int c, int dist, int taillex, int tailley);

#endif
