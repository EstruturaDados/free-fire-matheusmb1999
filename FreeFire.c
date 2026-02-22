// ------------------------------------- //
// --- CÓDIGO DA ILHA (NÍVEL MESTRE) --- //
// ------------------------------------- //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 10 // Número máximo de itens na mochila
#define SEPARADOR "------------------------------------------------------------------------"

// --- Estrutura para representar um item ---
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

// --- Estrutura para representar a mochila ---
typedef struct {
    Item itens[TAM_MAX];
    int quantidade;
    int ordenacao;
} Mochila;


// --- Protótipos das funções do jogo ---
void titulo(const Mochila *mochila); // Exibe o titulo e a quantidade de itens na mochila
void inicializarMochila(Mochila *mochila); // Inicializa a mochila como vazia
void carregarItensIniciais(Mochila *mochila); // Carrega itens iniciais na mochila (opcional)
void inserirItem(Mochila *mochila, const char* nomeItem, const char* tipoItem, int quantidadeItem, int prioridadeItem); // Insere um item na mochila
void removerItem(Mochila *mochila, const char* nomeItem); // Remove um item da mochila pelo nome
void listarItens(const Mochila *mochila); // Lista os itens na mochila com detalhes (nome, tipo, quantidade)
void listarItensSimples(const Mochila *mochila); // Lista apenas os nomes dos itens na mochila (usado antes de remover um item)
void buscarItem(const Mochila *mochila, const char* nomeItem); // Busca binária por nome (somente se ordenado por nome)
void trocarItens(Item *a, Item *b); // Troca dois itens de posição na mochila
int ordenarItens(Mochila *mochila, int criterio); // Ordena os itens da mochila por critério e retorna nº de comparações
void organizarMochila(Mochila *mochila); // Exibe menu de organização e aplica ordenação
void menuPrincipal(Mochila *mochila); // Exibe o menu principal e gerencia as opções do usuário

void limparBufferEntrada(void); // Função para limpar o buffer de entrada 
void esperarEnterDireto(void); // Usa quando não há lixo pendente no buffer
void esperarEnterAposScanf(void); // Usa quando acabou de ler com scanf sem limpar o buffer


