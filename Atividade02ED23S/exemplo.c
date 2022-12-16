#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1
#define ARV_B "arvore-binaria"
#define ARV_AVL "arvore-avl"
#define TAM_MAX_PALAVRA 50
#define BILLION  1000000000.0


// ARVORE BINARIA
struct no_arv_b {
    char palavra[TAM_MAX_PALAVRA];
    int n_ocorrencia;
    struct no_arv_b *esq;
    struct no_arv_b *dir;
};

// ARVORE AVL
typedef struct no_arv_avl* PtrNoArvAvl;
typedef struct no_arv_avl {
    PtrNoArvAvl dir, esq;
    int altura;
    char palavra[TAM_MAX_PALAVRA];
    int n_ocorrencia;
} no_arv_avl;


// FUNÇÕES PARA O ARQUIVO
FILE * abreL(char *nome) {
    return fopen(nome, "r");
};
void fecha(FILE *arquivo) {
    fclose(arquivo);
};
int tamanhoArquivo(FILE *arquivo) {
    if(arquivo == NULL) return 0;

    fseek(arquivo, 0, SEEK_END);
    int tamanho = ftell(arquivo);
    rewind(arquivo);

    return tamanho;
}


// FUNÇÕES DE ERROR
int errorQuantParametrosProgramaESair(void) {
    printf("Erro: Quantidade de parametros invalida!\n");
    exit(-1);
    return FALSE;
};
int errorArquivoESair(void) {
    printf("Erro: Arquivo não pode ser criado corretamente!\n");
    exit(-1);
    return FALSE;
};
int errorEstruturaArvoreIncorretaESair(void) {
    printf("Erro: Estrutura informada não identificada (arvore-binaria OU arvore-avl)!\n");
    exit(-1);
    return FALSE;
};
int errorSemMemoriaParaAlocarESair(void) {
    printf("Erro: Sem memória para alocar!\n");
    exit(-1);
    return FALSE;
};
int errorArquivoNaoAbriuParaLeitura(void) {
    printf("Não abriu para leitura o arquivo\n");
    printf("Terminando o programa...\n");
    exit(-1);
    return FALSE;
};

void printarResultadoComparacaoEDesempenho(
    char *texto,
    int quant,
    double tempo_desempenho
) {
    printf("%s\n", texto);
    printf("\t%d comparações\n", quant);
    printf("\t%f segundos\n\n", tempo_desempenho);
};


// A PARTIR DAQUI É FUNÇÕES PARA ÁRVORE AVL
void iniciaArvoreAVL(PtrNoArvAvl *no){
    (*no) = NULL;
}
void preOrdemAVL(PtrNoArvAvl *no) {
    if((*no) == NULL) return;
    
    preOrdemAVL(&(*no)->esq);
    preOrdemAVL(&(*no)->dir);
}
void preOrdemPrincipal(PtrNoArvAvl *no) {
    preOrdemAVL(no);
}

int alturaArvoreAVL(PtrNoArvAvl *no) {
    if ((*no) == NULL) return 0;
    else return (*no)->altura;
}
int atualizaAlturaNoAVL(PtrNoArvAvl *esq, PtrNoArvAvl *dir) {
    int ae, ad, ret;
    ae = alturaArvoreAVL(&(*esq));
    ad = alturaArvoreAVL(&(*dir));
    
    if(ae >= ad) ret = ae + 1;
    else ret = ad + 1;
    
    return (ret);
}

