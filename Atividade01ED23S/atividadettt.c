// IMPORT'S:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// DEFINE'S:
#define TRUE 1
#define FALSE 0
#define SEPARADOR ','
#define INICIO_VALOR '{'
#define TERMINO_VALOR '}'
#define TAMANHO_CARACTERS_LINHA_ARQUIVO 100
#define BUSCAR_CRESCENTE 1
#define BUSCAR_DECRESCENTE 2
#define BUSCAR_PACIENTE 3


// STRUCT'S
typedef struct paciente_auxiliar {
    char codigo[4];
    char nome[75];
    char sexo;
    char idade[6];
    char peso[6];
    char altura[6];
    char telefone[15];
} PacienteAuxiliar;

typedef struct paciente {
    int codigo;
    char nome[75];
    char sexo;
    int idade;
    double peso;
    double altura;
    char telefone[15];
} Paciente;

// VARIAVEIS:
char TEXTO_ARQUIVO_INVALIDO[] = {"Arquivo Inválido!"};
char TEXTO_ELEMENTO_N_ENCONTRADO[] = {"Elemento não encontrado!"};


typedef struct NoLista {
    Paciente paciente;
    struct NoLista* proximo;
    struct NoLista* anterior;
} NoLista;

typedef struct {
    struct NoLista* inicio;
    struct NoLista* fim;

    int qtde_pacientes;
} ListaPacientes;


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

// inicialização
void iniciaListaPacientes(ListaPacientes *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtde_pacientes = 0;
}

void printListaCrescente(ListaPacientes* lista, FILE *arquivo) {
    NoLista *ptr_no_lista = lista->fim;
    
    for (int i = lista->qtde_pacientes; i > 0; i--) {
        fprintf(arquivo, "%c", INICIO_VALOR);
        
        fprintf(arquivo, "%d", ptr_no_lista->paciente.codigo);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%s", ptr_no_lista->paciente.nome);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%c", ptr_no_lista->paciente.sexo);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%d", ptr_no_lista->paciente.idade);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%.2f", ptr_no_lista->paciente.peso);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%.2f", ptr_no_lista->paciente.altura);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%s", ptr_no_lista->paciente.telefone);

        fprintf(arquivo, "%c", TERMINO_VALOR);
        
        if (i > 1)
            fprintf(arquivo, "%c", '\n');
        
        ptr_no_lista = ptr_no_lista->anterior;
    }
}

void printListaDecrescente(ListaPacientes* lista, FILE *arquivo) {
    NoLista *ptr_no_lista = lista->inicio;
    
    for (int i = 0; i < lista->qtde_pacientes; i++) {
        fprintf(arquivo, "%c", INICIO_VALOR);
        
        fprintf(arquivo, "%d", ptr_no_lista->paciente.codigo);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%s", ptr_no_lista->paciente.nome);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%c", ptr_no_lista->paciente.sexo);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%d", ptr_no_lista->paciente.idade);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%.2f", ptr_no_lista->paciente.peso);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%.2f", ptr_no_lista->paciente.altura);
        fprintf(arquivo, "%c", SEPARADOR);

        fprintf(arquivo, "%s", ptr_no_lista->paciente.telefone);

        fprintf(arquivo, "%c", TERMINO_VALOR);
        
        if (i < (lista->qtde_pacientes) - 1)
            fprintf(arquivo, "%c", '\n');
        
        ptr_no_lista = ptr_no_lista->proximo;
    }
}

void printPaciente(ListaPacientes* lista, int codigo_busca, FILE *arquivo) {
    NoLista *ptr_no_lista = lista->inicio;
    int encontrou_paciente = 0;
    
    for (int i = 0; i < lista->qtde_pacientes; i++) {
        if (ptr_no_lista->paciente.codigo != codigo_busca) 
            ptr_no_lista = ptr_no_lista->proximo;
        else {
            encontrou_paciente = 1;

            fprintf(arquivo, "%c", INICIO_VALOR);
        
            fprintf(arquivo, "%d", ptr_no_lista->paciente.codigo);
            fprintf(arquivo, "%c", SEPARADOR);
    
            fprintf(arquivo, "%s", ptr_no_lista->paciente.nome);
            fprintf(arquivo, "%c", SEPARADOR);
    
            fprintf(arquivo, "%c", ptr_no_lista->paciente.sexo);
            fprintf(arquivo, "%c", SEPARADOR);
    
            fprintf(arquivo, "%d", ptr_no_lista->paciente.idade);
            fprintf(arquivo, "%c", SEPARADOR);
    
            fprintf(arquivo, "%.2f", ptr_no_lista->paciente.peso);
            fprintf(arquivo, "%c", SEPARADOR);
    
            fprintf(arquivo, "%.2f", ptr_no_lista->paciente.altura);
            fprintf(arquivo, "%c", SEPARADOR);
    
            fprintf(arquivo, "%s", ptr_no_lista->paciente.telefone);
    
            fprintf(arquivo, "%c", TERMINO_VALOR);
            
            break;
        }
    }

    if (!encontrou_paciente)
        fprintf(arquivo, "%s", TEXTO_ELEMENTO_N_ENCONTRADO);
}

