#include <stdio.h>
#include <stdbool.h>

struct Cliente {
    int id;
    char nome[50];
    char dataDeNascimento[11];
    char telefone[12];
    float multaPendente;
    int ativo; // 1 = Ativo, 0 = Removido
};

struct VHS_DVD {
    int id;
    char titulo[50];
    char tipoDeMidia[4]; // "VHS" ou "DVD"
    char genero[20];
    float precoLocacao;
    int copiasDisponiveis;
    int ativo; // 1 = Ativo, 0 = Removido
};

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

struct Cliente clientes[50];
int totalClientes = 0;

struct VHS_DVD vhsDvd[50];
int totalMidias = 0;



// ----------------------------------------------------------------------------
// Sylvaney Joice Alves de Barros - RGM: 47501863
// ----------------------------------------------------------------------------
void cadastrarCliente() {
    printf("\nCadastro de Cliente\n");
    if(totalClientes >= 50) {
        printf("Excede a capacidade de cadastro.\n");
        return;
    }
    printf("Nome: ");
    scanf("%s", clientes[totalClientes].nome);

    printf("Data de Nascimento: ");
    scanf(" %s", clientes[totalClientes].dataDeNascimento);

    printf("Telefone: ");
    scanf(" %s", clientes[totalClientes].telefone);

    clientes[totalClientes].id = totalClientes;

    clientes[totalClientes].ativo = 1;

    totalClientes++;

    printf("Cliente cadastrado com sucesso!\n");

}

void listarCliente() {
    printf("\nListagem de Clientes\n");

    if(totalClientes == 0) {
        printf("Não há clientes cadastrados.\n");
        return;
    }
    for(int i = 0; i < totalClientes; i++) {
        printf("%d - %s\n", clientes[i].id, clientes[i].nome);
    }
}

void localizarClienteNome() {

}

void localizarClienteId() {

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
                printf("Retornando ao menu cliente\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida!\n");
        }

    } while (menu != 0);
}

void excluirCliente() {
    printf("\nExcluir de Cliente...\n");
}

void menuCliente() {
    int menu;

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

// ----------------------------------------------------------------------------
// Natalia Santos - RGM: 37482971
// ----------------------------------------------------------------------------
void cadastrarMidia() {
    printf("\n[Em construcao] Cadastro de Midia...\n");
    printf("Campos previstos: Titulo, Tipo (VHS/DVD), Genero, Preco e Copias.\n");
}

void listarMidia() {
    printf("\n[Em construcao] Listagem e Busca de Midias...\n");
}

void editarMidia() {
    printf("\n[Em construcao] Edicao de Midia por ID...\n");
}

void excluirMidia() {
    printf("\n[Em construcao] Remocao de Midia...\n");
}

void menuMidia() {
    int menu;

    do {
        printf("\n--- MENU MIDIA VHS/DVD ---\n");
        printf(" 1 - Cadastrar midia\n");
        printf(" 2 - Listar / Buscar midia\n");
        printf(" 3 - Editar midia\n");
        printf(" 4 - Excluir midia\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma acao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                cadastrarMidia();
                break;
            case 2:
                listarMidia();
                break;
            case 3:
                editarMidia();
                break;
            case 4:
                excluirMidia();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (menu != 0);
}


struct CompraMidia {
    int id;
    char fornecedor[40];
    char descricao[40];
    float custoCompra;
    int quantidade;
    int ativo; // 1 = Ativa, 0 = Cancelada
};

struct CompraMidia compras[50];
int totalCompras = 0;

// ----------------------------------------------------------------------------
// Autor: Maria Vitória Machado - RGM: 39001814
// ----------------------------------------------------------------------------
void cadastrarCompra() {
    printf("\n[Em construcao] Registro de compra de midias...\n");
    printf("Campos previstos: Fornecedor, Descricao, Custo e Quantidade.\n");
}

void listarCompra() {
    printf("\n[Em construcao] Listagem e Busca de compras por fornecedor...\n");
}

void editarCompra() {
    printf("\n[Em construcao] Edicao de compra por ID...\n");
}

void excluirCompra() {
    printf("\n[Em construcao] Cancelamento de compra...\n");
}

void menuCompra() {
    int menu;

    do {
        printf("\n--- MENU COMPRA DE MIDIAS / FORNECEDORES ---\n");
        printf(" 1 - Registrar compra\n");
        printf(" 2 - Listar / Buscar compras\n");
        printf(" 3 - Editar compra\n");
        printf(" 4 - Cancelar compra\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma acao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                cadastrarCompra();
                break;
            case 2:
                listarCompra();
                break;
            case 3:
                editarCompra();
                break;
            case 4:
                excluirCompra();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (menu != 0);
}

// Autor: Stephany Christina Barbosa da Silva - RGM 46810927

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

int main(void) {

    int menu;

    do {
        printf("--- Locadora de video ---\n");
        printf(" 1 - Cliente\n");
        printf(" 2 - Midia VHS/DVD\n");
        printf(" 3 - Alugar/Devolver\n");
        printf(" 4 - Comprar midea\n");
        printf(" 0 - Sair\n");
        scanf("%d", &menu);

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
