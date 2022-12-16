// QUESTÃO 1:
/*
#include <stdio.h>
#include <stdlib.h>

int **matriz_irregular(int n, int vetor[]) {
  int i, **m = (int **) malloc(n * sizeof(int *));

  if (m == NULL) return NULL;

  for (i = 0; i < n; i++) {
    m[i] = (int *) malloc(n * sizeof(int));
    
    if (m[i] == NULL) {
      while (i) {
        i --;
        free(m[i]);
      }
      free(m);
      return NULL;
    }
  }
  
  for (i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      m[i][j] = vetor[i];
    }
  }
  
  return m;
}

int main() {
  int **m, n;
	scanf("%d", &n);
	
	int vetor[n];
	for (int i=0; i<n; i++){
		scanf("%d", &vetor[i]);
	}
	
	m = matriz_irregular(n, vetor);
	for (int i=0; i<n; i++){
		for (int j=0; j<vetor[i]; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	
  return 0;
}
*/



// QUESTÃO 2:
/*#include <stdio.h>

struct atleta {
  char nome[60];
  float salto1;
  float salto2;
  float salto3;
};

int maior_marca(float valor_marca1, float valor_marca2) {
  return (valor_marca1 > valor_marca2) ? 1 : 0;
}
void ler_salto(struct atleta at[],int n) {
  for (int i = 0; i <  n; i++) {
    scanf(" %[^\n]s", at[i].nome);
    scanf(" %f", &at[i].salto1);
    scanf(" %f", &at[i].salto2);
    scanf(" %f", &at[i].salto3);
  }
}

void exibir_marcas(struct atleta at[],int n) {
  for (int i = 0; i <  n; i++) {
    printf("%s ", at[i].nome);
    printf("%.2f - ", at[i].salto1);
    printf("%.2f - ", at[i].salto2);
    printf("%.2f, ", at[i].salto3);

    float melhor_marca = at[i].salto1;
    if (maior_marca(at[i].salto2, at[i].salto1) && maior_marca(at[i].salto2, at[i].salto3)) {
      melhor_marca = at[i].salto2;
    } else if (maior_marca(at[i].salto3, at[i].salto1) && maior_marca(at[i].salto3, at[i].salto2)) {
      melhor_marca = at[i].salto3;
    } else if (maior_marca(at[i].salto1, at[i].salto2) && maior_marca(at[i].salto1, at[i].salto3)) {
      melhor_marca = at[i].salto1;
    }

    printf("melhor marca: %.2f\n", melhor_marca);
  }
}

int main() {
  int n;
  scanf("%d",&n);
  struct atleta at[n];
  ler_salto(at, n);
  exibir_marcas(at, n);
	
  return 0;
}*/



// QUESTÃO 3:
#include <stdio.h>
#include <stdlib.h>
#define SEMANA 7

typedef struct temp_diaria{
	float min, max;
} TEMPERATURA;

TEMPERATURA ** ler_temperaturas(int num_semanas);
void imprimir_temperaturas(TEMPERATURA **semanas, int num_semanas);
void maior_amplitude_termica(TEMPERATURA **semanas, int num_semanas);

void imprimir_temperaturas(TEMPERATURA **semanas, int num_semanas){
  printf("Temperaturas aferidas, por Semana (S):\n");
	int i,j;
	for (i=0;i<num_semanas; i++){
		printf("S%d: ", i);
		for(j=0; j<SEMANA; j++){
      printf("(%.2f, %.2f) ", semanas[i][j].min, semanas[i][j].max);
		}
		printf("\n");
	}
}

// INSIRA O CODIGO DAS FUNCOES AQUI!
// O RESTANTE DO CODIGO NAO PODE SER ALTERADO!
void efetura_leitura_temperaturas(TEMPERATURA *temperatura) {
  fflush(stdin);
  scanf(" %f", &temperatura->min);
  scanf(" %f", &temperatura->max);
}

TEMPERATURA ** ler_temperaturas(int num_semanas) {
  int i;
  TEMPERATURA **m_temperaturas = (TEMPERATURA **) malloc(num_semanas * sizeof(TEMPERATURA *));

  if (m_temperaturas == NULL) return NULL;

  for (i = 0; i < SEMANA; i++) {
    m_temperaturas[i] = (TEMPERATURA *) malloc(1 * sizeof(TEMPERATURA));

    if (m_temperaturas[i] == NULL) {
      while (i) {
        i --;
        free(m_temperaturas[i]);
      }
      free(m_temperaturas);
      return NULL;
    }

    efetura_leitura_temperaturas(m_temperaturas[i]);
  }
  
  return m_temperaturas;
}

int main(void){
	int num_semanas;
	TEMPERATURA ** temp_semana = NULL;
	
	scanf("%d",&num_semanas);
	temp_semana = ler_temperaturas(num_semanas);	
	imprimir_temperaturas(temp_semana, num_semanas);
	// maior_amplitude_termica(temp_semana, num_semanas);
}