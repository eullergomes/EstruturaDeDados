#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct cel {
    int conteudo;
    //parte anterior e próxima de cada celula 
    struct cel *ant;
    struct cel *prox;
}celula;

//trocar elementos de posicao(para elementos vizinhos)
void troca(celula *elem1, celula *elem2){
    celula *prim = elem1->ant;
    celula *ult = elem2->prox;
    //trocando as posições (REPRESENTAÇÃO NO PAPEL)
    prim->prox = elem2;
    ult->ant = elem1;
    elem2->prox = elem1;
    elem1->prox = ult;
    elem1->ant = elem2; 
    elem2->ant = prim;
}

//imprimir lista
void imprimir(celula *cabeca) {
    celula *tmp = cabeca;
    while (tmp != NULL) {
        printf("%d -> ", tmp->conteudo);
        tmp = tmp->prox;
    }
    printf("NULL");
}

celula *ultimo(celula *aux){
    //verificando caso a lista não tenha nenhum elemento
    //if ()

    //chegando no ultimo elemento da lista
    while (aux->prox != NULL){
        aux = aux->prox; // recebendo o valor do ultimo elemento
    }
    return aux;
}

//função para calcular o tamanho da lista
int tamanho(celula *cabeca){
    //caso a lista não tenha nehum elemento
    if (cabeca == NULL){
        return 0;
    }

    int tam = 0;
    celula *aux = cabeca;
    //percorrendo a lista
    while (aux != NULL){
        aux = aux->prox;
        tam++;
    }
    return tam; //tamanho da lista
}

//divindo a lista em duas
celula *metade(celula *cabeca1){
    //arredonda  para cima
    int tam1 = ceil(tamanho(cabeca1) / 2.0f);
    celula *cabeca2 = NULL;

    celula *aux = cabeca1;
    int i = 0;
    while (i < tam1 - 1){
        aux - aux->prox;
        i++;
    }

    cabeca2 = aux->prox;
    aux->prox = NULL;

    return cabeca2;
}

//concatenar duas listas
void merge(celula *cabeca1, celula *cabeca2){
    
}


int main(void) {
    //criando as celulas
    celula c1;
    celula c2;
    celula c3;
    celula c4;

    //dando conteudo para cada alemento da lista
    c1.conteudo = 3;
    c2.conteudo = 5;
    c3.conteudo = 7;
    c4.conteudo = 1;

    //definindo para onde cada elemento da lista aponta
    celula *cabeca = &c1; //head -> c1
    c1.ant = NULL;
    c1.prox = &c2;
    c2.ant = &c1;
    c2.prox = &c3;
    c3.ant = &c2;
    c3.prox = &c4;
    c4.ant = &c3;
    c4.prox = NULL;

    printf("Antes:\n");
    imprimir(cabeca);

    printf("\nDepois:\n");
    troca(&c2, &c3);
    imprimir(cabeca);
    

    return 0;
}