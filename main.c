#include "locacoes.h"
#include "clientes.h"
#include "compras.h"
#include "midias.h"

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    int menu;

    carregarClientes();
    carregarMidias();
    carregarCompras();
    carregarAlugueis();

    do {
        printf("--- Locadora de video ---\n");
        printf(" 1 - Cliente\n");
        printf(" 2 - Midia VHS/DVD\n");
        printf(" 3 - Alugar/Devolver\n");
        printf(" 4 - Comprar midias\n");
        printf(" 0 - Sair\n");
        menu = lerInteiro();

        switch (menu) {
            case 1:
                menuCliente();
                break;
            case 2:
                menuMidia();
                break;
            case 3:
                menuAluguel();
                break;
            case 4:
            	menuCompra();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }
    while (menu != 0);

    return 0;
}
