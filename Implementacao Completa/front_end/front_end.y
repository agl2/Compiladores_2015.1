%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "front_end.h"
#include "fila.h"
void yyerror(char* s);	

Funcao* fs[1000];
int i = 0;
int m = 0;
int conta_argumentos(Celula *cod, char* f, int aux);
void analise_semantica ();
void analise_subs(Celula* codigo);
void analise_argumentos(char* funcao, int num);
Celula* substitui_codigo(Celula *cod, Funcao* f);
%}

%union
{
	int number;
	char *str;
	char *id;
	Funcao* funcao;
	Fila* brackets;
	Celula* codigo;
}

%start programa
%token 	IF ELSE TAIL HEAD EQ
%token <number> NUMBER
%token <str> STRING
%token <id> ID
%token NEW_LINE
%token TRUE
%token FALSE
%token BLOQ_DEFS

%type <funcao> def_func
%type <brackets> parametros

%type <codigo> comando

%type <codigo> expressao
%type <codigo> tipo_lista
%type <codigo> lista
%type <codigo> termo
%type <codigo> fator
%type <codigo> exponente_comparacao
%type <codigo> elemento
%type <codigo> cham_func
%type <codigo> cham_paramentros

%left EQ '<'


%%
programa:
	BLOQ_DEFS def_funcs BLOQ_DEFS cham_funcs		
	{
		analise_semantica();
	}
	;

def_funcs:
	def_func ';' def_funcs			
	{
		fs[i] = $1; 
		i++;
	}
	| def_func	';'  				
	{
		fs[i] = $1; 
		i++;
	}
	;

cham_funcs:
	cham_funcs cham_func ';'		
	{
		analise_subs($2); 
		imprime_arvore($2); 
		printf("\n");
	}
	| cham_func	';'					
	{
		analise_subs($1); 
		imprime_arvore($1); 
		printf("\n");
	}
	;

def_func:
	ID parametros '=' comando 		
	{
		$$ = nova_funcao($1, $2, $4);
	}				
	;

cham_func:
	ID '(' cham_paramentros ')'			
	{
		Celula *aux = $3;
		int num = 1; 
		while(aux->filho_esq != NULL) 
		{
			num++; 
			aux = aux->filho_esq;
		} 
		analise_argumentos($1, num); 
		aux->filho_esq = nova_celula_terminal_S($1); 
		$$ = $3;
	}
	;

cham_paramentros:
	cham_paramentros ',' expressao 		
	{
		$$ = nova_celula_deriv($1 , $3);
	}
	| expressao 						
	{
		$$ = nova_celula_deriv(NULL, $1);
	}
	;

parametros:
	ID parametros						
	{
		fila_insere($2, $1); $$ = $2;
	}
	| ID 								
	{
		Fila *nova; 
		nova = fila_cria(); 
		fila_insere(nova, $1); 
		$$ = nova;
	}
	;

comando:
	expressao				
	{
		$$ = $1;
	}
	| IF '(' expressao ')' '{' comando '}' ELSE '{' comando '}'  
	{
		$$ = nova_celula_deriv(nova_celula_deriv($3, $6) , $10);
	}
	;

