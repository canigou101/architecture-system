opt = -c -Wall -Wextra -std=c99

all: 
	make clean
	make cleanEXE
	make creerTable.exe
	make supprimerTable.exe
	make preparerTable.exe
	make reinitialiserTable.exe
	make clean

creerTable.exe : creerTable.o 
	gcc -o creerTable.exe creerTable.o

creerTable.o : creerTable.c
	gcc ${opt} creerTable.c

preparerTable.exe : preparerTable.o 
	gcc -o preparerTable.exe preparerTable.o

preparerTable.o : preparerTable.c
	gcc ${opt} preparerTable.c

reinitialiserTable.exe : reinitialiserTable.o 
	gcc -o reinitialiserTable.exe reinitialiserTable.o

reinitialiserTable.o : reinitialiserTable.c
	gcc ${opt} reinitialiserTable.c

supprimerTable.exe : supprimerTable.o
	gcc -o supprimerTable.exe supprimerTable.o

supprimerTable.o : supprimerTable.c 
	gcc ${opt} supprimerTable.c 

controlerType.exe : controlerType.o
	gcc -o controlerType.exe controlerType.o 

controlerType.o : controlerType.c
	gcc ${opt} controlerType.c

test.exe : test.o
	gcc -o test.exe test.o 

test.o : test.c structMeta.h
	gcc ${opt} test.c structMeta.h

test2.exe : test2.o 
	gcc -o test2.exe test2.o

test2.o : test2.c
	gcc ${opt} test2.c

clean :
	rm -rf *.o 
cleanEXE :
	rm -rf *.exe 