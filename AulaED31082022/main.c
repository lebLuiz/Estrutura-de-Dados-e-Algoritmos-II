#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NoPilha *PtrNoPilha;

struct NoPilha {
  int elemento;
  PtrNoPilha proximo;
} NoPilha;

typedef struct {
  PtrNoPilha topo;
  int qtde;
} PilhaDinamica;

void inicializaPilhaDinamica(PilhaDinamica *p) {
  p->qtde = 0;
  p->topo = NULL;
}

int tamanhoPilhaDinamica(PilhaDinamica *p) { return (p->qtde); }

bool estaVaziaPilhaDinamica(PilhaDinamica *p) {
  return tamanhoPilhaDinamica(p) == 0;
}

void imprimirPilhaDinamica(PilhaDinamica *p) {
  printf("Pilha = [");

  PtrNoPilha aux;
  for (aux = p->topo; aux != NULL; aux = aux->proximo) {
    printf("%d ", aux->elemento);
  }

  printf("]\n");
}

// inserir (push)
void pushPilhaDinamica(PilhaDinamica *p, int num) {
  PtrNoPilha aux = malloc(sizeof(NoPilha));
  aux->elemento = num;
  aux->proximo = p->topo;
  p->topo = aux;
  p->qtde++;
}

// remover (pop)
void popPilhaDinamica(PilhaDinamica *p) {
  if (!estaVaziaPilhaDinamica(p)) {
    PtrNoPilha aux;
    aux = p->topo;
    p->topo = p->topo->proximo;
    free(aux);
    p->qtde--;
  } else {
    printf("Warning: pilha está vazia!");
  }
}

int main(void) {
  PilhaDinamica pilha_dinamica;
  inicializaPilhaDinamica(&pilha_dinamica);

  if (estaVaziaPilhaDinamica(&pilha_dinamica))
    printf("Pilha está vazia!\n");
  else
    printf("Pilha não está vazia!\n");

  int tam = tamanhoPilhaDinamica(&pilha_dinamica);
  printf("Tamanho %d\n", tam);
  imprimirPilhaDinamica(&pilha_dinamica);

  pushPilhaDinamica(&pilha_dinamica, 7);
  imprimirPilhaDinamica(&pilha_dinamica);

  pushPilhaDinamica(&pilha_dinamica, 50);
  imprimirPilhaDinamica(&pilha_dinamica);

  popPilhaDinamica(&pilha_dinamica);
  imprimirPilhaDinamica(&pilha_dinamica);

  popPilhaDinamica(&pilha_dinamica);
  imprimirPilhaDinamica(&pilha_dinamica);

  return 0;
}