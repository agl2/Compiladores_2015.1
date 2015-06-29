%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <string.h>
	#include "front_end.h"

	#define funcao_atual funcao[qtd_funcoes]

	// Habilita/desabilita as checagens
	#define SAFE_MODE_on
	#define DEBUG_off

	Function* funcao[1000] ;
	int qtd_funcoes = 0 ;

	char str_aux[1001] ;
	int str_tam ;

	char parametro[1000][100] ;
	int tipo[1000] ;

	Op* new_op(int tipo, int qtd_op, ...) ;
	Lista* new_node (Op* elem, Lista* next) ;
	void analise_semantica(Lista* funcoes) ;

	int yylex() ;
	void yyerror(char*) ;
%}

%union {
	int numero ;
	char* string ;
	int bool ;
	char* id ;
	Op* operador ;
	Lista* lista ;
}

%token <numero> NUM
%token <bool>	BOOLEAN
%token <string> STRING ID

//Tokens de operadores
%token IF THEN ELSE NOT AND OR HEAD TAIL EQ
%token IFTHENELSE SOMA SUB MULT DIV EXPON MAIOR_QUE MENOR_QUE CONCAT VAZIA
%token APLICACAO FUNCAO

//Tokens de tipos diferentes de listas
%token LISTA LISTA_INT LISTA_BOOL LISTA_STRING

// Tipos das reduções
%type <lista> lista_funcoes lista_id lista parametros
%type <operador> funcao elemento codigo

%left '>' '<' EQ
%left '+' '-'
%left '*' '/'
%left '^'

%nonassoc NEG

%%

// Programa começa aqui.
programa:
	lista_funcoes				{analise_semantica($1) ;}
	;

lista_funcoes:
	funcao						{$$ = new_node($1, NULL) ;}
	| funcao lista_funcoes 		{$$ = new_node($1, $2) ;}
	;

funcao:
	lista_id '=' codigo		{$$ = new_op(FUNCAO, 2, new_op(LISTA, 0, $1), $3) ;}
	;

lista_id:
	ID 					{$$ = new_node(new_op(ID, 0, $1), NULL) ;}
	| ID lista_id		{$$ = new_node(new_op(ID, 0, $1), $2) ;}
	;

parametros:
	codigo						{$$ = new_node($1, NULL) ;}
	| codigo ',' parametros		{$$ = new_node($1, $3) ;}
	;

lista:
	elemento				{$$ = new_node($1, NULL) ;}
	| elemento ',' lista 	{$$ = new_node($1, $3) ;}
	;

elemento:
	NUM 				{$$ = new_op(NUM, 0, $1) ;}
	| '-' NUM %prec NEG	{$$ = new_op(NEG, 0, $2) ;}
	| STRING 			{$$ = new_op(STRING, 0, $1) ;}
	| BOOLEAN 			{$$ = new_op(BOOLEAN, 0, $1) ;}
	;

codigo:
	IF codigo THEN codigo ELSE codigo	{$$ = new_op(IFTHENELSE, 3, $2, $4, $6) ;}
	| '(' codigo ')'					{$$ = $2 ;}
	| elemento							{$$ = $1 ;}
	| ID '(' parametros ')'				{$$ = new_op(APLICACAO, 2, new_op(ID, 0, $1), new_op(LISTA, 0, $3)) ;}
	| ID '(' ')'						{$$ = new_op(APLICACAO, 2, new_op(ID, 0, $1), new_op(LISTA, 0, NULL)) ;}
	| ID 								{$$ = new_op(ID, 0, $1) ;}
	| '[' lista ']'						{$$ = new_op(LISTA, 0, $2) ;}
	| '['']'							{$$ = new_op(LISTA, 0, NULL) ;}
	| codigo ':' codigo					{$$ = new_op(CONCAT, 2, $1, $3) ;}
	| codigo '+' codigo					{$$ = new_op(SOMA, 2, $1, $3) ;}
	| codigo '-' codigo					{$$ = new_op(SUB, 2, $1, $3) ;}
	| codigo '*' codigo					{$$ = new_op(MULT, 2, $1, $3) ;}
	| codigo '^' codigo					{$$ = new_op(EXPON, 2, $1, $3) ;}
	| codigo '/' codigo					{$$ = new_op(DIV, 2, $1, $3) ;}
	| codigo AND codigo 				{$$ = new_op(AND, 2, $1, $3) ;}
	| codigo OR codigo					{$$ = new_op(OR, 2, $1, $3) ;}
	| NOT codigo						{$$ = new_op(NOT, 1, $2) ;}
	| HEAD codigo						{$$ = new_op(HEAD, 1, $2) ;}
	| TAIL codigo						{$$ = new_op(TAIL, 1, $2) ;}
	| VAZIA codigo						{$$ = new_op(VAZIA, 1, $2) ;}
	| codigo EQ codigo					{$$ = new_op(EQ, 2, $1, $3) ;}
	| codigo '>' codigo					{$$ = new_op(MAIOR_QUE, 2, $1, $3) ;}
	| codigo '<' codigo					{$$ = new_op(MENOR_QUE, 2, $1, $3) ;}
	;

