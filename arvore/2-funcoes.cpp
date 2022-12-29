#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    int tam;
    struct no *esq;
    struct no *dir;
}No;

//retorna um ponteiro para o nó
No *inserirNovaVersao(No *raiz, int valor){
    if (raiz == NULL){ //se não tiver ninguem
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

int tamanho (No *raiz){
    if (raiz == NULL){
        return 0;
    } else {
        return 1 + tamanho(raiz->esq) + tamanho(raiz->dir); 
    }
}

//Busca em ordem (ordenado)
void imprimirOrd(No *raiz){
    if(raiz != NULL){ //se não estiver vazia
        imprimirOrd(raiz->esq);
        printf("%d ", raiz->conteudo);
        imprimirOrd(raiz->dir);
    }
} 

//Busca Pré-Ordem (profundidade)
void imprimirPre(No *raiz){
    if(raiz != NULL){ //se não estiver vazia
        printf("%d ", raiz->conteudo);
        imprimirPre(raiz->esq);
        imprimirPre(raiz->dir);
    }
} 

int buscar (No *raiz, int chave){
    if (raiz == NULL){
        return -1; //considerando que todos os números são maiores que 0
    }
    else {
        if (raiz->conteudo == chave)
            return raiz->conteudo;
        else {
            if (chave < raiz->conteudo)
                return buscar(raiz->esq, chave);
            if (chave > raiz->conteudo)
                return buscar(raiz->dir, chave);
        }
    }
}

//retorna um ponteiro para o nó
No *remover (No *raiz, int chave){
    if (raiz == NULL){
        printf("\n\nValor não encontrado!\n");
        return NULL;
    } else {
        if (raiz->conteudo == chave){
            //remove nós folhoas(nós sem folhas)
            if(raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                return NULL; // a esq ou dir do nó pai vai apontar para NULL
            } else {
                //remove nós com apenas 1 filho
                if (raiz->esq != NULL || raiz->dir != NULL){
                    No *aux; //variavel para guarda o filho do nó a ser removido
                    if (raiz->esq != NULL)
                        aux = raiz->esq;
                    else 
                        aux = raiz->dir;
                    free(raiz);
                    return aux; //retornando o filho do nó removido o pai do nó removido (avô)
                }
            }
        }
        else {
            if (chave < raiz->conteudo)
                raiz->esq = remover(raiz->esq, chave);
            else
                raiz->dir = remover(raiz->dir, chave);
            return raiz;
        }
    }
}

void menu(){
    printf("\nMENU:\n");
    printf("1 - Inserir nó\n");
    printf("2 - Imprimir árvore ordenada\n");
    printf("3 - Imprimir árvore em profundidade\n");
    printf("4 - Buscar nó\n");
    printf("5 - Remover nó\n");
    printf("0 - Sair\n\n");
    printf("Informe a opção: ");
}

int main(void){
    int opc = 0, valor = 0;
    No *raiz = NULL;

    do{
        menu();
        scanf("%d", &opc);

        switch (opc){
        case 0:
            printf("\n\nSaindo...\n");
            break;
        case 1:
            printf("\nDigite um valor:\n");
            scanf("%d", &valor);
            raiz = inserirNovaVersao(raiz, valor);
            break;
        case 2:
            printf("\nImpressão da árvore binária em ordem:\n");
            imprimirOrd(raiz);
            printf("\n");
            printf("Tamanho: %d", tamanho(raiz));
            break;
        case 3:
            printf("\nImpressão da árvore binária em profundidade:\n");
            imprimirPre(raiz);
            printf("\n");
            printf("Tamanho: %d", tamanho(raiz));
            break;
        case 4:
            printf("\nDigite um número a ser buscado: ");
            scanf("%d", &valor);

            if (buscar(raiz, valor) == -1)
                printf("\nValor não encontrado!\n\n");
            else 
                printf("\n\nResultado da busca: %d", buscar(raiz, valor));
            break;
        case 5:
            printf("Digite um número para remover: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            printf("\n\nRemovido com sucesso!\n");
            break;
        default:
            printf("\n\nOpção inválida!\n");
            break;
        }
    } while (opc != 0);
    return 0;
}