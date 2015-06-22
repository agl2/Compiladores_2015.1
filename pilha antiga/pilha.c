#include "pilha.h"

inline int pilha_vazia(Pilha* p) {
    if(p->ponteiro_posicao > -1) {
        return 0;
    }
    else {
        return 1;
    }
}

inline void pilha_destroi(Pilha* p)
{
    free(p->dados);
    free(p);
}

inline void pilha_retira(Pilha* p)
{
    if(p->ponteiro_posicao > -1) {
        p->ponteiro_posicao--;
    }
}

inline TIPO pilha_topo(Pilha* p) {
    return p->dados[p->ponteiro_posicao];
}

inline void pilha_insere(Pilha* pl, TIPO elemento)
{
    pl->ponteiro_posicao++;
    pl->dados[pl->ponteiro_posicao] = elemento;
    if(pl->ponteiro_posicao + 1 == pl->tamanho)
    {
        pl->tamanho += 10;
        pl->dados = (TIPO*) realloc((TIPO*)pl->dados, sizeof(TIPO)*pl->tamanho);
    }
}

inline Pilha* pilha_cria()
{
    Pilha* nova_pilha = (Pilha*) malloc(sizeof(Pilha));
    nova_pilha->tamanho = 20;
    nova_pilha->ponteiro_posicao = -1;
    nova_pilha->dados = (TIPO*) malloc(sizeof(TIPO)*nova_pilha->tamanho);
    return nova_pilha;
}
