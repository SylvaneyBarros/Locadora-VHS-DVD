
#ifndef LOCADORA_VHS_DVD_CLIENTES_H
#define LOCADORA_VHS_DVD_CLIENTES_H

#include <stdio.h>
#include <string.h>
#include "utils.h"

struct Cliente {
    int id;
    char nome[50];
    char dataDeNascimento[11];
    char telefone[12];
    int ativo; // 1 = Ativo, 0 = Removido
};

FILE *arquivoClientes;

struct Cliente clientes[50];
int totalClientes = 0;

void cadastrarCliente() {

    limparTela();

    printf("\nCadastro de Cliente\n");

    if(totalClientes >= 50) {
        printf("Excede a capacidade de cadastro.\n");
        return;
    }
    printf("Nome: ");
    scanf(" %50[^\n]", clientes[totalClientes].nome);

    printf("Data de Nascimento: ");
    scanf(" %s", clientes[totalClientes].dataDeNascimento);

    printf("Telefone: ");
    scanf(" %s", clientes[totalClientes].telefone);

    clientes[totalClientes].id = totalClientes;

    clientes[totalClientes].ativo = 1;

    arquivoClientes = fopen("clientes.csv", "a");
    fprintf(arquivoClientes, "%d;%s;%s;%s;%d\n",
        clientes[totalClientes].id,
        clientes[totalClientes].nome,
        clientes[totalClientes].dataDeNascimento,
        clientes[totalClientes].telefone,
        clientes[totalClientes].ativo);

    fclose(arquivoClientes);

    totalClientes++;

    printf("Cliente cadastrado com sucesso!\n");

}
int clienteValido(int id) {
    if (id < 0 || id >= totalClientes) {
        return 0;
    }
    if (clientes[id].ativo == 0) {
        return 0;
    }
    return 1;
}

void editarClientePorId(int id) {
    if (!clienteValido(id)) {
        printf("Id inválido ou cliente removido.\n");
        return;
    }

    printf("\nDados atuais:\n");
    printf("Nome: %s\n", clientes[id].nome);
    printf("Data de Nascimento: %s\n", clientes[id].dataDeNascimento);
    printf("Telefone: %s\n", clientes[id].telefone);

    printf("\nInforme os novos dados:\n");

    printf("Nome: ");
    scanf("%s", clientes[id].nome);

    printf("Data de Nascimento: ");
    scanf(" %s", clientes[id].dataDeNascimento);

    printf("Telefone: ");
    scanf(" %s", clientes[id].telefone);

    printf("Cadastro atualizado com sucesso!\n\n");
}
void listarCliente() {

    limparTela();

    printf("\nListagem de Clientes\n");

    if(totalClientes == 0) {
        printf("Não há clientes cadastrados.\n");
        return;
    }
    for(int i = 0; i < totalClientes; i++) {
        printf("%d - %s - %s\n", clientes[i].id, clientes[i].nome, clientes[i].ativo == 1?"Ativo" : "Inativo");
    }

    pausar();
}

void localizarClienteNome() {

    char nome[50];
    int localizados = 0;
    int idCliente;

    printf("\nInforme o nome do cliente:");
    scanf("%s", nome);

    for(int i = 0; i < totalClientes; i++) {
        if (strstr (clientes[i].nome, nome) != NULL) {
            printf ("%d - %s\n", clientes[i].id, clientes[i].nome);
            localizados++;
        }
    }
    if (localizados == 0) {
        printf ("Nenhum cliente foi localizado!\n");
        return;
    }
    else {
        printf("Digite o Id do cliente para editar: ");
        scanf("%d", &idCliente);

        editarClientePorId(idCliente);
    }
}

void localizarClienteId() {

    int idCliente;
    printf("\nInforme o ID do cliente:");
    scanf("%d", &idCliente);

    editarClientePorId(idCliente);
}

void editarCliente() {
    printf("\nEditar cadastro\n");

    if(totalClientes == 0) {
        printf("Não há clientes cadastrados.\n");
        return;
    }

    int menu;

    do {
        printf("Localizar por:\n");
        printf(" 1 - Nome do cliente\n");
        printf(" 2 - Id do cliente\n");
        printf(" 0 - Voltar\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                localizarClienteNome();
                break;
            case 2:
                localizarClienteId();
                break;
            case 0:
                printf("Retornando ao menu cliente.\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida!\n");
        }

    } while (menu != 0);
}

void excluirCliente() {
    int idCliente;
    char confirmacao;

    printf("\nExcluir Cliente\n");

    if(totalClientes == 0) {
        printf("Não há clientes cadastrados.\n");
        return;
    }

    printf("Informe o Id do cliente: ");
    scanf("%d", &idCliente);

    if (!clienteValido(idCliente)) {
        printf("Id inválido ou cliente já removido.\n");
        return;
    }

    printf("Deseja realmente excluir %s? (S/N): ", clientes[idCliente].nome);
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        clientes[idCliente].ativo = 0;
        printf("Cliente excluído com sucesso!\n");
    } else {
        printf("Exclusão cancelada.\n");
    }
}

void carregarClientes() {
    arquivoClientes = fopen("clientes.csv", "r");
    if (arquivoClientes == NULL) {
       return;
    }

    struct Cliente auxCliente;

    while (fscanf(arquivoClientes, "%d;%49[^;];%10[^;];%11[^;];%d\n",
        &auxCliente.id,
        auxCliente.nome,
        auxCliente.dataDeNascimento,
        auxCliente.telefone,
        &auxCliente.ativo) == 5) {

        if (auxCliente.id >= 0 && auxCliente.id < 50) {
            clientes[auxCliente.id] = auxCliente;
            totalClientes++;
        }
    }

}

void menuCliente() {
    int menu;

    carregarClientes();

    limparTela();

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
                printf("\n[ERRO] Opção inválida!\n");
        }
    } while (menu != 0);
}

#endif //LOCADORA_VHS_DVD_CLIENTES_H
