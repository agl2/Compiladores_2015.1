#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct celula {
    char tipo;
    char mem;
    struct celula* filho_esq;
    struct celula* filho_dir;
} Celula;

inline Celula* cria_celula_folha(char tipo, char mem);

inline Celula* cria_celula_derivacao(Celula* filho_dir, Celula* filho_esq);

inline char* captura_string(char* str, int* i);

Celula* monta_arvore(char* str);

void imprime_arvore(Celula* raiz);


#endif // ARVORE_H_INCLUDED
