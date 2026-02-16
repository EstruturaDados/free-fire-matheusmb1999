// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

//     return 0;
// }

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.


// --------------------------------
// --- MEU CODIGO INICIA ABAIXO ---
// --------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 10 // Número máximo de itens na mochila

// --- Estrutura para representar um item ---
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --- Estrutura para representar a mochila ---
typedef struct {
    Item itens[TAM_MAX];
    int quantidade;
} Mochila;

// --- Funções do jogo ---

// Protótipos das funções do jogo
void titulo(const Mochila *mochila);
void inicializarMochila(Mochila *mochila);
void inserirItem(Mochila *mochila, const char* nomeItem, const char* tipoItem, int quantidadeItem);
void removerItem(Mochila *mochila, const char* nomeItem);
void listarItens(const Mochila *mochila);
void listarItensSimples(const Mochila *mochila);
void buscarItem(const Mochila *mochila, const char* nomeItem);
void menuPrincipal(Mochila *mochila);


// --- Programa principal ---
int main() {

    Mochila mochila;
    inicializarMochila(&mochila);
    menuPrincipal(&mochila);

    return 0;
}


// --- Implementação das funções --- //

// Função para exibir o título do jogo
void titulo(const Mochila *mochila) {
    printf("=========================================\n");
    printf("MOCHILA DE SOBREVIVÊNCIA - CODIGO DA ILHA\n");
    printf("=========================================\n");
    printf("Quantidade de itens na mochila: %d/%d\n\n", mochila->quantidade, TAM_MAX);
}


void inicializarMochila(Mochila *mochila) {
    mochila->quantidade = 0; // A mochila começa vazia
}

// Função para inserir um item na mochila
void inserirItem(Mochila *mochila, const char* nomeItem, const char* tipoItem, int quantidadeItem) {

    // Verifica se há espaço para inserir um novo item na mochila
    if (mochila->quantidade == TAM_MAX) {
        printf("\nErro: Mochila está cheia! Não é possível inserir mais itens.\n\n");
        return;
    }

    // A inserção ocorre na primeira posição livre do array
    // Copia os dados do item para a posição correta no array de itens
    strcpy(mochila->itens[mochila->quantidade].nome, nomeItem);
    strcpy(mochila->itens[mochila->quantidade].tipo, tipoItem);
    mochila->itens[mochila->quantidade].quantidade = quantidadeItem;

    // Incrementa a quantidade de itens na mochila
    mochila->quantidade++;
    printf("\nItem %s adicionado com sucesso!\n\n", nomeItem);

    // Exibe os itens atuais na mochila após a inserção
    listarItens(mochila);
}


// Função para listar os itens antes de remover ou buscar um item
void listarItensSimples(const Mochila *mochila) {

    // Verifica se a mochila está vazia
    if (mochila->quantidade == 0) {
        printf("\nA mochila está vazia!\n\n");
        return;
    }

    for (int i = 0; i < mochila->quantidade; i++) {
        printf("\n* %-20s\n", mochila->itens[i].nome);
    }
}


// Função para remover um item da mochila
void removerItem(Mochila *mochila, const char* nomeItem) {

    // Variáveis para controle do loop e posição do item a ser removido
    // i é o índice para percorrer a mochila
    // pos armazena a posição do item a ser removido (inicialmente -1 para indicar que não foi encontrado)
    int i, pos = -1;

    // Procura o item pelo nome usando strcmp
    // strcmp retorna 0 se as strings forem iguais
    for (i = 0; i < mochila->quantidade; i++) {
        if (strcmp(mochila->itens[i].nome, nomeItem) == 0) {
            pos = i; // Armazena a posição do item a ser removido
            break;
        }
    }

    // Tratamento para o caso de item não encontrado
    if (pos == -1) {
        printf("\nErro: Item %s não encontrado na mochila!\n\n", nomeItem);
        return;
    }

    // Desloca os itens seguintes para "fechar o buraco" deixado pela remoção
    // Começa da posição do item removido até o final da mochila
    for (i = pos; i < mochila->quantidade - 1; i++) {
        strcpy(mochila->itens[i].nome, mochila->itens[i + 1].nome);
        strcpy(mochila->itens[i].tipo, mochila->itens[i + 1].tipo);
        mochila->itens[i].quantidade = mochila->itens[i + 1].quantidade;
    }

    // Decrementa a quantidade de itens na mochila
    mochila->quantidade--;
    printf("Item %s removido com sucesso!\n\n", nomeItem);

    // Exibe os itens atuais na mochila após a remoção
    listarItens(mochila);
}


