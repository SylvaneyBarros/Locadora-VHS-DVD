//
// Created by Joice Barros on 13/11/26.
//

#ifndef LOCADORA_VHS_DVD_ALUGUEL_H
#define LOCADORA_VHS_DVD_ALUGUEL_H

#include <stdio.h>
#include <string.h>
#include "utils.h"

struct Aluguel {
    int id;
    int idCliente;
    int idMidia;
    char dataLocacao[11];
    char dataDevolucao[11];
    float valorTotal;
    int devolvido; // 1 = Devolvido, 0 = Em aberto
};

struct Aluguel aluguel[50];
int totalAlugueis = 0;

// ----------------------------------------------------------------------------
// Autor: Stephany Christina Barbosa da Silva - RGM 46810927
// ----------------------------------------------------------------------------

void menualugar() {
    int i;
    int idCliente;
    int idMidia;
    int posCliente = -1;

    printf("\n===== NOVA LOCACAO =====\n");

    printf("Digite o idCliente: ");
    scanf("%d", &idCliente);

    printf("Digite o idMidia: ");
    scanf("%d", &idMidia);

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
}

void listarAluguel() {
	int i;

	  printf("\n===== LISTA DE LOCACOES =====\n");

	if (totalAlugueis == 0) {
        printf("\nNenhuma locacao cadastrada!\n");
        return;
}

    for (i = 0; i < totalAlugueis; i++) {

		printf("\n-----------------------------\n");
		printf("ID da locacao: %d\n", aluguel[i].id);
		printf("ID do cliente: %d\n", aluguel[i].idCliente);
        printf("ID da midia: %d\n", aluguel[i].idMidia);
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
    printf("\n[Em construcao] Registro de devolucao por ID...\n");
}

void cancelarAluguel() {
    printf("\n[Em construcao] Cancelamento de locacao...\n");
}

void relatorioMidiaMaisAlugada() {
}

void relatorioClienteMaisLocacoes() {
}

void relatorioLocacoesDoCliente() {
}

void menuAluguel() {
    int menu;

    do {
        printf("\n--- MENU LOCACOES E RELATORIOS ---\n");
        printf("1 - Alugar\n");
        printf("2 - Listar / Buscar locacoes\n");
        printf("3 - Devolver\n");
        printf("4 - Cancelar locacao\n");
        printf("5 - [RELATORIO] Midia mais alugada\n");
        printf("6 - [RELATORIO] Cliente com mais locacoes\n");
        printf("7 - [RELATORIO] Locacoes de um cliente\n");
        printf("0 - Voltar\n");
        printf("Escolha uma acao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                menualugar();
                break;
            case 2:
                listarAluguel();
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
            case 0:
                printf("\nA voltar...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (menu != 0);
}

#endif //LOCADORA_VHS_DVD_ALUGUEL_H
