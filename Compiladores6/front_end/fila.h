#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define TIPO char*

typedef struct bloco {
    TIPO dado;
    struct bloco* proximo;
} Bloco;

typedef struct fila
{
	Bloco* cabeca;
	Bloco* ultimo;
	int tamanho;
} Fila;



inline Fila* fila_cria();
inline void fila_insere(Fila* pl, TIPO elemento);
inline TIPO fila_topo(Fila* p);
inline int fila_vazia(Fila*);
inline void fila_destroi(Fila*);
inline void fila_retira(Fila*);
#endif // FILA_H_INCLUDED
