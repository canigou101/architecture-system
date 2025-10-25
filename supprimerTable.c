#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/*utilisation de la biblio sys/stat.h pour la verrif si le dossier existe*/
#include <sys/stat.h>

   
    

int main(int argc, char** argv){
    
    /*verrification de la bonne utilisation des parametres*/
    if (argc!=2) {
        fprintf(stderr,"usage : \n\t%s REPERTOIRE\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    /*verrification de l'existance de la Table/dossier que l'on veux supprimer*/
    struct stat stats;
    char *chemin_Du_Dossier_A_Supprimer=argv[1];
    /*si le dossier existe on fait ce qui est dans la condition if sinon on ferme le programme avec un message d'erreur*/
    if (stat(chemin_Du_Dossier_A_Supprimer,&stats) == 0 && S_ISDIR(stats.st_mode)){
        /*création d'un processus pour faire la suppression de la table/dossier*/
        pid_t mon_pid = fork();
        if(mon_pid <0 ){
            perror("impossible de créer un processus \n");
            return(EXIT_FAILURE);
        }
        /*si le pid est égale à 0 on est alors dans le fils. donc on execute la commande rm pour remove avec le parametre donné*/
        if (mon_pid == 0){
            char* mes_params[]={"cp","-r",argv[1],(char*)NULL};
            execv("/usr/bin/rm",mes_params);
            /*dans le cas ou execv ne s'exécute pas j'affiche un message dans la sortie approprié*/
            fprintf(stderr,"la commande de création de dossier MKDIR n'a pas réussie à s'exécuter correctement");
            return(EXIT_FAILURE);

        }
        else{
            /*on est dans le processus père donc on attend le fils. et on vérifie si le fils s'est executé sans problème et on rend compte à l'utilisateur*/
            int mon_Code;
            wait(&mon_Code);
            if (mon_Code==0){
                printf("suppression effectuée \n");
                return EXIT_SUCCESS;
            }
            else
            {
                printf("suppression échoué\n");
                return mon_Code;
            }     
        }
        
    }else{
        /*affichage du message d'erreur et fermeture du programme*/
        fprintf(stderr,"le dossier n'existe pas essayez un autre nom");
        exit(EXIT_FAILURE);
    }
    
}