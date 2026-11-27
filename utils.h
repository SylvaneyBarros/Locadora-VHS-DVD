// Arquivo: utils.h | Funcoes de uso comum da equipe
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

// Limpa o terminal (Windows usa "cls", Linux/macOS usam "clear")
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Espera o usuario ler a mensagem antes da tela ser limpa de novo
void pausar() {
    #ifdef _WIN32
        system("pause");
    #else
        printf("\nPressione ENTER para continuar...");
        getchar();
        getchar();
    #endif
}

// Le um numero inteiro. Se o usuario digitar letra, descarta a linha e devolve -1
// (evita o programa entrar em loop infinito)
int lerInteiro() {
    int numero;
    if (scanf("%d", &numero) != 1) {
        scanf("%*[^\n]"); // o * descarta tudo ate o fim da linha, sem guardar
        return -1;
    }
    return numero;
}

#endif