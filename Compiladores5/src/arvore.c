#include "../include/arvore.h"

#define CHAR_NULL '\0'

inline Celula* cria_celula_folha(char tipo, char mem)
{
    Celula* rt = (Celula*) malloc(sizeof(Celula));
    rt->tipo = tipo;
    rt->inteiro = 0;
    rt->mem = mem;
    rt->filho_esq = NULL;
    rt->filho_dir = NULL;
    return rt;
}

inline Celula* cria_celula_folha_inteiro(int num, char mem)
{
    Celula* rt = (Celula*) malloc(sizeof(Celula));
    rt->inteiro = num;
    rt->tipo = '#'; //tipo vai ser inteiro
    rt->mem = mem;
    rt->filho_esq = NULL;
    rt->filho_dir = NULL;
    return rt;
}

inline Celula* cria_celula_derivacao(Celula* filho_esq, Celula* filho_dir)
{
    Celula* rt = (Celula*) malloc(sizeof(Celula));
    rt->tipo = '@';
    rt->mem = CHAR_NULL;
    rt->filho_esq = filho_esq;
    rt->filho_dir = filho_dir;
    return rt;
}
inline Celula* cria_celula_lista()
{
    Celula* rt = (Celula*) malloc(sizeof(Celula));
    rt->inteiro = 0;
    rt->tipo = '$'; //tipo vai ser inteiro
    rt->mem = CHAR_NULL;
    rt->filho_esq = NULL;
    rt->filho_dir = NULL;
    return rt;

}
inline char* captura_string_colchete(char* str, int* i)
{
    int nivel_colchete = 0;
    char* rt;
    int inicial = *i;
    int n;
    if(str[*i] == '[')
    {
        nivel_colchete++;

    }
    while(nivel_colchete != 0)
    {
        *i = *i + 1;
        if(str[*i] == ']')
        {
            nivel_colchete--;

        }
        else if(str[*i] == '[')
        {
            nivel_colchete++;

        }
    }

    n = *i - inicial;
    rt = (char*) malloc(sizeof(char)*(n+2));
    strncpy(rt, str+inicial, n+2);
    int j;
    char aux;
    rt[n+1] = CHAR_NULL;
    return rt;
}

inline char* captura_string(char* str, int* i)
{
    int nivel_parenteses = 0;
    char* rt;
    int inicial = *i;
    int n;
    if(str[*i] == '(')
    {
        nivel_parenteses++;
    }
    while(nivel_parenteses != 0)
    {
        *i = *i + 1;
        if(str[*i] == ')') {
            nivel_parenteses--;
        }
        else if(str[*i] == '(') {
            nivel_parenteses++;
        }
    }
    n = *i - inicial;
    rt = (char*) malloc(sizeof(char)*n);
    strncpy(rt, str+inicial + 1, n);
    rt[n-1] = CHAR_NULL;
    return rt;
}

inline int eh_digito(char c) {
    if('0' <= c && c <= '9') return 1;
    else return 0;
}


