#ifndef CELULA_H_INCLUDED
#define CELULA_H_INCLUDED
#include <stdlib.h>

typedef struct celula
{
    char tipo;
    int inteiro;
    char mem;
    struct celula* filho_esq;
    struct celula* filho_dir;
    struct celula* prox;
} Celula;

#endif
