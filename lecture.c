#include "projet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAILLE_MAX 56

int hexa_int(char* s){
    int x= 0; 
    unsigned char c= 0;
    while(*s!='\0'){
        if(*s>= '0' && *s <='9') c= *s-'0'; 
        else if(*s>= 'a' && *s <='f') c= *s-'a'+10; 
        else if(*s>= 'A' && *s <='F') c= *s-'A'+10; 
        else break; 
        x=x*16+c; 
        s++; 
    }

    return x; 
}
char* motsansespace(char*x ){
    char* s= malloc(strlen(x)*sizeof(char)); 
    int j=0; 
    for(int i=0; i<strlen(x);i++){
        if((x[i]!= ' ')&&(x[i]!='\n')){
            s[j]=x[i]; 
            j++; 
        }
    }
    s[j]='\0'; 
    //printf("Apres la suppression des espaces : %s", s); 
    free(x); 
    return s; 
}
void afficheoption(Option * option){
    if(option==NULL) return; 
    while(option !=NULL){
        printf(" Option : %s %d \t", option->op, option->octet);
        option= option->suiv; 
        printf("vrai" ); 
    }
}
char* supprimeoffset(char* ch){
    char* chaine = malloc(strlen(ch)*sizeof(char)); 
    int i=4; 
    while(i<strlen(ch)){
        chaine[i-4]=ch[i];
        i++; 
    }
    free(ch); 
    chaine[i-4]='\0'; 
    return chaine; 
}
void freeTrame(Trame* trame){
    while(trame){
        freeEthernet(trame->eth); 
        freeIPV4(trame->ipv4); 
        freeTCP(trame->tcp); 
        freeHTTP(trame->http);
        trame=trame->suiv; 
    }
}
void afficheTrame(Trame* trame){
    while(trame){
        afficheEthernet(trame->eth); 
        afficheIPV4(trame->ipv4); 
        afficheTCP(trame->tcp); 
        afficheHTTP(trame->http); 
        printf("\n"); 
        trame=trame->suiv; 
    }

}

//Lecture de l'ensemble du fichier texte 
Trame* lecture(char *name){
    //lecture d'une trame à partir d'un fichier 
    FILE* file= fopen(name, "r"); 
    if(file==NULL){
        return NULL; 
    }

    Ethernet* ethernet; 
    Trame* trame= malloc(sizeof(Trame)); 

    char* chainetot = malloc(6000*sizeof(char)); 
    chainetot[0]='\0'; 
    char* chaine= malloc(55*sizeof(char)); 
    // lecture intégrale du fichier texte
    while(fgets(chaine, TAILLE_MAX, file)!=NULL){
        chaine= supprimeoffset(chaine); 
        //printf("chaine : %s\n",chaine); 
        chainetot=strcat(chainetot,chaine); 
    }
    chainetot=motsansespace(chainetot); 
    //printf("chainetot : %s\n", chainetot); 
    //un ligne fait 36 caractère sans espace et avec offset
    // sans offset elle en fait 32
    
    // lecture d'un trame ethernet 
    //Trame ethernet fait au maximum sans le préambule et seulement avec les adresses Mac et le type
    //: 28
    char* ch= malloc(29*sizeof(char)); 
    ch[28]='\0'; 
    //int indice nous permettera de garder le compte sur où nous sommes dans la chaine de caractère
    int indice = 28; 
    for(int i=0; i<28; i++){
        ch[i]=chainetot[i]; 
    }
    //printf("\n chaine : %s", ch); 
    ethernet=lectureEthernet(ch); 
    //afficheEthernet(ethernet); 
    free(ch); 

    trame->eth=ethernet; 
    //lecture de IPV4 
    if(strcmp(ethernet->type,"0800")==0){
        //printf("La couche reseau est IPV4\n");
        IPV4* ipv4= malloc(sizeof(IPV4));  
        indice++; //car le 4 ne nous interesse pas 
        // intialisation du champs tos et de IHL
        ipv4->iHL[0]=chainetot[indice];
        ipv4->iHL[1]='\0'; 
        //printf(" IHL : %s\t",ipv4->iHL ); 
        //tos est pas défaut toujours à 0x00

        //Chaine pour ipv4
        //taille max =60 sans les data + 2 offset 
        indice=32; 
        //on rajoute à indice la taille de iHL et de Tos
        char* ch= malloc(61*sizeof(char)); 
        ch[60]='\0'; 
        for(int i=0; ((i<60)&&(chainetot[indice]!='\0')); i++){
            ch[i]=chainetot[indice];
            indice++;  
        } 

        //printf("chaine : %s\n", ch); 
        indice=32+lectureIPV4(ch,ipv4); 
        //printf(" indice : %d\n", indice); 
        //afficheIPV4(ipv4); 
        trame->ipv4=ipv4; 
        /*if(strcmp(ipv4->Protocol,"01")==0){
            //Protocole ICMP
        }*/
        if(strcmp(ipv4->Protocol,"06")==0){
            //Protocole TCP 

            char* ch= malloc(121*sizeof(char)); 
            //60*2 car c'est en octet et nous a des hexadécimal 
            
            int constante=indice; 
            for(int i=0; i<120 && chainetot[indice]!='\0'; i++){
                ch[i]=chainetot[indice];
                indice++;  
            } 
            ch[120]='\0'; 
            

            TCP* tcp= malloc(sizeof(TCP)); 
            //printf("\n chaine : %s", ch);
            indice= constante + lecturetcp(ch,tcp); 
            
            afficheTCP(tcp); 
            free(ch);
            trame->tcp=tcp; 
            
            if(indice<strlen(chainetot)){
                //alors il y a http
                //printf("\n %d", indice); 
                ch= malloc((strlen(chainetot)-indice+1)*sizeof(char)); 
                //60*2 car c'est en octet et nous a des hexadécimal 
            
                for(int i=0; chainetot[indice]!='\0'; i++){
                    ch[i]=chainetot[indice];
                    indice++;  
                } 
                ch[indice]='\0'; 
                //printf("http chaine : %s \n", ch); 
                HTTP* http= malloc(sizeof(HTTP)); 
                lecturehttp(ch,http); 
                //afficheHTTP(http);
                trame->http=http;  

                //printf(" %c ", 73); 
            }
        }
        /*if(strcmp(ipv4->Protocol,"11")==0){
            //Protocole UDP
        }*/ 
    
    }
    free(chaine); 
    free(ch); 
    free(chainetot); 
    fclose(file); 
    return trame; 
}
