#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Estoque de almoxarifado

typedef struct no{
    int id;
    char nome[30];
    char tipo; // A - C - P
    int quantidade;
    struct no *prox;
} No;

void inserir(No **lista){
    No *novo = (No*) malloc(sizeof(No));

    printf("Digite o nome do produto:\n");
    scanf("%30[^\n]", &novo->nome);
    fflush(stdin);
    printf("Digite o tipo:\n");
    scanf("%c", &novo->tipo);

    printf("Digite a quantidade no estoque:\n");
    scanf("%d", &novo->quantidade);

    novo->id = rand() % 1001; //0-1000
    printf("Id: %d\n", novo->id);

    novo->prox = *lista;
    *lista = novo;
}

//imprime apenas o produto buscado
void imprimirBusca(No *aux){
    printf("\n");
    printf("Nome: %s | ", aux->nome);
    printf("Tipo: %c | ", aux->tipo);
    printf("Quantidade: %d | ", aux->quantidade);
    printf("Id: %d | ", aux->id);
    printf("\n");
}

No *atualizar(No *head, char nome[]){
    printf("\n--------------------\n");
    printf("| Atualizar produto| ");
    printf("\n--------------------\n\n");
    printf("Produto selecionado: %s\n\n", nome);

    printf("Digite o novo nome: \n");
    scanf("%30[^\n]", &head->nome);
    fflush(stdin);
    printf("Tipo:\n");
    scanf("%c", &head->tipo);

    printf("Quantidade: \n");
    scanf("%d", &head->quantidade);

    printf("\nAtualizado com sucesso!\n\n");

    return head;
}

void buscarAtt(No **head) {
    No *aux = (*head);
    char nome[30];
    printf("\nDigite o nome do produto a ser buscado:\n");
    scanf("%30[^\n]", &nome);
    fflush(stdin);

    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
        aux = atualizar(aux, nome);  //Elemento encontrado
        return;
        }
    aux = aux->prox;
    }
}

No *retirar (No *head){
    int opc = 0, num = 0;
    printf("\nVocê gostaria de:\n");
    printf("\t1 - retirar mais produtos\n");
    printf("\t2 - cadastrar mais produtos\n");
    printf("Informe a opção: ");
    scanf("%d", &opc);

    switch (opc){
    case 1:
        printf("\nDigite a quantidade a ser retirada: ");
        scanf("%d", &num);

        head->quantidade -= num;
        printf("\nRetirado com sucesso!\n\n");
        return head;
    case 2:
        printf("\nDigite a quantidade a ser incrementada: ");
        scanf("%d", &num);

        head->quantidade += num;
        printf("\nIncrementado com sucesso!\n\n");
        return head;
    default:
        printf("\nOpção inválida!\n\n");
        break;
    }
}

void buscar(No **head) {
    char nome[30];
    printf("\nDigite o nome do produto a ser buscado:\n");
    scanf("%30[^\n]", &nome);
    fflush(stdin);

    while (*head != NULL) {
        if (strcmp((*head)->nome, nome) == 0) {
        *head = retirar((*head));  //Elemento encontrado
        return;
        }
    *head = (*head)->prox;
    }
}

void relatorio(No *head){
    int tipoA = 0, tipoB = 0, tipoC = 0;

    while (head != NULL){
        if (head->tipo == 'A' || head->tipo == 'a'){
            tipoA++;
        }
        if (head->tipo == 'C' || head->tipo == 'c'){
            tipoB++;
        }
        if (head->tipo == 'P' || head->tipo == 'p'){
            tipoC++;
        }

        head = head->prox;
    }
    printf("\n-------------\n");
    printf("| Relatório | ");
    printf("\n-------------\n\n");
    printf("Alimento - quantidade: %d\n", tipoA);
    printf("Consumo - quantidade: %d\n", tipoB);
    printf("Permanente - quantidade: %d\n", tipoC);
}

void imprimir(No *aux){
    while (aux != NULL){
        printf("\n");
        printf("Nome: %s | ", aux->nome);
        printf("Tipo: %c | ", aux->tipo);
        printf("Quantidade: %d | ", aux->quantidade);
        printf("Id: %d | ", aux->id);
        printf("\n");

        aux = aux->prox;
    } 
}

void menu(){
    printf("\nMENU\n");
    printf("1 - Inserir\n");
    printf("2 - Imprimir\n");
    printf("3 - Alterar\n");
    printf("4 - Atualizar\n");
    printf("5 - Relatório\n");
    printf("0 - Sair\n");
    printf("\nInforme a opção: ");
}

int main(void){
    srand(time(NULL));
    No *cabeca = NULL;
    int opc = 0;

    do{
        menu();
        scanf("%d", &opc);
        fflush(stdin);

        switch (opc){
        case 1:
            inserir(&cabeca);
            break;
        case 2:
            imprimir(cabeca);
            break;
        case 3:
            buscarAtt(&cabeca);
            break;
        case 4:
            buscar(&cabeca);
            break;
        case 5:
            relatorio(cabeca);
            break;
        case 0:
            printf("\nSaindo...\n\n");
            break;
        default:
            printf("\nOpção inválida!\n\n");
            break;
        }
    } while (opc != 0);
    return 0;
}