%%
//Funções de limpeza
void free_op (Op* operador) {
	int i ;
	if(operador->tipo == STRING || operador->tipo == ID) {
		free(operador->string) ;
	} else {
		for(i = 0; i < operador->qtd_args; i++) {
			free_op(operador->vetor_op[i]) ;
		}
		free(operador->vetor_op) ;
	}
	free(operador) ;
}

void free_bracket(Bracket* bracket) {
	int i ;
	free(bracket->terminal) ;
	for(i = 0; i < bracket->qtd_elem; i++){
		free_bracket(bracket->elems[i]) ;
	}
	free(bracket) ;
}

void free_funcoes(Lista* lista) {
	Lista* aux ;
	//Limpa a lista de funções
	while(lista != NULL) {
		aux = lista->next ;
		free_op(lista->elem) ;
		free(lista) ;
		lista = aux ;
	}

	//Limpa as funções da memória
	qtd_funcoes-- ;
	while(qtd_funcoes >= 0) {
		free(funcao[qtd_funcoes]->nome) ;
		free_bracket(funcao[qtd_funcoes]->codigo) ;
		free(funcao[qtd_funcoes]->tipos) ;
		free(funcao[qtd_funcoes]) ;
		qtd_funcoes-- ;
	}
}

void make_lista (Op* operador, Lista* head) {
	Lista* aux = head ;
	int i = 0;
	while(aux != NULL) {
		i++ ;
		aux = aux->next ;
	}

	operador->qtd_args = i ;
	if(i == 0) {
		operador->vetor_op = NULL ;
	} else {
		aux = head ;
		operador->vetor_op = (Op**) malloc (i*sizeof(Op*)) ;
		for(i = 0; i < operador->qtd_args; i++) {
			operador->vetor_op[i] = aux->elem ;
			head = aux ;
			aux = aux->next ;
			free(head) ;
		}
	}
}

Op* new_op(int tipo, int qtd_op, ...) {
	va_list args ;
	Lista* lista ;
	int i ;
	Op* operador = (Op*) malloc (sizeof(Op)) ;
	if (operador == NULL) {
		yyerror("Falta de memória!\n") ;
	}

	operador->tipo = tipo ;
	operador->qtd_args = qtd_op ;
	//Lê os operandos da lista de argumentos
	va_start(args, qtd_op) ;

	if(qtd_op == 0) {
		operador->vetor_op = NULL ; // O argumento não será um operando
		
		switch(tipo) {
			case ID:
			case STRING:
				operador->string = va_arg(args, char*) ;
			break ;

			case NEG:
				operador->num = 0 - va_arg(args, int) ;
				operador->tipo = NUM ;
			break ;

			case NUM:
				operador->num = va_arg(args, int) ;
			break ;

			case BOOLEAN:
				operador->boolean = va_arg(args, int) ;
			break ;

			case LISTA:
				make_lista(operador, va_arg(args, Lista*)) ;
			break ;
		}
	} else {
		operador->vetor_op = (Op**) malloc (qtd_op*sizeof(Op*)) ;
		if(operador->vetor_op == NULL) {
			yyerror("Falta de memória!\n") ;
		}

		for(i = 0; i < qtd_op; i++) {
			operador->vetor_op[i] = va_arg(args, Op*) ;
		}
	}
	va_end(args) ;

	return operador ;
}

Lista* new_node (Op* elem, Lista* next) {
	Lista* node = (Lista*) malloc (sizeof(Lista)) ;
	if(node == NULL) {
		yyerror("Falta de memória!\n") ;
	}

	node->elem = elem ;
	node->next = next ;

	return node ;
}

//Começo das funções de bracket abstraction
Bracket* new_bracket (char* string, int qtd) {
	Bracket* new_bracket = (Bracket*) malloc (sizeof(Bracket)) ;
	if(new_bracket == NULL) {
		yyerror("Falta de memória!") ;
	}

	if(string == NULL) {
		new_bracket->terminal = NULL ;
	} else {
		new_bracket->terminal = strdup(string) ;
	}
	new_bracket->qtd_elem = qtd ;
	new_bracket->elems = (Bracket**) malloc (qtd*sizeof(Bracket*)) ;
	if(new_bracket->elems == NULL) {
		yyerror("Falta de memória!") ;
	}

	return new_bracket ;
}