void inserirPacienteListaDecrescente(ListaPacientes *lista, Paciente paciente) {
    NoLista *novo = (NoLista *) malloc(sizeof(NoLista));
    novo->paciente = paciente;

    // Inserindo paciente em lista vazia
    if (lista->qtde_pacientes == 0) {
        lista->inicio = novo;
        lista->fim = novo;
        novo->anterior = novo;
        novo->proximo = novo;
        lista->qtde_pacientes = 1;
        return;
    }

    // Inserindo paciente antes do primeiro
    if (paciente.codigo > lista->inicio->paciente.codigo) {
        lista->inicio->anterior = novo;
        lista->fim->proximo = novo;
        novo->anterior = lista->fim;
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        lista->qtde_pacientes++;
        return;
    }

    // Inserindo paciente depois do ultimo
    if (paciente.codigo < lista->fim->paciente.codigo) {
        lista->fim->proximo = novo;
        lista->inicio->anterior = novo;
        novo->anterior = lista->fim;
        novo->proximo = lista->inicio;
        lista->fim = novo;
        lista->qtde_pacientes++;
        return;
    }

    // Inserindo paciente intermediario
    NoLista* ptr_no_lista = lista->inicio;
    for (int i = 0; i < lista->qtde_pacientes; i++) {
        if (ptr_no_lista->paciente.codigo < paciente.codigo)
            break;
        ptr_no_lista = ptr_no_lista->proximo;
    }

    ptr_no_lista->anterior->proximo = novo;
    
    novo->anterior = ptr_no_lista->anterior;
    novo->proximo = ptr_no_lista;
    
    ptr_no_lista->anterior = novo;
    
    lista->qtde_pacientes++;
}

int removerPacienteNoLista(Paciente *paciente, ListaPacientes *lista) {
    if (!lista->inicio) return FALSE;
    
    NoLista *aux_no_lista_paciente = lista->inicio;
    *paciente = aux_no_lista_paciente->paciente;
    
    // p1 <-- aux --> p2
    NoLista *p1 = aux_no_lista_paciente->anterior;
    NoLista *p2 = aux_no_lista_paciente->proximo;

    // Um único elemento ou aux_no_lista_paciente = p1
    if (aux_no_lista_paciente == p2) aux_no_lista_paciente = NULL;
    else {
        p1->proximo = p2;
        p2->anterior = p1;
        
        lista->inicio = p2;
    }

    lista->qtde_pacientes--;
    free(aux_no_lista_paciente);
    return TRUE;
};

