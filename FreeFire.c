// --- JOGO DA MOCHILA DE SOBREVIVÊNCIA ---

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
void limparBufferEntrada(void);
void esperarEnter(void);

// Funões para limpar o buffer de entrada e esperar enter
void limparBufferEntrada(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

void esperarEnter(void) {
    printf("Pressione Enter para continuar...\n");
    limparBufferEntrada();
}


// -------------------------- //
// --- PROGRAMA PRINCIPAL --- //
// -------------------------- //
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


// Função para listar os itens antes de remover um item (apenas nome)
void listarItensSimples(const Mochila *mochila) {

    // Verifica se a mochila está vazia
    if (mochila->quantidade == 0) {
        printf("\nErro: A mochila está vazia! Não é possível remover itens.\n\n");
        esperarEnter();
        return;
    }

    printf("\n --- ITENS NA MOCHILA ---\n");
    for (int i = 0; i < mochila->quantidade; i++) {
        printf("- %s\n", mochila->itens[i].nome);
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
        esperarEnter();
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
    printf("\nItem %s removido com sucesso!\n\n", nomeItem);

    // Exibe os itens atuais na mochila após a remoção
    listarItens(mochila);
}


// --- Função para listar os itens na mochila ---
void listarItens(const Mochila *mochila) {

    // Verifica se a mochila está vazia
    if (mochila->quantidade == 0) {
        printf("A mochila está vazia! Não há itens para listar.\n");
        esperarEnter();
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
    esperarEnter();
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
            printf("\n--- ITEM %s ENCONTRADO ---\n", nomeItem);
            printf("Nome: %s\n", mochila->itens[i].nome);
            printf("Tipo: %s\n", mochila->itens[i].tipo);
            printf("Quantidade: %d\n", mochila->itens[i].quantidade);
            printf("-----------------------------------------------\n");
            esperarEnter();
            return;
        }
    }

    // Se o item não for encontrado, exibe uma mensagem de erro
    printf("\nErro: Item não encontrado na mochila!\n");
    esperarEnter();
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
        printf("0. Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o buffer do teclado após ler a opção

        switch (opcao) {
            case 1:
                // Verifica se há espaço para inserir um novo item na mochila
                if (mochila->quantidade == TAM_MAX) {
                    printf("\nErro: Mochila está cheia! Não é possível inserir mais itens.\n\n");
                    esperarEnter();
                } else {
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
                    limparBufferEntrada();

                    inserirItem(mochila, nomeItem, tipoItem, quantidadeItem);
                }
                break;
            case 2:
                listarItensSimples(mochila); // Lista os itens
                // O nome do item a ser removido é armazenado em nomeItem para ser usado na função removerItem
                if (mochila->quantidade != 0) {
                    printf("\nDigite o nome do item que deseja remover: ");
                    fgets(nomeItem, sizeof(nomeItem), stdin);
                    nomeItem[strcspn(nomeItem, "\n")] = '\0'; // Remove o '\n' do final
                    removerItem(mochila, nomeItem);
                }
                break;
            case 3:
                printf("\n");
                listarItens(mochila);
                break;
            case 4:
                if(mochila->quantidade != 0) {
                    printf("\nDigite o nome do item que deseja buscar: ");
                    fgets(nomeItem, sizeof(nomeItem), stdin);
                    nomeItem[strcspn(nomeItem, "\n")] = '\0'; // Remove o '\n' do final
                    buscarItem(mochila, nomeItem);
                } else {
                    printf("\nA mochila está vazia! Não há itens para buscar.\n\n");
                }
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n\n");
                esperarEnter();
        }
    } while (opcao != 0);
}