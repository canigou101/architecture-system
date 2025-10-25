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
    int nbC=0;
    int tC;
    char nomFichier[30];
    sprintf(nomFichier, "%s/meta.txt", argv[1]);
    char* mes_params[]={"test","-f",nomFichier,(char*)NULL};
    pid_t mon_pid = fork();
    if(mon_pid==0){
        /*Vérification de l'existence du fichier meta dans la table indiquée*/
        execv("/usr/bin/test",mes_params);
    }else{
        int mon_Code;
        wait(&mon_Code);
        if (mon_Code==0){
            /*Si le fichier meta existe déjà, arrêt du programme*/
            printf("La table est déjà préparée, si vous voulez la changer, veuillez lancer une réinitialisation. \n");
            return EXIT_FAILURE;
        }
        else{
            /*Si le fichier meta n'existe pas, il est créé*/
            pid_t mon_pid2 = fork();
            if(mon_pid2<0){
                perror("Le processus ne s'est pas lancé. \n");
                return(EXIT_FAILURE);
            }else if(mon_pid2==0){
                /*Création du fichier meta*/
                char* mesParam2[]= {"touch", nomFichier};
                execv("/usr/bin/touch",mesParam2);
            }else{
                /*Si le fichier est créé avec succès, le programme demande à l'utilisateur d'entrer les données voulues*/
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
                    /*En cas d'échec de la commande touch*/
                    printf("echec de la préparation de la table\n");
                    return mon_Code2;
                }
            }
            return mon_Code;  
        }
    }
}