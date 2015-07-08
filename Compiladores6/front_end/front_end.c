#include "front_end.h"

Funcao* nova_funcao (char* nome, Fila* brackets, Celula* codigo) {
	char* bracket;
	
	while(!fila_vazia(brackets)) {
			bracket = fila_topo(brackets);
			bracket_abs(bracket, codigo);
			fila_retira(brackets);
	}

	if(!eh_constante(nome, codigo)) {
		codigo = bracket_abs(nome, codigo);
		codigo = nova_celula_deriv(nova_celula_terminal_S(strdup("Y")), codigo);
	}

	Funcao* rt = (Funcao*) malloc(sizeof(Funcao));
	rt->nome = nome;
	rt->brackets = brackets;
	rt->codigo = codigo;

	return rt;
}

Celula* nova_celula_deriv(Celula *esq, Celula *dir) {
	Celula* rt = (Celula*) malloc(sizeof(Celula));
	rt->tipo = '@';
	rt->filho_esq = esq;
	rt->filho_dir = dir;
	return rt;
}

Celula *nova_celula_terminal_S(char* c) {
	Celula* rt = (Celula*) malloc(sizeof(Celula));
	rt->tipo = 'S';
	rt->filho_esq = NULL;
	rt->filho_dir = NULL;
	rt->string = c;
	//printf("Celula terminal string: %s\n", rt->string);
	return rt;
}

Celula *nova_celula_terminal_I(int n) {
	Celula* rt = (Celula*) malloc(sizeof(Celula));
	rt->tipo = 'I';
	rt->filho_esq = NULL;
	rt->filho_dir = NULL;
	rt->numero = n;
	//printf("Celula terminal inteiro: %d\n", rt->numero);
	return rt;
}

void imprime_arvore(Celula* raiz)
{
    if(raiz->tipo == '@')
    {
        if(raiz->filho_esq != NULL)
        {
            imprime_arvore(raiz->filho_esq);
        }
        if(raiz->filho_dir != NULL)
        {
            if(raiz->filho_dir->tipo == '@')
            {
                printf("(");
            }
            imprime_arvore(raiz->filho_dir);
            if(raiz->filho_dir->tipo == '@')
            {
                printf(")");
            }
        }
    }
    else
    {
        if(raiz->tipo == 'I')
            printf("%d ", raiz->numero);
        else {
        	printf("%s", raiz->string);
        }
    }
}

int eh_constante(char *c, Celula *codigo) {
	int rt;
	if(codigo->tipo == '@') {
		rt =  ( eh_constante(c, codigo->filho_esq) && eh_constante(c, codigo->filho_dir) );
	}
	else if (codigo->tipo == 'S')  {
		rt = ! ( strcmp(c, codigo->string) == 0 );
	}
	else {
		rt = 1;
	}
	return rt;
}

Celula* substitui_codigo(Celula *cod, Funcao* f) {
	if (cod->tipo == 'S') {
		if( strcmp(cod->string, f->nome) == 0 ) {
			free(cod);
			return f->codigo;
		}
		else return cod;
	}
	else if(cod->tipo == '@') {
		cod->filho_esq = substitui_codigo(cod->filho_esq, f);
		cod->filho_dir = substitui_codigo(cod->filho_dir, f);
	}
	return cod;
}

Celula* bracket_abs(char* bracket, Celula *codigo) {
	Celula *rt;
	Celula *rc;
	Celula *rc2;
	Celula *aux;
	int constate_filho_esq;
	int constate_filho_dir;
	rt = codigo;
	if(codigo->tipo == '@') {
		constate_filho_esq = eh_constante(bracket, codigo->filho_esq) ;
		constate_filho_dir = eh_constante(bracket, codigo->filho_dir) ;
		if(constate_filho_esq && constate_filho_dir){
			rt = nova_celula_deriv(nova_celula_terminal_S(strdup("K")), codigo);
		}
		else if(constate_filho_esq && !constate_filho_dir) {
			rc = bracket_abs(bracket, codigo->filho_dir);
			aux = codigo->filho_esq;
			codigo->filho_esq = nova_celula_deriv(nova_celula_terminal_S(strdup("B")), aux);
			codigo->filho_dir = rc;
		}
		else if(!constate_filho_esq && constate_filho_dir) {
			rc = bracket_abs(bracket, codigo->filho_esq);
			codigo->filho_esq = nova_celula_deriv(nova_celula_terminal_S(strdup("C")), rc);
		}
		else {
			rc = bracket_abs(bracket, codigo->filho_esq);
			rc2 = bracket_abs(bracket, codigo->filho_dir);
			codigo->filho_esq = nova_celula_deriv(nova_celula_terminal_S(strdup("S")), rc);
			codigo->filho_dir = rc2;
		}
	}
	else if (codigo->tipo == 'S') {
		int eh_igual = (strcmp(bracket, codigo->string) == 0 );
		if(eh_igual) {
			strcpy(codigo->string, "I");
		}
		else {
			rt = nova_celula_deriv(nova_celula_terminal_S(strdup("K")), codigo);
		}
	}
	return rt;
}