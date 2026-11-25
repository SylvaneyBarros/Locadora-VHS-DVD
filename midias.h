// Arquivo: midias.h | Autor: Natalia Santos - RGM: 37482971
#ifndef MIDIAS_H
#define MIDIAS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

#define MAX_MIDIAS 50

struct VHS_DVD {
    int id;
    char titulo[50];
    char tipoDeMidia[4]; // "VHS" ou "DVD" (3 letras + o '\0')
    char genero[20];
    float precoLocacao;
    int copiasDisponiveis;
};

FILE *arquivoMidias;
struct VHS_DVD vhsDvd[MAX_MIDIAS];
int totalMidias = 0;

// ----------------------------------------------------------------------------
// PERSISTENCIA: grava e le o arquivo midias.csv (campos separados por ;)
// ----------------------------------------------------------------------------
void salvarMidiasCSV() {
    FILE *arq = fopen("midias.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar midias.csv!\n");
        return;
    }
    for (int i = 0; i < totalMidias; i++) {
        fprintf(arq, "%d;%s;%s;%s;%.2f;%d\n",
                vhsDvd[i].id,
                vhsDvd[i].titulo,
                vhsDvd[i].tipoDeMidia,
                vhsDvd[i].genero,
                vhsDvd[i].precoLocacao,
                vhsDvd[i].copiasDisponiveis);
    }
    fclose(arq);
}

void carregarMidias() {
    arquivoMidias = fopen("midias.csv", "r");
    if (arquivoMidias == NULL) {
        return;
    }
    totalMidias = 0;
    struct VHS_DVD auxMidia;
    while (fscanf(arquivoMidias, "%d;%49[^;];%3[^;];%19[^;];%f;%d\n",
                  &auxMidia.id,
                  auxMidia.titulo,
                  auxMidia.tipoDeMidia,
                  auxMidia.genero,
                  &auxMidia.precoLocacao,
                  &auxMidia.copiasDisponiveis) == 6) {
        if (totalMidias < MAX_MIDIAS) {
            vhsDvd[totalMidias] = auxMidia;
            totalMidias++;
        }
    }
    fclose(arquivoMidias);
}

// Devolve a posicao da midia no vetor, ou -1 se o ID nao existir
int buscarIndiceMidia(int idProcurado) {
    for (int i = 0; i < totalMidias; i++) {
        if (vhsDvd[i].id == idProcurado) return i;
    }
    return -1;
}

// ----------------------------------------------------------------------------
// OPERACOES DO MODULO
// ----------------------------------------------------------------------------
void cadastrarMidia() {
    if (totalMidias >= MAX_MIDIAS) {
        printf("\n[ERRO] Catalogo lotado!\n");
        return;
    }

    printf("\nID da nova midia: ");
    int id = lerInteiro();
    if (id <= 0) {
        printf("[ERRO] ID invalido!\n");
        return;
    }
    if (buscarIndiceMidia(id) != -1) {
        printf("[ERRO] Ja existe uma midia com o ID %d!\n", id);
        return;
    }

    vhsDvd[totalMidias].id = id;
    printf("Titulo: ");
    scanf(" %49[^\n]", vhsDvd[totalMidias].titulo);
    printf("Genero: ");
    scanf(" %19[^\n]", vhsDvd[totalMidias].genero);

    char tipo[4];
    do {
        printf("Tipo da midia (VHS ou DVD): ");
        scanf(" %3s", tipo);
    } while (strcmp(tipo, "VHS") != 0 && strcmp(tipo, "DVD") != 0);
    strcpy(vhsDvd[totalMidias].tipoDeMidia, tipo);

    printf("Preco da locacao (R$): ");
    scanf("%f", &vhsDvd[totalMidias].precoLocacao);
    printf("Copias disponiveis: ");
    vhsDvd[totalMidias].copiasDisponiveis = lerInteiro();
    if (vhsDvd[totalMidias].copiasDisponiveis < 0) vhsDvd[totalMidias].copiasDisponiveis = 0;

    totalMidias++;
    salvarMidiasCSV();
    printf("[OK] Midia cadastrada e salva em midias.csv!\n");
}

