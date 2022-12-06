#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
    int dado;
    struct NO *prox;
}NO;

typedef struct PILHA{
    NO *topo;
}PILHA;

void incializarPilha(PILHA *p){
    p->topo = NULL; //pilha vazia
}

void empilhar(int dado, PILHA *p){
    NO *ptr = (NO*) malloc(sizeof(NO)); //alocando memoria para os dados que vão sendo inseridos

    if (ptr == NULL){
        printf("Erro de alocação de nó\n"); //se não for alocado
        return;
    } else {
        ptr->dado = dado;
        ptr->prox = p->topo;
        p->topo = ptr;
    }
}

int desempilhar(PILHA *p){
    NO *ptr = p->topo; //nó de "backup"
    int dado;
    if(ptr == NULL){
        printf("Pilha vazia\n");
    } else {
        p->topo = ptr->prox;
        ptr->prox = NULL;
        dado = ptr->dado; //armazenando o valor removido
        free(ptr);
        return dado;
    }
}

void imprimirPilha(PILHA *p){ //imprimir do topo até a base
    NO *ptr = p->topo; 
    if(ptr == NULL){
        printf("Pilha vazia");
        return;
    } else {
        while(ptr != NULL){
            printf("%d -> ", ptr->dado);
            ptr = ptr->prox;
        }
        printf("NULL");
    }
}

int main(void){
    PILHA *p1 = (PILHA*) malloc (sizeof(PILHA));

    if(p1 == NULL){
        printf("Erro de alocação da pilha\n");
        exit(0);
    } else {
        incializarPilha(p1);

        empilhar(10, p1);
        empilhar(20, p1);
        empilhar(30, p1);

        imprimirPilha(p1);

        printf("\n");

        desempilhar(p1); //desempilha o último elemento

        imprimirPilha(p1);
    }


    return 0;
}