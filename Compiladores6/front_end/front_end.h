#ifndef FRONT_END_H_INCLUDED
#define FRONT_END_H_INCLUDED
#include "fila.h"
#include <string.h>

typedef struct celula
{
	char tipo; // @, I, C, S
	int exp_tipo;
	int tipo_lista;
	struct celula* filho_dir;
	struct celula* filho_esq;

	union {
		int numero;
		char *string;
	};
} Celula;


typedef struct funcao
{
	char *nome;
	Celula *codigo;
	Fila *brackets;
	int qtd_parametros;

}Funcao;

Funcao* nova_funcao (char* nome, Fila* brackets, Celula* codigo);
Celula* nova_celula_deriv(Celula *esq, Celula *dir);
Celula *nova_celula_terminal_S(char* c);
Celula *nova_celula_terminal_vazia(char* c);
Celula* nova_celula_lista(Celula *esq, Celula *dir);
void imprime_arvore(Celula* raiz);
Celula *nova_celula_terminal_I(int n) ;
int eh_constante(char *c, Celula *codigo);
Celula* bracket_abs(char * brakcet, Celula *codigo);
#endif