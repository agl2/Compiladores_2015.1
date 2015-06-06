#include "pilha.h"

inline int pilha_vazia(Pilha* p) 
{
    if(p->ponteiro_posicao > -1) 
    {
        return 0;
    }
    else //ta vazia
    {
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
    if(p->ponteiro_posicao > -1) 
    {
        p->ponteiro_posicao--;
    }
}

inline TIPO pilha_topo(Pilha* p) 
{
    return p->dados[p->ponteiro_posicao];
}

inline void pilha_insere(Pilha* pl, TIPO elemento) 
{
    pl->ponteiro_posicao++;                     //move a posicao do topo da pilha
    pl->dados[pl->ponteiro_posicao] = elemento; //f
    if(pl->ponteiro_posicao + 1 == pl->tamanho) 
    {
        pl->tamanho += 100;
        pl->dados = (TIPO*) realloc((TIPO*)pl->dados, sizeof(TIPO)*pl->tamanho);
    }
}
//a estrutura pilha tem um ponteiro pro tipo celula, um ponteiro_posicao e o um tamanho 
inline Pilha* pilha_cria() //funcao basica para criar pilha
{
    Pilha* nova_pilha = (Pilha*) malloc(sizeof(Pilha)); //aloca espaço para uma nova estrutura pilha
    nova_pilha->tamanho = 500;                          //define o tamanho
    nova_pilha->ponteiro_posicao = -1;                  
    nova_pilha->dados = (TIPO*) malloc(sizeof(TIPO)*nova_pilha->tamanho); //aloca espaço para dados que é do: Celula** dados
    return nova_pilha;
}
