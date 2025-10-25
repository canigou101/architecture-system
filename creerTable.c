#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


   
    

int main(int argc, char** argv){
    /*verrification de la bonne utilisation des parametres*/
    if (argc!=2) {
        fprintf(stderr,"usage : \n\t%s REPERTOIRE\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    pid_t mon_pid = fork();
    /*création d'un processus pour faire la création de la table/dossier*/
    if(mon_pid <0 ){
        perror("impossible de creer un processus \n");
        return(EXIT_FAILURE);
    }
    /*si le pid est égale à 0 on est alors dans le fils. donc on execute la commande mkdir pour make directory avec le parametre donné*/
    if (mon_pid == 0){
        char* mes_params[]={"mkdir",argv[1],(char*)NULL};
        execv("/usr/bin/mkdir",mes_params);
        return(EXIT_FAILURE);

    }
    else{
        /*on est dans le processus père donc on attend le fils. et on vérifie si le fils s'est executé sans problème et on rend compte à l'utilisateur*/
        int mon_Code;
        wait(&mon_Code);
        if (mon_Code==0){
            printf("table créée avec succès \n");
            return EXIT_SUCCESS;
        }
        else
        {
            printf("echec de la création de la table\n");
            return mon_Code;
        }     
    }
}