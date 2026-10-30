#include <stdio.h>

//============================================================================
// PARTE 4 - MODULO DE LOCACOES E RELATORIOS + FUNCAO MAIN
// ============================================================================


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
// Autor: Stephany Christina Barbosa da Silva - 46810927
// ----------------------------------------------------------------------------
void alugar() {
    printf("\n[Em construcao] Registro de locacao (ID Cliente + ID Midia)...\n");
}

void listarAluguel() {
    printf("\n[Em construcao] Listagem e Busca de locacoes...\n");
}

void devolver() {
    printf("\n[Em construcao] Registro de devolucao por ID...\n");
}

void cancelarAluguel() {
    printf("\n[Em construcao] Cancelamento de locacao...\n");
}

void relatorioMidiaMaisAlugada() {
    printf("\n[Em construcao] Relatorio: midia mais alugada...\n");
}

void relatorioClienteMaisLocacoes() {
    printf("\n[Em construcao] Relatorio: cliente com mais locacoes...\n");
}

void relatorioLocacoesDoCliente() {
    printf("\n[Em construcao] Relatorio: locacoes de um cliente...\n");
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
                alugar();
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

int main() {
    int menu;
    
    do {
        printf("\n========================================\n");
        printf("     LOCADORA DE VIDEO - VHS/DVD\n");
        printf("========================================\n");
        printf("1 - Cliente\n");
        printf("2 - Midia VHS/DVD\n");
        printf("3 - Compra de Midias / Fornecedores\n");
        printf("4 - Locacoes e Relatorios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);
        
        switch (menu) {
            case 1:
                // menuCliente();
                break;
            case 2:
                // menuMidia();
                break;
            case 3:
                // Compra/Fornecedores
                break;
            case 4:
                menuAluguel();
                break;
            case 0:
                printf("\nA sair do programa. Ate breve!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (menu != 0);
    
    return 0;
}
