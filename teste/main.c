#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#define N 5
int main() {
	Pilha* p = pilha_cria();
	int i;
	for(i = N; i>=0; i--) {
		pilha_insere(p, i);
	}
	for(i = N; i>=0; i--) {
		printf("%d ", pilha_topo(p));	
		pilha_retira(p);	
	}
}