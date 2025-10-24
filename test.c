#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    if (argc!=2) {
        fprintf(stderr,"usage : \n\t%s REPERTOIRE\n", argv[0] );
        exit(EXIT_FAILURE);
    }
    int nbC=0;
    int tC;
    char nomFichier[30];
    sprintf(nomFichier, "%s/test2.txt", argv[1]);
    char* mes_params[]={"test","-f",nomFichier,(char*)NULL};
    pid_t mon_pid = fork();
    if(mon_pid==0){
        execv("/usr/bin/test",mes_params);
    }else{
        int mon_Code;
        wait(&mon_Code);
        if (mon_Code==0){
            printf("La table est déjà préparée, si vous voulez la changer, veuillez lancer une réinitialisation. \n");
            return EXIT_SUCCESS;
        }
        else{
            pid_t mon_pid2 = fork();
            if(mon_pid2<0){
                perror("Le processus ne s'est pas lancé. \n");
                return(EXIT_FAILURE);
            }else if(mon_pid2==0){
                char* mesParam2[]= {"touch", nomFichier};
                execv("/usr/bin/touch",mesParam2);
            }else{
                int mon_Code2;
                wait(&mon_Code2);
                if (mon_Code2==0){
                    FILE* fich = fopen(nomFichier,"w");
                    printf("Combien de colonnes voulez-vous? ");
                    scanf("%d",&nbC);
                    fprintf(fich,"%d", nbC);
                    for(int i = 0;i<nbC;i++){
                        printf("Quelle est la taille de la %de colonne? ", i+1);
                        scanf("%d",&tC);
                        char nomC[sizeof(tC)];
                        printf("Quelle est son nom? ");
                        scanf("%s", nomC);
                        fprintf(fich, "\n%s %d",nomC, tC);
                    }
                    fclose(fich);
                }else{
                    printf("echec de la préparation de la table\n");
                    return mon_Code;
                }
            }
            return mon_Code;  
        }
    }
}