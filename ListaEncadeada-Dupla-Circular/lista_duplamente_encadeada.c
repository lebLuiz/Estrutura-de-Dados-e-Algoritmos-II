// PROJETO DE ESTUDO!

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *anterior;
    struct no *proximo;
} No;

void printarErroAlocarMemoria() {
    printf("Erro ao alocar memória!\n");
}

void inserirNoInicio(No **lista, int num) {
    No *novo = malloc(sizeof(No));

    if (novo) {
        novo->valor = num;
        novo->proximo = *lista;
        novo->anterior = NULL;

        if (*lista)
            (*lista)->anterior = novo;
        
        *lista = novo;
    } else printarErroAlocarMemoria();
}

void inserirNoFim(No **lista, int num) {
    No *aux, *novo = malloc(sizeof(No));

    if (novo) {
        novo->valor = num;
        novo->proximo = NULL;

        // é o primeiro?
        if (*lista == NULL) {
            *lista = novo;
            novo->anterior = NULL;
        } else {
            aux = *lista;
            while (aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
            novo->anterior = aux;
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
            novo->anterior = NULL;
            *lista = novo;
        } else {
            aux = *lista;
            
            while(aux->valor != ant && aux->proximo)
                aux = aux->proximo;
            
            novo->proximo = aux->proximo;

            if (aux->proximo)
                aux->proximo->anterior = novo;
            
            novo->anterior = aux;
            aux->proximo = novo;
        }
    } else printarErroAlocarMemoria();
}

void inserirOrdenado(No **lista, int num) {
    No *aux, *novo = malloc(sizeof(No));

    if (novo) {
        novo->valor = num;

        // a lista está vazia?
        if (*lista == NULL) {
            novo->proximo = NULL;
            novo->anterior = NULL;
            
            *lista = novo;
        } // é o menor?
        else if (novo->valor < (*lista)->valor) {
            novo->proximo = *lista;
            (*lista)->anterior = novo;
            *lista = novo;
        } else {
            aux = *lista;

            while(aux->proximo && novo->valor > aux->proximo->valor)
                aux = aux->proximo;

            novo->proximo = aux->proximo;

            if (aux->proximo)
                aux->proximo->anterior = novo;
                
            novo->anterior = aux;
            aux->proximo = novo;
        }
    } else printarErroAlocarMemoria();
}

No * remover(No **lista, int num) {
    No *aux, *remover = NULL;

    if (*lista) {
        if ((*lista)->valor == num) {
            remover = *lista;
            *lista = remover->proximo;

            if (*lista)
                (*lista)->anterior = NULL;
        } else {
            aux = *lista;
            while(aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if (aux->proximo) {
                remover = aux->proximo;
                aux->proximo = remover->proximo;

                if (aux->proximo)
                    aux->proximo->anterior = aux;
            }
        }
    }

    return remover;
}

No * buscar(No **lista, int num) {
    No *aux, *no = NULL;

    aux = *lista;
    while(aux && aux->valor != num)
        aux = aux->proximo;
    if (aux)
        no = aux;

    return no;
}

void imprimir(No *no) {
    printf("\n\tLista: ");
    while(no) {
        printf("%d ", no->valor);
        no = no->proximo;
    }
    printf("\n\n");
}

No* ultimoNo(No **lista) {
    No *aux = *lista;

    while(aux->proximo)
        aux = aux->proximo;

    return aux;
}

void imprimirContrario(No *no) {
    printf("\n\tLista: ");
    while(no) {
        printf("%d ", no->valor);
        no = no->anterior;
    }
    printf("\n\n");
}

int main() {
    int opcao, valor, anterior;
    No *removido, *lista = NULL;
    
    do {
        printf("\n\t0 - Sair\n\t1 - Inserir no Inicio\n\t2 - Inserir no Fim\n\t3 - Inserir no Meio\n\t4 - Inserir Ordenado\n\t5 - Remover\n\t6 - Imprimir\n\t7 - Buscar\n\t8 - Imprimir Contrário\n");
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
                printf("Digite um valor: ");
                scanf("%d", &valor);
                
                inserirOrdenado(&lista, valor);
                break;
            case 5:
                printf("Digite um valor a ser removido: ");
                scanf("%d", &valor);
                removido = remover(&lista, valor);

                if (removido) {
                    printf("Elemento a ser removido: %d\n", removido->valor);
                    free(removido);
                } else printf("Elemento inesistente!\n");
                break;
            case 6:
                imprimir(lista);
                break;
            case 7:
                printf("Digite um valor a ser buscado: ");
                scanf("%d", &valor);
                removido = buscar(&lista, valor);
                
                if (removido)
                    printf("Elemento encontrado: %d\n", removido->valor);
                else
                    printf("Elemento não encontrado!\n");
                break;
             case 8:
                imprimirContrario(ultimoNo(&lista));
                break;
            default:
                if (opcao != 0)
                    printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
    
    return 0;
}