// Arquivo: clientes.h | Autor: Sylvaney Joice Alves de Barros - RGM: 47501863
#ifndef LOCADORA_VHS_DVD_CLIENTES_H
#define LOCADORA_VHS_DVD_CLIENTES_H

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <ctype.h>

#define MAX_CLIENTES 50

struct Cliente {
    int id;
    char nome[50];
    char dataDeNascimento[11];
    char telefone[12];
    float multaPendente;
    int ativo; // 1 = Ativo, 0 = Removido
};

FILE *arquivoClientes;

struct Cliente clientes[50];
int totalClientes = 0;

/**copia uma string e converte todas as letras em minúsculas.
 *usada para não precisar diferenciar letras maiúsculas e minúscula.
 */
void paraMinusculo(char *dest, const char *orig) {
    int i;
    for (i = 0; orig[i] != '\0'; i++) {
        dest[i] = tolower((unsigned char) orig[i]);
    }
    dest[i] = '\0';
}
/**
 *Cadastra um novo cliente, lê nome, data de nascimento e telefone.
 *o cadastro é cancelado se atingir o limite máximo de 50 cadastros.
 *o vetor "vazio marca o cliente como ativo e acrescenta o 0
 *registro ao final do arquivo csv.
 */
void cadastrarCliente() {

    limparTela();

    printf("\nCadastro de Cliente\n");

    if(totalClientes >= 50) {
        printf("Excede a capacidade de cadastro.\n");
        return;
    }
    printf("Nome: ");
    scanf(" %49[^\n]", clientes[totalClientes].nome);

    if (strchr(clientes[totalClientes].nome, ';') != NULL) {
        printf("[ERRO] O nome nao pode conter ';'.\n");
        return;
    }

    printf("Data de Nascimento: ");
    scanf(" %10[^\n]", clientes[totalClientes].dataDeNascimento);
    scanf("%*[^\n]");

    printf("Telefone: ");
    scanf(" %11[^\n]", clientes[totalClientes].telefone);
    scanf("%*[^\n]");


    clientes[totalClientes].id = totalClientes;

    clientes[totalClientes].ativo = 1;

    arquivoClientes = fopen("clientes.csv", "a");

    if (arquivoClientes == NULL) {
        printf("[ERRO] Nao foi possivel abrir clientes.csv.\n");
        return;
    }

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
/**
 *verifique se o id corresponde a um cliente existente e ativo.
 *return 1 se o id esta dentro do intervalo cadastrado se o cliente está ativo. 0 se o cliente esta inativo ou foi removido.
 */
int clienteValido(int id) {
    if (id < 0 || id >= totalClientes) {
        return 0;
    }
    if (clientes[id].ativo == 0) {
        return 0;
    }
    return 1;
}
/**
 *fopen abre o arquivo, modo write, que sobrescreve o arquivo, porque nao da pra editar uma linha espeficia do arquivo.
 */
void salvarClientes() {
    arquivoClientes = fopen("clientes.csv", "w"); // "w" apaga o conteúdo antigo e regrava tudo
    if (arquivoClientes == NULL) {
        printf("[ERRO] Não foi possível abrir clientes.csv para gravação.\n");
        return;
    }

    for (int i = 0; i < totalClientes; i++) {
        fprintf(arquivoClientes, "%d;%s;%s;%s;%d\n",
            clientes[i].id,
            clientes[i].nome,
            clientes[i].dataDeNascimento,
            clientes[i].telefone,
            clientes[i].ativo);
    }

    fclose(arquivoClientes);
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

    char novoNome[50];
    printf("Nome: ");
    scanf(" %49[^\n]", novoNome);
    scanf("%*[^\n]");

    if (strchr(novoNome, ';') != NULL) {
        printf("[ERRO] O nome nao pode conter ';'.\n");
        return;
    }
    strcpy(clientes[id].nome, novoNome);

    printf("Data de Nascimento: ");
    scanf(" %10[^\n]", clientes[id].dataDeNascimento);
    scanf("%*[^\n]");

    printf("Telefone: ");
    scanf(" %11[^\n]", clientes[id].telefone);
    scanf("%*[^\n]");

    salvarClientes();

    printf("Cadastro atualizado com sucesso!\n\n");
}
void listarCliente() {


    printf("\nListagem de Clientes\n");

    if(totalClientes == 0) {
        printf("Não há clientes cadastrados.\n");
        return;
    }
    for(int i = 0; i < totalClientes; i++) {
        printf("%d - %s - %s\n", clientes[i].id, clientes[i].nome, clientes[i].ativo == 1?"Ativo" : "Inativo");
    }

}

void buscarClienteNome() {
    char nome[50], nomeMin[50], buscaMin[50];
    int localizados = 0;

    printf("\nInforme o nome (ou parte dele): ");
    scanf(" %49[^\n]", nome);
    paraMinusculo(buscaMin, nome);

    for (int i = 0; i < totalClientes; i++) {
        paraMinusculo(nomeMin, clientes[i].nome);
        if (strstr(nomeMin, buscaMin) != NULL) {
            printf("%d - %s - %s - %s\n", clientes[i].id, clientes[i].nome,
                   clientes[i].telefone, clientes[i].ativo == 1 ? "Ativo" : "Inativo");
            localizados++;
        }
    }
    if (localizados == 0) printf("Nenhum cliente foi localizado!\n");
}

void localizarClienteNome() {

    char nome[50];
    int localizados = 0;
    int idCliente;

    printf("\nInforme o nome do cliente:");
    scanf(" %49[^\n]", nome);

    char nomeMin[50], buscaMin[50];
    paraMinusculo(buscaMin, nome);

    for (int i = 0; i < totalClientes; i++) {
        paraMinusculo(nomeMin, clientes[i].nome);
        if (strstr(nomeMin, buscaMin) != NULL) {
            printf("%d - %s\n", clientes[i].id, clientes[i].nome);
            localizados++;
        }
    }

    if (localizados == 0) {
        printf ("Nenhum cliente foi localizado!\n");
        return;
    }
    else {
        printf("Digite o Id do cliente para editar: ");
        idCliente = lerInteiro();

        editarClientePorId(idCliente);
    }
}

void localizarClienteId() {

    int idCliente;
    printf("\nInforme o ID do cliente:");
    idCliente = lerInteiro();

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

        menu = lerInteiro();

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
    idCliente = lerInteiro();

    if (!clienteValido(idCliente)) {
        printf("Id inválido ou cliente já removido.\n");
        return;
    }

    printf("Deseja realmente excluir %s? (S/N): ", clientes[idCliente].nome);
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        clientes[idCliente].ativo = 0;

        salvarClientes();

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
    totalClientes = 0;

    struct Cliente auxCliente;

    while (fscanf(arquivoClientes, "%d;%49[^;];%10[^;];%11[^;];%d\n",
        &auxCliente.id,
        auxCliente.nome,
        auxCliente.dataDeNascimento,
        auxCliente.telefone,
        &auxCliente.ativo) == 5) {

        if (auxCliente.id >= 0 && auxCliente.id < 50) {
            auxCliente.multaPendente = 0;
            clientes[auxCliente.id] = auxCliente;
            totalClientes++;
        }
    }
    fclose(arquivoClientes);

}

void menuCliente() {
    int menu;

    do {
        limparTela();
        printf("\n--- MENU CLIENTE ---\n");
        printf(" 1 - Cadastrar cliente\n");
        printf(" 2 - Listar clientes\n");
        printf(" 3 - Editar cliente\n");
        printf(" 4 - Excluir cliente\n");
        printf(" 5 - Buscar cliente por nome\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma acao: ");

        menu = lerInteiro();

        switch (menu) {
            case 1:
                cadastrarCliente();
                pausar();
                break;
            case 2:
                listarCliente();
                pausar();
                break;
            case 3:
                editarCliente();
                pausar();
                break;
            case 4:
                excluirCliente();
                pausar();
                break;
            case 5:
                buscarClienteNome();
                pausar();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida!\n");
                pausar();
        }
    } while (menu != 0);
}

#endif //LOCADORA_VHS_DVD_CLIENTES_H
