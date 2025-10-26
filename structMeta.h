#include <stdlib.h>
#include <stdio.h>

typedef struct typeMeta{
    char code[4];
    char type[30];
    char taille[10];
    struct typeMeta* suivant;
}metaType;

metaType** defTypes();
metaType** recupererType(char* CodeI);