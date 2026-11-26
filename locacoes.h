// Arquivo: locacoes.h | Autor: Stephany Christina Barbosa da Silva - RGM: 46810927

#ifndef LOCACOES_H
#define LOCACOES_H

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "clientes.h"
#include "midias.h"

#define MAX_ALUGUEIS 50

struct Aluguel {
    int id;
    int idCliente;
    int idMidia;
    int diasLocados;
    char dataLocacao[11];
    char dataDevolucao[11];
    float valorTotal;
    int devolvido;
};

FILE *arquivoAlugueis;
struct Aluguel aluguel[MAX_ALUGUEIS];
int totalAlugueis = 0;
int matrizLocacoes[MAX_CLIENTES][MAX_MIDIAS];

void salvarAlugueisCSV() {
    FILE *arquivo;
    int i;

    arquivo = fopen("locacoes.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar as locacoes!\n");
        return;
    }

    for (i = 0; i < totalAlugueis; i++) {
        fprintf(arquivo, "%d;%d;%d;%d;%s;%s;%.2f;%d\n",
            aluguel[i].id,
            aluguel[i].idCliente,
            aluguel[i].idMidia,
            aluguel[i].diasLocados,
            aluguel[i].dataLocacao,
            aluguel[i].dataDevolucao,
            aluguel[i].valorTotal,
            aluguel[i].devolvido
        );
    }

    fclose(arquivo);
}

void carregarAlugueis() {
    arquivoAlugueis = fopen("locacoes.csv", "r");
    if (arquivoAlugueis == NULL) {
        return;
    }
    totalAlugueis = 0;
    struct Aluguel auxAluguel;
    while (fscanf(arquivoAlugueis, "%d;%d;%d;%d;%10[^;];%10[^;];%f;%d\n",
                  &auxAluguel.id,
                  &auxAluguel.idCliente,
                  &auxAluguel.idMidia,
                  &auxAluguel.diasLocados,
                  auxAluguel.dataLocacao,
                  auxAluguel.dataDevolucao,
                  &auxAluguel.valorTotal,
                  &auxAluguel.devolvido) == 8) {
        if (totalAlugueis < MAX_ALUGUEIS) {
            aluguel[totalAlugueis] = auxAluguel;
            totalAlugueis++;
        }
    }
    fclose(arquivoAlugueis);
}

int buscarIndiceAluguel(int id) {
    int i;

    for (i = 0; i < totalAlugueis; i++) {
        if (aluguel[i].id == id) {
            return i;
        }
    }

    return -1;
}

char* nomeDoCliente(int idCliente) {
    int i;

    for (i = 0; i < totalClientes; i++) {
        if (clientes[i].id == idCliente) {
            return clientes[i].nome;
        }
    }

    return "(removido)";
}

char* tituloDaMidia(int idMidia) {
    int i;

    for (i = 0; i < totalMidias; i++) {
        if (vhsDvd[i].id == idMidia) {
            return vhsDvd[i].titulo;
        }
    }

    return "(removida)";
}

