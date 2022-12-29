#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    char nome[30];
    int qtdAtual;
    int qtdMin;
    float preco;
    struct no *prox;
} Node;

//Inserir na lista (inicio)
void inserir(Node **cabeca){
    Node *novo = (Node*) malloc (sizeof(Node));
    printf("\nDigite o nome do produto: ");
    scanf("%30[^\n]s", novo->nome);
    
    printf("\nDigite o quantidade atual no estoque: ");
    scanf("%d", &novo->qtdAtual);
    
    printf("\nDigite a quantidade miníma: ");
    scanf("%d", &novo->qtdMin);

    printf("Digite o preço: ");
    scanf("%f", &novo->preco);

    novo->prox = *cabeca;
    *cabeca = novo;
}

void imprimir(Node *aux){
    while (aux != NULL){
        printf("\n----------------------------\n");
        printf("Nome: %s\n", aux->nome);
        printf("Quantidade no estoque: %d\n", aux->qtdAtual);
        printf("Quantidade mín: %d\n", aux->qtdMin);
        printf("Preço: %f\n", aux->preco);
        printf("-------------------------------\n");
        aux = aux->prox;
    }
    
}

void totalNoEstoque(Node *aux){
    int qtd = 0;
    float total = 0.0f;

    while (aux != NULL){
        qtd = aux->qtdAtual + qtd;
        total = aux->preco + total;

        aux = aux->prox;
    }
    printf("Preço total do estoque: %f\n", total);
    printf("Preço médio: %f\n", (total*qtd)/qtd);  
}

void menu(){
    printf("\nMENU\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Valor total do estoque e preço médio\n");
    printf("5 - Imprimir produtos\n");
    printf("0 - Sair\n");
    printf("\nInforme o valor: ");
}

int main(void){
    Node *head = NULL;
    int opc = 0;
    
    do{
        menu();
        scanf("%d", &opc);

        switch (opc){
        case 1:
            inserir(&head);
            break;
        case 2:
            totalNoEstoque(head);
            break;
        case 5:
            imprimir(head);
            break;
        case 0:
            printf("\n\nFinalizando...\n");
            break;
        
        default:
            printf("\n\nOpção inválida!\n\n");
            break;
        }

    } while (opc != 0);
    
    


    return 0;
}