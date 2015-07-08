#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "celula.h"
#define TIPO Celula*

typedef struct bloco {
    TIPO dado;
    struct bloco* anterior;
} Bloco;

typedef struct pilha
{
	Bloco* cabeca;
	int tamanho;
} Pilha;



inline Pilha* pilha_cria();
inline void pilha_insere(Pilha* pl, TIPO elemento);
inline TIPO pilha_topo(Pilha* p);
inline int pilha_vazia(Pilha*);
inline void pilha_destroi(Pilha*);
inline void pilha_retira(Pilha*);
#endif // PILHA_H_INCLUDED
