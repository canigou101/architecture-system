opt = -c -Wall -Wextra


creerTable.exe : creerTable.o 
	gcc -o creerTable.exe creerTable.o

creerTable.o : creerTable.c
	gcc ${opt} creerTable.c

supprimerTable.exe : supprimerTable.o
	gcc -o supprimerTable.exe supprimerTable.o

supprimerTable.o : supprimerTable.c 
	gcc ${opt} supprimerTable.c 
clean :
	rm -rf *.o 
cleanEXE :
	rm -rf *.exe 