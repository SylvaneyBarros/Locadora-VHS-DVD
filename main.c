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

void cadastrarVHS() {
    printf("Informe o nome do vhs:\n");
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
                cadastrarVHS(vhsDvd);
                break;
            case 3:
                alugar(aluguel);
                break;
            case 4:
                devolver(aluguel);
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
        printf("Escolha uma opção:\n");
        printf(" 1 - Cliente\n");
        printf(" 2 - Mídia VHS/DVD\n");
        printf(" 3 - Alugar\n");
        printf(" 4 - Devoluçào\n");
        printf(" 0 - Sair\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                menuCliente();
                break;
            case 2:
                cadastrarVHS(vhsDvd);
                break;
            case 3:
                alugar(aluguel);
                break;
            case 4:
                devolver(aluguel);
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
