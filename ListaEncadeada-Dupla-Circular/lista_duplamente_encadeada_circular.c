// PROJETO DE ESTUDO!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LCDE_H_INCLUDED

#define TRUE 1
#define FALSE 0

    
typedef struct mercadoria {
    char nome[80];
    float preco;
} Mercadoria;

typedef Mercadoria Tipo;

typedef struct node {
    Tipo c;
    struct node *prev; // anterior
    struct node *next; // próximo
} Node;

Node *corrente;

int lcdeCreate() {
    corrente = NULL;
    // aqui eh o local para ler de um arquivo. Uma eventual lista preservada em disco ou na internet.
    return TRUE;
}

int lcdeDestroy() {
    while (corrente) {
        Tipo aux;
        lcdeRemove(&aux);
        printf("%s Removido!\n", aux.nome);
    }
    return TRUE;
}

Node *encadeiaNovoElemento(Tipo c, Node *p1, Node *p2) {
    Node *aux;
    aux = (Node *) malloc(sizeof(Node));
    aux->c = c;
    aux->next = aux->prev = NULL;

    // cuidar do encadeamento própriamente dito
    if (!p1) {
        aux->next = aux;
        aux->prev = aux;
        // agora tenho um elemento apontando para ele mesmo (na ida e na volta / interior e próximo)
        return aux;
    }

    // pensar nos demais casos: lista com 1 elemento ou com n elementos
    aux->prev = p1;
    aux->next = p2;
    p1->next = aux;
    p2->prev = aux;

    return aux;
}

int lcdeIN(Tipo c) {
    Node *p1 = NULL, *p2 = NULL;

    //insercao vai ocorrer entre p1 e p2 ou após o corrente
    p1 = corrente;
    if (corrente)
        p2 = corrente->next;

    corrente = encadeiaNovoElemento(c, p1, p2);

    return TRUE;
}

int lcdeOUT(Tipo *c) {
    if (!corrente)
        return FALSE;
    
    *c = corrente->c;
    
    return TRUE;
}

int lcdeRemove(Tipo *c) {
    if (!corrente)
        return FALSE;
    
    Node *aux = corrente;
    *c = aux->c;
    // p1 <-- aux --> p2
    Node *p1 = aux->prev;
    Node *p2 = aux->next;

    // um único elemento ou aux = p1
    if (aux == p2) corrente = NULL;
    else {
        p1->next = p2;
        p2->prev = p1;
        
        // decidimos que o corrente em caso de eliminar
        corrente = p2; 
    }
    
    free(aux);
    
    return TRUE;
}

int lcdeNext() {
    if (!corrente)
        return FALSE;

    corrente = corrente->next;
    return TRUE;
}

int lcdePrevious() {
    if (!corrente)
        return FALSE;

    corrente = corrente->prev;
    return TRUE;
}

int lcdePrint() {
    if (!corrente) {
        printf("\n\nLISTA VÁZIA!\n\n");
        return TRUE;
    }
    
    printf("->");
    
    Node *aux = corrente;
    printf("[%s] -> ", corrente->c.nome);

    aux = corrente->next;
    
    while(aux != corrente) {
        printf("%s -> ", aux->c.nome);
        aux = aux->next;
    }
    
    return TRUE;
}



void menu() {
    printf("i - insere mercadoria\n");
    printf("d - delete corrente\n");
    printf("p - próxima\n");
    printf("a - anterior\n");
    printf("s - sair\n");
    
    lcdePrint();
}

void leMercadoria() {
    Mercadoria m;

    printf("\nDigite o nome da mercadoria: ");
    scanf("%s", m.nome);

    printf("\nDigite o preço: ");
    scanf("%f", &m.preco);
    
    lcdeIN(m);
}

