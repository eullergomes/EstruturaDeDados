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

ArvB *inicializarArvB(){
    ArvB *arv = (ArvB*) malloc(sizeof(ArvB));
    arv->raizBr = NULL;
    arv->raizArg = NULL;
    
    return arv;
}

No *criar_no(){
    No *node = (No*) malloc(sizeof(No));

    printf("\nDestino:\n");
    scanf("%30[^\n]s", &node->destino);

    printf("Data (dia/mês/ano):\n");
    scanf("%d\n%d\n%d", &node->dia, &node->mes, &node->ano);

    printf("Preço:\n");
    scanf("%f", &node->preco);

    node->localizador = rand() % 10; //0-9
    printf("Localizador: %d\n", node->localizador);

    node->esq = NULL;
    node->dir = NULL;

    return node;
}

void inserirNaRaiz(No *root, No *node){
    if (root == NULL){
        printf("\nErro!\n");
        return;
    }

    if (root->localizador == node->localizador){
        printf("\nErro, localizador já existe\n");
        return;
    }    

    if (root->localizador < node->localizador){
        if (root->dir == NULL){
            root->dir = node;
            return;
        }
        inserirNaRaiz(root->dir, node);
    } else {
        if (root->esq == NULL){
            root->esq = node;
            return;
        }
        inserirNaRaiz(root->esq, node);
    }
}

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

//Busca em ordem (ordenado) - não achei necessário mas funciona OK
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

No *buscar_no(No *node, char destino[]) {
    if (node == NULL){
        return NULL;
    }
    if (strcmp(node->destino, destino) == 0){
        return node;
    }
    if (strcmp(destino, node->destino) > 0){
        return buscar_no(node->dir, destino);
    }
    if (strcmp(destino, node->destino) < 0){
        return buscar_no(node->esq, destino);        
    }  
}

void buscar(No *raiz) {
    char destino[30];
    printf("\nDigite o destino a ser buscado:\n");
    scanf("%30[^\n]", &destino);
    getchar();
    No *res = buscar_no(raiz, destino);
    if (res != NULL) {
        imprimirPre(res);
    } else {
        printf("\nResultado não encontrado\n");
    }
}

// int valorArrecadado(No *root){
//     static float valor = 0;
//     if (root == NULL){
//         printf("\nÁrvore não encontrada\n");
//         return 0;
//     } else {
//         return valor = valorArrecadado(root->esq->preco) + valorArrecadado(root->dir);
//     }
// }

int tamanho (No *raiz){
    if (raiz == NULL){
        return 0;
    } else {
        return 0 + tamanho(raiz->esq) + tamanho(raiz->dir); 
    }
}

// int buscaAB(Node *raiz, int dado){
// 	if (raiz->dado == dado)
// 		return 1;
// 	else {
// 		if (dado > raiz->dado)
// 			raiz = direita(raiz);
// 		else
// 			raiz = esquerda(raiz);8
		
// 		if (raiz == NULL) return 0;
// 		buscaAB(raiz, dado);
// 	}
// }

void menu() {
    printf("\nMENU\n");
    printf("1 - Comprar passagem\n");
    printf("2 - Imprimir Árvore\n");
    printf("3 - Buscar\n");
    printf("4 - Tamanho da árvore\n");
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
            switch (opc2){
            case 1:
                buscar(root->raizBr);
                break;
            case 2:
                buscar(root->raizArg);
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
                break;
            case 2:
                printf("\nPASSAGENS VENDIDAS - Argentina:\n");
                printf("%d passagens\n", tamanho(root->raizArg));
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