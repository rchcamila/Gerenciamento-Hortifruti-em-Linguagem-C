#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int opcao;
int quantidade = 0;

typedef struct {
    int id;
    char nome[50];
    float preco_compra;
    float preco_venda;
    int quantidade;
    int categoria;
} Produto;

Produto produtos[MAX]; // Array para armazenar os produtos

// Função para comparar produtos por nome (usada no qsort)
int compara_nome(const void *a, const void *b) {
    Produto *prodA = (Produto *)a;
    Produto *prodB = (Produto *)b;
    return strcmp(prodA->nome, prodB->nome);
}

// Função para salvar os produtos no arquivo CSV
void salvar_arquivo(Produto produtos[], int quantidade) {
    FILE *arquivo = fopen("banco_dados/produtos.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }else{
        fseek(arquivo, 0, SEEK_END);
        int size = ftell(arquivo);
        if(size == 0){
            // Cabeçalho do arquivo
            fprintf(arquivo, "ID,Nome,Preco de Compra,Preco de Venda,Categoria\n");
        }
    }

    // Salvando os produtos
    fprintf(arquivo, "%d,%s,%.2f,%.2f,%d\n", produtos[quantidade -1 ].id, produtos[quantidade -1].nome, produtos[quantidade -1].preco_compra, produtos[quantidade -1].preco_venda, produtos[quantidade -1].categoria);

    fclose(arquivo);
    printf("Dados salvos com sucesso no arquivo produtos.csv!\n");
}


/////////////////////////////////
// Função para carregar produtos do arquivo
void carregarProdutos() {
    FILE *arquivo = fopen("banco_dados/produtos.csv", "r");
    if (arquivo != NULL) {
        char linha[100];
        fgets(linha, sizeof(linha), arquivo);
        while (fscanf(arquivo, "%d,%49[^,],%f,%f,%d\n", &produtos[quantidade].id, produtos[quantidade].nome, &produtos[quantidade].preco_compra, &produtos[quantidade].preco_venda, &produtos[quantidade].categoria) == 5) {
            quantidade++;
        }
        fclose(arquivo);
    }
}
/////////////////////

// Nova função criada para recarregar todos os produtos
void recarregarProdutos() {
    quantidade = 0; // Reinicie a contagem de produtos
    carregarProdutos();
}
// Função para visualizar produtos da categoria específica

void visualizarProdutosPorCategoria(int categoria) {
    const char *categorias[] = {"Frutas", "Legumes", "Verduras", "Enlatados", "Outros"};
    printf("\nProdutos na categoria %s:\n", categorias[categoria - 1]);
    int encontrou = 0; // Para verificar se algum produto foi encontrado
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].categoria == categoria) {
            printf("ID: %d\n", produtos[i].id);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preço de Compra: %.2f\n", produtos[i].preco_compra);
            printf("Preço de Venda: %.2f\n", produtos[i].preco_venda);
            printf("-----------------------------\n");
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("\n Nenhum produto encontrado na categoria %s.\n\n", categorias[categoria - 1]);
    }
    printf("Pressione Enter para continuar...");
    getchar();
    getchar();
}

// Função para cadastrar novos produtos
void cadastrarProduto() {
    Produto novo_produto;
    novo_produto.id = quantidade + 1;

    printf("Digite o nome do produto:\n> ");
    scanf(" %49[^\n]", novo_produto.nome);

    printf("Digite o preço de compra do produto:\n> ");
    scanf("%f", &novo_produto.preco_compra);

    printf("Digite o preço de venda do produto:\n> ");
    scanf("%f", &novo_produto.preco_venda);

    // Escolha da categoria do produto
    printf("Escolha a categoria do produto:\n");
    printf("1 - Frutas\n2 - Verduras\n3 - Legumes\n4 - Enlatados\n5 - Outros\n");
    scanf("%d", &novo_produto.categoria);

    // Adiciona o novo produto ao array
    produtos[quantidade] = novo_produto;
    quantidade++;

    // Ordena os produtos por nome
    qsort(produtos, quantidade, sizeof(Produto), compara_nome);

    // Salva os produtos no arquivo CSV
    salvar_arquivo(produtos, quantidade);

    printf("\nProduto cadastrado com sucesso!\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
    getchar();
}

// Função para visualizar categorias
void visualizarCategorias() {
    while (1) {
        printf("\nEscolha uma categoria para visualizar:\n");
        printf("1 - Frutas\n");
        printf("2 - Legumes\n");
        printf("3 - Verduras\n");
        printf("4 - Enlatados\n");
        printf("5 - Outros\n");
        printf("6 - Retornar ao menu anterior\n");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 5) {
            visualizarProdutosPorCategoria(opcao);
        } else if (opcao == 6) {
            return;
        } else {
            printf("Opção não encontrada, digite novamente.\n");
        }
    }
}

// Função para a rotina de compra/cadastro
void rotinaCompraCadastro() {
    carregarProdutos();
    while (1) {
        printf("Escolha uma opção:\n");
        printf("1 - Registrar novos produtos\n");
        printf("2 - Visualizar por categoria\n");
        printf("3 - Retornar ao menu anterior\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                visualizarCategorias();
                break;
            case 3:
                return;
            default:
                printf("Opção não encontrada, digite novamente.\n");
        }
    }
}
