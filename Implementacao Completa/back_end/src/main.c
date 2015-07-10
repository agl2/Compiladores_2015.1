#include <stdio.h>
#include <stdlib.h>
#include "../include/celula.h"
#include "../include/arvore.h"
#include <ctype.h>
#include <math.h>
#include "../include/pilha.h"
#define TRUE 1
#define FALSE 0



Pilha* raizes;
int tamanho_heap = 1000000;
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

int ehdiferente = 1;

void transforma_lista(Celula *raiz, Celula *raiz2)
{

    if(raiz->tipo == '$')
    {
        if(raiz->filho_esq != NULL && raiz2->filho_esq != NULL)
            transforma_lista(raiz->filho_esq, raiz2->filho_esq);
        else
            ehdiferente = 0;
        if(raiz->filho_dir != NULL && raiz2->filho_dir != NULL)
            transforma_lista(raiz->filho_dir, raiz2->filho_dir);
        else
            ehdiferente = 0;
    }
    else
    {
        if(raiz->tipo == '#'&& raiz2->tipo == '#')
        {
            if(raiz->inteiro == raiz2->inteiro);
            else ehdiferente = 0;
        }
        else 
        {
            if(raiz2->tipo == raiz->tipo);
            else ehdiferente = 0;
        }
            
    }
}

