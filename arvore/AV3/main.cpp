#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct no{
    int localizador;
    int dia, mes, ano;
    float preco;
    char destino[30];
    struct no *esq;
    struct no *dir;
} No;

typedef struct {
    No *raizBr;
    No *raizArg;
} ArvB;

//inicializa as árvores
ArvB *inicializarArvB(){
    ArvB *arv = (ArvB*) malloc(sizeof(ArvB));
    arv->raizBr = NULL;
    arv->raizArg = NULL;
    
    return arv;
}

//cria o nó
No *criar_no(){
    No *node = (No*) malloc(sizeof(No));

    printf("\nDestino:\n");
    scanf("%30[^\n]s", &node->destino);

    printf("Data (dia/mês/ano):\n");
    scanf("%d\n%d\n%d", &node->dia, &node->mes, &node->ano);

    printf("Preço:\n");
    scanf("%f", &node->preco);

    node->localizador = rand() % 5; //0-100000
    printf("Localizador: %d\n", node->localizador);

    node->esq = NULL;
    node->dir = NULL;

    return node;
}

// int verificarRadom (No *raiz, int localizador){
//     if (raiz == NULL){
//         return; //considerando que todos os números são maiores que 0
//     }
//     else {
//         if (raiz->localizador == localizador)
//             return raiz->localizador = rand() % 5;
//         else {
//             if (localizador < raiz->localizador)
//                 return verificarRadom(raiz->esq, localizador);
//             if (localizador > raiz->localizador)
//                 return verificarRadom(raiz->dir, localizador);
//         }
//     }
// }

//insere o nó na raiz 
void inserirNaRaiz(No *raiz, No *node){
    if (raiz == NULL){
        printf("\nErro!\n");
        return;
    }

    if (raiz->localizador == node->localizador){
        printf("\nErro, localizador já existe\n");
        return;
    }    

    if (raiz->localizador < node->localizador){
        if (raiz->dir == NULL){
            raiz->dir = node;
            return;
        }
        inserirNaRaiz(raiz->dir, node);
    } else {
        if (raiz->esq == NULL){
            raiz->esq = node;
            return;
        }
        inserirNaRaiz(raiz->esq, node);
    }
}


//insere o nó na árvore
void inserir_raiz(No **raiz){
    if (*raiz == NULL){
        *raiz = criar_no();
        return;
    }

    No *novo = criar_no();
    inserirNaRaiz(*raiz, novo);
}

//Busca Pré-Ordem (profundidade)
void imprimirPre(No *raiz){
    if (raiz != NULL){ //se não estiver vazia
        printf("\n------------------------------------");
        printf("\nDestino: %s", raiz->destino);
        printf("\nData: %.2d/%.2d/%.4d", raiz->dia, raiz->mes, raiz->ano);
        printf("\nPreço: R$ %.2f", raiz->preco);
        printf("\nLocalizador: %d", raiz->localizador);
        printf("\n------------------------------------\n");
        imprimirPre(raiz->esq);
        imprimirPre(raiz->dir);
    }
}

//Busca em ordem (ordenado) - não achei necessário inserir no cód. mas funciona OK
void imprimirOrd(No *raiz){
    if (raiz != NULL){ //se não estiver vazia
        imprimirOrd(raiz->esq);
        printf("\n------------------------------------");
        printf("\nDestino: %s", raiz->destino);
        printf("\nData: %.2d/%.2d/%.4d", raiz->dia, raiz->mes, raiz->ano);
        printf("\nPreço: R$ %.2f", raiz->preco);
        printf("\nLocalizador: %d", raiz->localizador);
        printf("\n------------------------------------\n");
        imprimirOrd(raiz->dir);
    }
} 

//buscar destino
void buscarDestino(No *raiz, char destino[]){
    if (raiz == NULL) return;
    buscarDestino(raiz->dir, destino);
    if (strcmp(raiz->destino, destino) == 0){
        imprimirPre(raiz);
    }
    buscarDestino(raiz->esq, destino);
}

