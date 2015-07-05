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
	char *str;
	char *id;
	Funcao* funcao;
	Fila* brackets;
	Celula* codigo;
}

%start variavel_inicial
%token 	IF ELSE TAIL HEAD EQ
%token <number> NUMBER
%token <str> STRING
%token <id> ID
%token NEW_LINE
%token TRUE
%token FALSE

%type <funcao> def_func
%type <brackets> parametros

%type <codigo> comando

%type <codigo> expressao
%type <codigo> termo
%type <codigo> fator
%type <codigo> exponente_comparacao

%type <codigo> elemento

%left EQ '<'


%%
variavel_inicial:
	programa							;
	;

programa:
	def_func NEW_LINE programa			{fs[i] = $1; i++;}
	| def_func							{fs[i] = $1; i++;}
	;

def_func:
	ID parametros '=' comando 		{$$ = nova_funcao($1, $2, $4);}
	;

parametros:
	ID parametros					{fila_insere($2, $1); $$ = $2;}
	| ID 							{Fila *nova; nova = fila_cria(); fila_insere(nova, $1); $$ = nova;}
	;

comando:
	expressao				{$$ = $1;}
	| IF '(' expressao ')' '{' comando '}' ELSE '{' comando '}'  {$$ = nova_celula_deriv(nova_celula_deriv($3, $6) , $10);}
	;

expressao:
	expressao '+' termo				{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("+")), $1) , $3);}
	| expressao '-' termo 			{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("-")), $1) , $3);}
	| expressao '|' termo			{$$ = nova_celula_deriv(nova_celula_deriv($1, nova_celula_terminal_S(strdup("K"))) , $3);}
	| termo								{$$ = $1;}
	;

termo:
	termo '*' exponente_comparacao						{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("*")), $1) , $3);}
	| termo '/' exponente_comparacao						{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("/")), $1) , $3);}
	| termo '&' exponente_comparacao			{$$ = nova_celula_deriv(nova_celula_deriv($1, $3) , nova_celula_terminal_S(strdup("F")) );}
	| exponente_comparacao								{$$ = $1;}
	;

exponente_comparacao:
	exponente_comparacao '^' fator			{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("^")), $1) , $3);}
	| fator EQ fator 						{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("=")), $1) , $3);}				
	| fator '<' fator 						{$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("<")), $1) , $3);}
	| fator									{$$ = $1;}
	;

fator:
	'(' expressao ')'		{$$ = $2;}
	| elemento				{$$ = $1;}
	;

elemento: 
	NUMBER 								{$$ = nova_celula_terminal_I($1);}
	| ID 								{$$ = nova_celula_terminal_S($1);}
	| TRUE								{$$ = nova_celula_terminal_S(strdup("K"));}
	| FALSE								{$$ = nova_celula_terminal_S(strdup("F"));}
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