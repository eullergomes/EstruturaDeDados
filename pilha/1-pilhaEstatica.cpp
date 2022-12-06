#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_PILHA 20 //contante 20

typedef struct {
    int vetor[TAMANHO_PILHA]; //tamanho da pilha
    int topo;
} Pilha;

void empilhar(int valor, Pilha *pilha){
    if (pilha->topo > TAMANHO_PILHA){
        printf("Pilha cheia\n");
        return;
    }
    pilha->vetor[pilha->topo] = valor;
    pilha->topo++;
}

void desempilhar(Pilha *pilha){
    if(pilha->topo <= 0){
        printf("Pilha vazia\n");
        return;
    }
    pilha->topo--;
    printf("Elemento retirado: %d", pilha->vetor[pilha->topo]);
}

void imprimir(Pilha *pilha){
    for(int i = (pilha->topo - 1); i >= 0; i--){
        printf("%d -> ", pilha->vetor[i]);
    }
    printf("NULL\n");
}

int main(void){
    int opc = 0;

    Pilha p;

    p.topo = 0; //inicializa a pilha com 0

    //empilha o numero 45 na posição 0
    p.vetor[p.topo] = 45;
    p.topo++;

    imprimir(&p);

    //desempilha o ultimo elemento
    p.topo--;
    printf("Elemento retirado: %d\n", p.vetor[p.topo]);
    imprimir(&p);
    printf("\n");
    
    //primeiro que entra, ultimo que sai
    empilhar(2, &p);
    empilhar(4, &p);
    empilhar(6, &p);
    empilhar(8, &p);
    empilhar(10, &p);

    imprimir(&p);
    printf("\n");

    desempilhar(&p);

    printf("\n");
    imprimir(&p);

    return 0;
}