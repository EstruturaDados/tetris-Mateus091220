#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------- CONFIGURAÇÕES ----------
#define TAM_FILA 5

// ---------- STRUCT DA PEÇA ----------
typedef struct {
    char tipo;  // I, O, T, L...
    int id;     // identificador único
} Peca;

// ---------- VARIÁVEIS DA FILA ----------
Peca fila[TAM_FILA];
int inicio = 0;
int fim = 0;
int quantidade = 0;
int proximoID = 1;

// ---------- FUNÇÕES DA FILA ----------
void inicializarFila() {
    inicio = fim = quantidade = 0;
}

int filaCheia() {
    return quantidade == TAM_FILA;
}

int filaVazia() {
    return quantidade == 0;
}

// Gera uma nova peça com tipo aleatório
Peca gerarPeca() {
    char tipos[4] = {'I','O','T','L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = proximoID++;
    return nova;
}

void enqueue(Peca p) {
    if (filaCheia()) {
        printf("⚠️  A fila está cheia! Não é possível inserir.\n");
        return;
    }

    fila[fim] = p;
    fim = (fim + 1) % TAM_FILA;
    quantidade++;
}

Peca dequeue() {
    Peca removida;

    if (filaVazia()) {
        printf("⚠️  A fila está vazia! Nada para remover.\n");
        removida.id = -1;
        return removida;
    }

    removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;

    return removida;
}

void mostrarFila() {
    printf("\n=== FILA DE PEÇAS ===\n");

    int i = inicio;
    for (int c = 0; c < quantidade; c++) {
        printf("[%c | id %d] ", fila[i].tipo, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }

    if (quantidade == 0)
        printf("(vazia)");

    printf("\n=====================\n\n");
}

// ---------- PROGRAMA PRINCIPAL ----------
int main() {
    srand(time(NULL));
    inicializarFila();

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++)
        enqueue(gerarPeca());

    int opcao;

    do {
        mostrarFila();
        printf("MENU:\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca removida = dequeue();
                if (removida.id != -1) {
                    printf("➡️  Peça jogada: %c (id %d)\n", removida.tipo, removida.id);
                    enqueue(gerarPeca());  // repõe automaticamente
                }
                break;
            }
            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
