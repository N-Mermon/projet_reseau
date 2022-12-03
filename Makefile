all : Main


#tache A

lecture.o : lecture.c
	gcc -Wall -c -o lecture.o lecture.c

Main.o : Main.c
	gcc -Wall -c -o Main.o Main.c
	
Main: Main.o lecture.o 
	gcc -o Main Main.o lecture.o

clean :
	rm -f *.o
	rm -f Main
all : Main


#tache A

lecture.o : lecture.c
	gcc -Wall -c -o lecture.o lecture.c

Main.o : main.c
	gcc -Wall -c -o Main.o main.c
	
Main: Main.o lecture.o 
	gcc -o Main Main.o lecture.o

clean :
	rm -f *.o
	rm -f Main
