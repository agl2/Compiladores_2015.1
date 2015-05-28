#include "arvore.h"
#define CHAR_NULL '\0'

inline Celula* cria_celula_folha(char tipo, char mem) {
    Celula* rt = (Celula*) malloc(sizeof(Celula));
    rt->tipo = tipo;
    rt->mem = mem;
    rt->filho_esq = NULL;
    rt->filho_dir = NULL;
    return rt;
}

inline Celula* cria_celula_derivacao(Celula* filho_esq, Celula* filho_dir) {
    Celula* rt = (Celula*) malloc(sizeof(Celula));
    rt->tipo = '@';
    rt->mem = CHAR_NULL;
    rt->filho_esq = filho_esq;
    rt->filho_dir = filho_dir;
    return rt;
}

inline char* captura_string(char* str, int* i) {
    int nivel_parenteses = 0;
    char* rt;
    int inicial = *i;
    int n;
    if(str[*i] == '(') {
        nivel_parenteses++;
    }
    while(nivel_parenteses != 0) {
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


Celula* monta_arvore(char* str) {

    int i;
    char* str_aux;
    Celula* it_aux = NULL;
    Celula* it = cria_celula_derivacao(NULL, NULL);

    for(i = 0; str[i]!= CHAR_NULL; i++)
    {
        switch(str[i])
        {
            case '(' :
                str_aux = captura_string(str, &i);
                if(it->filho_esq == NULL) {
                    it->filho_esq = monta_arvore(str_aux);
                }
                else if (it->filho_dir == NULL) {
                    it->filho_dir = monta_arvore(str_aux);
                }
                else {
                    it_aux = it;
                    it = cria_celula_derivacao(it_aux, monta_arvore(str_aux));
                }
                free(str_aux);
                break;
            default:
                if(it->filho_esq == NULL) {
                    it->filho_esq = cria_celula_folha(str[i],CHAR_NULL);
                }
                else if (it->filho_dir == NULL) {
                    it->filho_dir = cria_celula_folha(str[i],CHAR_NULL);
                }
                else {
                    it_aux = it;
                    it = cria_celula_derivacao(it_aux, cria_celula_folha(str[i], CHAR_NULL));
                }
                break;
        }
    }
    return it;
}

void imprime_arvore(Celula* raiz) {
    if(raiz->tipo == '@') {
        if(raiz->filho_esq != NULL)
            imprime_arvore(raiz->filho_esq);

        if(raiz->filho_dir != NULL) {
            if(raiz->filho_dir->tipo == '@')
                printf("(");
            imprime_arvore(raiz->filho_dir);
            if(raiz->filho_dir->tipo == '@')
                printf(")");
        }
    }
    else {
        printf("%c", raiz->tipo);
    }
}
