// PROJETO DE ESTUDO!

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *proximo;
} No;

void printarErroAlocarMemoria() {
    printf("Erro ao alocar memória!\n");
}

void inserirNoInicio(No **lista, int num) {
    No *novo = malloc(sizeof(No));

    if (novo) {
        novo->valor = num;
        novo->proximo = *lista;

        *lista = novo;
    } else printarErroAlocarMemoria();
}

void inserirNoFim(No **lista, int num) {
    No *aux, *novo = malloc(sizeof(No));

    if (novo) {
        novo->valor = num;
        novo->proximo = NULL;

        // é o primeiro?
        if (*lista == NULL)
            *lista = novo;
        else {
            aux = *lista;
            while (aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
        }
    } else printarErroAlocarMemoria();
}

void inserirNoMeio(No **lista, int num, int ant) {
    No *aux, *novo = malloc(sizeof(No));

    if (novo) {
        novo->valor = num;

        // é o primeiro?
        if (*lista == NULL) {
            novo->proximo = NULL;
            *lista = novo;
        } else {
            aux = *lista;
            while(aux->valor != ant && aux->proximo)
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    } else printarErroAlocarMemoria();
}

void imprimir(No *no) {
    printf("\n\tLista: ");
    while(no) {
        printf("%d ", no->valor);
        no = no->proximo;
    }
    printf("\n\n");
}

int main() {
    int opcao, valor, anterior;
    No *lista = NULL;
    
    do {
        printf("\n\t0 - Sair\n\t1 - Inserir no Inicio\n\t2 - Inserir no Fim\n\t3 - Inserir no Meio\n\t4 - Imprimir\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite um valor: ");
                scanf("%d", &valor);
                
                inserirNoInicio(&lista, valor);
                break;
            case 2:
                printf("Digite um valor: ");
                scanf("%d", &valor);
                
                inserirNoFim(&lista, valor);
                break;
            case 3:
                printf("Digite um valor e o valor de referência: ");
                scanf("%d%d", &valor, &anterior);
                
                inserirNoMeio(&lista, valor, anterior);
                break;
            case 4:
                imprimir(lista);
                break;
            default:
                if (opcao != 0)
                    printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
    
    return 0;
}