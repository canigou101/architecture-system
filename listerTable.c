#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    /*vérification de la bonne utilisation des paramètres*/
    if (argc!=2) {
        fprintf(stderr,"usage : \n\t%s REPERTOIRE\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    char nomFichier[30];
    sprintf(nomFichier, "%s/data.txt", argv[1]);
    char* mes_params[]={"test","-f",nomFichier,(char*)NULL};
    pid_t mon_pid = fork();
    if(mon_pid==0){
        /*Vérification de l'existence du fichier meta dans la table indiquée*/
        execv("/usr/bin/test",mes_params);
    }else{
        int mon_Code;
        wait(&mon_Code);
        if (mon_Code!=0){
            /*Si le fichier data existe déjà, arrêt du programme*/
            printf("La table demandée n'a pas de donnée. \n");
            return EXIT_FAILURE;
        }else{
            /*Si le fichier data existe, il est lu ligne par ligne*/
                    FILE* fich = fopen(nomFichier,"r");
                    char ligne[50];
                    printf("La table %s contient les données suivantes:\n", argv[1]);
                    while(fgets(ligne,50,fich)!=NULL){
                        printf("%s", ligne);
                    }
                    fclose(fich);
            return mon_Code;  
        }
    }
}