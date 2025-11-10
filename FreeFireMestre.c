#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// ==========================================
//  TORRE DE RESGATE – NÍVEL FINAL
//  Sistema que organiza componentes de uma torre de fuga
//  usando diferentes algoritmos de ordenação e busca binária.
//  Cada escolha afeta o tempo e o número de comparações.
// ==========================================


// ------------------ DEFINIÇÕES ------------------

#define MAX_COMPONENTES 20   // limite máximo de componentes

// Estrutura que define um componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;


// ------------------ VARIÁVEIS GLOBAIS ------------------

Componente torre[MAX_COMPONENTES];  // vetor principal de componentes
int total = 0;                      // quantidade de componentes cadastrados
long comparacoes = 0;               // contador global de comparações


// =======================================================
//  FUNÇÕES AUXILIARES
// =======================================================

// Limpa o buffer de entrada do teclado
void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Exibe todos os componentes da torre
void mostrarComponentes(Componente lista[], int n) {

    printf("\n--- Componentes da Torre ---\n");

    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}


// =======================================================
//  CADASTRO DE COMPONENTES
// =======================================================

void cadastrarComponente() {

    // verifica limite
    if (total >= MAX_COMPONENTES) {
        printf("\nLimite máximo atingido!\n");
        return;
    }

    printf("\n--- Cadastro de Componente ---\n");

    printf("Nome: ");
    scanf(" %[^\n]", torre[total].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", torre[total].tipo);

    printf("Prioridade (1-10): ");
    scanf("%d", &torre[total].prioridade);

    total++;

    printf("\nComponente adicionado com sucesso!\n");
}


// =======================================================
//  ORDENAÇÕES
// =======================================================


// ---------- Bubble Sort (por nome) ----------
void bubbleSortNome(Componente lista[], int n) {

    comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            comparacoes++;

            // compara os nomes e troca se necessário
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                Componente temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nOrdenado por nome (Bubble Sort)\n");
    printf("Comparações: %ld | Tempo: %.6f s\n", comparacoes, tempo);
}



// ---------- Insertion Sort (por tipo) ----------
void insertionSortTipo(Componente lista[], int n) {

    comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < n; i++) {

        Componente chave = lista[i];
        int j = i - 1;

        // desloca os maiores elementos pra frente
        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            lista[j + 1] = lista[j];
            j--;
            comparacoes++;
        }

        lista[j + 1] = chave;
        comparacoes++;
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nOrdenado por tipo (Insertion Sort)\n");
    printf("Comparações: %ld | Tempo: %.6f s\n", comparacoes, tempo);
}



// ---------- Selection Sort (por prioridade) ----------
void selectionSortPrioridade(Componente lista[], int n) {

    comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < n - 1; i++) {

        int min = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (lista[j].prioridade < lista[min].prioridade)
                min = j;
        }

        // troca os elementos
        if (min != i) {
            Componente temp = lista[i];
            lista[i] = lista[min];
            lista[min] = temp;
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nOrdenado por prioridade (Selection Sort)\n");
    printf("Comparações: %ld | Tempo: %.6f s\n", comparacoes, tempo);
}



// =======================================================
//  BUSCA BINÁRIA
// =======================================================

void buscaBinariaPorNome(Componente lista[], int n) {

    if (n == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    // A busca binária precisa da lista ordenada por nome
    bubbleSortNome(lista, n);

    char chave[30];
    printf("\nDigite o nome do componente-chave: ");
    scanf(" %[^\n]", chave);

    int inicio = 0, fim = n - 1;
    long comp = 0;
    clock_t t1 = clock();

    while (inicio <= fim) {

        int meio = (inicio + fim) / 2;
        comp++;

        int cmp = strcmp(lista[meio].nome, chave);

        if (cmp == 0) {
            clock_t t2 = clock();
            double tempo = (double)(t2 - t1) / CLOCKS_PER_SEC;

            printf("\nComponente encontrado!\n");
            printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                   lista[meio].nome, lista[meio].tipo, lista[meio].prioridade);
            printf("Comparações: %ld | Tempo: %.6f s\n", comp, tempo);
            printf("\nTorre ativada com sucesso!\n");
            return;
        }
        else if (cmp < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    printf("\nComponente não encontrado. Comparações: %ld\n", comp);
}



// =======================================================
//  MENU PRINCIPAL
// =======================================================

void menuPrincipal() {

    int opcao;

    do {

        printf("\n==============================\n");
        printf("      MENU DA TORRE DE RESGATE\n");
        printf("==============================\n");

        printf("1. Cadastrar componente\n");
        printf("2. Listar componentes\n");
        printf("3. Ordenar por nome (Bubble Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Buscar componente-chave (Busca Binária)\n");
        printf("0. Sair\n");

        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        // Quebra visual no console
        printf("\n----------------------------------\n");

        switch (opcao) {

            case 1:
                cadastrarComponente();
                break;

            case 2:
                mostrarComponentes(torre, total);
                break;

            case 3:
                bubbleSortNome(torre, total);
                mostrarComponentes(torre, total);
                break;

            case 4:
                insertionSortTipo(torre, total);
                mostrarComponentes(torre, total);
                break;

            case 5:
                selectionSortPrioridade(torre, total);
                mostrarComponentes(torre, total);
                break;

            case 6:
                buscaBinariaPorNome(torre, total);
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);
}



// =======================================================
//  FUNÇÃO PRINCIPAL
// =======================================================

int main() {

    // executa o menu principal do sistema
    menuPrincipal();

    return 0;
}