void listarMidias() {
    printf("\n--- CATALOGO DE MIDIAS (%d) ---\n", totalMidias);
    if (totalMidias == 0) {
        printf("Nenhuma midia cadastrada.\n");
        return;
    }
    printf("%-4s %-30s %-5s %-12s %-8s %s\n", "ID", "Titulo", "Tipo", "Genero", "Preco", "Copias");
    for (int i = 0; i < totalMidias; i++) {
        printf("%-4d %-30s %-5s %-12s R$ %.2f  %d\n",
               vhsDvd[i].id, vhsDvd[i].titulo, vhsDvd[i].tipoDeMidia,
               vhsDvd[i].genero, vhsDvd[i].precoLocacao, vhsDvd[i].copiasDisponiveis);
    }
}

// Copia o texto para "dest" trocando cada letra por minuscula (para a busca ignorar maiusculas)
void titulosMinusculo(char *dest, const char *orig) {
    int i;
    for (i = 0; orig[i] != '\0'; i++) {
        dest[i] = tolower((unsigned char) orig[i]);
    }
    dest[i] = '\0';
}

void buscarMidiaPorTitulo() {
    char termo[50];
    char termoMin[50];
    char tituloMin[50];
    int achou = 0;

    printf("\nDigite parte do titulo: ");
    scanf(" %49[^\n]", termo);

    titulosMinusculo(termoMin, termo);

    for (int i = 0; i < totalMidias; i++) {
        titulosMinusculo(tituloMin, vhsDvd[i].titulo);
        if (strstr(tituloMin, termoMin) != NULL) {
            printf(" -> [%d] %s (%s) | R$ %.2f | %d copias\n",
                   vhsDvd[i].id, vhsDvd[i].titulo, vhsDvd[i].tipoDeMidia,
                   vhsDvd[i].precoLocacao, vhsDvd[i].copiasDisponiveis);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhuma midia encontrada com '%s'.\n", termo);
}

void editarMidia() {
    printf("\nID da midia que deseja EDITAR: ");
    int id = lerInteiro();
    int pos = buscarIndiceMidia(id);
    if (pos == -1) {
        printf("[ERRO] Midia nao encontrada!\n");
        return;
    }

    printf("Editando '%s'.\n", vhsDvd[pos].titulo);
    printf("Novo preco da locacao (R$): ");
    scanf("%f", &vhsDvd[pos].precoLocacao);
    printf("Nova quantidade de copias: ");
    int copias = lerInteiro();
    if (copias < 0) {
        printf("[ERRO] Quantidade invalida! Copias mantidas.\n");
    } else {
        vhsDvd[pos].copiasDisponiveis = copias;
    }

    salvarMidiasCSV();
    printf("[OK] Midia atualizada na memoria e no arquivo CSV!\n");
}

void removerMidia() {
    printf("\nID da midia que deseja REMOVER: ");
    int id = lerInteiro();
    int pos = buscarIndiceMidia(id);
    if (pos == -1) {
        printf("[ERRO] Midia nao encontrada!\n");
        return;
    }

    for (int j = pos; j < totalMidias - 1; j++) {
        vhsDvd[j] = vhsDvd[j + 1];
    }
    totalMidias--;
    salvarMidiasCSV();
    printf("[OK] Midia removida do catalogo e do arquivo CSV!\n");
}

void menuMidia() {
    int menu;
    do {
        limparTela();
        printf("--- MENU MIDIA VHS/DVD ---\n");
        printf(" 1 - Cadastrar midia\n");
        printf(" 2 - Listar catalogo\n");
        printf(" 3 - Buscar midia por titulo\n");
        printf(" 4 - Editar midia\n");
        printf(" 5 - Remover midia\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma acao: ");
        menu = lerInteiro();

        switch (menu) {
            case 1: cadastrarMidia(); pausar(); break;
            case 2: listarMidias(); pausar(); break;
            case 3: buscarMidiaPorTitulo(); pausar(); break;
            case 4: editarMidia(); pausar(); break;
            case 5: removerMidia(); pausar(); break;
            case 0: break;
            default: printf("\n[ERRO] Opcao invalida!\n"); pausar();
        }
    } while (menu != 0);
}

#endif