void menualugar() {
    int idCliente;
    int idMidia;
    int diasLocados;
    int posCliente = -1;
    int posMidia;
    int i;
    int maiorId = 0;

    char dataLocacao[11];

    printf("\n===== NOVA LOCACAO =====\n");

    if (totalAlugueis >= MAX_ALUGUEIS) {
        printf("\nLimite de locacoes atingido!\n");
        return;
    }

    printf("Digite o ID do cliente: ");
    scanf("%d", &idCliente);

    // Busca o cliente
    for (i = 0; i < totalClientes; i++) {
        if (clientes[i].id == idCliente) {
            posCliente = i;
            break;
        }
    }

    if (posCliente == -1) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    if (clientes[posCliente].ativo != 1) {
        printf("\nEste cliente esta inativo!\n");
        return;
    }

    if (clientes[posCliente].multaPendente > 0) {
        printf("\nCliente possui multa pendente e nao pode alugar!\n");
        return;
    }

    printf("Digite o ID da midia: ");
    scanf("%d", &idMidia);

    posMidia = buscarIndiceMidia(idMidia);

    if (posMidia == -1) {
        printf("\nMidia nao encontrada!\n");
        return;
    }

    if (vhsDvd[posMidia].copiasDisponiveis <= 0) {
        printf("\nNao ha copias disponiveis!\n");
        return;
    }

    printf("Digite a quantidade de dias: ");
    scanf("%d", &diasLocados);

    if (diasLocados <= 0) {
        printf("\nQuantidade de dias invalida!\n");
        return;
    }

    printf("Digite a data da locacao (DD/MM/AAAA): ");
    scanf("%10s", dataLocacao);

    for (i = 0; i < totalAlugueis; i++) {
        if (aluguel[i].id > maiorId) {
            maiorId = aluguel[i].id;
        }
    }

    aluguel[totalAlugueis].id = maiorId + 1;
    aluguel[totalAlugueis].idCliente = idCliente;
    aluguel[totalAlugueis].idMidia = idMidia;
    aluguel[totalAlugueis].diasLocados = diasLocados;

    strcpy(aluguel[totalAlugueis].dataLocacao, dataLocacao);
    strcpy(aluguel[totalAlugueis].dataDevolucao, "-");

    aluguel[totalAlugueis].valorTotal =
        vhsDvd[posMidia].precoLocacao * diasLocados;

    aluguel[totalAlugueis].devolvido = 0;

    vhsDvd[posMidia].copiasDisponiveis--;

    totalAlugueis++;

    salvarAlugueisCSV();
    salvarMidiasCSV();

    printf("\nLocacao cadastrada com sucesso!\n");
    printf("Valor total: R$ %.2f\n",
        aluguel[totalAlugueis - 1].valorTotal);
}

void listarAlugueis() {
    int i;

    printf("\n===== LISTA DE LOCACOES =====\n");

    if (totalAlugueis == 0) {
        printf("\nNenhuma locacao cadastrada!\n");
        return;
    }

    for (i = 0; i < totalAlugueis; i++) {
        printf("\n-----------------------------\n");
        printf("ID da locacao: %d\n", aluguel[i].id);
        printf("Cliente: %s\n",
            nomeDoCliente(aluguel[i].idCliente));
        printf("Midia: %s\n",
            tituloDaMidia(aluguel[i].idMidia));
        printf("Dias locados: %d\n", aluguel[i].diasLocados);
        printf("Data da locacao: %s\n", aluguel[i].dataLocacao);
        printf("Data da devolucao: %s\n", aluguel[i].dataDevolucao);
        printf("Valor total: R$ %.2f\n", aluguel[i].valorTotal);

        if (aluguel[i].devolvido == 1) {
            printf("Status: Devolvido\n");
        } else {
            printf("Status: Em aberto\n");
        }
    }

    printf("\n-----------------------------\n");
}

void devolver() {
    int idLocacao;
    int posLocacao;
    int posMidia;
    char dataDevolucao[11];

    printf("\n===== DEVOLUCAO DE MIDIA =====\n");

    printf("Digite o ID da locacao: ");
    scanf("%d", &idLocacao);

    posLocacao = buscarIndiceAluguel(idLocacao);

    if (posLocacao == -1) {
        printf("\nLocacao nao encontrada!\n");
        return;
    }

    if (aluguel[posLocacao].devolvido == 1) {
        printf("\nEsta locacao ja foi devolvida!\n");
        return;
    }

    printf("Digite a data da devolucao (DD/MM/AAAA): ");
    scanf("%10s", dataDevolucao);

    aluguel[posLocacao].devolvido = 1;

    strcpy(aluguel[posLocacao].dataDevolucao, dataDevolucao);

    posMidia = buscarIndiceMidia(aluguel[posLocacao].idMidia);

    if (posMidia != -1) {
        vhsDvd[posMidia].copiasDisponiveis++;
        salvarMidiasCSV();
    }

    salvarAlugueisCSV();

    printf("\nDevolucao realizada com sucesso!\n");
}

