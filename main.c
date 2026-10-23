#include <stdio.h>

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
} Aluguel;

int main(void) {
    Cliente clientes[4];
    VHS_DVD vhs_dvd[50];
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
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
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