// --- Função para listar os itens na mochila ---
void listarItens(const Mochila *mochila) {

    // Verifica se a mochila está vazia
    if (mochila->quantidade == 0) {
        printf("\nA mochila está vazia!\n\n");
        return;
    }

    printf("--- ITENS NA MOCHILA (%d/%d) ---\n", mochila->quantidade, TAM_MAX);
    printf("---------------------------------------------------------\n");
    printf("%-20s | %-20s | %10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < mochila->quantidade; i++) {
        printf("%-20s | %-20s | %10d\n", mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade);
    }
    printf("---------------------------------------------------------\n");
    printf("Pressione Enter para continuar...");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}


// Função para buscar um item na mochila pelo nome
void buscarItem(const Mochila *mochila, const char* nomeItem) {

    // Variável para controle do loop
    // i é o índice para percorrer a mochila
    int i;

    // Procura o item pelo nome usando strcmp
    // strcmp retorna 0 se as strings forem iguais
    for (i = 0; i < mochila->quantidade; i++) {
        if (strcmp(mochila->itens[i].nome, nomeItem) == 0) {
            printf("--- ITEM %s ENCONTRADO ---\n", nomeItem);
            printf("---------------------------------------------------------\n");
            printf("%-20s | %-20s | %10s\n", "NOME", "TIPO", "QUANTIDADE");
            printf("---------------------------------------------------------\n");
            printf("%-20s | %-20s | %10d\n", mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade);
            return;
        }
    }

    // Se o item não for encontrado, exibe uma mensagem de erro
    printf("Erro: Item %s não encontrado na mochila!\n", nomeItem);
}


// --- Função do menu principal ---
void menuPrincipal(Mochila *mochila) {
    int opcao;
    char nomeItem[30];

    do {
        titulo(mochila); // Exibe o título do jogo

        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair do jogo\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { } // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                printf("\nNome do item: ");
                fgets(nomeItem, sizeof(nomeItem), stdin);
                nomeItem[strcspn(nomeItem, "\n")] = '\0'; // Remove o '\n' do final

                char tipoItem[20];
                printf("Tipo do item: ");
                fgets(tipoItem, sizeof(tipoItem), stdin);
                tipoItem[strcspn(tipoItem, "\n")] = '\0'; // Remove o '\n' do final

                int quantidadeItem;
                printf("Quantidade do item: ");
                scanf("%d", &quantidadeItem);
                while ((ch = getchar()) != '\n' && ch != EOF) { }

                inserirItem(mochila, nomeItem, tipoItem, quantidadeItem);
                break;
            case 2:
                listarItensSimples(mochila); // Lista os itens
                // O nome do item a ser removido é armazenado em nomeBusca e passado para a função removerItem
                if (mochila->quantidade != 0) {
                    printf("\nDigite o nome do item que deseja remover: ");
                    fgets(nomeItem, sizeof(nomeItem), stdin);
                    nomeItem[strcspn(nomeItem, "\n")] = '\0'; // Remove o '\n' do final
                    removerItem(mochila, nomeItem);
                }
                break;
            case 3:
                listarItens(mochila);
                break;
            case 4:
                listarItensSimples(mochila); // Lista os itens
                if(mochila->quantidade != 0) {
                    printf("Digite o nome do item que deseja detalhar: ");
                    fgets(nomeItem, sizeof(nomeItem), stdin);
                    nomeItem[strcspn(nomeItem, "\n")] = '\0'; // Remove o '\n' do final
                    buscarItem(mochila, nomeItem);
                }
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}