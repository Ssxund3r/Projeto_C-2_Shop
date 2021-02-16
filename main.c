#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h> // No Linux / Mac
#include <windows.h>


typedef struct{
    int codigo;
    char nome[30];
    float preco;
}produto;

typedef struct{
    produto produto;
    int quantidade;
}carrinho;

void infoProduto(produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
produto pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto = 0;
static int contador_carrinho = 0;
static carrinho carRinho[50];
static produto produtos[50];

//Rodar o Programa Market
int main() {
    menu();
    return 0;
}
//Informação detalhada do produto x
void infoProduto(produto prod){
    printf("Codigo: %d \nNome: %s \nPreco: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);
}
//Menu e seleção dos produtos selecionados pelo usuário
void menu(){
    printf("======================================\n");
    printf("============== Bem-Vindo(a) ==========\n");
    printf("============== Ssxund3r's shop =======\n");
    printf("======================================\n");

    printf("Selecione uma opcao abaixo: \n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Comprar produtos\n");
    printf("4 - Visualizar Carrinho\n");
    printf("5 - Fechar pedido\n");
    printf("6 - Sair do sistema\n");

    int opcao;
    scanf("%d", &opcao);
    getchar();

    switch (opcao){
        case 1:
            cadastrarProduto();
            break;
        case 2:
            listarProdutos();
            break;
        case 3:
            comprarProduto();
            break;
        case 4:
            visualizarCarrinho();
            break;
        case 5:
            fecharPedido();
            break;
        case 6:
            printf("Volte sempre!\n");
            Sleep(2);
            exit(0);
        default:
            printf("Opcao invalida.\n");
            Sleep(2);
            menu();
            break;
    }
}

//Cadastro dos produtos desejados pelo usuário
void cadastrarProduto(){
    printf("Cadastro de Produto:\n");
    printf("=======================");

    printf("Informe o nome do produto: \n");
    fgets(produtos[contador_produto].nome, 30, stdin);

    printf("Informe o preco do produto: \n");
    scanf("%f", &produtos[contador_produto].preco);

    printf("O produto %s foi cadastrado com sucesso.\n", strtok(produtos[contador_produto].nome, "\n"));

    produtos[contador_produto].codigo = (contador_produto + 1);
    contador_produto++;

    Sleep(3);
    menu();
}

//Lista os produtos adicionados pelo usuário
void listarProdutos(){
    if(contador_produto > 0){
        printf("Listagem de produtos.\n");
        printf("------------------------");
        for(int i = 0; i < contador_produto; i++){
            infoProduto(produtos[i]);
            printf("---------------------\n");
            Sleep(1);
        }
        Sleep(2);
        menu();
    }else{
        printf("Nao temos produtos cadastrados!\n");
        Sleep(1);
        menu();
    }
}

//Seleciona o produto desejado a compra pelo usuário, sendo o código x a referência de compra pelo produto desejado ao usuário
void comprarProduto(){
    if(contador_produto > 0){
       printf("Informe o codigo do produto que deseja adicionar no carrinho:\n");

       printf("======Produtos Disponiveis======\n");
       for(int i = 0; i < contador_produto; i++){
            infoProduto(produtos[i]);
            printf("-----------------------\n");
            Sleep(1);
       }
       int codigo;
       scanf("%d", &codigo);
       getchar();

       int tem_mercado = 0;
       for(int i = 0; i < contador_produto; i++){
            if(produtos[i].codigo == codigo){
                tem_mercado = 1;

                if(contador_carrinho  > 0){
                    int * retorno = temNoCarrinho(codigo);

                    if(retorno[0] == 1){
                        carRinho[retorno[1]].quantidade++;
                        printf("Aumentei a quantidade do produto %s ja existente no carrinho.\n", strtok(carRinho[retorno[1]].produto.nome, "\n"));
                        Sleep(2);
                        menu();
                    }else{
                        produto p = pegarProdutoPorCodigo(codigo);
                        carRinho[contador_carrinho].produto = p;
                        carRinho[contador_carrinho].quantidade = 1;
                        contador_carrinho++;
                        printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                        Sleep(2);
                        menu();
                    }
                }else{
                    produto p = pegarProdutoPorCodigo(codigo);
                    carRinho[contador_carrinho].produto = p;
                    carRinho[contador_carrinho].quantidade = 1;
                    contador_carrinho++;
                    printf("O produto %s foi adicionado ao carrinho", strtok(p.nome, "\n"));
                    Sleep(2);
                    menu();
                }
            }
       }
       if(tem_mercado < 1){
        printf("Nao foi encontrado o produto com o codigo %d.\n", codigo);
        Sleep(2);
        menu();

       }
    }else{
        printf("Nao existe produtos para vender no momento.\n");
        Sleep(2);
        menu();
    }
}

//Visualização de compra de produtos selecionados pelo usuário, exibindo a quantidade de um produto x comprado e exibindo o restante de produtos comprados
void visualizarCarrinho(){
    if(contador_carrinho > 0){
        printf("Produtos do carrinho:\n");
        printf("------------------------\n");
        for(int i = 0; i < contador_carrinho; i++){
           infoProduto(carRinho[i].produto);
           printf("Quantidade: %d\n", carRinho[i].quantidade);
           printf("-----------------------\n");
        }
        Sleep(2);
        menu();
    }else{
        printf("Nao temos produtos no carrinho!\n");
        Sleep(1);
        menu();
    }
}

//Referência por produto baseado em código x, assim gerando um código x para cada produto
produto pegarProdutoPorCodigo(int codigo){
    produto p;
    for(int i = 0; i < contador_produto; i++){
        if(produtos[i].codigo == codigo){
            p = produtos[i];
        }
    }
    return p;
}

//Exibe a seleção de produtos adicionados pelo usuário contendo código e índice de produto
int * temNoCarrinho(int codigo){
    int static retorno[] = {0, 0};
    for(int i = 0; i < contador_carrinho; i++){
        if(carRinho[i].produto.codigo == codigo){
        retorno[0] = 1; //tem o produto com este código no carrinho;
        retorno[1] = i; // O índice do produto no carrinho
     }
   }
   return retorno;
}

//Finalização de pedido, exibe o total da fatura do usuário sendo assim a finalização da compra e reinciando o programa novamente ao menu
void fecharPedido(){
    if(contador_carrinho > 0){
        float valorTotal = 0.0;
        printf("Produtos no carrinho:\n");
        printf("------------------------");
        for(int i = 0; i < contador_carrinho; i++){
            produto p = carRinho[i].produto;
            int quantidade = carRinho[i].quantidade;
            valorTotal += p.preco * quantidade;
            infoProduto(p);
            printf("Quantidade: %d\n", quantidade);
            printf("---------------------------\n");
            Sleep(1);
        }
        printf("Sua fatura fechou em R$ %.2f\n", valorTotal);

        //Limpar carrinho
        contador_carrinho = 0;
        printf("Obrigado pela preferencia.\n");
        Sleep(5);
        menu();

    }else{
        printf("Voce nao tem produtos no carrinho!\n");
        Sleep(3);
        menu();
    }
}



