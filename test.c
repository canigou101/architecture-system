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
    char nomFichier[30];
    char nomFichierMeta[30];
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
            FILE* fichMeta = fopen(nomFichierMeta, "r");
            char ligneMeta[30];
            int nbC = 0;
            fgets(ligneMeta, 30, fichMeta);
            for (size_t i=0; i<strlen(ligneMeta);i++){
                if (ligneMeta[i] != 13 && ligneMeta[i] != 10) nbC = nbC*10 + (ligneMeta[i]-'0');
            }
            //char* Code = (char*)malloc(*sizeof(char));
            char* Code = "test";
            int indic = 0;
            metaType** verifType = (metaType**)malloc(sizeof(metaType*));
            for(int j = 0; j<nbC; j++){
                fgets(ligneMeta, 30, fichMeta);
                for(size_t i=0; i<strlen(ligneMeta);i++){
                    if(indic==1) strcat(Code,&ligneMeta[i]);
                    if(ligneMeta[i]== ' ' || i<3) indic =1;
                }
                indic =0;
                verifType = recupererType("1");
                printf("%s", (*verifType)->code);
                /*if (strcpy((*verifType)->code, " ")==0){
                    printf("Le code indiqué dans le fichier meta n'existe pas.");
                    return EXIT_FAILURE;
                }
                size_t tailleInt = 0;
                for (size_t k=0; k<strlen((*verifType)->taille);k++){
                    if ((*verifType)->taille[k] != 13 && (*verifType)->taille[k] != 10) tailleInt = tailleInt*10 + ((*verifType)->taille[k]-'0');
                }
                char valeurColonne[tailleInt];
                printf("Quelle est la valeur de la %de colonne?\nElle sera considérée comme un(e) %s et devra faire moins de %s caractères ", j+1,(*verifType)->type,(*verifType)->taille);
                scanf("%s",valeurColonne);
                if(strlen(valeurColonne)<=tailleInt){
                    FILE* fich = fopen(nomFichier,"w");
                    fprintf(fich, "%s\n",valeurColonne);
                    fclose(fich);
                }else{
                    printf("La valeur est trop grande, veuillez diminuer son nombre de caractères ou changer le code indiqué dans le fichier meta.");
                    return EXIT_FAILURE;
                }*/
               free(verifType);
            }
            return mon_Code;
        }  
    }
}

/*
int main(){
    metaType** truc = (metaType**)malloc(sizeof(metaType*));
    char* test = (char*)malloc(5*sizeof(char));
    test = "1";
    truc = recupererType(test);
    printf("%s", (*truc)->type);
    free(truc);
    return 0;
}*/