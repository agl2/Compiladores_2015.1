#include "../include/arvore.h"

void testa_celulas_livres (int num, Pilha* raizes) {

	Celula* it = lista_celulas_livres;
	int i;
    int rodou_gc = 0;
	for(i = 0; i < num; i++) {
		if(it == NULL) {
            if(rodou_gc == 1) {
                printf("Erro 1: Falta de celulas\n");
                exit(1);
            }
			if(mark_scan(raizes) == 0)
			{
			    printf("Erro 1: Falta de celulas\n");
			    exit(1);
			}
            rodou_gc = 1;
			it = lista_celulas_livres;
			i = 0;
		}
        it = it->prox;
	}
}

inline Celula* cria_celula()
{
    Celula* rt = (Celula*) malloc(sizeof(Celula));
    rt->tipo = CHAR_NULL;
    rt->inteiro = 0;
    rt->mem = AMARELO;
    rt->filho_esq = NULL;
    rt->filho_dir = NULL;
    return rt;
}

void marque_verde(Celula* raiz)
{
    raiz->mem = VERDE;
    if(raiz->filho_esq != NULL )
    {
        if(raiz->filho_esq->mem != VERDE) marque_verde(raiz->filho_esq);
    }
    if(raiz->filho_dir != NULL )
    {
        if(raiz->filho_dir->mem != VERDE) marque_verde(raiz->filho_dir);
    }
}

int mark_scan(Pilha* raizes)
{
    #ifdef estatisticas
    garbe++;
    #endif
    //printf("mark_scan\n");
    int i;
    int num_celulas_desalocadas = 0;
    Bloco* aux = raizes->cabeca;
    while(aux != NULL) {
        marque_verde(aux->dado);
        aux = aux->anterior;
    }
    Celula* prox = NULL;
    for(i = tam_heap - 1; i >= 0; i--)
    {

        if(heap[i]->mem == VERDE)
        {
            heap[i]->mem = VERMELHO;
        }
        else if(heap[i]->mem == VERMELHO)
        {
            num_celulas_desalocadas++;
            heap[i]->mem = AMARELO;
            lista_celulas_livres = heap[i];
            lista_celulas_livres->prox = prox;
            prox = lista_celulas_livres;
        }
    }
    return num_celulas_desalocadas;
}

inline Celula* aloca_celula()
{
    if(lista_celulas_livres == NULL)
    {
        printf("Erro 1: Falta de celulas\n");
        exit(1);
    }
    Celula* rt = lista_celulas_livres;
    if(rt->mem != AMARELO)
    {
        printf("Erro 2: Tentando alocar celula ja alocada\n");
        exit(2);
    }
    rt->mem = VERMELHO;
    lista_celulas_livres = lista_celulas_livres->prox;
    return rt;
}

inline void inicia_heap(int tamanho_heap)
{
    int i;
    Celula* prox = NULL;
    heap = (Celula**) malloc(tamanho_heap*sizeof(Celula*));
    tam_heap = tamanho_heap;
    for(i = tamanho_heap-1; i >= 0; i--)
    {
        heap[i] = cria_celula();
        lista_celulas_livres = heap[i];
        lista_celulas_livres->prox = prox;
        prox = lista_celulas_livres;
    }
}

inline Celula* cria_celula_folha(char tipo)
{
    Celula* rt = aloca_celula();
    rt->tipo = tipo;
    rt->inteiro = 0;
    rt->filho_esq = NULL;
    rt->filho_dir = NULL;
    return rt;
}
inline Celula* cria_celula_folha_inteiro(int num)
{
    Celula* rt = aloca_celula();
    rt->inteiro = num;
    rt->tipo = '#'; //tipo vai ser inteiro
    rt->filho_esq = NULL;
    rt->filho_dir = NULL;
    return rt;
}
inline Celula* cria_celula_derivacao(Celula* filho_esq, Celula* filho_dir)
{
    Celula* rt = aloca_celula();
    rt->tipo = '@';
    rt->filho_esq = filho_esq;
    rt->filho_dir = filho_dir;
    return rt;
}
inline Celula* cria_celula_lista()
{
    Celula* rt = aloca_celula();
    rt->inteiro = 0;
    rt->tipo = '$'; //tipo vai ser inteiro
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
    rt = (char*) malloc(sizeof(char)*(n + 2));
    strncpy(rt, str + inicial, n + 2);
    rt[n + 1] = CHAR_NULL;
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
        if(str[*i] == ')')
        {
            nivel_parenteses--;
        }
        else if(str[*i] == '(')
        {
            nivel_parenteses++;
        }
    }
    n = *i - inicial;
    rt = (char*) malloc(sizeof(char)*n);
    strncpy(rt, str+inicial + 1, n);
    rt[n-1] = CHAR_NULL;
    return rt;
}

