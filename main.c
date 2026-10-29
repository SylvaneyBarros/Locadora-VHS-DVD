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

void cadastrarMidia() {
    return;
}

void listarMidia() {
    return;
}
void editarMidia() {
    return;
}

void excluirMidia() {
    return;
}

void menuMidia() {
    int menu;

    do {
        printf("Menu Mídia:\n");
        printf(" 1 - Cadastrar mídia\n");
        printf(" 2 - Listar mídia\n");
        printf(" 3 - Editar\n");
        printf(" 4 - Excluir\n");
        printf(" 0 - Voltar\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                cadastrarMidia();
                break;
            case 2:
                listarMidia();
                break;
            case 3:
                editarMidia();
                break;
            case 4:
                excluirMidia();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    while (menu != 0);
}

void cadastrarCliente() {
    return;
}

void listarCliente() {
    return;
}

void editarCadastrar() {
    return;
}

void excluirCliente() {
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
void alugar() {
     return;
}
void devolver() {
    return;
}

int main(void) {

    int menu;

    do {
        printf("Locadora de vídeo:\n");
        printf(" 1 - Cliente\n");
        printf(" 2 - Mídia VHS/DVD\n");
        printf(" 3 - Alugar\n");
        printf(" 4 - Devolver\n");
        printf(" 0 - Sair\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                menuCliente();
                break;
            case 2:
                menuMidia();
                break;
            case 3:
                alugar();
                break;
            case 4:
                devolver();
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
