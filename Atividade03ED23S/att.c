// IMPORT'S:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


// DEFINE'S:
#define FALSE 0
#define LETRA_C 'c'
#define LETRA_D 'd'
#define LETRA_R 'r'
#define VALOR_RANDOMICO_MAXIMO 32000
#define TAMANHO_CARACTERS_LINHA_ARQUIVO 50
#define TAMANHO_MAX_CARACTERES_PRINT_VALORES_VETORES 300000


// VARIAVEIS:
char TEXTO_ARQUIVO_INVALIDO[] = {"Arquivo Inválido!"};
char TEXTO_ARQUIVO_VAZIO[] = {"Arquivo vazio!"};
char TEXTO_ELEMENTO_N_ENCONTRADO[] = {"Elemento não encontrado!"};


// FUNÇÕES PARA O ARQUIVO
int errorQuantParametrosProgramaESair(void) {
    printf("Quantidade de parametros invalida!\n");
    exit(-1);
    return FALSE;
};
int errorArquivosESair(void) {
    printf("Erro: algum dos arquivos não pode ser criado corretamente!\n");
    exit(-1);
    return FALSE;
};
int arquivoInvalido(FILE *arquivo) {
    fprintf(arquivo, "%s", TEXTO_ARQUIVO_INVALIDO);
    printf("%s\n", TEXTO_ARQUIVO_INVALIDO);
    
    exit(-1);
    return FALSE;
};
int tamanhoArquivo(FILE *arquivo) {
    if(arquivo == NULL) return 0;

    fseek(arquivo, 0, SEEK_END);
    int tamanho = ftell(arquivo);
    rewind(arquivo);

    return tamanho;
};


// FUNÇÕES EM GERAL
void verificarValorValidoLetraOrdenacao(char letra, FILE *saida) {
    if (letra != LETRA_C && letra != LETRA_D &&  letra != LETRA_R)
        arquivoInvalido(saida);
};
void imprimirLista(int *v, int n, int comp, float timer_ms, char *txt, FILE *saida) {
    char lista_formatada[TAMANHO_MAX_CARACTERES_PRINT_VALORES_VETORES] = {""};
    
    for (int i = 0; i < n; i++) {
        char int_str[10];
        sprintf(int_str, " %d", v[i]);
        strcat(lista_formatada, int_str);
    }

    fprintf(saida, "%s:%s, %d comp, %f ms\n", txt, lista_formatada, comp, timer_ms);
};


void insertionSort(int *v, int n, int *ptr_comp, float *ptr_timer) {
    clock_t tempos[2];
    tempos[0] = clock();
    
    int i, j, aux;
    for (i = 1; i < n; i++) {
        aux = v[i];
        *ptr_comp+=1;
        
        for (j = i; (j > 0) && (aux < v[j - 1]); j--) {
            v[j] = v[j - 1];
            *ptr_comp+=1;
        }
        
        v[j] = aux;
    }
    
    tempos[1] = clock();
    *ptr_timer = (tempos[1] - tempos[0]) * 1000.0 / CLOCKS_PER_SEC;
};

void selectionSort(int *v, int n, int *ptr_comp, float *ptr_timer) {
    clock_t tempos[2];
    tempos[0] = clock();

    int i, j, menor, troca;
    for (i = 0; i < n-1; i++) {
        menor = i;
        *ptr_comp+=1;
        
        for (j = i+1; j < n; j++) {
            *ptr_comp+=1;
            if (v[j] < v[menor]) {
                menor = j;
                *ptr_comp+=1;
            }
        }

        if (i != menor) {
            troca = v[i];
            v[i] = v[menor];
            v[menor] = troca;

            *ptr_comp+=1;
        }
    }
    
    tempos[1] = clock();
    *ptr_timer = (tempos[1] - tempos[0]) * 1000.0 / CLOCKS_PER_SEC;
};

void bubbleSort(int *v, int n, int *ptr_comp, float *ptr_timer) {
    clock_t tempos[2];
    tempos[0] = clock();

    int i, continua, aux, fim = n;
    do {
        continua = 0;
        for (i = 0; i < fim-1; i++) {
            *ptr_comp+=1;
            if (v[i] > v[i+1]) {
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                continua = i;

                *ptr_comp+=1;
            }
        }
        fim--;

        *ptr_comp+=1;
    } while (continua != 0);
    
    tempos[1] = clock();
    *ptr_timer = (tempos[1] - tempos[0]) * 1000.0 / CLOCKS_PER_SEC;
};

