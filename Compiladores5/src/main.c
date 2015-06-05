#include <stdio.h>
#include <stdlib.h>
#include "../include/arvore.h"
#include "../include/pilha.h"
#define TRUE 1
#define FALSE 0
#define N 50000000

int tamanho_heap;
/*
                        UNIVERSIDADE FEDERAL DE PERNAMBUCO
                              CENTRO DE INFORMATICA
                              COMPILADORES 2015.1
                              ARY GUEDES LINS
                        CAROLINA MARIA DE ALMEIDA BARBOSA
                              RAFAEL NUNES DE LIMA


K a b => a
S a b c => (ac)(bc)
I a => a
B f g x => f (gx)
C f x y => f y x
s a b c d => a (bd)(cd)
b a b c d => a b (c d)
c a b c d => a (b d) c

*/

Celula* mg_v1 (Celula* raiz) //MAQUINDA DE GRAFO SEM PILHA
{
    Celula* it;
    Celula* ant[] = {NULL, NULL, NULL, NULL};// VETOR PARA GUARDAR OS TRES NOS ANTERIORES QUANDO SE DESCE NO GRAFO
    int fim = FALSE;
    int i;
    int numero1;
    int numero2;
    int total;
    while (!fim)
    {
        for(it = raiz; it->filho_esq != NULL; it = it->filho_esq)
        {
            ant[3] = ant[2];
            ant[2] = ant[1];
            ant[1] = ant[0];
            ant[0] = it;
        } // faz a busca em profundidade

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
                raiz = ant[0]->filho_dir;
            }
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
                raiz = ant[1]->filho_dir;
            }
            break;
        case 'S':
            if(ant[2] == NULL)
            {
                fim = TRUE;
                break;
            }
            ant[1]->filho_esq = ant[0]->filho_dir;
            ant[0]->filho_esq = ant[1]->filho_dir;
            ant[0]->filho_dir = ant[2]->filho_dir;
            ant[2]->filho_dir = ant[0];
            ant[1]->filho_dir = ant[0]->filho_dir;
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
            ant[2]->filho_esq = ant[0]->filho_dir;
            ant[0]->filho_esq = ant[2]->filho_dir;
            ant[0]->filho_dir = ant[3]->filho_dir;
            ant[1]->filho_esq = ant[1]->filho_dir;
            ant[1]->filho_dir = ant[3]->filho_dir;
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
                raiz = ant[0]->filho_dir;
                raiz->filho_dir = NULL;
                raiz->filho_esq = NULL;
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
            if(it != pilha_topo(p) && it->tipo == '@' )
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
}

int main()
{
    char str[] = "(8/(8/2))";
    Celula* raiz = monta_arvore(str);

    raiz = mg_v1(raiz);
    imprime_arvore(raiz);
    return 0;
}
