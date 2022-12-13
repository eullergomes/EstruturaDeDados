#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
    int dado;
    struct NO *prox;
}NO;

typedef struct FILA{
    NO *ini;
    NO *fim; //apenas pra fascilitar a lógica
}FILA;

void inicializaFila(FILA *f){
    f->ini = NULL;
    f->fim = NULL;
}

void enfileira(int dado, FILA *f){
    NO *ptr = (NO*) malloc(sizeof(NO));

    if (ptr == NULL){
        printf("Erro de alocação\n");
        return;
    } else {
        ptr->dado = dado;
        ptr->prox = NULL; //inicialmente ele vai receber o dado e sempre vai apontar para NULL
        if (f->ini == NULL){ // se TRUE é pq vai ser inserindo no primeiro nó
            f->ini = ptr;
        } else { // se não, inserir no fim (ultimo da fila)
            f->fim->prox = ptr; 
        }
        f->fim = ptr; // o final da fila sempre vai apontar para o novo nó
        return;
    }
}

int desenfileira(FILA *f){
    NO *ptr = f->ini;
    int dado; //variavel de "backup"
    if (ptr != NULL){
        f->ini = ptr->prox; // ou f->ini->prox;
        ptr->prox = NULL; //desenfileirando
        dado = ptr->dado; //armazenando o dado desenfileirado
        free(ptr);
        //opcional
        if (f->ini == NULL){
            f->fim = NULL;
        }
        return dado;
    } else {
        printf("Fila vazia\n");
        return NULL;
    }
}

void imprimeFila(FILA *f){
    NO *aux = f->ini;
    while (aux != NULL){
        printf("%d -> ", aux->dado);

        aux = aux->prox;
    }
    printf("NULL");
}

int main(void){

    FILA *f1 = (FILA*) malloc(sizeof(FILA));

    if (f1 == NULL){
        printf("Erro de alocação\n");
        exit(-1);
    } else {
        inicializaFila(f1);

        enfileira(10, f1);
        enfileira(20, f1);
        enfileira(30, f1);
        enfileira(40, f1);

        imprimeFila(f1);
        printf("\n");

        desenfileira(f1);
        imprimeFila(f1);
    }

    return 0;
}