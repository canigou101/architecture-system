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
    char* mes_params[]={"supprimerTable",argv[1],(char*)NULL};
    pid_t mon_pid = fork();
    if(mon_pid==0){
        /*suppression de la table dans le processus fils*/
        execv("supprimerTable",mes_params);
    }else{
        int mon_Code;
        wait(&mon_Code);
        if (mon_Code==0){
            /*si la supression s'est effectuée, on lance la création d'une table vide de même nom dans le processus père*/
            char* mes_params2[]={"creerTable",argv[1],(char*)NULL};
            pid_t mon_pid2 = fork();
            if(mon_pid2==0){
                execv("creerTable",mes_params2);
            }else{
                int mon_Code2;
                wait(&mon_Code2);
                if (mon_Code2==0){ /*vérification de la création de la table*/
                    printf("La table a été réinitialisée avec succès. \n");
                    return EXIT_SUCCESS;
                }else{
                    printf("Echec de la réinitialisation de la table\n");
                    return mon_Code2;
                }
            }
        }else{ /*Si la table n'a pas été supprimée, un message d'erreur est transmis*/
            printf("La table n'existe pas. \n");
            return mon_Code;  
        }
    }
}