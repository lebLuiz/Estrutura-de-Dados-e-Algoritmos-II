#include <stdio.h>
#include <stdlib.h>

typedef struct Carro {
 char modelo[10];
 float valor; 
} CARRO;

typedef struct Pessoa {
 char cpf[15];
 char nome[20]; 
} PESSOA;

typedef struct Cadastro {
 int codigo;
 CARRO carro;
  PESSOA pessoa;
} CADASTRO;

double** aloca_matriz(int m, int n) {
  int i;
  double **matriz;

  matriz = (double **) malloc(n * sizeof(double *));
  for (i = 0; i < n; i++){
    matriz[i] = (double *) malloc(m * sizeof(double));
  }

  return matriz;
}

int recursivo(int num) {
  printf("%d\n", num);
  if (num == 0) return num;
  return recursivo(num - 1);
}

int main(void) {
  int n = 5;

  recursivo(n);
}