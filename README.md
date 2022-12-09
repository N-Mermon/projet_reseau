# projet_reseau

Readme -Projet Réseau 

Le code est divisé en plusieurs fichiers .c qui sont compilés grâce à un Makefile. 

Fichier.c
Nous avons un fichier fichier.c qui va prendre le fichier text que nous aurons donné en paramètre de la fonction découpe et va découper le fichier de façon à analyser chaque trame. Cette fonction doit être combinée avec la fonction assemble qui va nous permettre d’avoir une liste de Trame. Enfin ce fichier contient également une fonction sauvegardeTxt qui permet de sauvegarder la liste de Trame dans un fichier. 

Lecture.c
Dans ce fichier nous avons une fonction hexa _int qui nous permet de passer d’une chaine d’hexadécimales à un entier. Il y a aussi une fonction motsansespace qui prend en paramètre une chaine de caractère. Cette fonction va permettre d’enlever les espaces à une chaine de caractères. 
AFFICHEOPTION(OPTION* OPTION) : cette fonction permet d’afficher les options de l’entête IP s’il y en a. 
SUPPRIMEOFFSET(CHAR* CH) : cette fonction va permettre d’enlever les offsets d’une chaine de caractères. Elle nous sera utile lors qu’on parcourra le fichier texte ligne par ligne. 

FREETRAME(TRAME* TRAME) : Cette fonction permet de libérer une trame et d’éviter les fuites mémoires. 
AFFICHETRAME(TRAME* TRAME) : Cette fonction permet d’afficher une liste de trame. Elle ne renvoi rien et affiche sur le terminal la liste de trame. 
LECTURE(CHAR* NAME) : Cette fonction prend un fichier texte ne contenant qu’une trame et analyse les information de la trame dans des structures (struct ethernet, struct ipv4, struct tpc, struct http). Ces structures seront réunion dans une autre structure appelée Trame qui constitue une liste de trames. Elle retourne une structure trame avec un seul élément. 


Ethernet.c

ETHERNET* LECTUREETHERNET(CHAR* CHAINE) : Cette fonction prend une chaine de caractère est créée une structure ethernet. Elle va lire les informations utiles dans cette trame. 
VOID AFFICHEETHERNET(ETHERNET*ETHER) : permet d’afficher la structure internet. 
VOID FREEETHERNET(ETHERNET* ETHER) : permet de libérer la mémoire alloué par malloc et de supprime ether. 
IPV4.c
Int lectureIPV4 (char* chaine, IPV4* ipv4) : cette fonction permet à partir d’une chaine de caractères d’implémenter ipv4 mis en paramètre. Elle renvoie un entier pour savoir quand est-ce qu’on s’arrête dans la chaine. 
Il y a également une fonction d’affichage de la structure ipv4 et une fonction freeIPV4 pour libérer la mémoire. Dans IPV4 on peut avoir des options. Pour afficher les options on a une fonction d’affichage dans lecture.c. 
La fonction traductionIP prend une chaine de caractères hexadécimales et la modifie pour qu'elle renvoie l'adresse IP correcte. 

tcp.c
Dans TCP on peut avoir des options, nous avons donc mis une fonction d’affichage pour les options et une fonction qui libère la place, freeOptionsTCP. Il y a également une fonction d’affichage pour la structure TCP et une fonction freeTCP. Nous avons une fonction lectureTCP qui permet de lire depuis une chaine de caractère les champs de tcp et de retenir ces champs dans une structure TCP. Pour l’ajout de option nous avons créé une autre fonction, ajoutfin. Elle permet d’ajouter à la fin de la liste d’option une option. 


http.c
Ce fichier contient des fonctions d’affichage et des fonctions free afin de libérer la mémoire : freeLig, freeHTTP, afficheLig, afficheHTTP. Elle contient également une fonction insérer_elem_fin qui permet d’ajouter à la fin d’une chaine de ligne une ligne avec son nom et sa valeur. Nous avons également une fonction de lecture qui va lire à partir d’une chaine de caractère l’entête http et implémenter la structure http. 

Il y a également des fichiers texte trame qui nous permettent de tester nos fonctions. D'autres fichiers sont générés par l'exécution. Le fichier sauvegardeTrame est obtenu lors de l'exécution de la fonction sauvegardeTxt dans fichier.c. Il s'agit d'un trace écrite de l'exécution de notre programme. 
