#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CHAR_NULL '\0'
#define GREEN (char) 0
#define RED (char) 1
#define YELLOW (char) 2

typedef struct celula
{
    char tipo;
    int inteiro;
    char mem;
    struct celula* filho_esq;
    struct celula* filho_dir;
    struct celula* prox;
} Celula;

Celula* lista_celulas_livres;
Celula** heap;
Celula* raiz;

inline Celula* cria_celula_folha(char tipo);

inline Celula* cria_celula_derivacao(Celula* filho_dir, Celula* filho_esq);

inline Celula* cria_celula_folha_inteiro(int num);

inline char* captura_string(char* str, int* i);

Celula* monta_arvore(char* str);

void imprime_arvore(Celula* raiz);

Celula* copia_arvore(Celula* original);

inline Celula* cria_celula();

inline void inicia_heap(int tamanho_heap);

inline Celula* aloca_celula();

inline int mark_scan();

#endif // ARVORE_H_INCLUDED
