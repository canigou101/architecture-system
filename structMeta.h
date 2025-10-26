#include <stdlib.h>
#include <stdio.h>

typedef struct typeMeta{
    char* code;
    char* type;
    char* taille;
    struct typeMeta* suivant;
}metaType;