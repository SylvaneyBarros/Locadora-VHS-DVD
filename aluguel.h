//
// Created by Joice Barros on 13/11/26.
//

#ifndef LOCADORA_VHS_DVD_ALUGUEL_H
#define LOCADORA_VHS_DVD_ALUGUEL_H

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "clientes.h"
#include "midias.h"

/* Os clientes.h e midias.h usam vetores com capacidade 50. */
#ifndef MAX_CLIENTES
#define MAX_CLIENTES 50
#endif

#ifndef MAX_ALUGUEIS
#define MAX_ALUGUEIS 50
#endif

struct Aluguel {
    int id;
    int idCliente;
    int idMidia;
    int diasLocados;
    char dataLocacao[11];
    char dataDevolucao[11];
    float valorTotal;
    int devolvido; /* 1 = devolvido; 0 = em aberto */
};

struct Aluguel aluguel[MAX_ALUGUEIS];
int totalAlugueis = 0;
int matrizLocacoes[MAX_CLIENTES][MAX_MIDIAS];

/* Salva todas as locacoes no arquivo CSV. */
void salvarAlugueisCSV(void) {
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
                aluguel[i].devolvido);
    }

    fclose(arquivo);
}

/* Carrega as locacoes salvas no arquivo CSV. */
void carregarAlugueisCSV(void) {
    FILE *arquivo;
    int resultado;

    arquivo = fopen("locacoes.csv", "r");
    if (arquivo == NULL) {
        /* Na primeira execucao, o arquivo ainda pode nao existir. */
        totalAlugueis = 0;
        return;
    }

    totalAlugueis = 0;

    while (totalAlugueis < MAX_ALUGUEIS) {
        resultado = fscanf(arquivo, "%d;%d;%d;%d;%10[^;];%10[^;];%f;%d",
        &aluguel[totalAlugueis].id,
        &aluguel[totalAlugueis].idCliente,
        &aluguel[totalAlugueis].idMidia,
        &aluguel[totalAlugueis].diasLocados,
        aluguel[totalAlugueis].dataLocacao,
        aluguel[totalAlugueis].dataDevolucao,
        &aluguel[totalAlugueis].valorTotal,
        &aluguel[totalAlugueis].devolvido);

        if (resultado != 8) {
            break;
        }

        totalAlugueis++;
    }

    fclose(arquivo);
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

const char *nomeDoCliente(int idCliente) {
    int i;

    for (i = 0; i < totalClientes; i++) {
        if (clientes[i].id == idCliente) {
            return clientes[i].nome;
        }
    }

    return "(removido)";
}

const char *tituloDaMidia(int idMidia) {
    int i;

    for (i = 0; i < totalMidias; i++) {
        if (vhsDvd[i].id == idMidia) {
            return vhsDvd[i].titulo;
        }
    }

    return "(removida)";
}


// ----------------------------------------------------------------------------
// Autor: Stephany Christina Barbosa da Silva - RGM 46810927
// ----------------------------------------------------------------------------

void menualugar(void) {
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
    if (scanf("%d", &idCliente) != 1) {
        printf("\nID invalido!\n");
        scanf("%*[^\n]");
        return;
    }

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

    /*
       O arquivo clientes.h enviado nao possui o campo multaPendente.
       Por isso, a verificacao de multa foi retirada para permitir compilar.
    */

    printf("Digite o ID da midia: ");
    if (scanf("%d", &idMidia) != 1) {
        printf("\nID invalido!\n");
        scanf("%*[^\n]");
        return;
    }

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
    if (scanf("%d", &diasLocados) != 1 || diasLocados <= 0) {
        printf("\nQuantidade de dias invalida!\n");
        scanf("%*[^\n]");
        return;
    }

    printf("Digite a data da locacao (DD/MM/AAAA): ");
    if (scanf("%10s", dataLocacao) != 1) {
        printf("\nData invalida!\n");
        return;
    }

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

void listarAlugueis(void) {
    int i;

    printf("\n===== LISTA DE LOCACOES =====\n");

    if (totalAlugueis == 0) {
        printf("\nNenhuma locacao cadastrada!\n");
        return;
    }

    for (i = 0; i < totalAlugueis; i++) {
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

    printf("\n-----------------------------\n");
}

void devolver(void) {
    int idLocacao;
    int posLocacao;
    int posMidia;
    char dataDevolucao[11];

    printf("\n===== DEVOLUCAO DE MIDIA =====\n");
    printf("Digite o ID da locacao: ");

    if (scanf("%d", &idLocacao) != 1) {
        printf("\nID invalido!\n");
        scanf("%*[^\n]");
        return;
    }

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
    if (scanf("%10s", dataDevolucao) != 1) {
        printf("\nData invalida!\n");
        return;
    }

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

void cancelarAluguel(void) {
    int idLocacao;
    int posLocacao;
    int posMidia;
    int i;

    printf("\n===== CANCELAMENTO DE LOCACAO =====\n");
    printf("Digite o ID da locacao: ");

    if (scanf("%d", &idLocacao) != 1) {
        printf("\nID invalido!\n");
        scanf("%*[^\n]");
        return;
    }

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

    for (i = posLocacao; i < totalAlugueis - 1; i++) {
        aluguel[i] = aluguel[i + 1];
    }

    totalAlugueis--;
    salvarAlugueisCSV();

    printf("\nLocacao cancelada com sucesso!\n");
}

void montarMatrizLocacoes(void) {
    int i;
    int j;

    for (i = 0; i < MAX_CLIENTES; i++) {
        for (j = 0; j < MAX_MIDIAS; j++) {
            matrizLocacoes[i][j] = 0;
        }
    }

    for (i = 0; i < totalAlugueis; i++) {
        int posCliente = -1;
        int posMidia = -1;
        int c;
        int m;

        for (c = 0; c < totalClientes && c < MAX_CLIENTES; c++) {
            if (clientes[c].id == aluguel[i].idCliente) {
                posCliente = c;
                break;
            }
        }

        for (m = 0; m < totalMidias && m < MAX_MIDIAS; m++) {
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

void relatorioMidiaMaisAlugada(void) {
    int i;
    int j;
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

        for (j = 0; j < totalClientes && j < MAX_CLIENTES; j++) {
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
        printf("\nMidia: %s\n", vhsDvd[ordem[i]].titulo);
        printf("Quantidade de locacoes: %d\n", total[ordem[i]]);
    }
}

void relatorioClienteMaisLocacoes(void) {
    int i;
    int j;
    int total[MAX_CLIENTES];
    int ordem[MAX_CLIENTES];
    int aux;

    printf("\n===== CLIENTES COM MAIS LOCACOES =====\n");

    if (totalClientes == 0 || totalAlugueis == 0) {
        printf("\nNao ha dados para gerar o relatorio!\n");
        return;
    }

    montarMatrizLocacoes();

    for (i = 0; i < totalClientes && i < MAX_CLIENTES; i++) {
        ordem[i] = i;
        total[i] = 0;

        for (j = 0; j < totalMidias && j < MAX_MIDIAS; j++) {
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

    for (i = 0; i < totalClientes && i < MAX_CLIENTES; i++) {
        printf("\nCliente: %s\n", clientes[ordem[i]].nome);
        printf("Quantidade de locacoes: %d\n", total[ordem[i]]);
    }
}

void relatorioLocacoesDoCliente(void) {
    char nomeBusca[50];
    int i;
    int encontrou = 0;

    printf("\n===== LOCACOES POR CLIENTE =====\n");
    printf("Digite o nome do cliente: ");
    scanf(" %49[^\n]", nomeBusca);

    for (i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].nome, nomeBusca) == 0) {
            int j;
            encontrou = 1;

            printf("\nCliente: %s\n", clientes[i].nome);

            for (j = 0; j < totalAlugueis; j++) {
                if (aluguel[j].idCliente == clientes[i].id) {
                    printf("\nID da locacao: %d\n", aluguel[j].id);
                    printf("Midia: %s\n",
                           tituloDaMidia(aluguel[j].idMidia));
                    printf("Data da locacao: %s\n",
                           aluguel[j].dataLocacao);
                    printf("Valor: R$ %.2f\n", aluguel[j].valorTotal);
                    printf("Status: %s\n",
                           aluguel[j].devolvido == 1 ?
                           "Devolvido" : "Em aberto");
                }
            }
            break;
        }
    }

    if (!encontrou) {
        printf("\nCliente nao encontrado!\n");
    }
}

void relatorioFinanceiro(void) {
    int i;
    float totalArrecadado = 0.0f;

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

void menuAluguel(void) {
    int opcao;

    do {
        printf("\n===== MENU DE LOCACOES =====\n");
        printf("1 - Alugar midia\n");
        printf("2 - Listar locacoes\n");
        printf("3 - Devolver midia\n");
        printf("4 - Cancelar locacao\n");
        printf("5 - Relatorio de midias mais alugadas\n");
        printf("6 - Relatorio de clientes com mais locacoes\n");
        printf("7 - Relatorio de locacoes por cliente\n");
        printf("8 - Relatorio financeiro\n");
        printf("0 - Voltar ao menu principal\n");

        printf("\nEscolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida!\n");
            scanf("%*[^\n]");
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                menualugar();
                break;
            case 2:
                listarAlugueis();
                break;
            case 3:
                devolver();
                break;
            case 4:
                cancelarAluguel();
                break;
            case 5:
                relatorioMidiaMaisAlugada();
                break;
            case 6:
                relatorioClienteMaisLocacoes();
                break;
            case 7:
                relatorioLocacoesDoCliente();
                break;
            case 8:
                relatorioFinanceiro();
                break;
            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);
}

#endif /* LOCADORA_VHS_DVD_ALUGUEL_H */

