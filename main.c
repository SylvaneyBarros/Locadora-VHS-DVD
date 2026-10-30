#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Cliente {
    int id;
    char nome[50];
    char dataDeNascimento[11];
    char telefone[12];
    float multaPendente;
    int ativo; // 1 = Ativo, 0 = Removido
};

struct VHS_DVD {
    int id;
    char titulo[50];
    char tipoDeMidia[4]; // "VHS" ou "DVD"
    char genero[20];
    float precoLocacao;
    int copiasDisponiveis;
    int ativo; // 1 = Ativo, 0 = Removido
};

struct Aluguel{
    int id;
    char cliente[100];
    char titulo[100];
    char dataLocacao[10];
    char dataDevolucao[10];
    bool devolvido;
} ;

struct Cliente clientes[50];
int totalClientes = 0;

struct VHS_DVD vhsDvd[50];
int totalMidias = 0;

struct Aluguel aluguel[50];

// ----------------------------------------------------------------------------
// Joice (Nome Completo e RGM)
// ----------------------------------------------------------------------------
void cadastrarCliente() {
    printf("\n[Em construcao] Cadastro de Cliente...\n");
    printf("Campos previstos: Nome, Data de Nascimento, Telefone e Multa.\n");
}

void listarCliente() {
    printf("\n[Em construcao] Listagem e Busca de Clientes...\n");
}

void editarCliente() {
    printf("\n[Em construcao] Edicao de Cliente por ID...\n");
}

void excluirCliente() {
    printf("\n[Em construcao] Remocao de Cliente...\n");
}

void menuCliente() {
    int menu;

    do {
        printf("\n--- MENU CLIENTE ---\n");
        printf(" 1 - Cadastrar cliente\n");
        printf(" 2 - Listar / Buscar cliente\n");
        printf(" 3 - Editar cliente\n");
        printf(" 4 - Excluir cliente\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma acao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarCliente();
                break;
            case 3:
                editarCliente();
                break;
            case 4:
                excluirCliente();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (menu != 0);
}

// ----------------------------------------------------------------------------
// Natalia - RGM: 37482971
// ----------------------------------------------------------------------------
void cadastrarMidia() {
    printf("\n[Em construcao] Cadastro de Midia...\n");
    printf("Campos previstos: Titulo, Tipo (VHS/DVD), Genero, Preco e Copias.\n");
}

void listarMidia() {
    printf("\n[Em construcao] Listagem e Busca de Midias...\n");
}

void editarMidia() {
    printf("\n[Em construcao] Edicao de Midia por ID...\n");
}

void excluirMidia() {
    printf("\n[Em construcao] Remocao de Midia...\n");
}

void menuMidia() {
    int menu;

    do {
        printf("\n--- MENU MIDIA VHS/DVD ---\n");
        printf(" 1 - Cadastrar midia\n");
        printf(" 2 - Listar / Buscar midia\n");
        printf(" 3 - Editar midia\n");
        printf(" 4 - Excluir midia\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma acao: ");
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
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (menu != 0);
}

void menuAlugar() {
     return;
}

void menuRelatorio() {

}

int main(void) {

    int menu;

    do {
        printf("--- Locadora de vídeo ---\n");
        printf(" 1 - Cliente\n");
        printf(" 2 - Mídia VHS/DVD\n");
        printf(" 3 - Alugar/Devolver\n");
        printf(" 4 - Relatorio\n");
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
                menuAlugar();
                break;
            case 4:
                menuRelatorio();
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