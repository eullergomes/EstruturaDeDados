#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no *esq;
    struct no *dir;
}No;

//retorna um ponteiro para o nó
No *inserirNovaVersao(No *raiz, int valor){
    if(raiz == NULL){ //se não tiver ninguem
        No *novo = (No*) malloc(sizeof(No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->conteudo = valor;
        return novo;
    } else { //se já tiver elementos
        if (valor < raiz->conteudo){
            raiz->esq = inserirNovaVersao(raiz->esq ,valor); //o valor vai para a esquerda, o raiz->esquerda está sendo usado como uma raíz
        }
        if (valor > raiz->conteudo){
            raiz->dir = inserirNovaVersao(raiz->dir, valor);
        }
        return raiz;
    }
}

void imprimir(No *raiz){
    if(raiz != NULL){ //se não estiver vazia
        imprimir(raiz->esq);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->dir);
    }
} 

int main(void){
    int opc = 0, valor = 0;
    No *raiz = NULL;

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
            raiz = inserirNovaVersao(raiz, valor);
            //inserir(&arv, valor);
            break;
        case 2:
            printf("\nImpressão da árvore binária:\n");
            imprimir(raiz);
            break;
        default:
            printf("\nOpção inválida!\n");
            break;
        }

    } while (opc != 0);
    

    return 0;
}