#include <stdio.h>
#include <stdlib.h>

// 2 * nº elem = 30
#define TAM 31


typedef struct no{
    int chave;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    int tam;
} Lista;

void inicializarLista(Lista *l){
    l->inicio = NULL;
    l->tam = NULL;
}

void inserir_na_lista(Lista *l, int valor){
    No *novo = new No;
    novo->chave = valor;
    novo->prox = l->inicio;
    l->inicio = novo;
    l->tam++;
}

int buscar_na_lista(Lista *l, int valor){
    No *aux = l->inicio;

    while (aux != NULL){
        if (aux->chave == valor){
            return aux->chave;
        }
        aux = aux->prox;
    }
    return 0; //nao encontrado 
}

void imprimir_lista(Lista *l){
    No *aux = l->inicio;
    printf("\nTam: %d\n\n", l->tam);
    while (aux != NULL){
        printf("%d\n", aux->chave);
        aux = aux->prox;
    }
}

void inicializarTabela(Lista t[]){
    for (int i = 0; i < TAM; i++){
        inicializarLista(&t[i]);
    }
}

int funcaoHash(int chave){
    return chave % TAM;
}

void inserir(Lista t[], int valor){
    int id = funcaoHash(valor);

    inserir_na_lista(&t[id], valor);

    printf("\nnumero inserido com sucesso\n\n");
}

int busca(Lista t[], int chave){
    int id = funcaoHash(chave);

    return buscar_na_lista(&t[id], chave);
}

void imprimir(Lista t[]){
    printf("\nINDICE  /   VALOR\n\n");
    for (int i = 0; i < TAM; i++){
        imprimir_lista(&t[i]);
        printf("\n");
    }
    printf("\n");
    
}

void menu(){
    printf("MENU\n");
    printf("1. Inserir\n");
    printf("2. Buscar\n");
    printf("3. Imprimir\n");
    printf("0. SAIR\n");
    printf("\nInforme a opcao: ");
}

int main (){
    Lista tabela[TAM];
    inicializarTabela(tabela);

    int opc = 0, num = 0, retorno = 0;

    do{
        menu();
        scanf("%d", &opc);

        switch (opc){
        case 1:
            printf("\nDigite um numero inteiro: ");
            scanf("%d", &num);
            inserir(tabela, num);
            break;

        case 2:
            printf("\nDigite o valor a ser buscado: ");
            scanf("%d", &num);
            retorno = busca(tabela, num);
            if (retorno == 0)
                printf("\nValor nao encontrado\n\n");
            else
                printf("\nIndice: %d    /   valor: %d\n\n", retorno, num);
            break;

        case 3:
            imprimir(tabela);
            break;
        case 0:
            printf("\nSAINDO...\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente\n\n");
        }

    } while (opc != 0);
    


    return 0;
}

