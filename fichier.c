#include "projet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
void sauvegardeTxt(Trame* t, char*name){
    FILE* f= fopen(name,"w"); 
    if(f==NULL){
        printf("Erreur à l'ouverture "); 
        return; 
    }
    Trame * temp=t; 
	while(temp){
		fprintf(f,"Ethernet \nMAC source : %s\tMAC Dest : %s\tType: %s\n",temp->eth->mac_source,temp->eth->mac_dest,temp->eth->type); 
		fprintf(f,"IPV4 \nIHL: %s\tTotalLength: %s\tIdentifier: %s\tFlags: %s\tFragmentoffset: %s\nTTL: %s\tProtocole: %s\tHeaderChecksum: %s\nDest Address: %s\tSource Address: %s\n", 
		temp->ipv4->iHL,temp->ipv4->totalLength,temp->ipv4->identifier,
		temp->ipv4->flags,temp->ipv4->fragmentOffset,
		temp->ipv4->ttl,temp->ipv4->Protocol,
		temp->ipv4->headerChecksum,temp->ipv4->destAddress,
		temp->ipv4->sourceAddress); 
		fprintf(f,"TCP \nSource Port : %s\tDest Port: %s\nSN: %s\nAN: %s\nTHL: %d\tFlags: %s\tWindow: %s\nChecksum: %s\tUrgentPointer: %s\n",
		temp->tcp->sourcePort,temp->tcp->destPort,temp->tcp->sn,temp->tcp->an,temp->tcp->tHL,temp->tcp->flags,temp->tcp->window,temp->tcp->checksum, temp->tcp->urgentPointer);
		fprintf(f,"HTTP \nMethode : %s\tURL: %s\nVersion: %s", temp->http->methode,temp->http->URL,temp->http->version); 
		fprintf(f,"\n\n"); 
		temp= temp->suiv;  
	}
	free(temp); 
    fclose(f); 
}
void decoupe(char* nom){

	char* chaine=(char*)malloc(sizeof(char)*60);
	FILE* file= fopen(nom, "r"); 
	int t=0;
	char* num = malloc(sizeof(char)*7);
	if(file==NULL){
				printf("erreur à l'ouverture du fichier\n"); 
	}
	int i=1,j=0;
	while ( (chaine!=NULL|| j==0 )&& i< 5 ){
		sprintf(num, "%d", (i));
		FILE* f= fopen(num, "w"); 
			if(file==NULL){
				printf("erreur à l'ouverture du fichier\n"); 
			}
			if(j!=0){
				fprintf(f,"%s",chaine);
			}
			t=(fgets(chaine, 59, file)!=NULL);
			while(t==1 && (chaine[0]!='0' || chaine[1]!='0' || chaine[2]!='0' || chaine[3]!='0' || j==0)){
				printf("%s\n",chaine);
				fprintf(f,"%s",chaine);
				j++;
			t=(fgets(chaine, 59, file)!=NULL);
			}
		fclose(f);
		i++;
	}
		fclose(file);
}
Trame* assemble(int v){
	Trame *resultat;
	Trame *temp=malloc(sizeof(Trame));
	temp=lecture("1");
	resultat=temp;

printf("aa\n");
	printf("%s\n", TCP_to_string(temp->tcp));
	char* name = malloc(sizeof(char)*7);
	for(int k=2;k<=v;k++){
printf("bb\n");
		sprintf(name, "%d", (k));
		//strcat(name,".txt");
printf("%s\n",name);
		Trame *tram=lecture(name);
printf("aa\n");
		temp->suiv=tram;
printf("dd\n");
		temp=tram;
	}
printf("cc\n");
	return resultat;



}
