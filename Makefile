all : Main

# main lecture

lecture.o : lecture.c projet.h	
	gcc -Wall -c -o lecture.o lecture.c

Main.o : main.c projet.h
	gcc -Wall -c -o Main.o main.c
	
Main: Main.o lecture.o 
	gcc -o Main Main.o lecture.o

clean :
	rm -f *.o
	rm -f Main