//quantidade de nós (passagens vendidas)
int tamanho (No *raiz){
    if (raiz == NULL){
        return 0;
    } else {
        return 1 + tamanho(raiz->esq) + tamanho(raiz->dir); 
    }
}

float valorArrecadado(No *raiz){
    float cont = 0.0f;
    if (raiz != NULL){
        return cont = raiz->preco + valorArrecadado(raiz->esq) + valorArrecadado(raiz->dir);
    }

    return cont;
}


void menu() {
    printf("\nMENU\n");
    printf("1 - Comprar passagem\n");
    printf("2 - Imprimir Árvores\n");
    printf("3 - Buscar por destino\n");
    printf("4 - Quantidade de voos e valor arrecadado\n");
    printf("0 - Sair\n\n");
    printf("Informe a opção: ");
}

int main (void){
    srand(time(NULL));

    ArvB *root = inicializarArvB();
    int opc = 0, opc2 = 0;
    char destino[30];

    do{
        menu();
        scanf("%d", &opc);
        getchar();
        switch (opc){
        case 0:
            printf("\n\nSaindo...\n");
            break;
        case 1:
            printf("\nINFORME SEU PAÍS:\n");
            printf("\n\t1 - Brasil");
            printf("\n\t2 - Argentina\n");

            printf("\nInforme a opção:\n");
            scanf("%d", &opc2);
            getchar();
            switch (opc2){
            case 1:
                inserir_raiz(&(root->raizBr));

                printf("\nCadastrado com sucesso!\n");
                break;
            case 2:

                inserir_raiz(&(root->raizArg));

                printf("\nCadastrado com sucesso!\n");
                break;
            default:
                printf("\n\nOpção inválida!\n");
                break;
            }
            
            break;
        case 2:
            printf("\nQual árvore gostaria de imprimir:\n");
            printf("\n\t1 - Brasil");
            printf("\n\t2 - Argentina\n");

            printf("\nInforme a opção:\n");
            scanf("%d", &opc2);
            getchar();
            switch (opc2){
            case 1:
                printf("\n*********BRASIL*************\n");
                imprimirPre(root->raizBr);
                break;
            case 2:
                printf("\n*********ARGENTINA*************\n");
                imprimirPre(root->raizArg);
                break;
            default:
                printf("\n\nOpção inválida!\n");
                break;
            }
            break;
        case 3:
            printf("\nEm qual árvore gostaria de buscar:\n");
            printf("\n\t1 - Brasil");
            printf("\n\t2 - Argentina\n");
            printf("\nInforme a opção: ");
            scanf("%d", &opc2);
            getchar();
            printf("\nInforme o destino:\n");
            scanf("%30[^\n]", &destino);
            switch (opc2){
            case 1:
                buscarDestino(root->raizBr, destino);
                break;
            case 2:
                buscarDestino(root->raizArg, destino);
                break;
            default:
                printf("\n\nOpção inválida!\n");
                break;
            }
            break;
        case 4:
            printf("\nEm qual árvore gostaria de verificar:\n");
            printf("\n\t1 - Brasil");
            printf("\n\t2 - Argentina\n");
            printf("\nInforme a opção: ");
            scanf("%d", &opc2);
            getchar();
            switch (opc2){
            case 1:
                printf("\nPASSAGENS VENDIDAS - Brasil:\n");
                printf("%d passagens\n", tamanho(root->raizBr));
                printf("Valor arrecadado: %f\n", valorArrecadado(root->raizBr));
                break;
            case 2:
                printf("\nPASSAGENS VENDIDAS - Argentina:\n");
                printf("%d passagens\n", tamanho(root->raizArg));
                printf("Valor arrecadado: %f\n", valorArrecadado(root->raizArg));
                break;
            default:
                printf("\n\nOpção inválida!\n");
                break;
            }
            break;
        
        default:
            printf("\nOpção inválida!\n");
            break;
        }
    } while (opc != 0);

}