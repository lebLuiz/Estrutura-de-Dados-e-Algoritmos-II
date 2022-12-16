// #include <stdio.h>
// #include <stdlib.h>

// // Estrutura de dados dinâmica

// typedef struct {
//   int dia, mes, ano;
// } Data;

// typedef struct {
//   char nome[50];
//   Data data;
// } Pessoa;

// typedef struct no {
//   Pessoa p;
//   struct no *proximo;
// } No;

// Pessoa lerPessoa() {
//   Pessoa p;

//   printf("\nDigite nome e data de nascimento dd mm aaaa:\n");
//   scanf("%49[^\n]%d%d%d", p.nome, &p.data.dia, &p.data.mes, &p.data.ano);

//   return p;
// }

// void imprimirPessoa(Pessoa p) {
//   printf("\nNome: %s\nData: %2d/%2d/%4d\n", p.nome, p.data.dia, p.data.mes,
//          p.data.ano);
// }

// // FUNÇÃO PARA A OPERAÇÃO PUSH (empilhar)
// No *push(No *topo) {
//   No *novo = malloc(sizeof(No));

//   if (novo) {
//     novo->p = lerPessoa();
//     novo->proximo = topo;
//     return novo;
//   } else
//     printf("\nErro ao alocar memoria");

//   return NULL;
// }

// No *pop(No **topo) {
//   if (*topo != NULL) {
//     No *remover = *topo;
//     *topo = remover->proximo;
//     return remover;
//   } else
//     printf("\nPilha vazia");
//   return NULL;
// }

// void imprimirPilha(No *topo) {
//   printf("\n--------------PILHA--------------\n");
//   while (topo) {
//     imprimirPessoa(topo->p);
//     topo = topo->proximo;
//   }
//   printf("\n--------------FIM PILHA--------------\n");
// }

// int main() {

//   No *remover, *topo = NULL;
//   int opcao;

//   do {
//     printf("\n0 - Sair\n1 - Empilhar\n2 - Desempilhar\n3 - Imprimir\n");
//     scanf("%d", &opcao);
//     getchar();

//     switch (opcao) {
//     case 1:
//       topo = push(topo);
//       break;
//     case 2:
//       remover = pop(&topo);
//       if (remover != NULL) {
//         printf("\nElemento removido com sucesso!\n");
//         imprimirPessoa(remover->p);
//       } else
//         printf("\nSem No a remover.\n");
//       break;
//     case 3:
//       imprimirPilha(topo);
//       break;
//     default:
//       if (opcao != 0)
//         printf("\nOpcao invalida!!!\n");
//     }
//   } while (opcao != 0);

//   return 0;
// }