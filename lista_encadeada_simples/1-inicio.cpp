#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
    int conteudo; //conteudo dos elementos da lista
    struct cel *prox; // para onde cada elemento da lista aponta
}celula;


int main(void) {
    //criando os elementos da lista
    celula c1;
    celula c2;
    celula c3;
    celula c4;
    celula *head; //cabeca da lista

    c1.conteudo = 3;
    c2.conteudo = 5;
    c3.conteudo = 7;
    c4.conteudo = 1;

    head = &c1;
    c1.prox = &c2;
    c2.prox = &c3;
    c3.prox = &c4;
    c4.prox = NULL;

    //percorrendo a lista
    celula *aux = head;
    while (aux != NULL) {
        printf("%d -> ", aux->conteudo);
        aux = aux->prox;
  }
  printf("NULL");

    return 0;
}