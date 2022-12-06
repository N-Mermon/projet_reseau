all : Main


lecture.o : lecture.c projet.h	
	gcc -Wall -c -o lecture.o lecture.c

ipv4.o : ipv4.c projet.h	
	gcc -Wall -c -o ipv4.o ipv4.c

ethernet.o : ethernet.c projet.h	
	gcc -Wall -c -o ethernet.o ethernet.c

tcp.o : tcp.c projet.h	
	gcc -Wall -c -o tcp.o tcp.c

http.o : http.c projet.h	
	gcc -Wall -c -o http.o http.c

Main.o : main.c projet.h
	gcc -Wall -c -o Main.o main.c
	
Main: Main.o lecture.o ethernet.o ipv4.o tcp.o http.o
	gcc -o Main Main.o lecture.o ethernet.o ipv4.o tcp.o http.o

clean :
	rm -f *.o
	rm -f Main
