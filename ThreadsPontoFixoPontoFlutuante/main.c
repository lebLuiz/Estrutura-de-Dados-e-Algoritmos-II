// PROJETO DE ESTUDO!

// // EX 1

// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdbool.h>

// #define NUM_THREADS 10
// #define SEGUNDOS 5
// #define TAM_CARACTERES_NOME 50

// bool sairThread(char nome_thread[50]) {
//     return strcmp(nome_thread, "Sair") == 0 ? true : false;
// }

// void encerrarThread() {
//     pthread_exit(NULL);
//     exit(-1);
// }

// void verificarSaidaThread(char nome_thread[50]) {
//     if (sairThread(nome_thread)) {
//         printf("Estou encerrando...");
//         encerrarThread();
//     }
// }

// void copiarTexto(char texto_recebe[TAM_CARACTERES_NOME], char texto_para_copia[TAM_CARACTERES_NOME]) {
//     for (int i = 0; texto_para_copia[i] != '\0'; i++) {
//         texto_recebe[i] = texto_para_copia[i];
//     }
// }

// // CADA THREAD VAI EXECUTAR ESSA FUNÇÃO
// void chamarThread(char nome_thread[TAM_CARACTERES_NOME]) {
//     char copia_nome[TAM_CARACTERES_NOME];
//     copiarTexto(copia_nome, nome_thread);

//     for (int i = 1; i <= NUM_THREADS && !sairThread(nome_thread); i++) {
//         verificarSaidaThread(nome_thread);
//         sleep(SEGUNDOS);
//         printf("%d - Ola %s\n", i, copia_nome);
//     }

//     printf("Tchau %s!\n", copia_nome);
//     encerrarThread(); // ENCERRA ESTA THREAD
// }

// // THREAD "main" (VAI CRIAR AS DEMAIS THREADS)
// int main(int argc, char *argv[]) {
//     long status;
//     int count = 1;
    
//     char nome_thread[TAM_CARACTERES_NOME];

//     do {
//         scanf(" %[^\n]s", nome_thread);
        
//         if (sairThread(nome_thread)) printf("Vai encerrar...\n");
//         else printf("CRIANDO THREAD %d\n", count);
        
//         pthread_t thread;
        
//         status = pthread_create(&thread, NULL, chamarThread, nome_thread);
        
//         // OCORREU UM ERRO
//         if (status) {
//             perror("pthread_create");
//             exit(-1);
//         }
        
//         count++;
//     } while (strcmp(nome_thread, "Sair") != 0 && count < 10);
    
//     // ENCERRA A THREAD "main"
//     encerrarThread();
    
//     return 0;
// }



// // EX 2

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int y = 0;

void * threadBody() {
    int x = 0;
    sleep(10);
    printf("x: %d, y: %d\n", ++x, ++y);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    pthread_t tA, tB, tC;

    pthread_create(&tA, NULL, threadBody, NULL);
    pthread_create(&tB, NULL, threadBody, NULL);
    // sleep(1);
    pthread_join(tA, (void **) tA);
    pthread_join(tB, (void **) tB);
    // sleep(1);
    pthread_create(&tC, NULL, threadBody, NULL);
    pthread_join(tC, (void **) tC);
    
    return 0;
}