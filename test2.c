#include "controlerType.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include "structMeta.h"

int main(){
    FILE* fich = fopen("tabletest/data.txt","r");
    FILE* fichMeta = fopen("tabletest/meta.txt", "r");
    FILE* fichTypes = fopen("Types/data.txt", "r");
    char ligne[30];
    char ligneMeta[30];
    //char ligneType[30];
    fgets(ligneMeta, 30, fichMeta);
    fgets(ligne, 30, fich);
    //fgets(ligneType, 30, fichTypes);
    fclose(fichMeta);
    fclose(fich);
    /*printf("%s", ligneMeta);
    printf("%s", ligneType);
    printf("%s", ligne);*/
    /*int nbC = 0;
    for (size_t i=0; i<strlen(ligneMeta);i++){
        if (ligneMeta[i] != 13 && ligneMeta[i] != 10) nbC = nbC*10 + (ligneMeta[i]-'0');
        printf("%d\n", ligneMeta[i]);
    }
    printf("%d", nbC);*/
    metaType **Donnees;
    Donnees = (metaType**)malloc(sizeof(metaType*));
    metaType** courant = (metaType**)malloc(sizeof(metaType*));
    *courant = *Donnees;
    char Code[30];
    char* sep = " ";
    char* tmp = NULL;
    int i;
    metaType* Nouveau;
    while(fgets(Code, 30, fichTypes) != NULL){
        printf("%s", Code);
        printf("4.5%s", (*Donnees)->taille);
        Nouveau = (metaType*)malloc(sizeof(metaType));
        //printf("5%s", (*Donnees)->taille);
        tmp =strtok(Code, sep);
        i = 0;
        //printf("%d", i);
        while (tmp!=NULL){
            printf("i2 :%d", i);
            printf("%s", sep);
            printf("-%s\n", tmp);
            switch(i){
                case 0:
                    strcpy((*courant)->code,tmp);
                    printf("c%s\n", (*courant)->code);
                    //printf("%s", tmp);
                    i++;
                    break;
                case 1:
                    printf("blo");
                    printf("tun%s\n", (*courant)->type);
                    strcpy((*courant)->type,tmp);
                    printf("tdeux%s\n", (*courant)->type);
                    i++;
                    break;
                case 2:
                    strcpy((*courant)->taille,tmp);
                    printf("tt%s\n", (*courant)->taille);
                    i=0;
                    break;
            }
            //printf("%s", tmp);
            tmp = strtok(NULL, sep);
            //printf("%s", tmp);
            printf("i : %d ", i);
        }
        //printf("1%s", (*Donnees)->taille);
        (*courant)->suivant = Nouveau;
        //printf("2%s", (*Donnees)->taille);
        Nouveau->suivant = NULL;
        //printf("3%s", (*Donnees)->taille);
        //printf("%s\n", courant->code);
        (*courant) = Nouveau;
        Nouveau = NULL;
        printf("4%s", (*Donnees)->taille);
        free(Nouveau);
        printf("6%s", (*Donnees)->taille);
        //printf("%s\n", Nouveau->code);
    }
    fclose(fichTypes);
    /*printf("%s\n", Donnees->code);
    printf("%s\n", Donnees->type);
    printf("%s\n", Donnees->taille);
    printf("%s\n", Donnees->suivant->code);
    printf("%s\n", Donnees->suivant->type);
    printf("%s\n", Donnees->suivant->taille);
    printf("%s\n", Donnees->suivant->suivant->code);
    printf("%s\n", Donnees->suivant->suivant->type);
    printf("%s\n", Donnees->suivant->suivant->taille);*/
    free(courant);
    free(Donnees);
}