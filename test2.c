#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include "structMeta.h"

metaType** defTypes(){
    FILE* fichTypes = fopen("Types/data.txt", "r");
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
        tmp =strtok(Code, sep);
        i = 0;
        while (tmp!=NULL){
            switch(i){
                case 0:
                    strcpy((*courant)->code,tmp);
                    i++;
                    break;
                case 1:
                    strcpy((*courant)->type,tmp);
                    i++;
                    break;
                case 2:
                    strcpy((*courant)->taille,tmp);
                    i=0;
                    break;
            }
            tmp = strtok(NULL, sep);
        }
        Nouveau = (metaType*)malloc(sizeof(metaType));
        (*courant)->suivant = Nouveau;
        Nouveau->suivant = NULL;
        (*courant) = Nouveau;
        Nouveau = NULL;
        free(Nouveau);
    }
    fclose(fichTypes);
    return Donnees;
}