void merge(int *v, int inicio, int meio, int fim, int *ptr_comp) {
    int *temp, p1, p2, tamanho, i, j, k,
        fim1 = 0, fim2 = 0;

    tamanho = (fim - inicio + 1);
    p1 = inicio;
    p2 = meio+1;
    temp = (int *) malloc(tamanho*sizeof(int));

    if (temp != NULL) {
        *ptr_comp+=1;
        for (i = 0; i < tamanho; i++) {
            *ptr_comp+=1;
            if (!fim1 && !fim2) {
                *ptr_comp+=1;
                if (v[p1] < v[p2]) temp[i] = v[p1++];
                else temp[i] = v[p2++];

                if (p1 > meio) {
                    fim1 = 1;
                    *ptr_comp+=1;
                }
                if (p2 > fim) {
                    fim2 = 1;
                    *ptr_comp+=1;
                }
            } else {
                *ptr_comp+=1;
                if (!fim1) temp[i] = v[p1++];    
                else temp[i] = v[p2++];
            }
        }

        for (j = 0, k = inicio; j < tamanho; j++, k++) {
            v[k] = temp[j];
            *ptr_comp+=1;
        }
    }
    free(temp);
};
void mergeSort(int *v, int inicio, int fim, int *ptr_comp, float *ptr_timer) {
    clock_t tempos[2];
    tempos[0] = clock();

    int meio;
    if (inicio < fim) {
        *ptr_comp+=1;
        meio = floor((inicio + fim) / 2);
        mergeSort(v, inicio, meio, ptr_comp, ptr_timer);
        mergeSort(v, meio+1, fim, ptr_comp, ptr_timer);
        merge(v, inicio, meio, fim, ptr_comp);
    }

    tempos[1] = clock();
    *ptr_timer = (tempos[1] - tempos[0]) * 1000.0 / CLOCKS_PER_SEC;
};

int particiona(int *v, int inicio, int finall, int *ptr_comp) {
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = finall;
    pivo = v[inicio];

    while (esq < dir) {
        *ptr_comp+=1;
        while (v[esq] <= pivo) {
            esq++;
            *ptr_comp+=1;
        }
        while (v[dir] > pivo) {
            dir--;
            *ptr_comp+=1;
        }

        if (esq < dir) {
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
            *ptr_comp+=1;
        }
    }

    v[inicio] = v[dir];
    v[dir] = pivo;
    
    return dir;
};
void quickSort(int *v, int inicio, int fim, int *ptr_comp, float *ptr_timer) {
    clock_t tempos[2];
    tempos[0] = clock();

    int pivo;
    if (fim > inicio) {
        pivo = particiona(v, inicio, fim, ptr_comp);
        quickSort(v, inicio, pivo-1, ptr_comp, ptr_timer);
        quickSort(v, pivo+1, fim, ptr_comp, ptr_timer);
    }

    tempos[1] = clock();
    *ptr_timer = (tempos[1] - tempos[0]) * 1000.0 / CLOCKS_PER_SEC;
};

void criaHeap(int *v, int i, int f, int *ptr_comp) {
    int aux = v[i];
    int j = i * 2 + 1;

    while (j <= f) {
        *ptr_comp+=1;
        if (j < f) {
            *ptr_comp+=1;
            if (v[j] < v[j + 1]) {
                j = j + 1;
                *ptr_comp+=1;
            }
        }

        if (aux < v[j]) {
            v[i] = v[j];
            i = j;
            j = 2 * i + 1;
            *ptr_comp+=1;
        } else {
            j = f + 1;
            *ptr_comp+=1;
        }
    }
    v[i] = aux;
};
void heapSort(int *v, int n, int *ptr_comp, float *ptr_timer) {
    clock_t tempos[2];
    tempos[0] = clock();
    
    int i, aux;
    for (i = (n-1)/2; i >= 0; i--) {
        *ptr_comp+=1;
        criaHeap(v, i, n-1, ptr_comp);
    }
    for (i = n-1; i >= 1; i--) {
        *ptr_comp+=1;
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        criaHeap(v, 0, i - 1, ptr_comp);
    }

    tempos[1] = clock();
    *ptr_timer = (tempos[1] - tempos[0]) * 1000.0 / CLOCKS_PER_SEC;
};