int main() {
    lcdeCreate();

    printf("LISTA CIRCULAR MERCADORIAS\n\n");
    
    while (TRUE) {
        menu();
        
        char letra;

        scanf("%s", &letra);
        
        if (letra == 's') break;
        else if (letra == 'i') {
            leMercadoria();
        } else if (letra == 'p') {
            lcdeNext();
        } else if (letra == 'a') {
            lcdePrevious();
        } else if (letra == 'd') {
            Tipo c;
            
            if(lcdeRemove(&c))
                printf("\nRemovi %s\n", c.nome);
            else
                printf("\nNada a fazer\n");
        }
    }

    lcdeDestroy();
    
    return 0;
}


typedef struct nodo {
    int inf;
    struct nodo *ant;
    struct nodo *prox;
} NODO;

typedef NODO *LISTA_CIR_DUP_ENC_NC;

void cria_lista(LISTA_CIR_DUP_ENC_NC *);
int eh_vazia(LISTA_CIR_DUP_ENC_NC);
int tam(LISTA_CIR_DUP_ENC_NC);
void ins(LISTA_CIR_DUP_ENC_NC, int, int);
int recup(LISTA_CIR_DUP_ENC_NC, int);
void ret(LISTA_CIR_DUP_ENC_NC, int);
void destruir(LISTA_CIR_DUP_ENC_NC);
void inverter_lista(LISTA_CIR_DUP_ENC_NC);

void cria_lista(LISTA_CIR_DUP_ENC_NC *p1) {
    *p1 =  malloc(sizeof(NODO));

    if (!(*p1)) {
        printf("\nERROR! Memória insuficiente!\n");
        exit(-1);
    }

    (*p1)->inf = 0;
    (*p1)->ant = (*p1)->prox = *p1;
}

int eh_vazia(LISTA_CIR_DUP_ENC_NC lista) {
    return (lista->inf == 0);
}

int tam(LISTA_CIR_DUP_ENC_NC lista) {
    return (lista->inf);
}

void ins(LISTA_CIR_DUP_ENC_NC lista, int v, int k) {
    LISTA_CIR_DUP_ENC_NC aux, novo;

    if (k < 1 || k > tam(lista) + 1) {
        printf("\nERROR! Posição inválida para inserção.\n");
        exit(-1);
    }

    novo = (LISTA_CIR_DUP_ENC_NC) malloc(sizeof(NODO));

    if (!novo) {
        printf("\nERROR! Memória insuficiente!");
        exit(-1);
    }

    novo->inf = v;
    for (aux = lista; k > 1; aux = aux->prox, k--);

    novo->prox = aux->prox;
    novo->ant = aux;
    aux->prox = novo;
    novo->prox->ant = novo;
    lista->inf++;
}

int recup(LISTA_CIR_DUP_ENC_NC lista, int k) {
    if (k < 1 || k > tam(lista)) {
        printf("\nERROR! Consulta inválida.\n");
        exit(-1);
    }

    for (; k > 0; k--)
        lista = lista->prox;

    return (lista->inf);
}

void ret(LISTA_CIR_DUP_ENC_NC lista, int k) {
    if (k < lista || k > tam(lista)) {
        printf("\nERROR! Posição inválida para retirada!\n");
        exit(-1);
    }

    lista->inf--;
    for (; k > 0; k--, lista = lista->prox);
    lista->ant->prox = lista->prox;
    lista->prox->ant = lista->ant;
    free(lista);
}

void destruir(LISTA_CIR_DUP_ENC_NC lista) {
    LISTA_CIR_DUP_ENC_NC aux;
    int tam = lista->inf;

    do {
        aux = lista;
        lista = lista->prox;
        free(aux);
    } while (tam--);
}

void inverter_lista(LISTA_CIR_DUP_ENC_NC lista) {
    int i = tam(lista);

    if (i > 1) {
        NODO *aux;
        
        for (i++; i; lista = lista->ant, i--) {
            aux = lista->ant;
            lista->ant = lista->prox;
            lista->prox = aux;
        }
    }
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