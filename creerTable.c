#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/*utilisation de la biblio sys/stat.h*/
#include <sys/stat.h>
    

int main(int argc, char** argv){
    /*verrification de la bonne utilisation des parametres*/
    if (argc!=2) {
        fprintf(stderr,"usage : \n\t%s REPERTOIRE\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    /*vérification de la présence ou non du dossier*/
    struct stat stats;
    char *chemin_du_repertoir =argv[1];
    int resultat=stat(chemin_du_repertoir,&stats);
    /*verification du résultat retourné par stat() ->0 = existe ->1 = n'existe pas*/
    if(resultat==0 && S_ISDIR(stats.st_mode)){
        fprintf(stderr,"le répertoire existe deja essayez un autre nom");
        exit(EXIT_FAILURE);
    }
    /*pas besoin d'un else car on cherche juste à savoir s'il existe pour couper le programme en affichant une erreur*/
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