expressao:
	expressao '+' termo				
	{
		if($1->exp_tipo == 3 || $3->exp_tipo == 3 || $1->exp_tipo == 2 || $3->exp_tipo == 2) //eh uma expressao booleana ou lista
		{
			printf("Erro: tipo invalido para soma\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("+")), $1) , $3);
		$$->exp_tipo = 1;
	}
	| expressao '-' termo 			
	{
		if($1->exp_tipo == 3 || $3->exp_tipo == 3 || $1->exp_tipo == 2 || $3->exp_tipo == 2) //eh uma expressao booleana ou lista 
		{
			printf("Erro: tipo invalido para subtração\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("-")), $1) , $3);
		$$->exp_tipo = 1;
	}
	| expressao '|' termo			
	{
		if($1->exp_tipo == 2 || $3->exp_tipo == 2 || $1->exp_tipo == 1 || $3->exp_tipo == 1) //se for uma lista ou expressao aritmetica
		{
			printf("Erro: tipo invalido para OU\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv($1, nova_celula_terminal_S(strdup("K"))) , $3);
		$$->exp_tipo = 3;
	}
	| HEAD termo					
	{
		if ($2->exp_tipo == 3 || $2->exp_tipo == 1) //eh uma expressao booleana ou operacao aritmetica
		{
			printf("Erro: tipo invalido para head\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_terminal_S(strdup("H")) , $2);
		$$->exp_tipo = $2->tipo_lista;  //vai retornar o tipo do primeiro elemento, pelo menos eu espero
	}
	| TAIL termo					
	{
		if ($2->exp_tipo == 3 || $2->exp_tipo == 1) //eh uma expressao booleana ou operacao aritmetica
		{
			printf("Erro: tipo invalido para tail\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_terminal_S(strdup("T")) , $2);
		$$->exp_tipo = 2; //retorno tipo lista
		$$->tipo_lista = $2->tipo_lista;
	}
	| expressao ':' termo			
	{
		if ($3->exp_tipo == 3 || $3->exp_tipo == 1) //eh uma expressao booleana ou operacao aritmetica
		{
			printf("Erro: tipo invalido para concatenação de listas\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup(":")), $1) , $3);
		$$->exp_tipo = 2; //retorno tipo lista
		$$->tipo_lista = $1->exp_tipo; //mudei aqui
	}
	| termo							
	{
		$$ = $1;
	}
	;

tipo_lista:
	'[' lista ']'	
	{
		$$ = $2;
	}
	|'['']'			
	{
		$$ = nova_celula_terminal_vazia(strdup("]"));
	}
	
lista:
	expressao ',' lista		
	{
		if($1->exp_tipo != $3->exp_tipo)
		{
			printf("Erro: lista contem tipos diferentes\n");
			exit(1);
		}
		$$ = nova_celula_lista($1, $3);
		$$->tipo_lista = $1->exp_tipo;
		$$->exp_tipo = $1->exp_tipo;
	}
	|expressao				
	{
		$$ = nova_celula_lista($1, nova_celula_terminal_vazia(strdup("]")));
		$$->tipo_lista = $1->exp_tipo;
		$$->exp_tipo = $1->exp_tipo;
	}

termo:
	termo '*' exponente_comparacao		
	{
		if($1->exp_tipo == 3 || $3->exp_tipo == 3 || $1->exp_tipo == 2 || $3->exp_tipo == 2) //eh uma expressao booleana ou lista
		{
			printf("Erro: tipo invalido para multiplicação\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("*")), $1) , $3);
		$$->exp_tipo = 1;
	}
	| termo '/' exponente_comparacao	
	{
		if($1->exp_tipo == 3 || $3->exp_tipo == 3 || $1->exp_tipo == 2 || $3->exp_tipo == 2) //eh uma expressao booleana ou lista
		{
			printf("Erro: tipo invalido para divisão\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("/")), $1) , $3);
		$$->exp_tipo = 1;
	}
	| termo '&' exponente_comparacao	
	{
		if($1->exp_tipo == 2 || $3->exp_tipo == 2 || $1->exp_tipo == 1 || $3->exp_tipo == 1) //eh lista ou expressao aritmetica
		{
			printf("Erro: tipo invalido para and\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv($1, $3) , nova_celula_terminal_S(strdup("F")) );
		$$->exp_tipo = 3;
	}
	| exponente_comparacao				
	{
		$$ = $1;
	}
	;

exponente_comparacao:
	exponente_comparacao '^' fator			
	{
		if($1->exp_tipo == 3 || $3->exp_tipo == 3 || $1->exp_tipo == 2 || $3->exp_tipo == 2) //eh uma expressao booleana ou lista
		{
			printf("Erro: tipo invalido para exponenciação\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("^")), $1) , $3);
		$$->exp_tipo = 1;
	}
	| fator EQ fator 						
	{
		if($1->exp_tipo == 3 || $3->exp_tipo == 3) //eh uma expressao booleana, pois eu acho q nao da pra comparar true e false
		{
			printf("Erro: tipo invalido para igualdade\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("=")), $1) , $3);
		$$->exp_tipo = 3; //retorna uma expressão booelana
	}				
	| fator '<' fator 						
	{
		if($1->exp_tipo == 3 || $3->exp_tipo == 3 || $1->exp_tipo == 2 || $3->exp_tipo == 2) //eh uma expressao booleana ou lista
		{
			printf("Erro: tipo invalido para menor que\n");
			exit(1);
		}
		$$ = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("<")), $1) , $3);
		$$->exp_tipo = 3;
	}
	| fator									
	{
		$$ = $1;
	}
	;

fator:
	'(' expressao ')'		
	{
		$$ = $2;
	}
	| elemento				
	{
		$$ = $1;
	}
	| cham_func				
	{
		$$ = $1;
	}
	;


elemento: 
	NUMBER 								
	{
		$$ = nova_celula_terminal_I($1);
		$$->exp_tipo = 1;
	}
	| ID 								
	{
		$$ = nova_celula_terminal_S($1);
		$$->exp_tipo = 0;
		$$->tipo_lista = 0;
	}
	| TRUE								
	{
		$$ = nova_celula_terminal_S(strdup("K"));
		$$->exp_tipo = 3;
	}
	| FALSE								
	{
		$$ = nova_celula_terminal_S(strdup("F"));
		$$->exp_tipo = 3;
	}
	| tipo_lista 						
	{
		$$ = $1;
		$$->exp_tipo = 2;
	}
	;
%%

void yyerror (char* err) 
{
	printf("%s\n", err) ;
	exit(1) ;
}

Celula* substitui_codigo(Celula *cod, Funcao* f) 
{
	if (cod->tipo == 'S') 
	{
		if( strcmp(cod->string, f->nome) == 0 ) 
		{
			free(cod);
			return f->codigo;
		}
		else return cod;
	}
	else if(cod->tipo == '@') 
	{
		cod->filho_esq = substitui_codigo(cod->filho_esq, f);
		cod->filho_dir = substitui_codigo(cod->filho_dir, f);
	}
	return cod;
}

void analise_subs(Celula* codigo) 
{
	int k = 0;
	for(k = 0; k < i; k++) 
	{
		if(!eh_constante(fs[k]->nome, codigo)) 
		{
			substitui_codigo(codigo, fs[k]);
		}
	}
}

void analise_argumentos(char* funcao, int num) 
{
	int k, j, tem = 0;
	for(j = 0; j < i; j++) 
	{
		for(k = 0; k < i; k++) 
		{
			if(j != k) 
			{
				if(strcmp(fs[k]->nome,fs[j]->nome)==0)
				{
					printf("Erro: função %s declarada mais de uma vez!\n", fs[k]->nome);
					exit(1);
				}
			}
			if(strcmp(funcao, fs[k]->nome) == 0) 
			{
				if(fs[k]->qtd_parametros != num)
				{
					printf("Erro: número de parâmetros para a função %s está incorreto\n", funcao);
					exit(1);
				}
				tem++;
			}
		}
		if(tem == 0) 
		{
			printf("Erro: função %s não declarada\n", funcao);
			exit(1);
		}
		tem = 0;
	}
}

void analise_semantica () 
{
	int j, k;
	for(j = 0; j < i; j++) 
	{
		for(k = 0; k < i; k++) 
		{
			if(j != k) 
			{
				if(!eh_constante(fs[k]->nome, fs[j]->codigo)) 
				{
					substitui_codigo(fs[j]->codigo, fs[k]);
				}
			}
		}
	}

}

int main() 
{
	int j;
	FILE* arquivo;
	arquivo = freopen("backend.in","w+",stdout);
	yyparse();
}