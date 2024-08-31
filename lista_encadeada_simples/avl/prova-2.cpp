#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cel{
    struct cel *ant;
    struct cel *prox;
    char nome[30];
    int ano;
    float compra;
    float venda;
}celula;

void inserir(celula **ptr_cabeca) {
  celula *nova = (celula *)malloc(sizeof(celula));

    printf("Digite o nome do produto: ");
    scanf("%30[^\n]s", nova->nome);
    printf("Digite o ano de fabricação: ");
    scanf("%d", &nova->ano);
    printf("Digite o preço da compra: ");
    scanf("%f", &nova->compra);
    nova->venda = nova->compra + (nova->compra * 0.2);

    if (*ptr_cabeca == NULL) {
        nova->prox = *ptr_cabeca;
        *ptr_cabeca = nova;
    } else {
        celula *aux = *ptr_cabeca;
        celula *ant = NULL;

        while (aux != NULL) {
            if (strcmp(nova->nome, aux->nome) < 0) {
                if (ant != NULL) {
                    ant->prox = nova;
                } else {
                    *ptr_cabeca = nova;
                }
                nova->prox = aux;
                return;
            }
            ant = aux;
            aux = aux->prox;
        }
        ant->prox = nova;
        nova->prox = aux;
    }
}

void menu(){
    printf("\n*****************************************\n");
    printf("*\t1 - Cadastrar veículo\t\t*\n");
    printf("*\t2 - Mostrar veículos a venda\t*\n");
    printf("*\t3 - Realizar busca por preço\t*\n");
    printf("*\t4 - Realizar busca por ano\t*\n");
    printf("*\t5 - Comprar carro (imcompleto)\t*\n");
    printf("*\t0 - Sair\t\t\t*\n");
    printf("*****************************************\n\n");
}

void imprimir(celula *aux) {
    while (aux != NULL) {
        printf("\n---------------------------\n");
        printf("Nome: %s\n", aux->nome);
        printf("Ano de fabricação: %d\n", aux->ano);
        printf("Preço da compra: %.2f\n", aux->compra);
        printf("Preço da venda: %.2f\n", aux->venda);
        aux = aux->prox;
    }
}

//COMPRA - busca o nome
celula *buscar(celula *cabeca) {
    //celula *cabeca2 = NULL;

    char nomeCarro[30];
    printf("Digite o nome do carro para compra: ");
    scanf("%30[^\n]s", nomeCarro);
    celula *aux = cabeca;
    while (aux != NULL) {
        if (strcmp(aux->nome, nomeCarro) == 0) { //retorna 0 se as strings forem iguais
            aux->prox == cabeca;
            cabeca = aux;
        }
        aux = aux->prox;
    }
    return NULL;  //"Elemento não encontrado"
}


void buscarPreco(celula *aux) {
    float valor = 0.0f;
    printf("Digite o valor do seu orçamento:\n");
    scanf("%f", &valor);
    while (aux != NULL) {
        if (aux->venda <= valor) {
            printf("\n---------------------------\n");
            printf("Nome: %s\n", aux->nome);
            printf("Ano de fabricação: %d\n", aux->ano);
            printf("Preço para venda: %.2f\n", aux->venda);
        }
        aux = aux->prox;    
    }
}

void buscarAno(celula *aux) {
    int valor = 0;
    printf("Digite o ano do carro:\n");
    scanf("%d", &valor);
    while (aux != NULL) {
        if (aux->ano == valor) {
            printf("\n---------------------------\n");
            printf("Nome: %s\n", aux->nome);
            printf("Ano de fabricação: %d\n", aux->ano);
            printf("Preço para venda: %.2f\n", aux->venda);
        }
        aux = aux->prox;
    }
}

int main(void){
    celula *cabeca1 = NULL; //veiculos a venda    
    celula *cabeca2 = NULL; //veiculos vendidos
    int opc = 0;

    do{
        menu();
        scanf("%d", &opc);
        fflush(stdin);
        system("cls");
        switch (opc){
            case 1:     
                inserir(&cabeca1);
                break;
            case 2:
                imprimir(cabeca1);
                break;
            case 3:
                buscarPreco(cabeca1);
                break;
            case 4:
                buscarAno(cabeca1);
                break;
            case 5:
                
                
                break;
            case 0:
                printf("\nFinalizando...\n");
                break;
        
            default:
                break;
        }
    } while (opc != 0);

    return 0;
}
