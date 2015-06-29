%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(char* s);	
%}

%union{
	int number;
	int bool;
	char *str;
	char *id;
}

%start programa
%token 	IF ELSE AND OR TAIL HEAD EQ
%token <bool> BOOLEAN
%token <number> NUMBER
%token <str> STRING
%token <id> ID
%token NEW_LINE


%%
programa:
	def_func NEW_LINE programa			;
	| comandos							;
	;

def_func:
	ID parametros '=' comando 			;
	;

comandos:
	comando NEW_LINE comandos			;
	| comando 							;
	;

parametros:
	ID parametros						;
	| parametro 						;
	;

comando:
	cham_func							;
	| expressao							;
	;

cham_func:
	ID '(' parametros_chamada ')' 				;
	;

parametros_chamada:
	comando parametros_chamada					;
	| comando 									;
	;

expressao:
	expressao_num						;
	;

expressao_num:
	expressao_num '+' expressao_num		;
	| expressao_num '-' expressao_num 	;
	| NUMBER 							;
	;

%%

void yyerror (char* err) {
	printf("%s\n", err) ;
	exit(1) ;
}