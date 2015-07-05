#include "../include/pilha.h"

inline int pilha_vazia(Pilha* p) {
    if(p->tamanho == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

inline void pilha_destroi(Pilha* p)
{
    Bloco* aux;
    while(p->cabeca != NULL) {
        aux = p->cabeca->anterior;
        free(p->cabeca);
        p->cabeca = aux;
    }
    free(p);
}

inline void pilha_retira(Pilha* p)
{
    if(p->tamanho!=0) {
        Bloco *aux = p->cabeca->anterior;
        free(p->cabeca);
        p->cabeca = aux;
        p->tamanho--;
    }
    else {
        printf("Tentando retirar de pilha vazia\n");
    }
}

inline TIPO pilha_topo(Pilha* p) {
    if(p->cabeca != NULL) {
        return p->cabeca->dado;
    }
    else {
        return NULL;
        printf("Tentando acessar pilha vazia\n");
    }
}

inline void pilha_insere(Pilha* pl, TIPO elemento)
{
    if(pl->cabeca == NULL) {
        pl->cabeca = (Bloco*) malloc(sizeof(Bloco));
        pl->cabeca->dado = elemento;
        pl->cabeca->anterior = NULL;
    }
    else {
        Bloco *aux = pl->cabeca;
        pl->cabeca = (Bloco*) malloc(sizeof(Bloco));
        pl->cabeca->dado = elemento;
        pl->cabeca->anterior = aux;
    }
    pl->tamanho++;
}

inline Pilha* pilha_cria()
{
    Pilha* rt = (Pilha*) malloc(sizeof(Pilha));
    rt->tamanho = 0;
    rt->cabeca = NULL;
    return rt;
}