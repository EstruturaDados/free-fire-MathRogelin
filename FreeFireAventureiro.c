#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa compara duas formas de gerenciar a mochila: vetor e lista encadeada.
// Ele introduz busca binária, ordenação e análise de desempenho (tempo e comparações).

#define MAX_ITENS 10

// Estrutura que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura para a lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Vetor e variáveis de controle
Item mochila[MAX_ITENS];
int totalItens = 0;
long comparacoesSequencial = 0;
long comparacoesBinaria = 0;

// Funções do vetor
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void ordenarVetor();
void buscarSequencialVetor();
void buscarBinariaVetor();

// Funções da lista encadeada
No* inserirItemLista(No* inicio);
No* removerItemLista(No* inicio);
void listarItensLista(No* inicio);
void buscarItemLista(No* inicio);

// Funções auxiliares
void menuVetor();
void menuLista();
void limparEntrada();


// ===================== FUNÇÕES VETOR =====================

void inserirItemVetor() {
    if (totalItens >= MAX_ITENS) {
        printf("\nA mochila está cheia!\n");
        return;
    }

    Item novoItem;
    printf("\n--- Cadastro de Item (Vetor) ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novoItem.nome);
    printf("Tipo (arma, munição, cura...): ");
    scanf(" %[^\n]", novoItem.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("\nItem adicionado com sucesso!\n");
}

void removerItemVetor() {
    if (totalItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nome[30];
    printf("\n--- Remover Item (Vetor) ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("\nItem removido com sucesso!\n");
            return;
        }
    }
    printf("\nItem não encontrado.\n");
}

void listarItensVetor() {
    printf("\n--- Itens na Mochila (Vetor) ---\n");

    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void ordenarVetor() {
    printf("\n--- Ordenando Itens (Bubble Sort) ---\n");
    int i, j;
    Item temp;
    clock_t inicio = clock();

    for (i = 0; i < totalItens - 1; i++) {
        for (j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Itens ordenados por nome em %.6f segundos.\n", tempo);
}

void buscarSequencialVetor() {
    if (totalItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nome[30];
    printf("\n--- Busca Sequencial (Vetor) ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nome);

    comparacoesSequencial = 0;
    clock_t inicio = clock();

    for (int i = 0; i < totalItens; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("\nItem encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Comparações: %ld | Tempo: %.6f s\n", comparacoesSequencial, tempo);
            return;
        }
    }

    printf("\nItem não encontrado. Comparações: %ld\n", comparacoesSequencial);
}

void buscarBinariaVetor() {
    if (totalItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    ordenarVetor();
    char nome[30];
    printf("\n--- Busca Binária (Vetor) ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nome);

    int inicio = 0, fim = totalItens - 1, meio;
    comparacoesBinaria = 0;
    clock_t t1 = clock();

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            clock_t t2 = clock();
            double tempo = (double)(t2 - t1) / CLOCKS_PER_SEC;
            printf("\nItem encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            printf("Comparações: %ld | Tempo: %.6f s\n", comparacoesBinaria, tempo);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\nItem não encontrado. Comparações: %ld\n", comparacoesBinaria);
}


// ===================== FUNÇÕES LISTA ENCADEADA =====================

No* inserirItemLista(No* inicio) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("\nErro de memória!\n");
        return inicio;
    }

    printf("\n--- Cadastro de Item (Lista) ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = inicio;

    printf("\nItem adicionado com sucesso!\n");
    return novo;
}

No* removerItemLista(No* inicio) {
    if (inicio == NULL) {
        printf("\nA mochila está vazia!\n");
        return inicio;
    }

    char nome[30];
    printf("\n--- Remover Item (Lista) ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nome);

    No* atual = inicio;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("\nItem removido com sucesso!\n");
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("\nItem não encontrado.\n");
    return inicio;
}

void listarItensLista(No* inicio) {
    printf("\n--- Itens na Mochila (Lista Encadeada) ---\n");
    if (inicio == NULL) {
        printf("A mochila está vazia.\n");
        return;
    }

    No* atual = inicio;
    int i = 1;
    while (atual != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        i++;
    }
}

void buscarItemLista(No* inicio) {
    if (inicio == NULL) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nome[30];
    printf("\n--- Buscar Item (Lista) ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nome);

    comparacoesSequencial = 0;
    clock_t inicioT = clock();
    No* atual = inicio;

    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            clock_t fim = clock();
            double tempo = (double)(fim - inicioT) / CLOCKS_PER_SEC;
            printf("\nItem encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações: %ld | Tempo: %.6f s\n", comparacoesSequencial, tempo);
            return;
        }
        atual = atual->proximo;
    }

    printf("\nItem não encontrado. Comparações: %ld\n", comparacoesSequencial);
}


// ===================== MENUS =====================

void menuVetor() {
    int opcao;
    do {
        printf("\n=== Sistema de Inventário (Vetor) ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar itens\n");
        printf("5. Buscar sequencial\n");
        printf("6. Buscar binária\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: buscarSequencialVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 0: printf("\nVoltando ao menu principal...\n"); break;
            default: printf("\nOpção inválida.\n");
        }
    } while (opcao != 0);
}

void menuLista() {
    int opcao;
    No* inicio = NULL;

    do {
        printf("\n=== Sistema de Inventário (Lista Encadeada) ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inicio = inserirItemLista(inicio); break;
            case 2: inicio = removerItemLista(inicio); break;
            case 3: listarItensLista(inicio); break;
            case 4: buscarItemLista(inicio); break;
            case 0: printf("\nVoltando ao menu principal...\n"); break;
            default: printf("\nOpção inválida.\n");
        }
    } while (opcao != 0);
}


// ===================== MAIN =====================

int main() {
    int modo;

    do {
        printf("\n=== COMPARATIVO DE ESTRUTURAS ===\n");
        printf("1. Mochila com Vetor\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &modo);

        switch (modo) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("\nEncerrando o sistema...\n"); break;
            default: printf("\nOpção inválida.\n");
        }
    } while (modo != 0);

    return 0;
}