void cancelarAluguel() {
    int idLocacao;
    int posLocacao;
    int posMidia;
    int i;

    printf("\n===== CANCELAMENTO DE LOCACAO =====\n");

    printf("Digite o ID da locacao: ");
    scanf("%d", &idLocacao);

    posLocacao = buscarIndiceAluguel(idLocacao);

    if (posLocacao == -1) {
        printf("\nLocacao nao encontrada!\n");
        return;
    }

    if (aluguel[posLocacao].devolvido == 1) {
        printf("\nNao e possivel cancelar uma locacao ja devolvida!\n");
        return;
    }

    posMidia = buscarIndiceMidia(aluguel[posLocacao].idMidia);

    if (posMidia != -1) {
        vhsDvd[posMidia].copiasDisponiveis++;
        salvarMidiasCSV();
    }

    // Remove a locacao deslocando os elementos
    for (i = posLocacao; i < totalAlugueis - 1; i++) {
        aluguel[i] = aluguel[i + 1];
    }

    totalAlugueis--;

    salvarAlugueisCSV();

    printf("\nLocacao cancelada com sucesso!\n");
}

void montarMatrizLocacoes() {
    int i, j;

    for (i = 0; i < MAX_CLIENTES; i++) {
        for (j = 0; j < MAX_MIDIAS; j++) {
            matrizLocacoes[i][j] = 0;
        }
    }

    for (i = 0; i < totalAlugueis; i++) {
        int posCliente = -1;
        int posMidia = -1;
        int c, m;

        for (c = 0; c < totalClientes; c++) {
            if (clientes[c].id == aluguel[i].idCliente) {
                posCliente = c;
                break;
            }
        }

        for (m = 0; m < totalMidias; m++) {
            if (vhsDvd[m].id == aluguel[i].idMidia) {
                posMidia = m;
                break;
            }
        }

        if (posCliente != -1 && posMidia != -1) {
            matrizLocacoes[posCliente][posMidia]++;
        }
    }
}

void relatorioMidiaMaisAlugada() {
    int i, j;
    int quantidade;
    int ordem[MAX_MIDIAS];
    int total[MAX_MIDIAS];
    int aux;

    printf("\n===== MIDIAS MAIS ALUGADAS =====\n");

    if (totalMidias == 0 || totalAlugueis == 0) {
        printf("\nNao ha dados para gerar o relatorio!\n");
        return;
    }

    montarMatrizLocacoes();

    for (i = 0; i < totalMidias; i++) {
        ordem[i] = i;
        total[i] = 0;

        for (j = 0; j < totalClientes; j++) {
            total[i] += matrizLocacoes[j][i];
        }
    }

    for (i = 0; i < totalMidias - 1; i++) {
        for (j = 0; j < totalMidias - 1 - i; j++) {
            if (total[ordem[j]] < total[ordem[j + 1]]) {
                aux = ordem[j];
                ordem[j] = ordem[j + 1];
                ordem[j + 1] = aux;
            }
        }
    }

    for (i = 0; i < totalMidias; i++) {
        quantidade = total[ordem[i]];

        printf("\nMidia: %s\n", vhsDvd[ordem[i]].titulo);
        printf("Quantidade de locacoes: %d\n", quantidade);
    }
}

