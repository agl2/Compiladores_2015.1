#include "front_end.h"

Funcao* nova_funcao (char* nome, Fila* brackets, Celula* codigo) 
{
	char* bracket;
	int parametros = 0;
	while(!fila_vazia(brackets)) 
	{
		bracket = fila_topo(brackets);
		parametros++;
		bracket_abs(bracket, codigo); //faz bracket para os parametros 
		fila_retira(brackets);
	}

	if(!eh_constante(nome, codigo)) //se tenho a funcao no codigo
	{
		codigo = bracket_abs(nome, codigo); //faço bracket pra ela
		codigo = nova_celula_deriv(nova_celula_terminal_S(strdup("Y")), codigo); //coloco y no começo	
	}

	Funcao* rt = (Funcao*) malloc(sizeof(Funcao));
	rt->nome = nome;
	rt->brackets = brackets;
	rt->codigo = codigo;
	rt->qtd_parametros = parametros;
	return rt;
}

Celula* nova_celula_deriv(Celula *esq, Celula *dir) {
	Celula* rt = (Celula*) malloc(sizeof(Celula));
	rt->tipo = '@';
	rt->filho_esq = esq;
	rt->filho_dir = dir;
	return rt;
}

Celula* nova_celula_lista(Celula *esq, Celula *dir) {
	Celula* rt = (Celula*) malloc(sizeof(Celula));
	rt->tipo = '$';
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

Celula *nova_celula_terminal_vazia(char* c) {
	Celula* rt = (Celula*) malloc(sizeof(Celula));
	rt->tipo = ']';
	rt->filho_esq = NULL;
	rt->filho_dir = NULL;
	rt->string = c;
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

void imprime_lista(Celula *raiz)
{
    if(raiz->tipo == '$')
    {
        if(raiz->filho_esq != NULL)
        {
        	if(raiz->filho_esq->tipo == '$' || raiz->filho_esq->tipo == ']')
        	{
        		printf("[");
        	}
        	imprime_lista(raiz->filho_esq);
        }
        if(raiz->filho_dir != NULL)
        {
        	if(raiz->filho_dir->tipo != ']')
        	{
        		printf(",");
        	}
        	imprime_lista(raiz->filho_dir);
        }
    }
    else if(raiz->tipo=='@')
    {
    	printf("(");
    	imprime_arvore(raiz);
    	printf(")");
    }
    else
    {
        if(raiz->tipo == 'I')
        {
        	printf("%d", raiz->numero);
        }
        else
        {
        	printf("%s", raiz->string);
        }
    }
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
    else if(raiz->tipo == '$')
    {
    	printf("[");
        imprime_lista(raiz);
    }
    else
    {
        if(raiz->tipo == 'I')
        {
        	printf("%d ", raiz->numero);
        }
        else if(strcmp(raiz->string, "B1") == 0) 
        {
    		printf("b");
    	}
    	else if(strcmp(raiz->string, "C1") == 0) 
    	{
    		printf("c");
    	}
    	else if(strcmp(raiz->string, "S1") == 0) 
    	{
    		printf("s");
    	}
        else if(raiz->tipo == ']')
        {
        	printf("[]");
        }
        else
        {
        	printf("%s", raiz->string);
        }
    }
}

int eh_constante(char *c, Celula *codigo) {
	int rt;
	if(codigo->tipo == '@') 
	{
		rt =  ( eh_constante(c, codigo->filho_esq) && eh_constante(c, codigo->filho_dir) );
	}
	else if (codigo->tipo == 'S')  
	{
		rt = ! ( strcmp(c, codigo->string) == 0 );
	}
	else 
	{
		rt = 1;
	}
	return rt;
}


int verifica_B_linha(Celula *codigo)
{ 
	int retorno = 0;
	
	if(codigo->tipo=='@' && codigo->filho_dir != NULL && codigo->filho_esq != NULL)
	{
		retorno = 1;		
	}
	else;

	return retorno;
}
int verifica_C_S_linha(char* bracket, Celula *codigo)
{
	int retorno=0;
	int direita=0;
	int esquerda=0;

	if(codigo->filho_dir!=NULL&&codigo->filho_esq!=NULL)
	{
		direita = eh_constante(bracket,codigo->filho_dir);
		esquerda = eh_constante(bracket,codigo->filho_esq);
	}
	if(esquerda==1&&direita==0)
	{
		retorno=1;	
	}

	return retorno;
}


Celula* bracket_abs(char* bracket, Celula *codigo) {
	Celula *rt;
	Celula *rc;
	Celula *rc2;
	Celula *aux;
	int otimiza= 0;
	int constate_filho_esq;
	int constate_filho_dir;
	rt = codigo;

	if(codigo->tipo == '@' || codigo->tipo == '$') {

		constate_filho_esq = eh_constante(bracket, codigo->filho_esq) ;
		constate_filho_dir = eh_constante(bracket, codigo->filho_dir) ;
		if(constate_filho_esq && constate_filho_dir){
			rt = nova_celula_deriv(nova_celula_terminal_S(strdup("K")), codigo);
		}
		else if(constate_filho_esq && !constate_filho_dir) {
			
				
				otimiza = verifica_B_linha(codigo->filho_esq);

				if(otimiza==0)
				{
					rc = bracket_abs(bracket, codigo->filho_dir);
					aux = codigo->filho_esq;
					codigo->filho_esq = nova_celula_deriv(nova_celula_terminal_S(strdup("B")), aux);
					codigo->filho_dir = rc;
				}
				else
				{
					rc = bracket_abs(bracket, codigo->filho_dir);
					aux = codigo->filho_esq;
					codigo->filho_esq= nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("B1")), aux->filho_esq),aux->filho_dir);
					codigo->filho_dir = rc;
				}

		}
		else if(!constate_filho_esq && constate_filho_dir) {
			
			otimiza = verifica_C_S_linha(bracket,codigo->filho_esq);

			if(otimiza==0)
			{
				rc = bracket_abs(bracket, codigo->filho_esq);
				codigo->filho_esq = nova_celula_deriv(nova_celula_terminal_S(strdup("C")), rc);
			}
			else
			{
				aux = codigo->filho_esq;
				rc = bracket_abs(bracket, codigo->filho_esq->filho_dir);
				codigo->filho_esq = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("C1")), aux->filho_esq),rc);

			}
		}
		else {

			otimiza = verifica_C_S_linha(bracket,codigo->filho_esq);
			if(otimiza == 0)
			{
				rc = bracket_abs(bracket, codigo->filho_esq);
				rc2 = bracket_abs(bracket, codigo->filho_dir);
				codigo->filho_esq = nova_celula_deriv(nova_celula_terminal_S(strdup("S")), rc);
				codigo->filho_dir = rc2;
			}
			else
			{
				aux= codigo->filho_esq;
				rc = bracket_abs(bracket,codigo->filho_dir);
				rc2 = bracket_abs(bracket,aux->filho_dir);
				codigo->filho_dir=rc;
				codigo->filho_esq = nova_celula_deriv(nova_celula_deriv(nova_celula_terminal_S(strdup("S1")),aux->filho_esq),rc2); 

			}
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