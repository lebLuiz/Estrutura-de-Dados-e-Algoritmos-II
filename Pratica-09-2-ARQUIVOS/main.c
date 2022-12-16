#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//Estrutura p/ armazenar o número do cartão e as 6 dezenas de cada aposta.
typedef struct Aposta {
	int nroCartao;
	int dezenas[6];
} APOSTA;

void printar_tracos_quebra_linha(void);
void quebar_duas_linhas(void);
void error_arquivo(void);
void printar_notificacao_valor_numero(void);
void printar_retorno_limpar_apostas(void);
int valor_maior_que_limite(int valor);
void ler_numero_cartao(int *num_cartao_momento);
void ler_numero(int posicao, int *num_momento);

void Gravar_apostas(void);
void Ler_apostas(void);
void Pesquisar_cartao(void);
void Limpar_apostas(void);
int nroRepetido(int vet[], int nro);

/* 
*  OBS: O CAMINHO DO ARQUIVO É RELATIVO
*  DEPENDENDO DA MÁQUINA (PC) QUE SERÁ
*  EXECUTADO ESSE CÓDIGO!
*/ 
char local_arquivo[] = {".\\arquivo_pratica09_2.bin"};

int main() {
	int opcao;
	do {
    system("cls");
		printf("MENU:\n");
    printf("1 - Gravar apostas\n");
    printf("2 - Ler apostas\n");
    printf("3 - Limpar apostas\n");
    printf("4 - Pesquisar cartao\n");
    printf("0 - Encerrar o Programa\n");
    printf("-----------------------------\n");
    printf("Informe a opção desejada:\n");
    do {
      scanf("%d", &opcao);
      if((opcao < 0) || (opcao > 4))
        printf("Opcao invalida! Tente novamente.\n");
    } while ((opcao < 0) || (opcao > 4));
    
    switch (opcao) {
      case 1: Gravar_apostas(); break;
      case 2: Ler_apostas(); break;
      case 3: Limpar_apostas();break;
      case 4: Pesquisar_cartao();
    }
  } while (opcao != 0);
  
  return 0;
}

// PRINTS:
void printar_tracos_quebra_linha(void) {
  printf("\n-----------------------------\n");
};
void quebar_duas_linhas(void) {
  printf("\n\n");
};
void error_arquivo(void) {
  printf("Não foi possível abrir o arquivo");
  exit(-100);
};
void printar_notificacao_valor_numero(void) {
  printf("Número não pode ser repetido e valor precisa ser menor ou igual a 60!");
  quebar_duas_linhas();
};
void printar_retorno_limpar_apostas(void) {
  printf("Retorno: %d\n", remove(local_arquivo));
};

// VALIDACAO:
int valor_maior_que_limite(int valor) {
  return valor > 60 ? 1 : 0;
};

// LEITURA_DE_VALORES:
void ler_numero_cartao(int *num_cartao_momento) {
  printf("Número do Cartão:");
  scanf(" %d", num_cartao_momento);
};
void ler_numero(int posicao, int *num_momento) {
  printf("Número(%d):", posicao);
  scanf(" %d", num_momento);
};


void Gravar_apostas(void) {
	FILE *arq_gravar = fopen(local_arquivo, "ab");
  if (arq_gravar == NULL) error_arquivo();

  APOSTA aposta;

  ler_numero_cartao(&aposta.nroCartao);
  quebar_duas_linhas();

  for (int i = 0; i < 6; i++) {
    int numero_momento;
    int posicao = (i + 1);
    int primeira_tentativa = 0;

    do {
      if (primeira_tentativa > 0) printar_notificacao_valor_numero();
      ler_numero(posicao, &numero_momento);
      primeira_tentativa++;
    } while (nroRepetido(aposta.dezenas, numero_momento) ||
            valor_maior_que_limite(numero_momento));

    aposta.dezenas[i] = numero_momento;
    quebar_duas_linhas();
  }
  
  fwrite(&aposta, sizeof(APOSTA), 1, arq_gravar);

  printar_tracos_quebra_linha();
	fclose(arq_gravar);
}

void Ler_apostas(void) {
  FILE *arq_ler = fopen(local_arquivo, "rb");

  if (arq_ler == NULL) error_arquivo();

  APOSTA aposta;

  printf("#### TODOS OS CARTÕES LISTADOS ABAIXO ####");
  quebar_duas_linhas();
  
  while (!feof(arq_ler)) {
    if (fread(&aposta, sizeof(APOSTA), 1, arq_ler)) {
      printf("NºCartão: %d\n", aposta.nroCartao);
      for (int i = 0; i < 6; i++) {
        printf("Número(%d) = %d\n", (i + 1), aposta.dezenas[i]);
      }
      quebar_duas_linhas();
    }
  }

  printar_tracos_quebra_linha();
  fclose(arq_ler);
}

void Pesquisar_cartao(void) {
	FILE *arq_ler = fopen(local_arquivo, "rb");

  if (arq_ler == NULL) error_arquivo();

  APOSTA aposta;
  int numero_cartao_buscar, encontrou = 0;

  ler_numero_cartao(&numero_cartao_buscar);
  
  while (!feof(arq_ler)) {
    if (fread(&aposta, sizeof(APOSTA), 1, arq_ler) &&
      aposta.nroCartao == numero_cartao_buscar) {
      encontrou = 1;
      printf("#### NÚMEROS DO CARTÃO %d ABAIXO ####", aposta.nroCartao);
      quebar_duas_linhas();
      
      for (int i = 0; i < 6; i++) {
        printf("Número(%d) = %d\n", (i + 1), aposta.dezenas[i]);
      }
      
      quebar_duas_linhas();
      break;
    }
  }

  if (!encontrou) printf("Cartão não encontrado!");

  printar_tracos_quebra_linha();
  fclose(arq_ler);
}

void Limpar_apostas(void) {
  FILE *arq_limpa = fopen(local_arquivo, "wb");
  
  if (arq_limpa == NULL) {
    printar_retorno_limpar_apostas();
    quebar_duas_linhas();
  } else {
    fclose(arq_limpa);
    printar_retorno_limpar_apostas();
  }
  
	fopen(local_arquivo, "wb");
}

int nroRepetido(int vet[], int nro){
	int ret = 0; //false
	for(int i = 0; i < 6; i++){
		if(vet[i] == nro){
			ret = 1;
			break;
		}
	}
	return ret;
}