char* lista_to_string (Op** lista, int tam) {
	int i = 0, j ;

	i += sprintf(str_aux + i, "[") ;

	if(tam > 0) {
		switch(lista[0]->tipo){
			case NUM:
				if(lista[0]->num < 0){
					i += sprintf(str_aux + i, "-#0#%d", -lista[0]->num) ;
				} else { 
					i += sprintf(str_aux + i, "#%d", lista[0]->num) ;
				}
			break ;

			case STRING:
				i += sprintf(str_aux + i, "%s", lista[0]->string) ;
			break ;

			case BOOLEAN:
				if(lista[0]->boolean == 1) {
					i += sprintf(str_aux + i, "K") ;
				} else {
					i += sprintf(str_aux + i, "k") ;
				}
			break ;
		}
	}
	for(j = 1; j < tam; j++) {
		switch(lista[j]->tipo){
			case NUM:
				if(lista[j]->num < 0){
					i += sprintf(str_aux + i, ",-#0#%d", -lista[j]->num) ;
				} else { 
					i += sprintf(str_aux + i, ",#%d", lista[j]->num) ;
				}
			break ;

			case STRING:
				i += sprintf(str_aux + i, ",%s", lista[j]->string) ;
			break ;

			case BOOLEAN:
				if(lista[j]->boolean == 1) {
					i += sprintf(str_aux + i, ",K") ;
				} else {
					i += sprintf(str_aux + i, ",k") ;
				}
			break ;
		}
	}

	i += sprintf(str_aux + i, "]") ;
	return str_aux ;
}

