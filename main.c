#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    char nome[100];
    char dataDeNascimento[10];
    char telefone[11];
} Cliente;

typedef struct {
    int id;
    char titulo[100];
    char tipoDeMidia[3];
    char genero[20];
} VHS_DVD;

typedef struct {
    int id;
    char cliente[100];
    char titulo[100];
    char dataLocacao[10];
    char dataDevolucao[10];
    bool devolvido;
} Aluguel;

Cliente clientes[4];
VHS_DVD vhsDvd[50];
Aluguel aluguel[100];

void cadastrarCliente() {
    printf("Informe o nome do cliente:\n");
    return;
}

void listarCliente() {
    printf("Informe o nome do cliente:\n");
    return;
}

void editarCadastrar() {
    printf("Informe o nome do cliente:\n");
    return;
}

void excluirCliente() {
    printf("Informe o nome do cliente:\n");
    return;
}

void cadastrarMidia() {
    printf("Informe o nome do vhs:\n");
    return;
}

void tipoDeMidia() {
    printf("Informe o tipo da midia:\n");
    return;
}

void alugar() {
    printf("Informe o nome do alugar:\n");
    return;
}
void devolver() {
    printf("Informe o nome do alugar:\n");
    return;
}
void excluir() {
    printf("Informe o nome do alugar:\n");
    return;
}

void menuCliente() {
    int menu;

    do {
        printf("Menu Cliente:\n");
        printf(" 1 - Cadastrar cliente\n");
        printf(" 2 - Listar cliente\n");
        printf(" 3 - Editar\n");
        printf(" 4 - Excluir\n");
        printf(" 0 - Voltar\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarCliente();
                break;
            case 3:
                editarCadastrar();
                break;
            case 4:
                excluirCliente();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    while (menu != 0);
}

int main(void) {

    int menu;

    do {
        printf("Menu Mídia:\n");
        printf(" 1 - Cadastrar mídia\n");
        printf(" 2 - Tipo de Mídia VHS/DVD\n");
        printf(" 3 - Alugar\n");
        printf(" 4 - Devolver\n");
        printf ("5 - Excluir\n");
        printf(" 0 - Voltar\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                cadastrarMidia();
                break;
            case 2:
                tipoDeMidia();
                break;
            case 3:
                alugar();
                break;
            case 4:
                devolver();
                break;
            case 5:
                excluir();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    while (menu != 0);

    return 0;
}
