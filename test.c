#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


/*il sert à quoi ce fichier ?*/
int main(int argc, char** argv){
    if (argc!=2) {
        fprintf(stderr,"usage : \n\t%s REPERTOIRE\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    char* mes_params[]={"supprimerTable",argv[1],(char*)NULL};
    pid_t mon_pid = fork();
    if(mon_pid==0){
        execv("supprimerTable",mes_params);
    }else{
        int mon_Code;
        wait(&mon_Code);
        if (mon_Code==0){
            char* mes_params2[]={"creerTable",argv[1],(char*)NULL};
            pid_t mon_pid2 = fork();
            if(mon_pid2==0){
                execv("creerTable",mes_params2);
            }else{
                int mon_Code2;
                wait(&mon_Code2);
                if (mon_Code2==0){
                    printf("La table a été réinitialisée avec succès. \n");
                    return EXIT_SUCCESS;
                }else{
                    printf("Echec de la réinitialisation de la table\n");
                    return mon_Code2;
                }
            }
        }else{
            printf("La table n'existe pas. \n");
            return mon_Code;  
        }
    }
}