void destruirListaPacientes(ListaPacientes *lista) {
    while (lista->qtde_pacientes > 0) {
        Paciente aux_paciente;
        removerPacienteNoLista(&aux_paciente, lista);
    }
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

    int count_numeros_finais = 1,
        operacao = 0, busca = -1000;

  	char letra, linhas_arq[TAMANHO_CARACTERS_LINHA_ARQUIVO];

    ListaPacientes lista;
    linhas_arq[0] = '\0';

    iniciaListaPacientes(&lista);

    // fgets vai capturando linha por linha no arquivo
  	while (fgets(linhas_arq, sizeof(linhas_arq), entrada)) {
        // Verifica se é as linhas de operacao, e a de busca (caso seja operação 3)
        if ((linhas_arq[0] != INICIO_VALOR && linhas_arq[1] != SEPARADOR) &&
            atoi(linhas_arq)) {
            if (count_numeros_finais == 1)
                operacao = atoi(linhas_arq);
            else if (count_numeros_finais == 2)
                busca = atoi(linhas_arq);

            count_numeros_finais++;
        } else if (linhas_arq[0] != INICIO_VALOR || linhas_arq[1] == SEPARADOR) {
            arquivoInvalido(saida);
        } else {
            int quant_separador_valores = 0;
            Paciente paciente;
            
            // 1º - Captura quantidade de separadores(,)
            for (int i = 1; linhas_arq[i] != TERMINO_VALOR && linhas_arq[i] != '\n'; i++) {
                if (linhas_arq[i] == SEPARADOR)
                    quant_separador_valores++;
            }
    
            // 2º - Quantidade de separadores tem que ser: 6
            if (quant_separador_valores != 6)
                arquivoInvalido(saida);
            
            // 3º - Começa tratar valores da linha (cada paciente)
            char copia_linha[TAMANHO_CARACTERS_LINHA_ARQUIVO];
            strcpy(copia_linha, linhas_arq);

            int j = 0;
            for (int i = 0; i < (strlen(linhas_arq) - 1); i++) {
                if (linhas_arq[i] != INICIO_VALOR && linhas_arq[i] != TERMINO_VALOR) {
                    copia_linha[j] = linhas_arq[i];
                    j++;
                }
            }

            // Removendo "}"
            for (int i = 0; copia_linha[i] != '\n'; i++) {
                if (copia_linha[i] == TERMINO_VALOR)
                    copia_linha[i] = '\0';
            }

            int cont_separador = 1;

            PacienteAuxiliar paciente_aux;
            
            // Garantir iniciação valores zerados
            paciente_aux.codigo[0] = '\0';
            paciente_aux.nome[0] = '\0';
            paciente_aux.sexo = '\0';
            paciente_aux.idade[0] = '\0';
            paciente_aux.peso[0] = '\0';
            paciente_aux.altura[0] = '\0';
            paciente_aux.telefone[0] = '\0';

            paciente.codigo = 0;
            paciente.nome[0] = '\0';
            paciente.sexo = '\0';
            paciente.idade = 0;
            paciente.peso = 0;
            paciente.altura = 0;
            paciente.telefone[0] = '\0';

            // 4º - Começa criar os Paciente e alocar na Lista
            int jk = 0;
            
            for (int i = 0; copia_linha[i] != '\0' && copia_linha[i] != '\n'; i++) {
                int caracter_igual_sepador = copia_linha[i] == SEPARADOR ? TRUE : FALSE;
                
                if (caracter_igual_sepador) 
                    cont_separador++;
                
                if (cont_separador == 1 && !caracter_igual_sepador) {
                    strncat(paciente_aux.codigo, &copia_linha[i], 1);
                } else if (cont_separador == 2 && !caracter_igual_sepador) {
                    strncat(paciente_aux.nome, &copia_linha[i], 1);
                } else if (cont_separador == 3 && !caracter_igual_sepador) {
                    paciente_aux.sexo = copia_linha[i];
                } else if (cont_separador == 4 && !caracter_igual_sepador) {
                    strncat(paciente_aux.idade, &copia_linha[i], 1);
                } else if (cont_separador == 5 && !caracter_igual_sepador) {
                    strncat(paciente_aux.peso, &copia_linha[i], 1);
                } else if (cont_separador == 6 && !caracter_igual_sepador) {
                    strncat(paciente_aux.altura, &copia_linha[i], 1);
                } else if (cont_separador == 7 && !caracter_igual_sepador) {
                    paciente_aux.telefone[jk] = copia_linha[i];
                    
                    jk++;
                }
            }
            jk = 0;

            // Captura valores do paciente auxiliar e transforma para o paciente
            paciente.codigo = atoi(paciente_aux.codigo);
            strcpy(paciente.nome, paciente_aux.nome);
            paciente.sexo = paciente_aux.sexo;
            paciente.idade = atoi(paciente_aux.idade);
            paciente.peso = atof(paciente_aux.peso);
            paciente.altura = atof(paciente_aux.altura);
            for (int i = 0; paciente_aux.telefone[i] != '\0' && paciente_aux.telefone[i] != SEPARADOR; i++) {
                paciente.telefone[i] = paciente_aux.telefone[i];
            }

            inserirPacienteListaDecrescente(&lista, paciente);
            
            // LIMPANDO valores novamente:
            paciente_aux.codigo[0] = '\0';
            paciente_aux.nome[0] = '\0';
            paciente_aux.sexo = '\0';
            paciente_aux.idade[0] = '\0';
            paciente_aux.peso[0] = '\0';
            paciente_aux.altura[0] = '\0';
            paciente_aux.telefone[0] = '\0';

            paciente.codigo = 0;
            paciente.nome[0] = '\0';
            paciente.sexo = '\0';
            paciente.idade = 0;
            paciente.peso = 0;
            paciente.altura = 0;
            paciente.telefone[0] = '\0';

            // Limpando string copia_linha, linhas_arq, e reset;
            memset(copia_linha, '\0', TAMANHO_CARACTERS_LINHA_ARQUIVO);
            memset(linhas_arq, '\0', TAMANHO_CARACTERS_LINHA_ARQUIVO);
            fflush(stdout);
        }
    }

    if (operacao == BUSCAR_CRESCENTE) {
        printListaCrescente(&lista, saida);
    } else if (operacao == BUSCAR_DECRESCENTE) {
        printListaDecrescente(&lista, saida);
    } else if (operacao == BUSCAR_PACIENTE) {
        printPaciente(&lista, busca, saida);
    }
    
    fclose(entrada);
    fclose(saida);
    destruirListaPacientes(&lista);
    
    return 0;
}