Celula* copia_arvore(Celula* original)
{
    Celula* copia;
    if(original->tipo == '@')
    {
        copia = cria_celula_derivacao(NULL, NULL);
        if(original->filho_esq != NULL)
        {
            copia->filho_esq = copia_arvore(original->filho_esq);
        }
        if(original->filho_dir != NULL)
        {
            copia->filho_dir = copia_arvore(original->filho_dir);
        }
    }
    else if (original->tipo == '$')
    {
        copia = cria_celula_lista();
        if(original->filho_esq != NULL)
        {
            copia->filho_esq = copia_arvore(original->filho_esq);
        }
        if(original->filho_dir != NULL)
        {
            copia->filho_dir = copia_arvore(original->filho_dir);
        }
    }
    else
    {
        if(original->tipo == '#')
        {
            copia = cria_celula_folha_inteiro(original->inteiro);
        }
        else
        {
            copia = cria_celula_folha(original->tipo);
        }
    }
    return copia;
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

                        if(isdigit(str[i]))
                        {
                            int inteiroAux;
                            sscanf(str+i, "%d" ,&inteiroAux);
                            it->filho_dir->filho_esq = cria_celula_folha_inteiro(inteiroAux);
                            while(isdigit(str[i])) i++;
                            i--;
                        }
                        else
                        {
                            it->filho_dir->filho_esq = cria_celula_folha(str[i]);
                        }
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
                it->filho_dir = cria_celula_folha(']');
            }
            else
            {
                Celula* aux2 = cria_celula_derivacao(it, NULL);
                it_aux = aux2;
                i--;
            }
            it = it_aux;
            break;
        ///TERMINA A BAGUNCA
        default:
            if(it->filho_esq == NULL)
            {
                if(isdigit(str[i]))
                {
                    sscanf(str + i, "%d" ,&aux);
                    while(isdigit(str[i])) i++;

                    it->filho_esq = cria_celula_folha_inteiro(aux);
                    i--;
                }
                else
                {
                    it->filho_esq = cria_celula_folha(str[i]);
                }
            }
            else if (it->filho_dir == NULL)
            {
                if(isdigit(str[i]))
                {
                    sscanf(str + i, "%d" ,&aux);
                    while(isdigit(str[i])) i++;

                    it->filho_dir = cria_celula_folha_inteiro(aux);
                    if(str[i] != ' ')
                    {
                        i--;
                    }
                }
                else
                {
                    it->filho_dir = cria_celula_folha(str[i]);
                }
            }
            else
            {
                it_aux = it;

                if(isdigit(str[i]))
                {
                    sscanf(str + i, "%d" ,&aux);
                    while(isdigit(str[i])) i++;

                    it = cria_celula_derivacao(it_aux, cria_celula_folha_inteiro(aux));
                    if(str[i] != ' ')
                    {
                        i--;
                    }

                }
                else
                {
                    it = cria_celula_derivacao( it_aux, cria_celula_folha(str[i]) ) ;
                }
            }
            break;
        }
    }
    return it;
}

void imprime_lista(Celula *raiz)
{
    if(raiz->tipo == '$')
    {
        if(raiz->filho_esq != NULL)
            imprime_lista(raiz->filho_esq);
        if(raiz->filho_dir != NULL)
            imprime_lista(raiz->filho_dir);
    }
    else if(raiz->tipo=='@')
        imprime_arvore(raiz);
    else
    {
        if(raiz->tipo == '#')
            printf("%d ", raiz->inteiro);
        else
            printf("%c", raiz->tipo);
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
    else if (raiz->tipo=='$')
    {
        printf("[");
        imprime_lista(raiz);

    }
    else
    {
        if(raiz->tipo == '#')
            printf("%d", raiz->inteiro);
        else
            printf("%c", raiz->tipo);
    }
}