Celula* mg_v2(Celula* raiz)// MAQUINA DE GRAFO COM PILHA
{
    pilha_insere(raizes, raiz);

    Celula* it;
    Celula* ant[] = {NULL, NULL, NULL, NULL, NULL};
    int fim = FALSE;
    int i;
    Celula* aux;
    Celula* aux2;
    Celula* aux3;
    Celula* aux4;
    Pilha* p = pilha_cria();
    pilha_insere(p, raiz);

    while (!fim)
    {

        for(it = pilha_topo(p); it->filho_esq != NULL; it = it->filho_esq) //
        {
            if(it != pilha_topo(p) && it->tipo == '@')
            {
                pilha_insere(p, it);
            }
        }

        aux = raiz;
        for(; aux->filho_esq == NULL && raiz->filho_dir != NULL;)
        {
            if(raiz->filho_dir->tipo == '$')
            {
                raiz->filho_dir->filho_esq = mg_v2(raiz->filho_dir->filho_esq);
            }
            
            pilha_retira(raizes);
            raiz = raiz->filho_dir;
            pilha_insere(raizes, raiz);
        }
        pilha_retira(raizes);
        raiz = aux;
        pilha_insere(raizes, raiz);
       
       // printf("%c\n", it->tipo);
        switch(it->tipo)
        {
        case 'K':
         #ifdef estatisticas
         redK++;
         #endif
            for(i=0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
            }
            if(fim) break;

            if(ant[1] != raiz)
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[0]->filho_dir;
            }
            else
            {
                pilha_retira(raizes);
                raiz = ant[0]->filho_dir;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            break;
        case 'F':
         #ifdef estatisticas
         redF++;
         #endif
            for(i = 0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
            }
            if(fim) break;

            if(ant[1] != raiz)
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = ant[1]->filho_dir;
            }
            else
            {
                pilha_retira(raizes);
                raiz = ant[1]->filho_dir;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            break;
        case 'S':
         #ifdef estatisticas
         redS++;
         #endif
            for(i=0; i < 3; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
            }
            if(fim) break;

            testa_celulas_livres(3, raizes);
            aux = cria_celula_derivacao(ant[0]->filho_dir, ant[2]->filho_dir);
            aux2 = cria_celula_derivacao(ant[1]->filho_dir, ant[2]->filho_dir);
            aux3 = cria_celula_derivacao(aux, aux2);

            if(ant[2] == raiz)
            {
                pilha_retira(raizes);
                raiz = aux3;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            else
            {
                ant[3] = pilha_topo(p);
                ant[3]->filho_esq = aux3;
            }
            break;
        case 'I':
         #ifdef estatisticas
         redI++;
         #endif
            ant[0] = pilha_topo(p);
            pilha_retira(p);

            if(ant[0]->filho_dir == NULL) fim = TRUE;
            if(fim) break;

            if(ant[0] != raiz)
            {
                ant[1] = pilha_topo(p);
                ant[1]->filho_esq = ant[0]->filho_dir;
            }
            else
            {
                pilha_retira(raizes);
                raiz = ant[0]->filho_dir;
                pilha_insere(raizes, raiz);       
                pilha_insere(p, raiz);
            }
            break;
        case 'Y':
         #ifdef estatisticas
         redY++;
         #endif
            ant[0] = pilha_topo(p);
            pilha_retira(p);

            if(ant[0]->filho_dir == NULL) fim = TRUE;
            if(fim) break;


            testa_celulas_livres(2, raizes);
            aux2 = cria_celula_derivacao(ant[0]->filho_esq, ant[0]->filho_dir);
            aux = cria_celula_derivacao(ant[0]->filho_dir, aux2);

            if(ant[0] == raiz)
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz);
                pilha_insere(p,raiz);
            }
            else
            {
                ant[1] = pilha_topo(p);
                ant[1]->filho_esq = aux;
            }
            break;

        case 'B':
         #ifdef estatisticas
         redB++;
         #endif
            for(i=0; i < 3; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
            }
            if(fim) break;

            testa_celulas_livres (2, raizes);
            aux = cria_celula_derivacao(ant[1]->filho_dir,ant[2]->filho_dir);
            aux2 = cria_celula_derivacao(ant[0]->filho_dir, aux);

            if(ant[2] == raiz)
            {
                pilha_retira(raizes);
                raiz = aux2;
                pilha_insere(raizes, raiz);
                pilha_insere(p,raiz);
            }
            else
            {
                ant[3] = pilha_topo(p);
                ant[3]->filho_esq = aux2;
            }
            break;
        case 'C':
         #ifdef estatisticas
         redC++;
         #endif
            for(i=0; i < 3; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
            }
            if(fim) break;


            testa_celulas_livres (2, raizes);
            aux2 = cria_celula_derivacao(ant[0]->filho_dir, ant[2]->filho_dir);
            aux = cria_celula_derivacao(aux2, ant[1]->filho_dir);

            if(ant[2] == raiz)
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz);
                pilha_insere(p,raiz);
            }
            else
            {
                ant[3] = pilha_topo(p);
                ant[3]->filho_esq = aux;
            }
            break;
        case 's':
         #ifdef estatisticas
         reds++;
         #endif
            for(i=0; i < 4; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
            }
            if(fim) break;


            testa_celulas_livres (4, raizes);
            aux = cria_celula_derivacao(ant[1]->filho_dir,ant[3]->filho_dir);
            aux2 = cria_celula_derivacao(ant[0]->filho_dir,aux);
            aux3 = cria_celula_derivacao(ant[2]->filho_dir,ant[3]->filho_dir);
            aux4 = cria_celula_derivacao(aux2, aux3);

            if(ant[3] == raiz)
            {
                pilha_retira(raizes);
                raiz = aux4;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            else
            {
                ant[4] = pilha_topo(p);
                ant[4]->filho_esq = aux4;
            }
            break;
        case 'b':
         #ifdef estatisticas
         redb++;
         #endif
            for(i = 0; i < 4; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
            }
            if(fim) break;


            testa_celulas_livres(3, raizes);
            aux = cria_celula_derivacao(ant[0]->filho_dir,ant[1]->filho_dir);
            aux2 = cria_celula_derivacao(ant[2]->filho_dir,ant[3]->filho_dir);
            aux3 = cria_celula_derivacao(aux,aux2);

            if(ant[3] == raiz)
            {
                pilha_retira(raizes);
                raiz = aux3;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            else
            {
                ant[4] = pilha_topo(p);
                ant[4]->filho_esq = aux3;
            }
            break;
        case 'c':
         #ifdef estatisticas
         redc++;
         #endif
            for(i=0; i < 4; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
            }
            if(fim) break;


            testa_celulas_livres (3, raizes);
            aux = cria_celula_derivacao(ant[1]->filho_dir,ant[3]->filho_dir);
            aux2 = cria_celula_derivacao(ant[0]->filho_dir, aux);
            aux3 = cria_celula_derivacao(aux2, ant[2]->filho_dir);

            if(ant[3] == raiz)
            {
                pilha_retira(raizes);
                raiz = aux3;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            else
            {
                ant[4] = pilha_topo(p);
                ant[4]->filho_esq = aux3;
            }
            break;
        case '+':
         #ifdef estatisticas
         redMais++;
         #endif
            for(i = 0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
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
            testa_celulas_livres(1, raizes);
            aux = cria_celula_folha_inteiro(ant[0]->filho_dir->inteiro + ant[1]->filho_dir->inteiro);

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = aux;
            }
            else //Aplica a regra e reduz a Ka
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz);                
                pilha_insere(p, raiz);
            }
            break;
        case '-':
         #ifdef estatisticas
         redMenos++;
         #endif
            for(i = 0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
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
            testa_celulas_livres(1,raizes);
            aux = cria_celula_folha_inteiro(ant[0]->filho_dir->inteiro - ant[1]->filho_dir->inteiro);

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = aux;
            }
            else //Aplica a regra e reduz a Ka
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz);    
                pilha_insere(p, raiz);
            }
            break;
        case '*':
         #ifdef estatisticas
         redMult++;
         #endif
            for(i = 0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
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
            testa_celulas_livres(1, raizes);
            aux = cria_celula_folha_inteiro(ant[0]->filho_dir->inteiro * ant[1]->filho_dir->inteiro);

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = aux;
            }
            else //Aplica a regra e reduz a Ka
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            break;
        case '/':
         #ifdef estatisticas
         redDiv++;
         #endif
            for(i = 0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
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
            testa_celulas_livres(1, raizes);
            aux = cria_celula_folha_inteiro(ant[0]->filho_dir->inteiro / ant[1]->filho_dir->inteiro);

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = aux;
            }
            else //Aplica a regra e reduz a Ka
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            break;
        case '^':
         #ifdef estatisticas
         redExp++;
         #endif
            for(i = 0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
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
            testa_celulas_livres(1, raizes);
            aux = cria_celula_folha_inteiro(pow(ant[0]->filho_dir->inteiro,  ant[1]->filho_dir->inteiro));

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = aux;
            }
            else //Aplica a regra e reduz a Ka
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            break;
        case '<':
         #ifdef estatisticas
         redMenor++;
         #endif
            for(i = 0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
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
                testa_celulas_livres(1, raizes);
                aux = cria_celula_folha('K'); //true escolhe o primeiro mais perto Kab = a
            }
            else
            {
                testa_celulas_livres(1, raizes);
                aux = cria_celula_folha('F');  //false escolhe o segundo
            }

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = aux;
            }
            else //Aplica a regra e reduz a Ka
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            break;
        case '=':
         #ifdef estatisticas
         redEqual++;
         #endif
            for(i = 0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
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
            ehdiferente = 1;
            if((ant[0]->filho_dir->tipo == '$' || ant[0]->filho_dir->tipo == ']') && (ant[1]->filho_dir->tipo == '$' || ant[1]->filho_dir->tipo == ']')) 
            {
                transforma_lista(ant[0]->filho_dir, ant[1]->filho_dir); 
                if(ehdiferente == 0)
                {
                    testa_celulas_livres(1,raizes);
                    aux = cria_celula_folha('F'); //true escolhe o primeiro mais perto Kab = a
                }
                else
                {
                    testa_celulas_livres(1,raizes);
                    aux = cria_celula_folha('K'); //true escolhe o primeiro mais perto Kab = a
                }
            }
            else if(ant[0]->filho_dir->inteiro == ant[1]->filho_dir->inteiro)
            {
                testa_celulas_livres(1,raizes);
                aux = cria_celula_folha('K'); //true escolhe o primeiro mais perto Kab = a
            }
            else
            {
                testa_celulas_livres(1, raizes);
                aux = cria_celula_folha('F');  //false escolhe o segundo
            }

            if(ant[1] != raiz) // faz o filho de cima apontar logo para a
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = aux;
            }
            else //Aplica a regra e reduz a Ka
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz);
                pilha_insere(p, raiz);
            }
            break;
        case 'H':
         #ifdef estatisticas
         redH++;
         #endif
            ant[0] = pilha_topo(p);
            pilha_retira(p);

            if(ant[0]->filho_dir == NULL) fim = TRUE;
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }

            if(ant[0] != raiz)
            {
                ant[1] = pilha_topo(p);
                ant[1]->filho_esq = ant[0]->filho_dir->filho_esq;
            }
            else
            {
                pilha_retira(raizes);
                raiz = ant[0]->filho_dir->filho_esq;
                pilha_insere(raizes, raiz); 
                pilha_insere(p, raiz);
            }
            break;
        case 'T':
         #ifdef estatisticas
         redT++;
         #endif
            ant[0] = pilha_topo(p);
            pilha_retira(p);

            if(ant[0]->filho_dir == NULL) fim = TRUE;
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }

            if(ant[0] != raiz)
            {
                ant[1] = pilha_topo(p);
                ant[1]->filho_esq = ant[0]->filho_dir->filho_dir;
            }
            else
            {
                pilha_retira(raizes);
                raiz = ant[0]->filho_dir->filho_dir;
                pilha_insere(raizes, raiz); 
                pilha_insere(p, raiz);
            }
            break;
        case ':':
         #ifdef estatisticas
         redList++;
         #endif
            for(i = 0; i < 2; i++)
            {
                ant[i] = pilha_topo(p);
                pilha_retira(p);
                if(ant[i] == NULL) fim = TRUE;
            }
            if(fim) break;

            if(ant[0]->filho_dir->tipo == '@')
            {
                ant[0]->filho_dir = mg_v2(ant[0]->filho_dir);
            }
            if(ant[1]->filho_dir->tipo == '@')
            {
                ant[1]->filho_dir = mg_v2(ant[1]->filho_dir);
            }
            testa_celulas_livres(1, raizes);
            aux = cria_celula_lista();
            aux->filho_esq = ant[0]->filho_dir;
            aux->filho_dir = ant[1]->filho_dir;

            if(ant[1] != raiz)
            {
                ant[2] = pilha_topo(p);
                ant[2]->filho_esq = aux;
            }
            else
            {
                pilha_retira(raizes);
                raiz = aux;
                pilha_insere(raizes, raiz); 
                pilha_insere(p, raiz);
            }
            break;
        default:
            fim = TRUE;
            break;
        }
        ant[0] = NULL;
        ant[1] = NULL;
        ant[2] = NULL;
        ant[3] = NULL;
        ant[4] = NULL;


    }
    pilha_destroi(p);
    pilha_retira(raizes);
    return raiz;
}