void rotacaoSimplesDireita(PtrNoArvAvl *p) {
    PtrNoArvAvl v = (*p)->esq;
    (*p)->esq = v->dir;
    v->dir = (*p);
    (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
    v->altura = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
    (*p) = v;
}
void rotacaoSimplesEsquerda(PtrNoArvAvl *p) {
    PtrNoArvAvl v = (*p)->dir;
    (*p)->dir  = v->esq;
    v->esq = (*p);
    (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
    v->altura = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
    (*p) = v;
}

void rotacaoDuplaDireita(PtrNoArvAvl *p) {
    PtrNoArvAvl u = (*p)->esq;
    PtrNoArvAvl v = u->dir;
    u->dir = v->esq;
    (*p)->esq = v->dir;
    v->esq = u;
    v->dir = (*p);
    (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
    v->altura = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
    u->altura = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
    (*p) = v;
}
void rotacaoDuplaEsquerda(PtrNoArvAvl *p) {
    PtrNoArvAvl u = (*p)->dir;
    PtrNoArvAvl v = u->esq;
    u->esq = v->dir;
    (*p)->dir = v->esq;
    v->esq = (*p);
    v->dir = u;
    (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
    v->altura = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
    u->altura = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
    (*p) = v;
}

void aplicarRotacoes(PtrNoArvAvl *no) {
    int ae, ad, fatorBalanceamento;
    ae = alturaArvoreAVL(&(*no)->esq);
    ad = alturaArvoreAVL(&(*no)->dir);
    fatorBalanceamento = ad - ae;
    PtrNoArvAvl u;
    int aUdir, aUesq;
    if(fatorBalanceamento == -2) {
        u = (*no)->esq;
        aUdir = alturaArvoreAVL(&u->dir);
        aUesq = alturaArvoreAVL(&u->esq);
        
        //Rotacoes p Direita {Simples, Dupla}
        if(aUesq >= aUdir)
            rotacaoSimplesDireita(&(*no));
        else
            rotacaoDuplaDireita(&(*no));
    } else { // == +2
        u = (*no)->dir;
        aUdir = alturaArvoreAVL(&u->dir);
        aUesq = alturaArvoreAVL(&u->esq);
        
        //Rotacoes p Esquerda {Simples, Dupla}
        if(aUdir >= aUesq)
            rotacaoSimplesEsquerda(&(*no));
        else
            rotacaoDuplaEsquerda(&(*no));
    }
}

bool insereArvoreAVL(PtrNoArvAvl *no, char *palavra) {
    if((*no) == NULL) {
        (*no) = malloc(sizeof(no_arv_avl));
        (*no)->esq = NULL;
        (*no)->dir = NULL;
        strcpy((*no)->palavra, palavra);
        (*no)->altura = 1;
        (*no)->n_ocorrencia = 1;
        return true;
    }

    int i;
    bool ret;

    if ((i = strcmp((*no)->palavra, palavra)) == 0) {
        (*no)->n_ocorrencia++;
    } else {
        if (i > 0) ret = insereArvoreAVL(&(*no)->dir, palavra);
        else ret = insereArvoreAVL(&(*no)->esq, palavra);
    }

    // Não inseriu elemento, Não desbalanceou
    if(!ret) return false;
    
    int ad, ae, fatorBalanceamento;
    ad = alturaArvoreAVL(&(*no)->dir);
    ae = alturaArvoreAVL(&(*no)->esq);
    fatorBalanceamento = ad - ae;
    
    if(fatorBalanceamento == 2 || fatorBalanceamento == -2) {
        aplicarRotacoes(&(*no));
    }
    
    (*no)->altura = atualizaAlturaNoAVL(&(*no)->esq, &(*no)->dir);
    return true;
}

void imprimirQuantidadeOcorrenciasArvoreAVL(PtrNoArvAvl *no) {
    if (no) {
        if ((*no)->dir)
            imprimirQuantidadeOcorrenciasArvoreAVL(&(*no)->dir);

        if ((*no)->n_ocorrencia > 1)
            printf("%s: %d\n", (*no)->palavra, (*no)->n_ocorrencia);

        if ((*no)->esq)
            imprimirQuantidadeOcorrenciasArvoreAVL(&(*no)->esq);
    }
}

void removerArvoreAvl(PtrNoArvAvl *raiz){
    if (*raiz) {
        removerArvoreAvl(&(*raiz)->esq);
        removerArvoreAvl(&(*raiz)->dir);
        free(*raiz);
    }
}


// A PARTIR DAQUI É FUNÇÕES PARA ÁRVORE BINÁRIA
void iniciaArvoreBinaria(struct no_arv_b *no){
    no = NULL;
}
struct no_arv_b *insereArvoreBinaria(struct no_arv_b *no, char pal[]) {
    int i;

    if (no == NULL) {
        // Inicio da raíz, não tem sub_arvores
        if ((no = (struct no_arv_b *) malloc(sizeof(*no))) == NULL) 
            errorSemMemoriaParaAlocarESair();
        
        sprintf(no->palavra, "%s", pal);
        no->n_ocorrencia = 1;
        no->dir = NULL;
        no->esq = NULL;
    } else {
        if ((i = strcmp(no->palavra, pal)) == 0) {
            no->n_ocorrencia++;
        } else {
            if (i > 0)
                no->esq = insereArvoreBinaria(no->esq, pal);
            else
                no->dir = insereArvoreBinaria(no->dir, pal);
        }
    }

    return no;
}

void imprimirQuantidadeOcorrenciasArvoreBinaria(struct no_arv_b *no) {
    if (no) {
        imprimirQuantidadeOcorrenciasArvoreBinaria(no->esq);
        
        if (no->n_ocorrencia > 1)
            printf("%s: %d\n", no->palavra, no->n_ocorrencia);
        
        imprimirQuantidadeOcorrenciasArvoreBinaria(no->dir);
    }
}

void removerArvoreBinaria(struct no_arv_b *raiz){
    if (raiz) {
        removerArvoreBinaria(raiz->esq);
        removerArvoreBinaria(raiz->dir);
        free(raiz);
    }
}

// PARA EXECUTAR (em Shell):
// 1º:  gcc [NOME_ARQUIVO_PROGRAMA.c] -o [NOME_ARQUIVO_PROGRAMA]
// 2º:  ./[NOME_ARQUIVO_PROGRAMA] [ARQUIVO_ENTRADA.txt] [ARQUIVO_SAIDA.txt]
int main(int argc, const char * argv[]) {
    if(argc != 3) errorQuantParametrosProgramaESair();

    FILE* entrada = fopen(argv[1], "r");

    // Checar error de abertura de arquivo
    if (!tamanhoArquivo(entrada)) errorArquivoESair();

    int comparar_arv_b = strcmp(argv[2], ARV_B),
        comparar_arv_avl = strcmp(argv[2], ARV_AVL),
        estrutura = 0; // estrutura: ARV_B = 1, ARV_AVL = 2.
    
    if (comparar_arv_b == 0) estrutura = 1; // ARV_B
    else if (comparar_arv_avl == 0) estrutura = 2; // ARV_AVL
    else errorEstruturaArvoreIncorretaESair();

    struct no_arv_b *raiz_b;
    PtrNoArvAvl raiz_avl;

    char palavra[TAM_MAX_PALAVRA], letra;
    int ocorrencias, i,
        quant_b = 0,
        quant_avl = 0;
    
    // Para armazenar o tempo/desempenho de execução dos algoritmos de inserção
    struct timespec tempo_inicio_exec_arv_b, tempo_fim_exec_arv_b,
                    tempo_inicio_exec_arv_avl, tempo_fim_exec_arv_avl;

    iniciaArvoreBinaria(raiz_b);
    iniciaArvoreAVL(&raiz_avl);

    if (entrada) {
        clock_gettime(CLOCK_REALTIME, &tempo_inicio_exec_arv_b);
        while (!feof(entrada) && !ferror(entrada)) {
            i = 0;
            
            while (1) {
                letra = fgetc(entrada);
                if (letra == EOF)
                    break;
                if (letra == ' ' || letra == '\n' || letra == '\t' || letra == '\r')
                    break;
                else {
                    palavra[i] = tolower(letra);
                    i++;
                }
            }

            if (i > 0) {
                palavra[i++] = '\0';

                raiz_b = insereArvoreBinaria(raiz_b, palavra);
                quant_b++;
            }
        }
        clock_gettime(CLOCK_REALTIME, &tempo_fim_exec_arv_b);

        // PARA REINICIAR AO INICIO O ARQUIVO
        rewind(entrada);

        clock_gettime(CLOCK_REALTIME, &tempo_inicio_exec_arv_avl);
        while (!feof(entrada) && !ferror(entrada)) {
            i = 0;
            
            while (1) {
                letra = fgetc(entrada);
                if (letra == EOF)
                    break;
                if (letra == ' ' || letra == '\n' || letra == '\t' || letra == '\r')
                    break;
                else {
                    palavra[i] = tolower(letra);
                    i++;
                }
            }

            if (i > 0) {
                palavra[i++] = '\0';

                preOrdemPrincipal(&raiz_avl);
                insereArvoreAVL(&raiz_avl, palavra);
                preOrdemPrincipal(&raiz_avl);
                quant_avl++;
            }
        }
        clock_gettime(CLOCK_REALTIME, &tempo_fim_exec_arv_avl);
        
        fecha(entrada);
    } else errorArquivoNaoAbriuParaLeitura();

    double tempo_desempenho_arv_b,
            tempo_desempenho_arv_avl;

    tempo_desempenho_arv_b = (tempo_fim_exec_arv_b.tv_sec - tempo_inicio_exec_arv_b.tv_sec) +
                            (tempo_fim_exec_arv_b.tv_nsec - tempo_inicio_exec_arv_b.tv_nsec) / BILLION;
    
    tempo_desempenho_arv_avl = (tempo_fim_exec_arv_avl.tv_sec - tempo_inicio_exec_arv_avl.tv_sec) +
                                (tempo_fim_exec_arv_avl.tv_nsec - tempo_inicio_exec_arv_avl.tv_nsec) / BILLION;

    if (tempo_desempenho_arv_b < tempo_desempenho_arv_avl) {
        printarResultadoComparacaoEDesempenho("arvore binaria:", quant_b, tempo_desempenho_arv_b);
        printarResultadoComparacaoEDesempenho("arvore avl:", quant_avl, tempo_desempenho_arv_avl);
    } else {
        printarResultadoComparacaoEDesempenho("arvore avl:", quant_avl, tempo_desempenho_arv_avl);
        printarResultadoComparacaoEDesempenho("arvore binaria:", quant_b, tempo_desempenho_arv_b);
    }

    printf("\nfrequência das palavras:\n");

    if (estrutura == 1)
        imprimirQuantidadeOcorrenciasArvoreBinaria(raiz_b);
    else if (estrutura == 2)
        imprimirQuantidadeOcorrenciasArvoreAVL(&raiz_avl);
    
    // LIMPA TODO O ARMAZENAMENTO DE MEMÓRIA:
    removerArvoreBinaria(raiz_b);
    removerArvoreAvl(&raiz_avl);
    
    return 0;
}