Celula* monta_arvore(char* str)
{
    int i;
    char* str_aux;
    Celula* it_aux = NULL;
    Celula* it = cria_celula_derivacao(NULL, NULL);
    int aux;
    for(i = 0; str[i]!= CHAR_NULL; i++)
    {
        switch(str[i])
        {
            case '(' :
                str_aux = captura_string(str, &i);
                if(it->filho_esq == NULL)
                {
                    it->filho_esq = monta_arvore(str_aux);
                }
                else if (it->filho_dir == NULL)
                {
                    it->filho_dir = monta_arvore(str_aux);
                }
                else
                {
                    it_aux = it;
                    it = cria_celula_derivacao(it_aux, monta_arvore(str_aux));
                }
                free(str_aux);
                break;
            ///BAGUNCA DE RAFAEL
            case '[':
                it_aux = it;
                if(it->filho_dir== NULL)
                {
                    for(i = i + 1; str[i]!= ']'; i++)
                    {
						if(str[i]!= ',' && str[i] != '('&&str[i]!='[')
						{
							it->filho_dir = cria_celula_lista();
							it->filho_dir->filho_esq = (Celula*) malloc(sizeof(Celula));
                            if(eh_digito(str[i]))
                            {
                                sscanf(str+i, "%d" ,&it->filho_dir->filho_esq->inteiro);
                                it->filho_dir->filho_esq->tipo = '#';
                                while(eh_digito(str[i])) i++;
                                i--;
							}
							else
							{
								it->filho_dir->filho_esq->tipo = str[i];
								it->filho_dir->filho_esq->inteiro = 0;
							}
							it->filho_dir->filho_esq->filho_dir=NULL;
							it->filho_dir->filho_esq->filho_esq=NULL;

							it = it->filho_dir;
						}
						else if(str[i] == '(')
                        {
                            it->filho_dir = cria_celula_lista();
                            str_aux = captura_string(str, &i);
                            it->filho_dir->filho_esq =  monta_arvore(str_aux);
                            it = it->filho_dir;
                        }
                        else if(str[i]=='[')
                        {
                          it->filho_dir = cria_celula_lista();
                          str_aux = captura_string_colchete(str, &i);
                          it->filho_dir->filho_esq = monta_arvore(str_aux);
                          it = it->filho_dir;
                        }
                    }
                    it->filho_dir = (Celula*) malloc(sizeof(Celula));
                    it->filho_dir->tipo = ']';//representa lista vazia
                    it->filho_dir->inteiro = 0;
                    it->filho_dir->filho_esq=NULL;
                    it->filho_dir->filho_dir=NULL;
                }
                else
                {
                    Celula* aux2 = (Celula*) malloc(sizeof(Celula));
                    aux2->tipo = '@';
                    aux2->mem = CHAR_NULL;
                    aux2->filho_esq = it;
                    aux2->filho_dir = NULL;
                    it_aux = aux2;
                    i--;
                }
                it = it_aux;
                break;
            ///TERMINA A BAGUNCA
            default:
                if(it->filho_esq == NULL)
                {
                    if(eh_digito(str[i]))
                    {
                        sscanf(str + i, "%d" ,&aux);
                        while(eh_digito(str[i])) i++;

                        it->filho_esq = cria_celula_folha_inteiro(aux, CHAR_NULL);
                        i--;
                    }
                    else
                    {
                        it->filho_esq = cria_celula_folha(str[i],CHAR_NULL);
                    }
                }
                else if (it->filho_dir == NULL)
                {
                    if(eh_digito(str[i]))
                    {
                        sscanf(str + i, "%d" ,&aux);
                        while(eh_digito(str[i])) i++;

                        it->filho_dir = cria_celula_folha_inteiro(aux, CHAR_NULL);
                        i--;
                    }
                    else
                    {
                        it->filho_dir = cria_celula_folha(str[i],CHAR_NULL);
                        if(str[i] == '+' || str[i] == '/' || str[i] == '-' || str[i] == '^' || str[i] == '*' || str[i] == '<' || str[i] == '=' || str[i] == ':')//essa condicao aqui eh pra quando tiver normal 1 + 2, para +1 2 tirar isso
                        {
                            Celula* aux_it_2 = it->filho_esq;
                            it->filho_esq = it->filho_dir;
                            it->filho_dir = aux_it_2;
                        }
                    }
                }
                else
                {
                    it_aux = it;

                    if(eh_digito(str[i]))
                    {
                        sscanf(str + i, "%d" ,&aux);
                        while(eh_digito(str[i])) i++;

                        it = cria_celula_derivacao(it_aux, cria_celula_folha_inteiro(aux, CHAR_NULL));
                        i--;
                    }
                    else
                    {
                        it = cria_celula_derivacao(it_aux, cria_celula_folha(str[i], CHAR_NULL));
                    }
                }
                break;
        }
    }
    return it;
}

void imprime_arvore(Celula* raiz)
{
    if(raiz->tipo == '@')
    {
        if(raiz->filho_esq != NULL)
            imprime_arvore(raiz->filho_esq);

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
    else if (raiz->tipo=='$')
    {
        printf("[");
        imprime_lista(raiz);

    }
    else
    {
        if(raiz->tipo == '#')
        {
            printf("%d", raiz->inteiro);
        }
        else
        {
            printf("%c", raiz->tipo);
        }

    }
}
void imprime_lista(Celula *raiz)
{
        if(raiz->tipo == '$')
    {

        if(raiz->filho_esq != NULL)
            imprime_lista(raiz->filho_esq);

        if(raiz->filho_dir != NULL)
        {
            imprime_lista(raiz->filho_dir);


        }
    }
    else if(raiz->tipo=='@')
    {
        imprime_arvore(raiz);
    }
    else
    {
        if(raiz->tipo == '#')
        {
            printf("%d ", raiz->inteiro);
        }
        else
        {
            printf("%c", raiz->tipo);
        }

    }

}