// PARA EXECUTAR (em Shell):
// 1º:  gcc [NOME_ARQUIVO_PROGRAMA.c] -o [NOME_ARQUIVO_PROGRAMA]
// 2º:  ./[NOME_ARQUIVO_PROGRAMA] [ARQUIVO_ENTRADA.txt] [ARQUIVO_SAIDA.txt]
int main(int argc, char *argv[]) {
    if(argc != 3) errorQuantParametrosProgramaESair();

    FILE* entrada = fopen(argv[1], "r");
    FILE* saida = fopen(argv[2], "w");

    // Checar erros de abertura de arquivo
    if(!entrada || !saida) errorArquivosESair();
    if (!tamanhoArquivo(entrada) || feof(entrada) || ferror(entrada))
        arquivoInvalido(saida);

    int contador_linhas_arq = 1,
        quantidade = 0;
    
    char linhas_arq[TAMANHO_CARACTERS_LINHA_ARQUIVO], letra;
    linhas_arq[0] = '\0';
    
    // fgets vai capturando linha por linha no arquivo
    while (fgets(linhas_arq, sizeof(linhas_arq), entrada)) {
        if (contador_linhas_arq == 1) {
            if (atoi(linhas_arq)) {
                quantidade = atoi(linhas_arq);
                contador_linhas_arq++;
            } else arquivoInvalido(saida);
        } else if (contador_linhas_arq == 2) {
            letra = linhas_arq[0];
            contador_linhas_arq++;
        } else break;
    }

    verificarValorValidoLetraOrdenacao(letra, saida);

    int v_insertion_sort[quantidade],
        v_selection_sort[quantidade],
        v_bubble_sort[quantidade],
        v_merge_sort[quantidade],
        v_quick_sort[quantidade],
        v_heap_sort[quantidade],
        
        comp_insertion_sort = 0,
        comp_selection_sort = 0,
        comp_bubble_sort = 0,
        comp_merge_sort = 0,
        comp_quick_sort = 0,
        comp_heap_sort = 0;

    float timer_ms_insertion_sort = 0,
        timer_ms_selection_sort = 0,
        timer_ms_bubble_sort = 0,
        timer_ms_merge_sort = 0,
        timer_ms_quick_sort = 0,
        timer_ms_heap_sort = 0;

    // INSERE OS VALORES DE ACORDO COM O CASO
    if (letra == LETRA_R) {
        for (int i = 0; i < quantidade; i++) {
            int valor_randomico = (rand() % VALOR_RANDOMICO_MAXIMO);
            
            v_insertion_sort[i] = valor_randomico;
            v_selection_sort[i] = valor_randomico;
            v_bubble_sort[i] = valor_randomico;
            v_merge_sort[i] = valor_randomico;
            v_quick_sort[i] = valor_randomico;
            v_heap_sort[i] = valor_randomico;
        }
    } else if (letra == LETRA_C) {
        for (int i = 0; i < quantidade; i++) {
            v_insertion_sort[i] = i+1;
            v_selection_sort[i] = i+1;
            v_bubble_sort[i] = i+1;
            v_merge_sort[i] = i+1;
            v_quick_sort[i] = i+1;
            v_heap_sort[i] = i+1;
        }
    } else if (letra == LETRA_D) {
        int i, j;
        for (i = 0, j = quantidade; j >= 0; j--, i++) {
            v_insertion_sort[i] = j;
            v_selection_sort[i] = j;
            v_bubble_sort[i] = j;
            v_merge_sort[i] = j;
            v_quick_sort[i] = j;
            v_heap_sort[i] = j;
        }
    }
    
    // FAZ A ORDENAÇÃO DE CADA UM
    insertionSort(v_insertion_sort, quantidade, &comp_insertion_sort, &timer_ms_insertion_sort);
    selectionSort(v_selection_sort, quantidade, &comp_selection_sort, &timer_ms_selection_sort);
    bubbleSort(v_bubble_sort, quantidade, &comp_bubble_sort, &timer_ms_bubble_sort);
    mergeSort(v_merge_sort, 0, quantidade-1, &comp_merge_sort, &timer_ms_merge_sort);
    quickSort(v_quick_sort, 0, quantidade-1, &comp_quick_sort, &timer_ms_quick_sort);
    heapSort(v_heap_sort, quantidade, &comp_heap_sort, &timer_ms_heap_sort);

    
    // IMPRIME A LISTA DE CADA UM
    imprimirLista(v_insertion_sort, quantidade, comp_insertion_sort, timer_ms_insertion_sort, "insertionSort", saida);
    imprimirLista(v_selection_sort, quantidade, comp_selection_sort, timer_ms_selection_sort, "selectionSort", saida);
    imprimirLista(v_bubble_sort, quantidade, comp_bubble_sort, timer_ms_bubble_sort, "bubbleSort", saida);
    imprimirLista(v_merge_sort, quantidade, comp_merge_sort, timer_ms_merge_sort, "mergeSort", saida);
    imprimirLista(v_quick_sort, quantidade, comp_quick_sort, timer_ms_quick_sort, "quickSort", saida);
    imprimirLista(v_heap_sort, quantidade, comp_heap_sort, timer_ms_heap_sort, "heapSort", saida);
    
    fclose(entrada);
    fclose(saida);
    
    return 0;
}