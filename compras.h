// Arquivo: compras.h | Autor: Maria Vitoria Machado - RGM: 39001814
#ifndef COMPRAS_H
#define COMPRAS_H

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "midias.h" // a compra aumenta o estoque de copias da midia

#define MAX_COMPRAS 50

struct CompraMidia {
    int id;
    int idMidia;          // qual midia foi comprada (cruza com midias.h)
    char fornecedor[40];
    char descricao[40];
    float custoCompra;    // custo de UMA copia
    int quantidade;
};

struct CompraMidia compras[MAX_COMPRAS];
int totalCompras = 0;

// ----------------------------------------------------------------------------
// PERSISTENCIA: grava e le o arquivo compras.csv
// ----------------------------------------------------------------------------
void salvarComprasCSV() {
    FILE *arq = fopen("compras.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar compras.csv!\n");
        return;
    }
    for (int i = 0; i < totalCompras; i++) {
        fprintf(arq, "%d;%d;%s;%s;%.2f;%d\n",
                compras[i].id,
                compras[i].idMidia,
                compras[i].fornecedor,
                compras[i].descricao,
                compras[i].custoCompra,
                compras[i].quantidade);
    }
    fclose(arq);
}

void carregarComprasCSV() {
    FILE *arq = fopen("compras.csv", "r");
    if (arq == NULL) return;

    totalCompras = 0;
    while (totalCompras < MAX_COMPRAS &&
           fscanf(arq, "%d;%d;%39[^;];%39[^;];%f;%d\n",
                  &compras[totalCompras].id,
                  &compras[totalCompras].idMidia,
                  compras[totalCompras].fornecedor,
                  compras[totalCompras].descricao,
                  &compras[totalCompras].custoCompra,
                  &compras[totalCompras].quantidade) == 6) {
        totalCompras++;
    }
    fclose(arq);
}

int buscarIndiceCompra(int idProcurado) {
    for (int i = 0; i < totalCompras; i++) {
        if (compras[i].id == idProcurado) return i;
    }
    return -1;
}

// ----------------------------------------------------------------------------
// OPERACOES DO MODULO
// ----------------------------------------------------------------------------
void cadastrarCompra() {
    if (totalCompras >= MAX_COMPRAS) {
        printf("\n[ERRO] Limite de compras atingido!\n");
        return;
    }

    printf("\nID da nova compra: ");
    int id = lerInteiro();
    if (id <= 0) {
        printf("[ERRO] ID invalido!\n");
        return;
    }
    if (buscarIndiceCompra(id) != -1) {
        printf("[ERRO] Ja existe uma compra com o ID %d!\n", id);
        return;
    }

    printf("ID da midia comprada: ");
    int idMidia = lerInteiro();
    int posMidia = buscarIndiceMidia(idMidia);
    if (posMidia == -1) {
        printf("[ERRO] Midia nao encontrada! Cadastre a midia antes.\n");
        return;
    }

    compras[totalCompras].id = id;
    compras[totalCompras].idMidia = idMidia;
    printf("Fornecedor: ");
    scanf(" %39[^\n]", compras[totalCompras].fornecedor);
    printf("Descricao da compra: ");
    scanf(" %39[^\n]", compras[totalCompras].descricao);
    printf("Custo de cada copia (R$): ");
    scanf("%f", &compras[totalCompras].custoCompra);
    printf("Quantidade comprada: ");
    int qtd = lerInteiro();
    if (qtd <= 0) {
        printf("[ERRO] Quantidade invalida! Compra cancelada.\n");
        return;
    }
    compras[totalCompras].quantidade = qtd;

    vhsDvd[posMidia].copiasDisponiveis += qtd; // da entrada no estoque da midia
    totalCompras++;

    salvarComprasCSV();
    salvarMidiasCSV();
    printf("[OK] Compra registrada! '%s' agora tem %d copias.\n",
           vhsDvd[posMidia].titulo, vhsDvd[posMidia].copiasDisponiveis);
}

void listarCompras() {
    printf("\n--- COMPRAS REGISTRADAS (%d) ---\n", totalCompras);
    if (totalCompras == 0) {
        printf("Nenhuma compra registrada.\n");
        return;
    }
    printf("%-4s %-7s %-26s %-8s %-5s %s\n", "ID", "Midia", "Fornecedor", "Custo", "Qtd", "Total");
    for (int i = 0; i < totalCompras; i++) {
        printf("%-4d %-7d %-26s R$ %-5.2f %-5d R$ %.2f\n",
               compras[i].id, compras[i].idMidia, compras[i].fornecedor,
               compras[i].custoCompra, compras[i].quantidade,
               compras[i].custoCompra * compras[i].quantidade);
    }
}