int main()
{
    inicia_heap(tamanho_heap);
    
    //char str[] = "Y(b(bS)(C(c=I[])[])(b(s(s:))(cBI(BHI))(C(cc(BbI)I)(BTI))))(c^I2 )[1,2]";
    char str[1000];
    while(fgets(str, 1000, stdin) != NULL) {
        Celula* raiz = monta_arvore(str);
        raizes = pilha_cria();
        raiz = mg_v2(raiz);
        imprime_arvore(raiz);
        pilha_destroi(raizes);
    }
    //printf("\n");
    #ifdef estatisticas
        printf("Reducoes K: %d\nReducoes S: %d\nReducoes I: %d\nReducoes B: %d\nReducoes C: %d\n",redK, redS,redI, redB,redC);
        printf("Reducoes s': %d\nReducoes b': %d\nReducoes c': %d\nReducoes Y: %d\nReducoes False: %d\n",reds,redb,redc,redY,redF);
        printf("Reducoes (+): %d\nReducoes (-): %d\nReducoes (*): %d\nReducoes (/): %d\nReducoes (^): %d\n",redMais,redMenos,redMult,redDiv,redExp);
        printf("Reducoes (<): %d\nReducoes (=): %d\nReducoes Head: %d\nReducoes Tail: %d\nReducoes (:): %d\n",redMenor,redEqual,redH,redT,redList);
        printf("Chamada ao garbage collection : %d\n", garbe);
    #endif

    printf("\n");
    return 0;
}
