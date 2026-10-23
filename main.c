#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    char nome[100];
} Cliente;

typedef struct {
    int id;
    char titulo[100];
} VHS_DVD;

typedef struct {
    int id;
    char cliente[100];
    char titulo[100];
    char dataLocacao[10];
    char dataDevolucao[10];
    bool devolvido;
} Aluguel;

void cadastrarCliente(Cliente* clientes) {
    printf("Informe o nome do cliente:\n");
    return;
}

void cadastrarVHS(VHS_DVD* vhsDvd) {
    printf("Informe o nome do vhs:\n");
    return;
}

void alugar(Aluguel* aluguel) {
    printf("Informe o nome do alugar:\n");
    return;
}
void devolver(Aluguel* aluguel) {
    printf("Informe o nome do alugar:\n");
    return;
}

int main(void) {
    Cliente clientes[4];
    VHS_DVD vhsDvd[50];
    Aluguel aluguel[100];

    int menu;

    do {
        printf("Escolha uma opção:\n");
        printf(" 1 - Cadastro de cliente\n");
        printf(" 2 - Cadastro de Fita VHS/DVD\n");
        printf(" 3 - Alugar\n");
        printf(" 4 - Devoluçào\n");
        printf(" 0 - Sair\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                cadastrarCliente(clientes);
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