void relatorioClienteMaisLocacoes() {
    int i, j;
    int total[MAX_CLIENTES];
    int ordem[MAX_CLIENTES];
    int aux;

    printf("\n===== CLIENTES COM MAIS LOCACOES =====\n");

    if (totalClientes == 0 || totalAlugueis == 0) {
        printf("\nNao ha dados para gerar o relatorio!\n");
        return;
    }

    montarMatrizLocacoes();

    for (i = 0; i < totalClientes; i++) {
        ordem[i] = i;
        total[i] = 0;

        for (j = 0; j < totalMidias; j++) {
            total[i] += matrizLocacoes[i][j];
        }
    }

    for (i = 0; i < totalClientes - 1; i++) {
        for (j = 0; j < totalClientes - 1 - i; j++) {
            if (total[ordem[j]] < total[ordem[j + 1]]) {
                aux = ordem[j];
                ordem[j] = ordem[j + 1];
                ordem[j + 1] = aux;
            }
        }
    }

    for (i = 0; i < totalClientes; i++) {
        printf("\nCliente: %s\n", clientes[ordem[i]].nome);
        printf("Quantidade de locacoes: %d\n", total[ordem[i]]);
    }
}

void exibirMatrizLocacoes() {
    montarMatrizLocacoes();

    printf("\n===== MATRIZ 2D DE LOCACOES =====\n");

    printf("%-20s", "CLIENTE");

    for (int j = 0; j < totalMidias; j++) {
        printf("%-15s", vhsDvd[j].titulo);
    }

    printf("\n");

    for (int i = 0; i < totalClientes; i++) {
        printf("%-20s", clientes[i].nome);

        for (int j = 0; j < totalMidias; j++) {
            printf("%-15d", matrizLocacoes[i][j]);
        }

        printf("\n");
    }
}
void relatorioLocacoesDoCliente() {
    char nomeBusca[50];
    int i;
    int encontrou = 0;

    printf("\n===== LOCACOES POR CLIENTE =====\n");

    printf("Digite o nome do cliente: ");
    scanf(" %49[^\n]", nomeBusca);

    for (i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].nome, nomeBusca) == 0) {
            encontrou = 1;

            printf("\nCliente: %s\n", clientes[i].nome);

            for (int j = 0; j < totalAlugueis; j++) {
                if (aluguel[j].idCliente == clientes[i].id) {
                    printf("\nID da locacao: %d\n", aluguel[j].id);
                    printf("Midia: %s\n",
                        tituloDaMidia(aluguel[j].idMidia));
                    printf("Data da locacao: %s\n",
                        aluguel[j].dataLocacao);
                    printf("Valor: R$ %.2f\n",
                        aluguel[j].valorTotal);
                    printf("Status: %s\n",
                        aluguel[j].devolvido == 1 ?
                        "Devolvido" : "Em aberto");
                }
            }

            break;
        }
    }

    if (encontrou == 0) {
        printf("\nCliente nao encontrado!\n");
    }
}

void buscarAlugueis() {
    char nomeBusca[50];
    int i;
    int encontrou = 0;

    printf("\n===== BUSCAR LOCACOES =====\n");

    printf("Digite o nome ou parte do nome do cliente: ");
    scanf(" %49[^\n]", nomeBusca);

    for (i = 0; i < totalAlugueis; i++) {
        if (strstr(nomeDoCliente(aluguel[i].idCliente), nomeBusca) != NULL) {
            encontrou = 1;

            printf("\n-----------------------------\n");
            printf("ID da locacao: %d\n", aluguel[i].id);
            printf("Cliente: %s\n", nomeDoCliente(aluguel[i].idCliente));
            printf("Midia: %s\n", tituloDaMidia(aluguel[i].idMidia));
            printf("Dias locados: %d\n", aluguel[i].diasLocados);
            printf("Data da locacao: %s\n", aluguel[i].dataLocacao);
            printf("Data da devolucao: %s\n", aluguel[i].dataDevolucao);
            printf("Valor total: R$ %.2f\n", aluguel[i].valorTotal);

            printf("Status: %s\n",
                aluguel[i].devolvido == 1 ? "Devolvido" : "Em aberto");
        }
    }

    if (encontrou == 0) {
        printf("\nNenhuma locacao encontrada para esse cliente!\n");
    }
}

