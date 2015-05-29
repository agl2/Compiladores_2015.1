#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "pilha.h"
#define TRUE 1
#define FALSE 0
#define N 50000000

int tamanho_heap;

void mg_v1 (Celula* raiz) {
    Celula* it;
    Celula* ant[] = {NULL, NULL, NULL, NULL};
    int fim = FALSE;
    int i;
   while (!fim) {
        for(it = raiz; it->filho_esq != NULL; it = it->filho_esq) {
           ant[3] = ant[2];
            ant[2] = ant[1];
            ant[1] = ant[0];
          ant[0] = it;
        }

        switch(it->tipo) {
            case 'K':
                if(ant[1] == NULL) {
                    fim = TRUE;
                    break;
                }
                if(ant[1] != raiz) {
                    ant[2]->filho_esq = ant[0]->filho_dir;
                }
                else {
                    ant[1]->filho_esq = ant[0]->filho_dir;
                    ant[1]->filho_dir = NULL;
                }

            break;
            case 'S':
                if(ant[2] == NULL) {
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
                if(ant[0] == NULL) {
                    fim = TRUE;
                    break;
                }
                if(ant[0] != raiz) {
                    ant[1]->filho_esq = ant[0]->filho_dir;
                }
                else {
                    raiz = raiz->filho_dir;
                }
            break;
            case 'B':
                if(ant[2] == NULL) {
                    fim = TRUE;
                    break;
                }
                ant[1]->filho_esq = ant[1]->filho_dir;
                ant[1]->filho_dir = ant[2]->filho_dir;
                ant[2]->filho_dir = ant[1];
                ant[2]->filho_esq = ant[0]->filho_dir;
            break;
            case 'C':
                if(ant[2] == NULL) {
                    fim = TRUE;
                    break;
                }
                it = ant[1]->filho_dir;
                ant[1]->filho_dir = ant[2]->filho_dir;
                ant[2]->filho_dir = it;
                ant[1]->filho_esq = ant[0]->filho_dir;
            break;
            case 's':
                if(ant[3] == NULL) {
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
                if(ant[3] == NULL) {
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
                if(ant[3] == NULL) {
                    fim = TRUE;
                    break;
                }
                ant[2]->filho_esq = ant[0]->filho_dir;
                ant[1]->filho_esq = ant[1]->filho_dir;
                ant[1]->filho_dir = ant[3]->filho_dir;
                ant[3]->filho_dir = ant[2]->filho_dir;
                ant[2]->filho_dir = ant[1];
            break;
            default:
                fim = TRUE;
                break;
        }

        for(i = 0; i < 4; i++) {
            ant[i] = NULL;
        }
    }
}

void mg_v2(Celula* raiz) {


    Celula* it;
    Celula* ant[] = {NULL, NULL, NULL, NULL};
    int fim = FALSE;
    int i;

    Pilha* p = pilha_cria();
    pilha_insere(p, raiz);
   while (!fim) {
        for(it = pilha_topo(p); it->filho_esq != NULL; it = it->filho_esq) {
            if(it != pilha_topo(p) && it->tipo == '@' ) pilha_insere(p, it);
        }

        switch(it->tipo) {
            case 'K':
                for(i=0; i < 2; i++) {
                    if(!pilha_vazia(p)) {
                        ant[i] = pilha_topo(p);
                        if(i!=1)pilha_retira(p);
                    }
                    else {
                        fim = TRUE;
                    }
                }
                if(fim) break;

                if(ant[1] != raiz) {
                    if(pilha_vazia(p)) {
                        fim = TRUE;
                        break;
                    }
                    pilha_retira(p);
                    ant[2] = pilha_topo(p);
                    ant[2]->filho_esq = ant[0]->filho_dir;
                }
                else {
                    ant[1]->filho_esq = ant[0]->filho_dir;
                    ant[1]->filho_dir = NULL;
                }

            break;
            case 'S':
                for(i=0; i < 3; i++) {
                    if(!pilha_vazia(p)) {
                        ant[i] = pilha_topo(p);
                        if(i!=2)pilha_retira(p);
                    }
                    else {
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
                if(pilha_vazia(p)) {
                    fim = TRUE;
                    break;
                }
                ant[0] = pilha_topo(p);
                if(ant[0] != raiz) {
                    if(pilha_vazia(p)) {
                        fim = TRUE;
                        break;
                    }
                    ant[1] = pilha_topo(p);

                    ant[1]->filho_esq = ant[0]->filho_dir;
                }
                else {
                    raiz = raiz->filho_dir;
                }
            break;
            case 'B':
                for(i=0; i < 3; i++) {
                    if(!pilha_vazia(p)) {
                        ant[i] = pilha_topo(p);
                         if(i!=2)pilha_retira(p);
                    }
                    else {
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
                for(i=0; i < 3; i++) {
                    if(!pilha_vazia(p)) {
                        ant[i] = pilha_topo(p);
                        if(i!=2)pilha_retira(p);
                    }
                    else {
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
                for(i=0; i < 4; i++) {
                    if(!pilha_vazia(p)) {
                        ant[i] = pilha_topo(p);
                        if(i!=3)pilha_retira(p);
                    }
                    else {
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
                for(i=0; i < 4; i++) {
                    if(!pilha_vazia(p)) {
                        ant[i] = pilha_topo(p);
                        if(i!=3)pilha_retira(p);
                    }
                    else {
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
                for(i=0; i < 4; i++) {
                    if(!pilha_vazia(p)) {
                        ant[i] = pilha_topo(p);
                        if(i!=3)pilha_retira(p);
                    }
                    else {
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
            default:
                fim = TRUE;
                break;
        }

        for(i = 0; i < 4; i++) {
            ant[i] = NULL;
        }
    }
}

int main()
{
   // FILE* entrada = fopen("entrada.txt", "r");
    //char str[N];
   char str[] = "s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)(KK))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K)";

    Celula* raiz = monta_arvore(str);
    mg_v2(raiz);
    imprime_arvore(raiz);
    return 0;
}
