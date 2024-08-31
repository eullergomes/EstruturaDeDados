#include <stdio.h>
#include <stdlib.h>

typedef struct no{

    int valor;
    struct no *proximo;

}No;

// Função para Ler um valor.
void ler_valor(int *valor){

    printf("\n\tInforme um Valor: ");
    scanf("%d", &*valor);
}

// Função para Inserir no Inicio.
void inserir_no_inicio(No **lista_inicio, No **lista_fim, int valor, int *tam){

    No *novo = (No*) malloc(sizeof(No));

    novo->valor = valor;
    novo->proximo = *lista_inicio;
    *lista_inicio = novo;

    // inicio: 300
    // fim: 100
    // 300 -> 200 -> 100
    if(*lista_fim == NULL){

        *lista_fim = novo;
    }

    // 300 -> 200 -> 100 -> 300
    (*lista_fim)->proximo = *lista_inicio;

    *tam += 1;
}

// Função para Inserir no Fim.
void inserir_no_fim(No **lista_inicio, No **lista_fim, int valor, int *tam){

    No *novo = (No*) malloc(sizeof(No));

    novo->valor = valor;

    if(*lista_inicio == NULL){

        inserir_no_inicio(lista_inicio, lista_fim, valor, tam);
    }
    else{

        // novo: 300
        // fim: 300
        // 100 -> 200 -> 300 -> 100
        (*lista_fim)->proximo = novo;
        *lista_fim = novo;

        novo->proximo = *lista_inicio;
        //(*lista_fim)->proximo = *lista_inicio;

        *tam += 1;
    }
}

// Função para Inserir Ordenado.
void inserir_ordenado(No **lista_inicio, No **lista_fim, int valor, int *tam){

    No *aux, *novo = (No*) malloc(sizeof(No));

    novo->valor = valor;

    // NULL
    if(*lista_inicio == NULL){

        inserir_no_inicio(lista_inicio, lista_fim, valor, tam);
    }
    else if(novo->valor < (*lista_inicio)->valor){

        // novo: 50
        // 50 -> 100
        inserir_no_inicio(lista_inicio, lista_fim, valor, tam);
    }
    else{

        aux = *lista_inicio;

        while(aux->proximo != *lista_inicio && novo->valor > aux->proximo->valor){

            aux = aux->proximo;
        }

        // novo: 400
        // 100 -> 200 -> 300 -> 400 || 300 -> 100
        if(aux->proximo == *lista_inicio){

            inserir_no_fim(lista_inicio, lista_fim, valor, tam);
        }
        else{

            // novo: 250
            // 100 -> 200 -> 250 -> 300 -> 400
            novo->proximo = aux->proximo;
            aux->proximo = novo;

            *tam += 1;
        }
    }
}

// Função para Inserir no Meio.
void inserir_no_meio(No **lista_inicio, No **lista_fim, int ant, int valor, int *tam){

    No *aux, *novo = (No*) malloc(sizeof(No));

    novo->valor = valor;

    if(*lista_inicio == NULL){

        inserir_no_inicio(lista_inicio, lista_fim, valor, tam);
    }
    else{

        aux = *lista_inicio;

        while(aux->proximo != *lista_inicio && aux->valor != ant){

            aux = aux->proximo;
        }

        if(aux->proximo == *lista_inicio){

            inserir_no_fim(lista_inicio, lista_fim, valor, tam);
        }
        else{

            novo->proximo = aux->proximo;
            aux->proximo = novo;

            *tam += 1;
        }
    }
}

// Função para Imprimir a Lista usando o Tamanho.
void imprimir_1(No *lista_inicio, int tam){

    int cont = 0;

    printf("\n\t-------------------------------------------------\n\t");

    while(cont != tam){

        // 100 -> 200 -> 300
        printf("%d ", lista_inicio->valor);

        lista_inicio = lista_inicio->proximo;

        cont++;
    }

    printf("\n\t-------------------------------------------------\n");
}

// Função para Imprimir a Lista Usando o Inicio e fim da Lista.
void imprimir_2(No *lista_inicio, No *lista_fim){

    printf("\n\t-------------------------------------------------\n\t");

    do{
        printf("%d ", lista_inicio->valor);

        lista_inicio = lista_inicio->proximo;

    // 100 -> 200 -> 300 || 300 -> 100
    }while(lista_inicio != lista_fim->proximo);

    printf("\n\t-------------------------------------------------\n");
}