// --- Implementação das funções auxiliares --- //
void limparBufferEntrada(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

// Direto: utilizado para pausar o programa e esperar o usuário pressionar Enter, sem se preocupar com lixo no buffer
void esperarEnterDireto(void) {
    int ch;
    printf("\n%s\n", SEPARADOR);
    printf("Pressione Enter para continuar...\n");
    fflush(stdout); // Garante que a mensagem seja exibida antes de esperar o Enter
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

// Após scanf: utilizado para pausar o programa e esperar o usuário pressionar Enter, garantindo que o buffer esteja limpo de lixo antes de esperar
void esperarEnterAposScanf(void) {
    int ch;
    printf("\n%s\n", SEPARADOR);
    printf("Pressione Enter para continuar...\n");
    fflush(stdout);
    limparBufferEntrada();
    while ((ch = getchar()) != '\n' && ch != EOF) { }
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


// --------------------------------- //
// --- IMPLEMENTAÇÃO DAS FUNÇÕES --- //
// --------------------------------- //

// --- Exibe o título do jogo e quantidade de itens na mochila ---
void titulo(const Mochila *mochila) {
    printf("%s\n", SEPARADOR);
    printf("PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("%s\n", SEPARADOR);
    printf("Quantidade de itens na mochila: %d/%d\n", mochila->quantidade, TAM_MAX);
    printf("Status da Ordenação por NOME: %s\n\n", (mochila->ordenacao == 1) ? "ORDENADO" : "NÃO ORDENADO"); // Só fica "ORDENADO" após usar a opção 4 e escolher ordenação por nome
}


// ---Inicializa a mochila como vazia ou carrega itens iniciais ---
void inicializarMochila(Mochila *mochila) {
    mochila->quantidade = 0; // A mochila começa vazia
    mochila->ordenacao = 0; // Estado inicial: não ordenado por nome
    carregarItensIniciais(mochila); // Carrega itens iniciais (opcional)
}


// --- Carrega itens iniciais na mochila (opcional) ----
void carregarItensIniciais(Mochila *mochila) {
    strcpy(mochila->itens[mochila->quantidade].nome, "Painel Solar");
    strcpy(mochila->itens[mochila->quantidade].tipo, "Energia");
    mochila->itens[mochila->quantidade].quantidade = 2;
    mochila->itens[mochila->quantidade].prioridade = 3;
    mochila->quantidade++;

    strcpy(mochila->itens[mochila->quantidade].nome, "Viga de Aco");
    strcpy(mochila->itens[mochila->quantidade].tipo, "Estrutural");
    mochila->itens[mochila->quantidade].quantidade = 8;
    mochila->itens[mochila->quantidade].prioridade = 1;
    mochila->quantidade++;

    strcpy(mochila->itens[mochila->quantidade].nome, "Antena");
    strcpy(mochila->itens[mochila->quantidade].tipo, "Eletronico");
    mochila->itens[mochila->quantidade].quantidade = 1;
    mochila->itens[mochila->quantidade].prioridade = 4;
    mochila->quantidade++;

    strcpy(mochila->itens[mochila->quantidade].nome, "Bateria");
    strcpy(mochila->itens[mochila->quantidade].tipo, "Energia");
    mochila->itens[mochila->quantidade].quantidade = 4;
    mochila->itens[mochila->quantidade].prioridade = 2;
    mochila->quantidade++;

    strcpy(mochila->itens[mochila->quantidade].nome, "Placa Mae");
    strcpy(mochila->itens[mochila->quantidade].tipo, "Eletronico");
    mochila->itens[mochila->quantidade].quantidade = 1;
    mochila->itens[mochila->quantidade].prioridade = 5;
    mochila->quantidade++;

    strcpy(mochila->itens[mochila->quantidade].nome, "Parafusos");
    strcpy(mochila->itens[mochila->quantidade].tipo, "Estrutural");
    mochila->itens[mochila->quantidade].quantidade = 50;
    mochila->itens[mochila->quantidade].prioridade = 1;
    mochila->quantidade++;

    strcpy(mochila->itens[mochila->quantidade].nome, "Chave Mestra");
    strcpy(mochila->itens[mochila->quantidade].tipo, "Ativador");
    mochila->itens[mochila->quantidade].quantidade = 1;
    mochila->itens[mochila->quantidade].prioridade = 5;
    mochila->quantidade++;

    strcpy(mochila->itens[mochila->quantidade].nome, "Fiacao");
    strcpy(mochila->itens[mochila->quantidade].tipo, "Eletronico");
    mochila->itens[mochila->quantidade].quantidade = 20;
    mochila->itens[mochila->quantidade].prioridade = 2;
    mochila->quantidade++;
}


// --- Insere um item na mochila ---
void inserirItem(Mochila *mochila, const char* nomeItem, const char* tipoItem, int quantidadeItem, int prioridadeItem) {

    // A inserção ocorre na primeira posição livre do array
    // Copia os dados do item para a posição correta no array de itens
    strcpy(mochila->itens[mochila->quantidade].nome, nomeItem);
    strcpy(mochila->itens[mochila->quantidade].tipo, tipoItem);
    mochila->itens[mochila->quantidade].quantidade = quantidadeItem;
    mochila->itens[mochila->quantidade].prioridade = prioridadeItem;

    // Incrementa a quantidade de itens na mochila
    mochila->quantidade++;
    mochila->ordenacao = 0; // A inserção de um novo item desorganiza a ordem por nome, o 0 troca o status para "NÃO ORDENADO"
    printf("\nItem %s adicionado com sucesso!\n\n", nomeItem);

    // Exibe os itens atuais na mochila após a inserção
    listarItens(mochila);
}


// --- Lista os itens antes de remover um item (apenas nome) ---
void listarItensSimples(const Mochila *mochila) {

    // Verifica se a mochila está vazia
    if (mochila->quantidade == 0) {
        printf("\nErro: A mochila está vazia! Não é possível remover itens.\n\n");
        esperarEnterDireto();
        return;
    }

    printf("\n --- ITENS NA MOCHILA ---\n");
    for (int i = 0; i < mochila->quantidade; i++) {
        printf("- %s\n", mochila->itens[i].nome);
    }
}


// --- Remove um item da mochila ---
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
        esperarEnterDireto();
        return;
    }

    // Desloca os itens seguintes para "fechar o buraco" deixado pela remoção
    // Começa da posição do item removido até o final da mochila
    for (i = pos; i < mochila->quantidade - 1; i++) {
        strcpy(mochila->itens[i].nome, mochila->itens[i + 1].nome);
        strcpy(mochila->itens[i].tipo, mochila->itens[i + 1].tipo);
        mochila->itens[i].quantidade = mochila->itens[i + 1].quantidade;
        mochila->itens[i].prioridade = mochila->itens[i + 1].prioridade;
    }

    // Decrementa a quantidade de itens na mochila
    mochila->quantidade--;
    mochila->ordenacao = 0;
    printf("\nItem %s removido com sucesso!\n\n", nomeItem);

    // Exibe os itens atuais na mochila após a remoção
    listarItens(mochila);
}


// --- Lista os itens na mochila ---
void listarItens(const Mochila *mochila) {

    // Verifica se a mochila está vazia
    if (mochila->quantidade == 0) {
        printf("A mochila está vazia! Não há itens para listar.\n");
        esperarEnterDireto();
        return;
    }

    printf("%s\n", SEPARADOR);
    printf("INVENTARIO ATUAL (%d/%d)\n", mochila->quantidade, TAM_MAX);
    printf("%s\n", SEPARADOR);
    printf("%-20s | %-20s | %-10s | %10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("%s\n", SEPARADOR);
    for (int i = 0; i < mochila->quantidade; i++) {
        printf("%-20s | %-20s | %-10d | %10d\n", mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade, mochila->itens[i].prioridade);
    }
    printf("%s\n", SEPARADOR);
    esperarEnterDireto();
}


// --- Busca binária de um item na mochila pelo nome ---
// A busca binária só funciona se a mochila estiver ordenada por nome (ordenacao == 1)
void buscarItem(const Mochila *mochila, const char* nomeItem) {
    if (mochila->ordenacao != 1) {
        esperarEnterDireto();
        return;
    }

    // Variáveis para controle do início e fim da busca
    int inicio = 0;
    int fim = mochila->quantidade - 1;

    // Loop de busca binária
    // O loop continua enquanto o início for menor ou igual ao fim
    // Calcula o meio do intervalo atual e compara o nome do item no meio com o nome buscado
    // Se a comparação for 0, o item foi encontrado e seus detalhes são exibidos
    // Se a comparação for menor que 0, o item buscado é maior que o item do meio, então o início é ajustado para meio + 1
    // Se a comparação for maior que 0, o item buscado é menor que o item do meio, então o fim é ajustado para meio - 1
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int comparacao = strcmp(mochila->itens[meio].nome, nomeItem);

        if (comparacao == 0) {
            printf("\n--- ITEM %s ENCONTRADO ---\n", nomeItem);
            printf("Nome: %s\n", mochila->itens[meio].nome);
            printf("Tipo: %s\n", mochila->itens[meio].tipo);
            printf("Quantidade: %d\n", mochila->itens[meio].quantidade);
            printf("Prioridade: %d\n", mochila->itens[meio].prioridade);
            esperarEnterDireto();
            return;
        } else if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\nErro: Item não encontrado na mochila!\n");
    esperarEnterDireto();
}


// --- Função auxiliar de troca: Troca dois itens de posição na mochila ---
void trocarItens(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}


// --- Ordena os itens da mochila com base no critério escolhido ---
// Critério 1: Bubble Sort por nome
// Critério 2: Insertion Sort por tipo (desempate por nome)
// Critério 3: Selection Sort por prioridade
int ordenarItens(Mochila *mochila, int criterio) {
    int comparacoes = 0;
    int quantidade = mochila->quantidade;

    if (criterio == 1) {
        for (int i = 0; i < quantidade - 1; i++) {
            for (int j = 0; j < quantidade - i - 1; j++) {
                comparacoes++;
                if (strcmp(mochila->itens[j].nome, mochila->itens[j + 1].nome) > 0) {
                    trocarItens(&mochila->itens[j], &mochila->itens[j + 1]);
                }
            }
        }
    } else if (criterio == 2) {
        for (int i = 1; i < quantidade; i++) {
            Item chave = mochila->itens[i];
            int j = i - 1;

            while (j >= 0) {
                int mover = 0;
                int comparacaoTipo;

                comparacoes++;
                comparacaoTipo = strcmp(mochila->itens[j].tipo, chave.tipo);

                if (comparacaoTipo > 0) {
                    mover = 1;
                } else if (comparacaoTipo == 0) {
                    comparacoes++;
                    if (strcmp(mochila->itens[j].nome, chave.nome) > 0) {
                        mover = 1;
                    }
                }

                if (!mover) {
                    break;
                }

                mochila->itens[j + 1] = mochila->itens[j];
                j--;
            }

            mochila->itens[j + 1] = chave;
        }
    } else if (criterio == 3) {
        for (int i = 0; i < quantidade - 1; i++) {
            int indiceMenor = i;

            for (int j = i + 1; j < quantidade; j++) {
                comparacoes++;
                if (mochila->itens[j].prioridade < mochila->itens[indiceMenor].prioridade) {
                    indiceMenor = j;
                }
            }

            if (indiceMenor != i) {
                trocarItens(&mochila->itens[i], &mochila->itens[indiceMenor]);
            }
        }
    }

    // Indica se os itens estão ordenados por nome, 1 = pode ser usada a busca binária
    mochila->ordenacao = (criterio == 1) ? 1 : 0;
    return comparacoes;
}


// --- Organiza os itens da mochila por um tipo de ordem especifica ---
// Exibe um menu para o usuário escolher o critério de ordenação e chama a função de ordenação correspondente
// Após a ordenação, exibe o número de comparações realizadas e lista os itens organizados
void organizarMochila(Mochila *mochila) {
    printf("%s\n", SEPARADOR);
    printf("ESTRATEGIA DE ORGANIZACAO\n");
    printf("%s\n", SEPARADOR);
    printf("Como deseja ordenar os componentes?\n");

    int opcao;
    printf("1. Ordenar por NOME (A-Z)\n");
    printf("2. Ordenar por TIPO\n");
    printf("3. Ordenar por PRIORIDADE de Montagem\n");
    printf("0. Voltar ao Menu Principal\n");
    printf("Escolha o criterio: ");
    fflush(stdout); // Garante que a mensagem seja exibida antes de ler a opção do usuário

    if (scanf("%d", &opcao) != 1) {
        printf("Entrada inválida! Digite um número.\n");
        esperarEnterAposScanf();
        return;
    }
    limparBufferEntrada();

    switch (opcao) {
        case 1:
            int comparacoes;
            printf("\nMochila organizada por NOME (A-Z).\n");
            comparacoes = ordenarItens(mochila, 1);
            printf("Analise de desempenho: Foram necessárias %d comparações.\n", comparacoes);
            listarItens(mochila);
            break;
        case 2:
            printf("\nMochila organizada por TIPO.\n");
            comparacoes = ordenarItens(mochila, 2);
            printf("Analise de desempenho: Foram necessárias %d comparações.\n", comparacoes);
            listarItens(mochila);
            break;
        case 3:
            printf("\nMochila organizada por PRIORIDADE de Montagem.\n");
            comparacoes = ordenarItens(mochila, 3);
            printf("Analise de desempenho: Foram necessárias %d comparações.\n", comparacoes);
            listarItens(mochila);
            break;
        case 0:
            printf("Voltando ao Menu Principal...\n\n");
            return;
        default:
            printf("\nOpção inválida!\n\n");
            esperarEnterDireto();
    }
}


// --- Função do menu principal ---
void menuPrincipal(Mochila *mochila) {
    int opcao = -1; // Inicializa para evitar lixo de memória
    char nomeItem[30];

    do {
        titulo(mochila); // Exibe o título do jogo

        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (Apenas se ordenado por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");

        printf("Escolha uma opção: ");
        fflush(stdout);
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            esperarEnterAposScanf();
            continue;
        }
        limparBufferEntrada(); // Limpa o buffer do teclado após ler a opção

        switch (opcao) {
            case 1:
                // Verifica se há espaço para inserir um novo item na mochila
                if (mochila->quantidade == TAM_MAX) {
                    printf("\nErro: Mochila está cheia! Não é possível inserir mais itens.\n\n");
                    esperarEnterDireto();
                } else {
                    printf("\nNome do item: ");
                    fgets(nomeItem, sizeof(nomeItem), stdin);
                    nomeItem[strcspn(nomeItem, "\n")] = '\0'; // Remove o '\n' do final

                    char tipoItem[20];
                    printf("Tipo (Estrutural, Eletronico, Energia): ");
                    fgets(tipoItem, sizeof(tipoItem), stdin);
                    tipoItem[strcspn(tipoItem, "\n")] = '\0';

                    int quantidadeItem;
                    printf("Quantidade: ");
                    if (scanf("%d", &quantidadeItem) != 1) {
                        printf("Entrada inválida! Digite um número.\n");
                        esperarEnterAposScanf();
                        continue;
                    }
                    limparBufferEntrada();

                    int prioridadeItem;
                    printf("Prioridade de Montagem (1-5): ");
                    if (scanf("%d", &prioridadeItem) != 1) {
                        printf("Entrada inválida! Digite um número.\n");
                        esperarEnterAposScanf();
                        continue;
                    }
                    limparBufferEntrada();

                    // Chama a função para inserir o item na mochila
                    inserirItem(mochila, nomeItem, tipoItem, quantidadeItem, prioridadeItem);
                }
                break;
            case 2:
                listarItensSimples(mochila); // Lista os itens
                // O nome do item a ser removido é armazenado em nomeItem para ser usado na função removerItem
                // O if no scanf é para evitar que o programa trave caso o usuário digite algo que não seja um número
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
                organizarMochila(mochila);
                break;
            case 5:
                if(mochila->quantidade != 0) {
                    if (mochila->ordenacao != 1) {
                        printf("\nA busca binária só funciona com a mochila ordenada por NOME.\n");
                        printf("Use a opção 4 e escolha ordenação por NOME (A-Z).\n");
                        esperarEnterDireto();
                        break;
                    }

                    printf("\nDigite o nome do item que deseja buscar: ");
                    fgets(nomeItem, sizeof(nomeItem), stdin);
                    nomeItem[strcspn(nomeItem, "\n")] = '\0';
                    buscarItem(mochila, nomeItem);
                } else {
                    printf("\nA mochila está vazia! Não há itens para buscar.\n\n");
                    esperarEnterDireto();
                }
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n\n");
                esperarEnterDireto();
        }
    } while (opcao != 0);
}
