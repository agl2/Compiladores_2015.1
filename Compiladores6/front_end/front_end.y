%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "front_end.h"
#include "fila.h"
void yyerror(char* s);	

Funcao* fs[1000];
int i = 0;
%}

%union{
	int number;
	int bool;
	char *str;
	char *id;
	Funcao* funcao;
	Fila* brackets;
	Celula* codigo;
}

%start variavel_inicial
%token 	IF ELSE AND OR TAIL HEAD EQ
%token <bool> BOOLEAN
%token <number> NUMBER
%token <str> STRING
%token <id> ID
%token NEW_LINE

%type <funcao> def_func
%type <brackets> parametros
%type <codigo> expressao_num
%type <codigo> elemento
%type <codigo> termo
%type <codigo> fator
%type <codigo> exponente


%%
variavel_inicial:
	programa							;
	;

programa:
	def_func NEW_LINE programa			{fs[i] = $1; i++;}
	| def_func							{fs[i] = $1; i++;}
	;

def_func:
	ID parametros '=' expressao_num 	{$$ = nova_funcao($1, $2, $4);}
	;

parametros:
	ID parametros						{fila_insere($2, $1); $$ = $2;}
	| ID 								{Fila *nova; nova = fila_cria(); fila_insere(nova, $1); $$ = nova;}
	;


expressao_num:
	expressao_num '+' termo		{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("+")), $1) , $3);}
	| expressao_num '-' termo 	{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("-")), $1) , $3);}
	| termo						{$$ = $1;}
	;

termo:
	termo '*' exponente			{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("*")), $1) , $3);}
	| termo '/' exponente		{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("/")), $1) , $3);}
	| exponente					{$$ = $1;}
	;

exponente:
	exponente '^' fator			{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("^")), $1) , $3);}
	| fator						{$$ = $1;}
	;

fator:
	'(' expressao_num ')'		{$$ = $2;}
	| elemento					{$$ = $1;}
	;

elemento: 
	NUMBER 								{$$ = nova_celula_terminal_I($1);}
	| ID 								{$$ = nova_celula_terminal_S($1);}
	;
%%

void yyerror (char* err) {
	printf("%s\n", err) ;
	exit(1) ;
}

int main() {
	char* bracket;
	int j;
	yyparse() ;
	printf("%d\n", i);
	imprime_arvore(fs[0]->codigo);
	printf("\n");
	for(j = 0; j < i; j++) {
		while(!fila_vazia(fs[j]->brackets)) {
			bracket = fila_topo(fs[j]->brackets);
			bracket_abs(bracket, fs[j]->codigo);
			fila_retira(fs[j]->brackets);
		}
	}
	imprime_arvore(fs[0]->codigo);
	printf("\n");
	return 0;
}