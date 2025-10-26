#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "structMeta.h"


int main(int argc, char** argv){
    //vérification de la bonne utilisation des paramètres
    if (argc!=2) {
        fprintf(stderr,"usage : \n\t%s REPERTOIRE\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    int nbC=0;
    char* valeurColonne;
    char nomFichier[30];
    char nomFichierMeta[30];
    char* nomFichierTypes = "Types/meta.txt";
    sprintf(nomFichier, "%s/data.txt", argv[1]);
    sprintf(nomFichierMeta, "%s/meta.txt", argv[1]);
    char* mes_params[]={"test","-f",nomFichier,(char*)NULL};
    pid_t mon_pid = fork();
    if(mon_pid==0){
        //Vérification de l'existence du fichier data dans la table indiquée
        execv("/usr/bin/test",mes_params);
    }else{
        int mon_Code;
        wait(&mon_Code);
        if (mon_Code!=0){
            //Si le fichier data n'existe pas, il est créé
            pid_t mon_pid2 = fork();
            if(mon_pid2<0){
                perror("Le processus ne s'est pas lancé. \n");
                return(EXIT_FAILURE);
            }else if(mon_pid2==0){
                //Création du fichier data
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
            char Code[4];
            int indic =0;
            metaType Donnees;
            fgets(Donnees.code, 30, fichTypes);
            strncpy(Donnees.code, Donnees.code, strcspn(Donnees.code,' '));
            for(int j = 0; j<nbC; j++){
                printf("Quelle est la valeur de la %de colonne?\nElle sera considérée comme un(e) %s et devra faire moins de %s caractères ", j+1,,);
                scanf("%s",&valeurColonne);
                fgets(ligneMeta, 30, fichMeta);
                for(int i=0; i<strlen(ligneMeta);i++){
                    if(indic==1) strcat(Code,&ligneMeta[i]);
                    if(ligneMeta[i]== ' ' || i<3) indic =1;
                }
                indic =0;
                metaType** verifType = recupererType(Code);
                if (verifType = (metaType**)NULL){
                    printf("Le code indiqué dans le fichier meta n'existe pas.")
                    return EXIT_FAILURE
                }
                printf("%s", (*truc)->type);
                //free(truc);
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