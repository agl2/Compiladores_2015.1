#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "celula.h"
#include "pilha.h"
#define CHAR_NULL '\0'
#define VERDE (char) 0
#define VERMELHO (char) 1
#define AMARELO (char) 2
#define estatisticas = 1
#ifdef estatisticas
int redK, redF, redS,reds, redI, redB,redb,redC,redc,redY, noConsumido;
int redMais,redMenos,redMult,redDiv,redList,redExp,redH,redT,redMenor,redEqual,redString, garbe;
#endif

Celula* lista_celulas_livres;
Celula** heap;
int tam_heap;

inline Celula* cria_celula_folha(char tipo);

inline Celula* cria_celula_derivacao(Celula* filho_dir, Celula* filho_esq);

inline Celula* cria_celula_lista();

inline Celula* cria_celula_folha_inteiro(int num);

inline char* captura_string(char* str, int* i);

Celula* monta_arvore(char* str);

void imprime_arvore(Celula* raiz);

Celula* copia_arvore(Celula* original);

inline Celula* cria_celula();

inline void inicia_heap(int tamanho_heap);

inline Celula* aloca_celula();

int mark_scan();

void marque_verde(Celula *raiz);

inline void checa_raiz(Celula* raiz, Celula* nova);

void testa_celulas_livres (int num, Pilha* raizes);

#endif // ARVORE_H_INCLUDED