//cria a glc com os terminais nas folhas.
Bracket* prepare_bracket(Op* operador) {
	int aux, i ;
	Lista* lista_aux ;
	Bracket* resultado ;
	
	switch(operador->tipo) {
		case IFTHENELSE:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[1]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[2]) ;
		break ;

		case AND:
			// como se fosse em lambda calculo
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[1]) ;
			resultado->elems[2] = new_bracket("k", 0) ;
		break ;

		case OR:
			//como se fosse em lambda calculo
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[1] = new_bracket("K", 0) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
		break ;

		case NOT:
			//como se fosse em lamda calculo
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[1] = new_bracket("k", 0) ;
			resultado->elems[2] = new_bracket("K", 0) ;
		break ;

		case CONCAT:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = new_bracket(":", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
		break ;

		case SOMA:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = new_bracket("+", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
		break ;
		
		case EXPON:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = new_bracket("^", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
			break;

		case SUB:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = new_bracket("-", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
		break ;

		case MULT:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = new_bracket("*", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
		break ;

		case DIV:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = new_bracket("/", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
		break ;

		case EQ:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = new_bracket("=", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
		break ;

		case MAIOR_QUE:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = new_bracket(">", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
		break ;

		case MENOR_QUE:
			resultado = new_bracket(NULL, 3) ;
			resultado->elems[0] = new_bracket("<", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
			resultado->elems[2] = prepare_bracket(operador->vetor_op[1]) ;
		break ;

		case HEAD:
			resultado = new_bracket(NULL, 2) ;
			resultado->elems[0] = new_bracket("H", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
		break ;

		case TAIL:
			resultado = new_bracket(NULL, 2) ;
			resultado->elems[0] = new_bracket("T", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
		break ;

		case VAZIA:
			resultado = new_bracket(NULL, 2) ;
			resultado->elems[0] = new_bracket("N", 0) ;
			resultado->elems[1] = prepare_bracket(operador->vetor_op[0]) ;
		break ;

		case APLICACAO:
			resultado = new_bracket(NULL, operador->vetor_op[1]->qtd_args + 1) ;
			for(i = 0; i < qtd_funcoes; i++) {
				if(strcmp(operador->vetor_op[0]->string, funcao[i]->nome) == 0){
					resultado->elems[0] = new_bracket(funcao[i]->codigo->terminal, 0) ;
					i = qtd_funcoes + 1; 
				}
			}
			if(i == qtd_funcoes) {
				resultado->elems[0] =  new_bracket(operador->vetor_op[0]->string, 0) ;
			}
			for(i = 1; i <= operador->vetor_op[1]->qtd_args; i++) {
				resultado->elems[i] = prepare_bracket(operador->vetor_op[1]->vetor_op[i-1]) ;
			}
		break ;

		case ID:
			resultado = new_bracket(operador->string, 0) ;
		break ;

		case NUM:
			if(operador->num < 0) {
				sprintf(str_aux, "(-#0#%d)", (-operador->num)) ;
			} else { 
				sprintf(str_aux, "#%d", operador->num) ;
			}
			resultado = new_bracket(str_aux, 0) ;
		break ;

		case STRING:
			resultado = new_bracket(operador->string, 0) ;
		break ;

		case BOOLEAN:
			if(operador->boolean == 1) {
				resultado = new_bracket("K", 0) ;
			} else {
				resultado = new_bracket("k", 0) ;
			}
		break ;

		case LISTA:
			resultado = new_bracket(lista_to_string(operador->vetor_op, operador->qtd_args), 0) ;
		break ;

		default:
		break ;
	}
	return resultado ;
}

// Imprime em string um bracket
void sprint (Bracket* bracket) {
	int i ;
	if(bracket->qtd_elem == 0) {
		str_tam += sprintf(str_aux + str_tam, "%s", bracket->terminal) ;
	} else {
		str_tam += sprintf(str_aux + str_tam, "(") ;
		for(i = 0; i < bracket->qtd_elem; i++) {
			sprint(bracket->elems[i]) ;
		}
		str_tam += sprintf(str_aux + str_tam, ")") ;
	}
}

//Checa se a variável existe na sequência
int check_var (Bracket* bracket, char* var){
	int i, max = 0 ;
	if(bracket->qtd_elem == 0) {
		if(strcmp(bracket->terminal, var) == 0){
			return 1 ;
		} else {
			return 0 ;
		}
	} else {
		for(i = 0; i < bracket->qtd_elem; i++) {
			max = max || check_var(bracket->elems[i], var) ;
		}
		return max ;
	}
}

//Bracket abstraction com todos os operadores (dando free)
/*
[1]. [[x.a]] -> [x] [[a]]
[2]. [[a b]] -> [[a]] [[b]]
[3]. [[x]] -> a , se x variável ou cte.
[4]. [x] ((a b) c) -> B1 a b ([x] c), se a e b cte em x
[5]. [x] ((a b) c) -> C1 a ([x] b) c, se a e c cte em x
[6]. [x] ((a b) c) -> S1 a ([x]b) ([x]c), se a cte em x
[7]. [x] (a b) -> B a ([x] b), se a cte em x
[8]. [x] (a b) -> C ([x] a) b, se a cte em x
[9]. [x] ab -> S([x] a) ([x] b)
[10]. [x] y -> Ky, se x não livre em y
[11]. I , se x=y
*/
Bracket* do_abstraction (Bracket* bracket, char* var) {
	Bracket* resultado ;
	Bracket* a, * b, *c ;
	int i, max ;
	//se quantidade de elementos for igual a zero, são os terminais da glc.
	if(bracket->qtd_elem == 0) {
		// se a condição for verdadeira, entra na regra 11
		// caso não seja verdade, entra na regra 10
		if(check_var(bracket, var) == 1) {
			resultado = new_bracket("I", 0) ;
			free(bracket) ;
		} else {
			resultado = new_bracket(NULL, 2) ;
			resultado->elems[0] = new_bracket("K", 0) ;
			resultado->elems[1] = bracket ;
		}
	} else {
		// se o variavel nao existir nos operadores, entao entra aqui e aplica a regra 10.
		if (check_var(bracket, var) == 0) {
			resultado = new_bracket(NULL, 2) ;
			resultado->elems[0] = new_bracket("K", 0) ;
			resultado->elems[1] = bracket ;
		} else {
			if(bracket->qtd_elem >= 3){ //Combinadores de 4 parâmetros
			
				if(bracket->qtd_elem > 3) {
					a = new_bracket(NULL, bracket->qtd_elem - 2) ;
					for(i =  0; i < bracket->qtd_elem - 2; i++){
						a->elems[i] = bracket->elems[i] ;
					}
				} else {
					a = bracket->elems[0] ;
				}
				b = bracket->elems[bracket->qtd_elem - 2] ;
				c = bracket->elems[bracket->qtd_elem - 1] ;
				//todos as funções de 4 combinadores tem o a como constante, então primeiro vamos checar se ele é constante.
				if(check_var(a, var) == 0) {
					// se o a for constante, sabemos que temos uma substituição com 4 combinadores.
					if(check_var(b, var) == 0){
						//se b tambem for constante, aplicamos a regra 4
						resultado = new_bracket(NULL, 4) ;
						resultado->elems[0] = new_bracket("b", 0) ;
						resultado->elems[1] = a ;
						resultado->elems[2] = b ;
						resultado->elems[3] = do_abstraction(c, var) ;
					} else {
						if(check_var(c, var) == 0){
							// se o a e c for constante aplicamos a regra 5
							resultado = new_bracket(NULL, 4) ;
							resultado->elems[0] = new_bracket("c", 0) ;
							resultado->elems[1] = a ;
							resultado->elems[2] = do_abstraction(b, var) ;
							resultado->elems[3] = c ;
						} else {
							// caso contrario aplicamos a regra 6
							resultado = new_bracket(NULL, 4) ;
							resultado->elems[0] = new_bracket("s", 0) ;
							resultado->elems[1] = a ;
							resultado->elems[2] = do_abstraction(b, var) ;
							resultado->elems[3] = do_abstraction(c, var) ;
						}
					}
					return resultado ;
				}
			}
		 	if(bracket->qtd_elem > 2) {
				a = new_bracket(NULL, bracket->qtd_elem - 1) ;
				for(i =  0; i < bracket->qtd_elem - 1; i++){
					a->elems[i] = bracket->elems[i] ;
				}
			} else {
				a = bracket->elems[0] ;
			}
			b = bracket->elems[bracket->qtd_elem - 1] ;

			if(check_var(a, var) == 0){
				// se A for constante usa a regra 7
				resultado = new_bracket(NULL, 3) ;
				resultado->elems[0] = new_bracket("B", 0) ;
				resultado->elems[1] = a ;
				resultado->elems[2] = do_abstraction(b, var) ;
			} else if(check_var(b, var) == 0){
				// se o B for constante usa a regra 8
				resultado = new_bracket(NULL, 3) ;
				resultado->elems[0] = new_bracket("C", 0) ;
				resultado->elems[1] = do_abstraction(a, var) ;
				resultado->elems[2] = b ;
			} else {
				//caso contrario usa a 9
				resultado = new_bracket(NULL, 3) ;
				resultado->elems[0] = new_bracket("S", 0) ;
				resultado->elems[1] = do_abstraction(a, var) ;
				resultado->elems[2] = do_abstraction(b, var) ;
			}
			free(bracket) ;
		}
	}
	return resultado ;
}

//Op implementação tem duas partes vetor_op[0] tem a parte da lista_id e vetor_op[1] tem a parte do código.
Bracket* bracket_abstraction(Op* implementacao) {
	//chama a função que vai prepara que monta a glc com a parte do código.
	Bracket* codigo = prepare_bracket(implementacao->vetor_op[1]) ;
	Bracket* aux ;
	
	//pega o vetor de operadores da funcao.
	Op** variaveis = implementacao->vetor_op[0]->vetor_op ;
	int qtd_variaveis = implementacao->vetor_op[0]->qtd_args - 1 ;
	
	while(qtd_variaveis >= 0) {
		codigo = do_abstraction(codigo, variaveis[qtd_variaveis]->string) ;
		qtd_variaveis-- ;
	}

	//Checa se a função é recursiva. Se for, insere o Y no início
	if(codigo->qtd_elem == 2 && strcmp(codigo->elems[0]->terminal, "K") == 0) {
		codigo = codigo->elems[1] ;
		aux = codigo ;
	} else {
		aux = new_bracket(NULL, 2) ;
		aux->elems[0] = new_bracket("Y", 0) ;
		aux->elems[1] = codigo ;
	}

	//Otimizacao para próximas bracket abstractions
	//transforma o bracket em string.
	str_tam = 0 ;
	sprint(aux) ;
	free_bracket(aux) ;
	aux = new_bracket(strdup(str_aux), 0) ;
	
	return aux ;
}

int checa_codigo (Op* operador, int tipo_esperado) {
	int i, j ;
	switch(operador->tipo) {
		case NUM:
		case BOOLEAN:
		case STRING:
			if(tipo_esperado != -1 && tipo_esperado != operador->tipo) {
				printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
				exit(1) ;
			}
			return operador->tipo ;
		break ;

		case LISTA:
			for(i = 1; i < operador->qtd_args; i++){
				if(operador->vetor_op[0]->tipo != operador->vetor_op[i]->tipo) {
					printf("Lista com tipos diferentes encontrada na função %s\n", funcao_atual->nome) ;
					exit(1) ;
				}
			}
			if(operador->qtd_args == 0) {
				if(tipo_esperado != -1 && tipo_esperado != LISTA && tipo_esperado != LISTA_INT && tipo_esperado != LISTA_BOOL && tipo_esperado != LISTA_STRING) {
					printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
					exit(1) ;
				}
				return LISTA ;
			}
			switch(operador->vetor_op[0]->tipo) {
				case NUM:
					if(tipo_esperado != -1 && tipo_esperado != LISTA && tipo_esperado != LISTA_INT) {
						printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
						exit(1) ;
					}
					return LISTA_INT ;
				break ;

				case BOOLEAN:
					if(tipo_esperado != -1 && tipo_esperado != LISTA && tipo_esperado != LISTA_BOOL) {
						printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
						exit(1) ;
					}
					return LISTA_BOOL ;
				break ;

				case STRING:
					if(tipo_esperado != -1 && tipo_esperado != LISTA && tipo_esperado != LISTA_STRING) {
						printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
						exit(1) ;
					}
					return LISTA_STRING ;
				break ;

				default:
					yyerror("Erro desconhecido") ;
				break ;
			}
		break ;

		case ID:
			for(i = 0; i != -1 && i < funcao_atual->qtd_param ; i++) {
				if(strcmp(operador->string, parametro[i]) == 0) {
					if(tipo_esperado != -1 && tipo[i] != -1 && tipo[i] != tipo_esperado) {
						printf("Tipo conflitante na label %s da funcao %s\n", parametro[i], funcao_atual->nome) ;
						exit(1) ;
					} else {
						if(tipo[i] == -1) {
							tipo[i] = tipo_esperado ;
							return tipo_esperado ;
						} else {
							return tipo[i] ;
						}
					}
				}
			}

			printf("Parâmetro %s não está presente na declaração da função %s\n", operador->string, funcao_atual->nome) ;
			exit(1) ;
		break ;

		case APLICACAO:
			if(strcmp(funcao_atual->nome, operador->vetor_op[0]->string) == 0){
				if(funcao_atual->qtd_param < operador->vetor_op[1]->qtd_args) {
					printf("Função %s foi chamada com a quantidade errada de argumentos, na função %s\n", funcao[i]->nome, funcao_atual->nome) ;
					exit(1) ;
				} else {
					for(j = 0; j < operador->vetor_op[1]->qtd_args; j++) {
						i = checa_codigo(operador->vetor_op[1]->vetor_op[j], tipo[j]) ;
						if(tipo[j] != -1 && i != tipo[j]) {
							printf("%s: Erro de retorno na aplicação de %s\n", funcao_atual->nome, funcao[i]->nome) ;
							exit(1) ;
						} else if (tipo[j] == -1) {
							tipo[j] = i ;
						}
					}
					if(funcao_atual->qtd_param == operador->vetor_op[1]->qtd_args) {
						if(tipo_esperado != -1 && tipo_esperado != funcao_atual->saida && funcao_atual->saida != -1) {
							printf("%s: Erro de retorno na aplicação de %s\n", funcao_atual->nome, funcao_atual->nome) ;
							exit(1) ;
						}
						funcao_atual->saida = tipo_esperado ;
						return funcao_atual->saida ;
					} else {
						if(tipo_esperado != -1 && tipo_esperado != FUNCAO) {
							printf("%s: Erro de retorno na aplicação de %s\n", funcao_atual->nome, funcao_atual->nome) ;
							exit(1) ;
						}
						return FUNCAO ;
					}
				}
			}
			for(i = 0; i < qtd_funcoes && i != -1; i++) {
				if(strcmp(funcao[i]->nome, operador->vetor_op[0]->string) == 0) {
					if(funcao[i]->qtd_param < operador->vetor_op[1]->qtd_args) {
						printf("Função %s foi chamada com a quantidade errada de argumentos, na função %s\n", funcao[i]->nome, funcao_atual->nome) ;
						exit(1) ;
					} else {
						for(j = 0; j < operador->vetor_op[1]->qtd_args; j++) {
							checa_codigo(operador->vetor_op[1]->vetor_op[j], funcao[i]->tipos[j]) ;
						}
						if(funcao[i]->qtd_param == operador->vetor_op[1]->qtd_args) {
							if(tipo_esperado != -1 && tipo_esperado != funcao[i]->saida) {
								printf("%s: Erro de retorno na aplicação de %s\n", funcao_atual->nome, funcao[i]->nome) ;
								exit(1) ;
							}
							return funcao[i]->saida ;
						} else {
							if(tipo_esperado != -1 && tipo_esperado != FUNCAO) {
								printf("%s: Erro de retorno na aplicação de %s\n", funcao_atual->nome, funcao[i]->nome) ;
								exit(1) ;
							}
							return FUNCAO ;
						}
					}
				}
			}

			checa_codigo(operador->vetor_op[0], FUNCAO) ;
			return -1 ;
		break ;

		case IFTHENELSE:
			checa_codigo(operador->vetor_op[0], BOOLEAN) ;
			i = checa_codigo(operador->vetor_op[1], -1) ;
			j = checa_codigo(operador->vetor_op[2], -1) ;
			if(i == -1 && j == -1) {
				i = checa_codigo(operador->vetor_op[1], -1) ;
				j = checa_codigo(operador->vetor_op[2], -1) ;
				if(i == -1 && j == -1) {
					return -1 ;
				} else {
					return checa_codigo(operador, -1) ;
				}				
			} else if(i == -1 && j != -1) {
				i = checa_codigo(operador->vetor_op[1], j) ;
				if(i != -1 && i != j) {
					printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
					exit(1) ;
				}
				return j ;
			} else if(i != -1 && j == -1) {
				j = checa_codigo(operador->vetor_op[2], i) ;
				if(j != -1 && i != j) {
					printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
					exit(1) ;
				}
				return i ;
			} else {
				if(i != j) {
					printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
					exit(1) ;
				}
				return i ;
			}
		break ;

		case CONCAT:
			if(tipo_esperado != -1 && tipo_esperado != LISTA && tipo_esperado != LISTA_INT && tipo_esperado != LISTA_BOOL && tipo_esperado != LISTA_STRING) {
				printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
				exit(1) ;
			}

			i = checa_codigo(operador->vetor_op[0], -1) ;
			switch(i) {
				case NUM:
					if(tipo_esperado != -1 && tipo_esperado != LISTA && tipo_esperado != LISTA_INT) {
						printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
						exit(1) ;
					}
					checa_codigo(operador->vetor_op[1], LISTA_INT) ;
					return LISTA_INT ;
				break ;
				
				case BOOLEAN:
					if(tipo_esperado != -1 && tipo_esperado != LISTA && tipo_esperado != LISTA_BOOL) {
						printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
						exit(1) ;
					}
					checa_codigo(operador->vetor_op[1], LISTA_BOOL) ;
					return LISTA_BOOL ;
				break ;

				case STRING:
					if(tipo_esperado != -1 && tipo_esperado != LISTA && tipo_esperado != LISTA_STRING) {
						printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
						exit(1) ;
					}
					checa_codigo(operador->vetor_op[1], LISTA_STRING) ;
					return LISTA_STRING ;
				break ;

				case -1:
					i = checa_codigo(operador->vetor_op[1], LISTA) ;
					switch(i) {
						case LISTA_INT:
							checa_codigo(operador->vetor_op[0], NUM) ;
						break ;

						case LISTA_BOOL:
							checa_codigo(operador->vetor_op[0], BOOLEAN) ;
						break ;

						case LISTA_STRING:
							checa_codigo(operador->vetor_op[0], STRING) ;
						break ;
					}
					return i ;
				break ;
			}
		break ;

		case SUB:
		case SOMA:
		case DIV:
		case MULT:
		case EXPON:
			if(tipo_esperado != -1 && tipo_esperado != NUM) {
				printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
				exit(1) ;
			}
			checa_codigo(operador->vetor_op[0], NUM) ;
			checa_codigo(operador->vetor_op[1], NUM) ;
			return NUM ;
		break ;

		case AND:
		case OR:
			if(tipo_esperado != -1 && tipo_esperado != BOOLEAN) {
				printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
				exit(1) ;
			}
			checa_codigo(operador->vetor_op[0], BOOLEAN) ;
			checa_codigo(operador->vetor_op[1], BOOLEAN) ;
			return BOOLEAN ;
		break ;

		case NOT:
			if(tipo_esperado != -1 && tipo_esperado != BOOLEAN) {
				printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
				exit(1) ;
			}
			checa_codigo(operador->vetor_op[0], BOOLEAN) ;
			return BOOLEAN ;
		break ;

		case HEAD:
			i = checa_codigo(operador->vetor_op[0], LISTA) ;
			switch(i) {
				case LISTA_INT:
					if(tipo_esperado != -1 && tipo_esperado != NUM) {
						printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
						exit(1) ;
					}
				break ;

				case LISTA_BOOL:
					if(tipo_esperado != -1 && tipo_esperado != BOOLEAN) {
						printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
						exit(1) ;
					}
				break ;

				case LISTA_STRING:
					if(tipo_esperado != -1 && tipo_esperado != STRING) {
						printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
						exit(1) ;
					}
				break ;
			}
			return i ;
		break ;

		case TAIL:
			i = checa_codigo(operador->vetor_op[0], LISTA) ;
			if(tipo_esperado != -1 && tipo_esperado != LISTA && tipo_esperado != i) {
				printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
				exit(1) ;
			}
			return i ;
		break ;

		case VAZIA:
			if(tipo_esperado != -1 && tipo_esperado != BOOLEAN) {
				printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
				exit(1) ;
			}
			checa_codigo(operador->vetor_op[0], LISTA) ;
			return BOOLEAN ;
		break ;

		case EQ:
		case MAIOR_QUE:
		case MENOR_QUE:
			if(tipo_esperado != -1 && tipo_esperado != BOOLEAN) {
				printf("Erro na função %s: tipos dos operando não batem\n", funcao_atual->nome) ;
				exit(1) ;
			}
			checa_codigo(operador->vetor_op[0], NUM) ;
			checa_codigo(operador->vetor_op[1], NUM) ;
			return BOOLEAN ;
		break ;
	}
}

void processa_funcao (Op* op_funcao) {
	int i, j ;
	//função atual é o define que usamos para não ter que estar reescrevendo direto funcao[qtd_funcao]
	funcao_atual = (Function*) malloc (sizeof(Function)) ;
	// A função strdup copia uma string para o ponteiro. mesma coisa que seria usar a strlen depois usar o malloc e depois usar strcpy.
	
	// a arvore inicial para um caso f=2 seria promgrama -> funcao -> lista_id-> f, como chamamos essa função passando o parametro funcao, 
	//então para acessar o nome da função temos que usar isso op_funcao->vetor_op[0]->vetor_op[0]->string
	funcao_atual->nome = strdup(op_funcao->vetor_op[0]->vetor_op[0]->string) ;
	
	//procura se a função já foi declarada antes.
	for(i = 0; i < qtd_funcoes; i++) {
		if(strcmp(funcao[i]->nome, funcao_atual->nome) == 0) {
			printf("Declaração prévia da função %s encontrada\n", funcao_atual->nome) ;
			exit(1) ;
		}
	}
	
	//como um dos paretros da quantidade de argumentos é o nome da função, então a qtd de parametros é a quantidade de argumentos -1.
	funcao_atual->qtd_param = op_funcao->vetor_op[0]->qtd_args - 1 ;
	funcao_atual->tipos = (int*) malloc (funcao_atual->qtd_param*sizeof(int)) ;
	
	//ler o printf para maiores esclarecimentos, se já não tiverem sido usados, então copia para funcao_atual
	for(i = 1; i <= funcao_atual->qtd_param; i++) {
		for(j = 0; j < qtd_funcoes; j++) {
			if(strcmp(funcao[j]->nome, op_funcao->vetor_op[0]->vetor_op[i]->string) == 0) {
				printf("Parâmetro %s da função %s tem mesma label de uma função previamente definida\n", op_funcao->vetor_op[0]->vetor_op[i]->string, funcao_atual->nome) ;
				exit(1) ;
			}
		}
		strcpy(parametro[i -1], op_funcao->vetor_op[0]->vetor_op[i]->string) ;
		tipo[i - 1] = -1 ;

	}
	#ifdef SAFE_MODE_on
		funcao_atual->saida = -1 ;
		funcao_atual->saida = checa_codigo(op_funcao->vetor_op[1], -1) ;
		for(i = 0; i < funcao_atual->qtd_param; i++) {
			funcao_atual->tipos[i] = tipo[i] ;
		}
		#ifdef DEBUG_on
			printf("%s :: ", funcao_atual->nome) ;
			for(i = 0; i < funcao_atual->qtd_param; i++) {
				printf("%d -> ", funcao_atual->tipos[i]) ;
			}
			printf("%d\n", funcao_atual->saida) ;
		#endif
	#endif
	funcao_atual->codigo = bracket_abstraction(op_funcao) ;
	qtd_funcoes++ ;
}

void analise_semantica(Lista* lista_funcoes) {
	Lista* lista = lista_funcoes ;

	while(lista != NULL) {
		processa_funcao(lista->elem) ;
		lista = lista->next ;
	}

	//Checagens da main
	qtd_funcoes-- ;
	if(strcmp(funcao_atual->nome, "main") != 0) {
		yyerror("Main não encontrada (deve ser declarada no final do script)") ;
	} else if(funcao_atual->qtd_param != 0) {
		yyerror("A main não deve possuir parâmetros") ;
	} else if(funcao_atual->saida == FUNCAO) {
		yyerror("A main deve retornar um tipo básico (está retornando uma função)") ;
	}

	freopen("back_end.in", "w", stdout) ;
	printf("%s", funcao_atual->codigo->terminal) ;
	fclose(stdout) ;

	free_funcoes(lista_funcoes) ;
}

void yyerror (char* err) {
	printf("%s\n", err) ;
	exit(1) ;
}

int main() {
	yyparse() ;
	return 0 ;
}
