#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <ctype.h>
#include <math.h>
#include "pilha.h"
#define TRUE 1
#define FALSE 0
#define N 50000000

int tamanho_heap = 11;
/*
                        UNIVERSIDADE FEDERAL DE PERNAMBUCO
                              CENTRO DE INFORMATICA
                              COMPILADORES 2015.1
                              ARY GUEDES LINS
                        CAROLINA MARIA DE ALMEIDA BARBOSA
                              RAFAEL NUNES DE LIMA


K a b => a ok
S a b c => (ac)(bc) ok
I a => a ok
B f g x => f (gx) ok
C f x y => f y x ok
s a b c d => a (bd)(cd)
b a b c d => a b (c d) ok
c a b c d => a (b d) c ok
Y x => x (Y x) ok
*/

Celula* mg_v1 (Celula* raiz) //MAQUINDA DE GRAFO SEM PILHA
{
    Celula* it;
    Celula* ant[] = {NULL, NULL, NULL, NULL};// VETOR PARA GUARDAR OS TRES NOS ANTERIORES QUANDO SE DESCE NO GRAFO
    int fim = FALSE;
    int i;
    Celula* copia;
    Celula* aux;

    while (!fim)
    {
        for(it = raiz; it->filho_esq != NULL; it = it->filho_esq)
        {
            ant[3] = ant[2];
            ant[2] = ant[1];
            ant[1] = ant[0];
            ant[0] = it;
        } // faz a busca em profundidade
        ///AQUI SERVE PRA ENTRAR NA LISTA
        aux = raiz;
        for(;aux->filho_esq == NULL && raiz->filho_dir != NULL;)
        {
            if(raiz->filho_dir->tipo == '$')
            {
                raiz->filho_dir->filho_esq = mg_v1(raiz->filho_dir->filho_esq);
            }
            checa_raiz(raiz, raiz->filho_dir);
            raiz = raiz->filho_dir;
        }
        checa_raiz(raiz, aux);
        raiz = aux;
        ///------------------------------------
        switch(it->tipo)
        {
        case 'K':
            if(ant[1] == NULL)  // encontrou um K (Sair do la?o)
            {
                fim = TRUE;
                break;
            }
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
            }
            break;
        case 'Y':
            if(ant[0] == NULL)  // encontrou um K (Sair do la?o)
            {
                fim = TRUE;
                break;
            }
            copia = copia_arvore(ant[0]->filho_dir); //criar copia de ant[0]->filho_dir
            Celula* nova = cria_celula_derivacao(ant[0]->filho_esq, copia);
            ant[0]->filho_esq = ant[0]->filho_dir;
            ant[0]->filho_dir = nova;
        break;
        case 'F':
            if(ant[1] == NULL)  // encontrou um K (Sair do la?o)
            {
                fim = TRUE;
                break;
            }
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2]->filho_esq = ant[1]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[1]->filho_dir);
                raiz = ant[1]->filho_dir;
            }
            break;
        case 'S':

            if(ant[2] == NULL)
            {
                fim = TRUE;
                break;
            }
            copia = copia_arvore(ant[2]->filho_dir);
            ant[1]->filho_esq = ant[0]->filho_dir;
            ant[0]->filho_esq = ant[1]->filho_dir;
            ant[0]->filho_dir = ant[2]->filho_dir;
            ant[2]->filho_dir = ant[0];
            ant[1]->filho_dir = copia;
            break;

        case 'I':
            if(ant[0] == NULL)
            {
                fim = TRUE;
                break;
            }
            if(ant[0] != raiz)
            {
                ant[1]->filho_esq = ant[0]->filho_dir;
            }
            else
            {
                checa_raiz(raiz, raiz->filho_dir);
                raiz = raiz->filho_dir;
            }
            break;
        case 'B':
            if(ant[2] == NULL)
            {
                fim = TRUE;
                break;
            }
            ant[1]->filho_esq = ant[1]->filho_dir;
            ant[1]->filho_dir = ant[2]->filho_dir;
            ant[2]->filho_dir = ant[1];
            ant[2]->filho_esq = ant[0]->filho_dir;

            break;
        case 'C':
            if(ant[2] == NULL)
            {
                fim = TRUE;
                break;
            }
            it = ant[1]->filho_dir;
            ant[1]->filho_dir = ant[2]->filho_dir;
            ant[2]->filho_dir = it;
            ant[1]->filho_esq = ant[0]->filho_dir;
            break;
        case 's':
            if(ant[3] == NULL)
            {
                fim = TRUE;
                break;
            }
            //s a b c d => a (bd)(cd)
            copia = copia_arvore(ant[3]->filho_dir);
            ant[2]->filho_esq = ant[0]->filho_dir;
            ant[0]->filho_esq = ant[2]->filho_dir;
            ant[0]->filho_dir = ant[3]->filho_dir;
            ant[1]->filho_esq = ant[1]->filho_dir;
            ant[1]->filho_dir = copia;
            ant[3]->filho_dir = ant[0];
            ant[2]->filho_dir = ant[1];
            break;
        case 'b':
            if(ant[3] == NULL)
            {
                fim = TRUE;
                break;
            }
            ant[1]->filho_esq = ant[0]->filho_dir;
            ant[2]->filho_esq = ant[2]->filho_dir;
            ant[2]->filho_dir = ant[3]->filho_dir;
            ant[3]->filho_esq = ant[1];
            ant[3]->filho_dir = ant[2];
            break;
        case 'c':
            if(ant[3] == NULL)
            {
                fim = TRUE;
                break;
            }
            ant[2]->filho_esq = ant[0]->filho_dir;
            ant[1]->filho_esq = ant[1]->filho_dir;
            ant[1]->filho_dir = ant[3]->filho_dir;
            ant[3]->filho_dir = ant[2]->filho_dir;
            ant[2]->filho_dir = ant[1];
            break;
        case '+':
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v1(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = ant[0]->filho_dir->inteiro + ant[1]->filho_dir->inteiro;

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
            }
        break;
        case '-':
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v1(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = ant[0]->filho_dir->inteiro - ant[1]->filho_dir->inteiro;

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
            }
        break;
        case '/':
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v1(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = ant[0]->filho_dir->inteiro/ant[1]->filho_dir->inteiro;

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
            }
        break;
        case '^':
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v1(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = pow(ant[0]->filho_dir->inteiro, ant[1]->filho_dir->inteiro); //mudar isso depois

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
            }
        break;
        case '*':
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v1(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = ant[0]->filho_dir->inteiro*ant[1]->filho_dir->inteiro; //mudar isso depois

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
            }
        break;
        case '<':
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v1(ant[1]->filho_dir);
            }
            if(ant[0]->filho_dir->inteiro < ant[1]->filho_dir->inteiro)
            {
                ant[0]->filho_dir->tipo = 'K'; //true escolhe o primeiro mais perto Kab = a
            }
            else
            {
                ant[0]->filho_dir->tipo = 'F'; //false escolhe o segundo
            }
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
            }
        break;
        case '=':
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v1(ant[1]->filho_dir);
            }
            if(ant[0]->filho_dir->inteiro == ant[1]->filho_dir->inteiro)
            {
                ant[0]->filho_dir->tipo = 'K'; //true escolhe o primeiro mais perto Kab = a
            }
            else
            {
                ant[0]->filho_dir->tipo = 'F'; //false escolhe o segundo
            }
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
            }
            break;
        case 'H':
            if(ant[0] == NULL)
            {
                fim = TRUE;
                break;
            }
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[0] != raiz)
            {
                ant[1]->filho_esq = ant[0]->filho_dir->filho_esq;
            }
            else
            {
                checa_raiz(raiz, raiz->filho_dir->filho_esq);
                raiz = raiz->filho_dir->filho_esq;
            }
            break;
        case 'T':
            if(ant[0] == NULL)
            {
                fim = TRUE;
                break;
            }
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[0] != raiz)
            {
                ant[1]->filho_esq = ant[0]->filho_dir->filho_dir;
            }
            else
            {
                checa_raiz(raiz, raiz->filho_dir->filho_esq);
                raiz = raiz->filho_dir->filho_dir;
            }
            break;
        case ':':
            if(ant[1] == NULL)
            {
                fim = TRUE;
                break;
            }
            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v1(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo == '@')
            {
                ant[1]->filho_dir = mg_v1(ant[1]->filho_dir);
            }
            ant[0]->tipo = '$';
            ant[0]->filho_esq = ant[0]->filho_dir;
            ant[0]->filho_dir = ant[1]->filho_dir;

            if(ant[1] != raiz)
            {
                ant[2]->filho_esq = ant[0];
            }
            else
            {
                checa_raiz(raiz, ant[0]);
                raiz = ant[0];
            }
            break;
        default:
            fim = TRUE;
            break;
        }

        for(i = 0; i < 4; i++)
        {
            ant[i] = NULL;
        }

    }

    return raiz;
}

