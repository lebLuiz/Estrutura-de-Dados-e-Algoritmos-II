#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ptr_no_arvore {
    int chave;

    struct ptr_no_arvore *esquerda;
    struct ptr_no_arvore *direita;
};

typedef struct ptr_no_arvore PtrNoArvore;

void inicioArvoreBinario(PtrNoArvore **arvore) {
    *arvore = NULL;
}

bool estaVaziaArvoreBinario(PtrNoArvore **arvore) {
    return (*arvore) == NULL;
}

void insercao(PtrNoArvore **arvore, int numero_novo) {
	if (estaVaziaArvoreBinario(&(*arvore))) {
        *arvore = (PtrNoArvore *) malloc(sizeof (PtrNoArvore));
        (*arvore)->esquerda=NULL;
        (*arvore)->direita=NULL;
        (*arvore)->chave = numero_novo;
	} else {
		if (numero_novo < ((*arvore)->chave)) {
			insercao(&((*arvore)->esquerda), numero_novo);
		} else {
			insercao(&((*arvore)->direita), numero_novo);
		}
	}
}

void printOrdemArvoreBinario(PtrNoArvore **arvore) {
    if (estaVaziaArvoreBinario(&(*arvore)))
        return; // Clausula base

    printf("%d ", (*arvore)->chave);
    printOrdemArvoreBinario(&(*arvore)->esquerda);
    printOrdemArvoreBinario(&(*arvore)->direita);
}

int main(void) {
    
    PtrNoArvore *raiz;
    inicioArvoreBinario(&raiz);

    insercao(&raiz, 1);
    insercao(&raiz, 6);
    insercao(&raiz, 21);
    insercao(&raiz, 64);
    insercao(&raiz, 2);

    printOrdemArvoreBinario(&raiz);

    if (estaVaziaArvoreBinario(&raiz))
        printf("Está vazia!");
    
    return 0;
}