void buscarCompraPorFornecedor() {
    char termo[40];
    int achou = 0;

    printf("\nDigite parte do nome do fornecedor: ");
    scanf(" %39[^\n]", termo);

    for (int i = 0; i < totalCompras; i++) {
        if (strstr(compras[i].fornecedor, termo) != NULL) {
            printf(" -> [%d] %s | %s | %d un. a R$ %.2f\n",
                   compras[i].id, compras[i].fornecedor, compras[i].descricao,
                   compras[i].quantidade, compras[i].custoCompra);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhuma compra encontrada para '%s'.\n", termo);
}

void editarCompra() {
    printf("\nID da compra que deseja EDITAR: ");
    int id = lerInteiro();
    int pos = buscarIndiceCompra(id);
    if (pos == -1) {
        printf("[ERRO] Compra nao encontrada!\n");
        return;
    }

    printf("Editando compra de '%s'.\n", compras[pos].descricao);
    printf("Novo custo de cada copia (R$): ");
    float novoCusto;
    scanf("%f", &novoCusto);
    printf("Nova quantidade: ");
    int novaQtd = lerInteiro();
    if (novaQtd <= 0) {
        printf("[ERRO] Quantidade invalida! Nada foi alterado.\n");
        return;
    }

    int posMidia = buscarIndiceMidia(compras[pos].idMidia);
    int diferenca = novaQtd - compras[pos].quantidade;
    if (posMidia != -1) {
        if (vhsDvd[posMidia].copiasDisponiveis + diferenca < 0) {
            printf("[ERRO] Estoque ficaria negativo (copias ja alugadas)! Nada foi alterado.\n");
            return;
        }
        vhsDvd[posMidia].copiasDisponiveis += diferenca; // ajusta o estoque pela diferenca
    }

    compras[pos].custoCompra = novoCusto;
    compras[pos].quantidade = novaQtd;
    salvarComprasCSV();
    salvarMidiasCSV();
    printf("[OK] Compra atualizada na memoria e nos arquivos CSV!\n");
}

void removerCompra() {
    printf("\nID da compra que deseja REMOVER: ");
    int id = lerInteiro();
    int pos = buscarIndiceCompra(id);
    if (pos == -1) {
        printf("[ERRO] Compra nao encontrada!\n");
        return;
    }

    int posMidia = buscarIndiceMidia(compras[pos].idMidia);
    if (posMidia != -1) {
        if (vhsDvd[posMidia].copiasDisponiveis < compras[pos].quantidade) {
            printf("[ERRO] Nao da para cancelar: parte dessas copias ja esta alugada!\n");
            return;
        }
        vhsDvd[posMidia].copiasDisponiveis -= compras[pos].quantidade; // tira do estoque
    }

    for (int j = pos; j < totalCompras - 1; j++) {
        compras[j] = compras[j + 1];
    }
    totalCompras--;
    salvarComprasCSV();
    salvarMidiasCSV();
    printf("[OK] Compra removida do sistema e dos arquivos CSV!\n");
}

// Relatorio: quanto a locadora ja investiu e qual foi a compra mais cara
void relatorioInvestimento() {
    if (totalCompras == 0) {
        printf("\nNenhuma compra registrada para gerar o relatorio.\n");
        return;
    }

    float totalGasto = 0;
    int totalCopias = 0;
    int posMaior = 0;
    for (int i = 0; i < totalCompras; i++) {
        float subtotal = compras[i].custoCompra * compras[i].quantidade;
        totalGasto += subtotal;
        totalCopias += compras[i].quantidade;
        if (subtotal > compras[posMaior].custoCompra * compras[posMaior].quantidade) {
            posMaior = i;
        }
    }

    printf("\n--- RELATORIO DE INVESTIMENTO EM MIDIAS ---\n");
    printf("Compras registradas : %d\n", totalCompras);
    printf("Copias compradas    : %d\n", totalCopias);
    printf("Total investido     : R$ %.2f\n", totalGasto);
    printf("Custo medio por copia: R$ %.2f\n", totalGasto / totalCopias);
    printf("Compra mais cara    : [%d] %s - R$ %.2f\n",
           compras[posMaior].id, compras[posMaior].descricao,
           compras[posMaior].custoCompra * compras[posMaior].quantidade);
}

void menuCompra() {
    int menu;
    do {
        limparTela();
        printf("--- MENU COMPRA DE MIDIAS / FORNECEDORES ---\n");
        printf(" 1 - Registrar compra\n");
        printf(" 2 - Listar compras\n");
        printf(" 3 - Buscar compra por fornecedor\n");
        printf(" 4 - Editar compra\n");
        printf(" 5 - Remover compra\n");
        printf(" 6 - [RELATORIO] Investimento em midias\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma acao: ");
        menu = lerInteiro();

        switch (menu) {
            case 1: cadastrarCompra(); pausar(); break;
            case 2: listarCompras(); pausar(); break;
            case 3: buscarCompraPorFornecedor(); pausar(); break;
            case 4: editarCompra(); pausar(); break;
            case 5: removerCompra(); pausar(); break;
            case 6: relatorioInvestimento(); pausar(); break;
            case 0: break;
            default: printf("\n[ERRO] Opcao invalida!\n"); pausar();
        }
    } while (menu != 0);
}

#endif