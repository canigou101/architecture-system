opt = -c -Wall -Wextra -std=c99


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

test.exe : test.o
	gcc -o test.exe test.o 

test.o : test.c
	gcc ${opt} test.c

clean :
	rm -rf *.o 
cleanEXE :
	rm -rf *.exe 