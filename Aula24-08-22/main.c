#include <stdio.h>
#include <stdbool.h>

#define TAMANHO 6

typedef struct {
  int vetor[TAMANHO];
  int topo;
} PILHA_ESTATICA;

// INICIAR PILHA ESTATICA
void iniciarPilhaEstatica(PILHA_ESTATICA *pilha) {
  pilha->topo = 0;
};

// ESTA_VAZIA_PILHA_ESTATICA
bool estaVaziaPilhaEstatica(PILHA_ESTATICA *pilha) {
  return pilha->topo == 0;
}

// ESTA_CHEIA_PILHA_ESTATICA
bool estaCheiaPilhaEstatica(PILHA_ESTATICA *pilha) {
  return pilha->topo == TAMANHO;
}

// RETORNA_TAMANHO_PILHA
int retornaTamanhoPilhaEstatica(PILHA_ESTATICA *pilha) {
  return pilha->topo;
}

// IMPRIME_TOPO_PILHA
int imprimeTopoPilhaEstatica(PILHA_ESTATICA *pilha) {
  int elemento_topo = pilha->vetor[pilha->topo - 1];
  return elemento_topo;
}

// INSERIR_PILHA_ESTATICA
void inserirPilhaEstatica(PILHA_ESTATICA *pilha, int elemento) {
  if (!estaCheiaPilhaEstatica(pilha)) {
    pilha->vetor[pilha->topo] = elemento;
    pilha->topo++;
  } else {
    printf("Warning: Pilha cheia!\n");
  }
}

// REMOVER_PILHA_ESTATICA
void removePilhaEstatica(PILHA_ESTATICA *pilha) {
  if (!estaVaziaPilhaEstatica(pilha))
    pilha->topo--;
}

// IMPRIME_PILHA
void imprimePilhaEstatica(PILHA_ESTATICA *pilha) {
  printf("Pilha Estática: \t");
  printf("Pilha = [");

  for (int i = 0; i < pilha->vetor[i]; i++) {
    printf("%d ", pilha->vetor[i]);
  }
  
 printf("]\n");
}

int main(int argc, const char *argv[]) {

  PILHA_ESTATICA pilha;
  iniciarPilhaEstatica(&pilha);

  if (estaVaziaPilhaEstatica(&pilha))
    printf("Pilha vazia!\n");

  if (!estaCheiaPilhaEstatica(&pilha))
    printf("Não está cheia! Podemos adicionar elementos!\n\n");

  printf("Tamanho da pilha: %d\n", retornaTamanhoPilhaEstatica(&pilha));
  inserirPilhaEstatica(&pilha, 34);
  printf("Topo = %d\n", imprimeTopoPilhaEstatica(&pilha));
  inserirPilhaEstatica(&pilha, 14);
  imprimePilhaEstatica(&pilha);
  inserirPilhaEstatica(&pilha, 21);
  imprimePilhaEstatica(&pilha);
  inserirPilhaEstatica(&pilha, 56);
  imprimePilhaEstatica(&pilha);
  removePilhaEstatica(&pilha);
  
  return 0;
}