void editarAluguel() {
    int idLocacao;
    int posLocacao;
    int posMidia;
    int novosDias;
    char novaData[11];

    printf("\n===== EDITAR LOCACAO =====\n");

    printf("Digite o ID da locacao: ");
    scanf("%d", &idLocacao);

    posLocacao = buscarIndiceAluguel(idLocacao);

    if (posLocacao == -1) {
        printf("\nLocacao nao encontrada!\n");
        return;
    }

    if (aluguel[posLocacao].devolvido == 1) {
        printf("\nNao e possivel editar uma locacao ja devolvida!\n");
        return;
    }

    posMidia = buscarIndiceMidia(aluguel[posLocacao].idMidia);

    if (posMidia == -1) {
        printf("\nMidia nao encontrada!\n");
        return;
    }

    printf("Digite a nova quantidade de dias: ");
    scanf("%d", &novosDias);

    if (novosDias <= 0) {
        printf("\nQuantidade de dias invalida!\n");
        return;
    }

    printf("Digite a nova data da locacao (DD/MM/AAAA): ");
    scanf("%10s", novaData);

    aluguel[posLocacao].diasLocados = novosDias;

    strcpy(aluguel[posLocacao].dataLocacao, novaData);

    aluguel[posLocacao].valorTotal =
        vhsDvd[posMidia].precoLocacao * novosDias;

    salvarAlugueisCSV();

    printf("\nLocacao editada com sucesso!\n");
    printf("Novo valor total: R$ %.2f\n",
        aluguel[posLocacao].valorTotal);
}

void relatorioFinanceiro() {
    int i;
    float totalArrecadado = 0;

    printf("\n===== RELATORIO FINANCEIRO =====\n");

    if (totalAlugueis == 0) {
        printf("\nNenhuma locacao cadastrada!\n");
        return;
    }

    for (i = 0; i < totalAlugueis; i++) {
        totalArrecadado += aluguel[i].valorTotal;
    }

    printf("\nTotal de locacoes: %d\n", totalAlugueis);
    printf("Valor total das locacoes: R$ %.2f\n", totalArrecadado);
}

void menuAluguel() {
    int opcao;

    do {
        limparTela();
        printf("\n===== MENU DE LOCACOES =====\n");
        printf("1 - Alugar midia\n");
        printf("2 - Listar locacoes\n");
        printf("3 - Devolver midia\n");
        printf("4 - Cancelar locacao\n");
        printf("5 - Relatorio de midias mais alugadas\n");
        printf("6 - Relatorio de clientes com mais locacoes\n");
        printf("7 - Relatorio de locacoes por cliente\n");
        printf("8 - Relatorio financeiro\n");
        printf("9 - Buscar locacoes\n");
        printf("10 - Editar locacao\n");
        printf("11 - Exibir matriz 2D de locacoes\n");
        printf("0 - Voltar ao menu principal\n");

        printf("\nEscolha uma opcao: ");
        opcao = lerInteiro();

        switch (opcao) {
            case 1:
                menualugar();
                pausar();
                break;

            case 2:
                listarAlugueis();
                pausar();
                break;

            case 3:
                devolver();
                pausar();
                break;

            case 4:
                cancelarAluguel();
                pausar();
                break;

            case 5:
                relatorioMidiaMaisAlugada();
                pausar();
                break;

            case 6:
                relatorioClienteMaisLocacoes();
                pausar();
                break;

            case 7:
                relatorioLocacoesDoCliente();
                pausar();
                break;

            case 8:
                relatorioFinanceiro();
                pausar();
                break;

            case 9:
                buscarAlugueis();
                pausar();
                break;

            case 10:
                editarAluguel();
                pausar();
                break;
            case 11:
    			exibirMatrizLocacoes();
    			pausar();
    			break;
                
            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }

    } while (opcao != 0);
}

#endif
