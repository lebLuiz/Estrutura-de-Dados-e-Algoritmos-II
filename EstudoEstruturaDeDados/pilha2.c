#include <stdio.h>
#include <stdlib.h>

// Estrutura de dados dinâmica

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    char nome[50];
    Data data;
} Pessoa;

typedef struct no {
    Pessoa p;
    struct no *proximo;
} No;

typedef struct {
    No *topo;
    int tam;
} Pilha;

void criarPilha(Pilha *pilha) {
    pilha->topo = NULL;
    pilha->tam = 0;
}

Pessoa lerPessoa() {
    Pessoa p;
        
    printf("\nDigite nome e data de nascimento dd mm aaaa:\n");
    scanf("%49[^\n]%d%d%d", p.nome, &p.data.dia, &p.data.mes, &p.data.ano);
    
    return p;
}

void imprimirPessoa(Pessoa p) {
    printf("\nNome: %s\nData: %2d/%2d/%4d\n", p.nome, p.data.dia, p.data.mes, p.data.ano);
}

// FUNÇÃO PARA A OPERAÇÃO PUSH (empilhar)
void push(Pilha *pilha) {
    No *novo = malloc(sizeof(No));
    
    if (novo) {
        novo->p = lerPessoa();
        novo->proximo = pilha->topo;
        pilha->topo = novo;
        pilha->tam++;
    } else printf("\nErro ao alocar memoria");
}

No *pop(Pilha *pilha) {
    if (pilha->topo) {
        No *remover = pilha->topo;
        pilha->topo = remover->proximo;
        pilha->tam--;
        return remover;
    } else printf("\nPilha vazia");
    
    return NULL;
}

void imprimirPilha(Pilha *pilha) {
    No *aux = pilha->topo;
    printf("\n--------------PILHA Tam: %d--------------\n", pilha->tam);
    while (aux) {
        imprimirPessoa(aux->p);
        aux = aux->proximo;
    }
    printf("\n--------------FIM PILHA--------------\n");
}

int main() {
    No *remover;
    Pilha pilha;
    int opcao;

    criarPilha(&pilha);
    
    do {
        printf("\n0 - Sair\n1 - Empilhar\n2 - Desempilhar\n3 - Imprimir\n");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                push(&pilha);
                break;
            case 2:
                remover = pop(&pilha);
                if (remover != NULL) {
                    printf("\nElemento removido com sucesso!\n");
                    imprimirPessoa(remover->p);

                    free(remover);
                } else
                    printf("\nSem No a remover.\n");
                break;
            case 3:
                imprimirPilha(&pilha);
                break;
            default:
                if (opcao != 0)
                    printf("\nOpcao invalida!!!\n");
        }
    } while (opcao != 0);

    return 0;
}