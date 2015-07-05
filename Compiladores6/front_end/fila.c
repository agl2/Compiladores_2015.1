#include "fila.h"

inline int fila_vazia(Fila* p) {
    if(p->tamanho == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

inline void fila_destroi(Fila* p)
{
    Bloco* aux;
    while(p->cabeca != NULL) {
        aux = p->cabeca->proximo;
        free(p->cabeca);
        p->cabeca = aux;
    }
    free(p);
}

inline void fila_retira(Fila* p)
{
    if(p->tamanho!=0) {
        Bloco *aux = p->cabeca->proximo;
        free(p->cabeca);
        p->cabeca = aux;
        p->tamanho--;
    }
    else {
        printf("Tentando retirar de fila vazia\n");
    }
}

inline TIPO fila_topo(Fila* p) {
    if(p->cabeca != NULL) {
        return p->cabeca->dado;
    }
    else {
        return NULL;
        printf("Tentando acessar fila vazia\n");
    }
}

inline void fila_insere(Fila* pl, TIPO elemento)
{
    if(pl->cabeca == NULL) {
        pl->cabeca = (Bloco*) malloc(sizeof(Bloco));
        pl->cabeca->dado = elemento;
        pl->cabeca->proximo = NULL;
        pl->ultimo = pl->cabeca;
    }
    else {
        Bloco *aux = pl->ultimo;
        pl->ultimo = (Bloco*) malloc(sizeof(Bloco));
        pl->ultimo->dado = elemento;
        pl->ultimo->proximo = NULL;
        aux->proximo = pl->ultimo;
    }
    pl->tamanho++;
}

inline Fila* fila_cria()
{
    Fila* rt = (Fila*) malloc(sizeof(Fila));
    rt->tamanho = 0;
    rt->cabeca = NULL;
    rt->ultimo = NULL;
    return rt;
}
