#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no *esq;
    struct no *dir;
}No;

typedef struct{
    No *raiz;
    //int quant; //quantidade de nós da árvore
} ArvB;

//assinatura do procedimento pois ele só vem depois dessa função 
void inserirDireita(No *no, int valor);

void inserirEsquerda(No *no, int valor){
    //se não tiver ninguem a esquerda
    if(no->esq == NULL){
        No *novo = (No*) malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        no->esq = novo;
    } else { //se ja tiver elementos
        if(valor < no->esq->conteudo){
            inserirEsquerda(no->esq, valor); //chamada repursiva
        } if(valor > no->esq->conteudo) { //
            inserirDireita(no->esq, valor);
        }
    }
}

void inserirDireita(No *no, int valor){
    //se não tem ninguem a direita
    if(no->dir == NULL){
        No *novo = (No*) malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        no->dir = novo;
    } else { //se já tiver elementos na direita
        if(valor > no->dir->conteudo){
            inserirDireita(no->dir, valor);
        } if (valor < no->dir->conteudo) {
            inserirEsquerda(no->dir, valor); //o valor vai ficar a esquerda do nó da direita
        }
    }
}

void inserir(ArvB *arv, int valor){
    //quando não tem ninguem na raiz
    if(arv->raiz == NULL){
        No *novo = (No*) malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        arv->raiz = novo;
    } else { //se ja tiver elementos
        if(valor < arv->raiz->conteudo){
            inserirEsquerda(arv->raiz, valor); //menor que a raiz da arvore
        } if(valor > arv->raiz->conteudo) {
            inserirDireita(arv->raiz, valor);
        }
    }
}

//Pré-ordem
void imprimir1(No *raiz){
    if(raiz != NULL){ //se não estiver vazia
        printf("%d ", raiz->conteudo);
        imprimir1(raiz->esq);
        imprimir1(raiz->dir);
    }
}
//Em ordem
void imprimir2(No *raiz){
    if(raiz != NULL){ //se não estiver vazia
        imprimir2(raiz->esq);
        printf("%d ", raiz->conteudo);
        imprimir2(raiz->dir);
    }
}

//Pós-ordem
void imprimir(No *raiz){
    if(raiz != NULL){ //se não estiver vazia
        imprimir(raiz->esq);
        imprimir(raiz->dir);
        printf("%d ", raiz->conteudo);
    }
}

int main(void){
    int opc = 0, valor = 0;
    ArvB arvore;

    arvore.raiz = NULL;

    do{
        printf("\n0 - sair\n1 - Inserir\n2 - Imprimir\n\n");
        printf("Informe a opção: ");
        scanf("%d", &opc);

        switch (opc){
        case 0:
            printf("\nSaindo...\n");
            break;
        case 1:
            printf("\nDigite um valor:\n");
            scanf("%d", &valor);

            inserir(&arvore, valor);
            break;
        case 2:
            printf("\nImpressão da árvore binária:\n");
            imprimir(arvore.raiz);
            break;
        default:
            printf("\nOpção inválida!\n");
            break;
        }

    } while (opc != 0);
    
    return 0;
}