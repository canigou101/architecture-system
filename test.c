#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "structMeta.h"

int main(int argc, char** argv){
    /*vérification de la bonne utilisation des paramètres*/
    if (argc!=2) {
        fprintf(stderr,"usage : \n\t%s REPERTOIRE\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    int nbC=0;
    int tC;
    char nomFichier[30];
    char nomFichierMeta[30];
    char* nomFichierTypes = "Types/meta.txt";
    sprintf(nomFichier, "%s/data.txt", argv[1]);
    sprintf(nomFichierMeta, "%s/meta.txt", argv[1]);
    char* mes_params[]={"test","-f",nomFichier,(char*)NULL};
    pid_t mon_pid = fork();
    if(mon_pid==0){
        /*Vérification de l'existence du fichier data dans la table indiquée*/
        execv("/usr/bin/test",mes_params);
    }else{
        int mon_Code;
        wait(&mon_Code);
        if (mon_Code!=0){
            /*Si le fichier data n'existe pas, il est créé*/
            pid_t mon_pid2 = fork();
            if(mon_pid2<0){
                perror("Le processus ne s'est pas lancé. \n");
                return(EXIT_FAILURE);
            }else if(mon_pid2==0){
                /*Création du fichier data*/
                char* mesParam2[]= {"touch", nomFichier};
                execv("/usr/bin/touch",mesParam2);
            }
        }else{
            FILE* fich = fopen(nomFichier,"w");
            FILE* fichMeta = fopen(nomFichierMeta, "w");
            FILE* fichTypes = fopen(nomFichierTypes, "w");
            char ligne[30];
            char ligneMeta[30];
            int nbC = 0;
            fgets(ligneMeta, 30, fichMeta);
            for (size_t i=0; i<strlen(ligneMeta);i++){
                if (ligneMeta[i] != 13 && ligneMeta[i] != 10) nbC = nbC*10 + (ligneMeta[i]-'0');
            }
            int Code =0;
            metaType Donnees;
            fgets(Donnees.code, 30, fichTypes);
            strncpy(Donnees.code, Donnees.code, strcspn(Donnees.code,' '));
            for(int j = 0; j<nbC; j++){

                printf("Quelle est la taille de la %de colonne? ", i+1);
                scanf("%d",&tC);
                char nomC[sizeof(tC)];
                printf("Quelle est son nom? ");
                scanf("%s", nomC);
                fprintf(fich, "\n%s %d",nomC, tC);
            }
            fclose(fich);
            return mon_Code;
        }  
    }
}