Celula* mg_v2(Celula* raiz)// MAQUINA DE GRAFO COM PILHA
{

    Celula* it;
    Celula* ant[] = {NULL, NULL, NULL, NULL};
    int fim = FALSE;
    int i;

    Pilha* p = pilha_cria();
    pilha_insere(p, raiz);
    while (!fim)
    {
        for(it = pilha_topo(p); it->filho_esq != NULL; it = it->filho_esq) //
        {
            if(it != pilha_topo(p) && (it->tipo == '@' || it->tipo == '#'))
            {
                pilha_insere(p, it);
            }
        }

        switch(it->tipo)
        {
        case 'K':
            for(i=0; i < 2; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i!=1) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            if(ant[1] != raiz)
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }

                pilha_retira(p);
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else
            {
                ant[1]->filho_esq = ant[0]->filho_dir;
                ant[1]->filho_dir = NULL;
            }

            break;
        case 'F':
            for(i=0; i < 2; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i!=1) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            if(ant[1] != raiz)
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }

                pilha_retira(p);
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[1]->filho_dir;
            }
            else
            {
                ant[1]->filho_esq = ant[1]->filho_dir;
                ant[1]->filho_dir = NULL;
            }

            break;
        case 'S':
            for(i=0; i < 3; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i!=2) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            ant[1]->filho_esq = ant[0]->filho_dir;
            ant[0]->filho_esq = ant[1]->filho_dir;
            ant[0]->filho_dir = ant[2]->filho_dir;
            ant[2]->filho_dir = ant[0];
            ant[1]->filho_dir = ant[0]->filho_dir;
            break;
        case 'I':
            if(pilha_vazia(p))
            {
                fim = TRUE;
                break;
            }
            ant[0] = pilha_topo(p);
            if(ant[0] != raiz)
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }
                pilha_retira(p);
                ant[1] = pilha_topo(p);
                ant[1]->filho_esq = ant[0]->filho_dir;
            }
            else
            {
                ant[0]->filho_esq = ant[0]->filho_dir;
                ant[0]->filho_dir = NULL;
            }
            break;
        case 'B':
            for(i=0; i < 3; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i!=2)pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            ant[1]->filho_esq = ant[1]->filho_dir;
            ant[1]->filho_dir = ant[2]->filho_dir;
            ant[2]->filho_dir = ant[1];
            ant[2]->filho_esq = ant[0]->filho_dir;
            break;
        case 'C':
            for(i=0; i < 3; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i!=2)pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            it = ant[1]->filho_dir;
            ant[1]->filho_dir = ant[2]->filho_dir;
            ant[2]->filho_dir = it;
            ant[1]->filho_esq = ant[0]->filho_dir;
            break;
        case 's':
            for(i=0; i < 4; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i!=3) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            ant[2]->filho_esq = ant[0]->filho_dir;
            ant[0]->filho_esq = ant[2]->filho_dir;
            ant[0]->filho_dir = ant[3]->filho_dir;
            ant[1]->filho_esq = ant[1]->filho_dir;
            ant[1]->filho_dir = ant[3]->filho_dir;
            ant[3]->filho_dir = ant[0];
            ant[2]->filho_dir = ant[1];
            break;
        case 'b':
            for(i=0; i < 4; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i!=3)pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            ant[1]->filho_esq = ant[0]->filho_dir;
            ant[2]->filho_esq = ant[2]->filho_dir;
            ant[2]->filho_dir = ant[3]->filho_dir;
            ant[3]->filho_esq = ant[1];
            ant[3]->filho_dir = ant[2];
            break;
        case 'c':
            for(i=0; i < 4; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i!=3)pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;
            ant[2]->filho_esq = ant[0]->filho_dir;
            ant[1]->filho_esq = ant[1]->filho_dir;
            ant[1]->filho_dir = ant[3]->filho_dir;
            ant[3]->filho_dir = ant[2]->filho_dir;
            ant[2]->filho_dir = ant[1];
            break;
        case '+':
            for(i = 0; i < 2; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i != 1) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v2(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = ant[0]->filho_dir->inteiro + ant[1]->filho_dir->inteiro;
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }
                pilha_retira(p);
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
                fim = TRUE; ///nao sei pq precisa disso, mas sei q só funciona com isso
            }
            break;
        case '-':
            for(i = 0; i < 2; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i != 1) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v2(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = ant[0]->filho_dir->inteiro - ant[1]->filho_dir->inteiro;
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }
                pilha_retira(p);
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
                fim = TRUE; ///nao sei pq precisa disso, mas sei q só funciona com isso
            }
            break;
        case '*':
            for(i = 0; i < 2; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i != 1) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v2(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = ant[0]->filho_dir->inteiro*ant[1]->filho_dir->inteiro;
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }
                pilha_retira(p);
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
                fim = TRUE; ///nao sei pq precisa disso, mas sei q só funciona com isso
            }
            break;
        case '/':
            for(i = 0; i < 2; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i != 1) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v2(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = ant[0]->filho_dir->inteiro/ant[1]->filho_dir->inteiro;
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }
                pilha_retira(p);
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
                fim = TRUE; ///nao sei pq precisa disso, mas sei q só funciona com isso
            }
            break;
        case '^':
            for(i = 0; i < 2; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i != 1) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v2(ant[1]->filho_dir);
            }
            ant[0]->filho_dir->inteiro = pow(ant[0]->filho_dir->inteiro,ant[1]->filho_dir->inteiro);
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }
                pilha_retira(p);
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
                fim = TRUE; ///nao sei pq precisa disso, mas sei q só funciona com isso
            }
            break;
        case '<':
            for(i = 0; i < 2; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i != 1) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v2(ant[1]->filho_dir);
            }
            if(ant[0]->filho_dir->inteiro < ant[1]->filho_dir->inteiro)
            {
                ant[0]->filho_dir->tipo = 'K'; //true escolhe o primeiro mais perto Kab = a
            }
            else
            {
                ant[0]->filho_dir->tipo = 'F'; //false escolhe o segundo
            }
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }
                pilha_retira(p);
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
                fim = TRUE; ///nao sei pq precisa disso, mas sei q só funciona com isso
            }
            break;
        case '=':
            for(i = 0; i < 2; i++)
            {
                if(!pilha_vazia(p))
                {
                    ant[i] = pilha_topo(p);
                    if(i != 1) pilha_retira(p);
                }
                else
                {
                    fim = TRUE;
                }
            }
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo =='@')
            {
                ant[1]->filho_dir = mg_v2(ant[1]->filho_dir);
            }
            if(ant[0]->filho_dir->inteiro == ant[1]->filho_dir->inteiro)
            {
                ant[0]->filho_dir->tipo = 'K'; //true escolhe o primeiro mais perto Kab = a
            }
            else
            {
                ant[0]->filho_dir->tipo = 'F'; //false escolhe o segundo
            }
            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                if(pilha_vazia(p))
                {
                    fim = TRUE;
                    break;
                }
                pilha_retira(p);
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else //Aplica a regra e reduz a Ka
            {
                checa_raiz(raiz, ant[0]->filho_dir);
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
                fim = TRUE; ///nao sei pq precisa disso, mas sei q só funciona com isso
            }
            break;
        default:
            fim = TRUE;
            break;
        }

        for(i = 0; i < 4; i++)
        {
            ant[i] = NULL;
        }
    }

    return raiz;
}

int main()
{
    char str[] = "K(Sabc)f";
    inicia_heap(tamanho_heap);
    Celula* raiz = monta_arvore(str);
    inicia_mark_scan(raiz, tamanho_heap);
    raiz = mg_v1(raiz);
    imprime_arvore(raiz);
    printf("\n");
    return 0;
}
