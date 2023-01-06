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
    No *raizVendas;
} ArvB;

//inicializa as árvores
ArvB *inicializarArvB(){
    ArvB *arv = (ArvB*) malloc(sizeof(ArvB));
    arv->raizBr = NULL;
    arv->raizArg = NULL;
    arv->raizVendas = NULL;
    
    return arv;
}

ArvB *root = inicializarArvB();

//Verifica se o localizador já existe em alguma das árvores
No *buscar_no(No *node, int localizador){
    if (node == NULL) return NULL;
    if (node->localizador == localizador) return node;
    if (localizador > node->localizador) return buscar_no(node->dir, localizador);
    else return buscar_no(node->esq, localizador);
}

//Gera um número aleatório que ainda não foi usado como localizador
int randomNum (){
    int num = rand() % 1001; //0-1000
    if (buscar_no(root->raizBr, num) == NULL && buscar_no(root->raizArg, num) == NULL) return num;
    else randomNum();
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

    node->localizador = randomNum();
    printf("Localizador: %d\n", node->localizador);

    printf("\nCadastrado com sucesso!\n");

    node->esq = NULL;
    node->dir = NULL;

    return node;
}

//insere o nó na raiz 
void inserirNaRaiz(No *raiz, No *node){
    if (raiz == NULL){
        printf("\nErro!\n");
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
        printf("\n---------------------------");
        printf("\nDestino: %s", raiz->destino);
        printf("\nData: %.2d/%.2d/%.4d", raiz->dia, raiz->mes, raiz->ano);
        printf("\nPreço: R$ %.2f", raiz->preco);
        printf("\nLocalizador: %d", raiz->localizador);
        printf("\n---------------------------\n");
        imprimirPre(raiz->esq);
        imprimirPre(raiz->dir);
    }
}

//Busca em ordem (ordenado) - não achei necessário inserir no cód. mas funciona OK
void imprimirOrd(No *raiz){
    if (raiz != NULL){ //se não estiver vazia
        imprimirOrd(raiz->esq);
        printf("\n---------------------------");
        printf("\nDestino: %s", raiz->destino);
        printf("\nData: %.2d/%.2d/%.4d", raiz->dia, raiz->mes, raiz->ano);
        printf("\nPreço: R$ %.2f", raiz->preco);
        printf("\nLocalizador: %d", raiz->localizador);
        printf("\n---------------------------\n");
        imprimirOrd(raiz->dir);
    }
} 

void imprimirDestino(No *raiz){
    if (raiz != NULL){ //se não estiver vazia
        printf("\n---------------------------");
        printf("\nDestino: %s", raiz->destino);
        printf("\nData: %.2d/%.2d/%.4d", raiz->dia, raiz->mes, raiz->ano);
        printf("\nPreço: R$ %.2f", raiz->preco);
        printf("\nLocalizador: %d", raiz->localizador);
        printf("\n---------------------------\n");
    }
}

//buscar destino
void buscarDestino(No *raiz, char *destino){
    if (raiz == NULL) return;

    if (strcmp(raiz->destino, destino) == 0){
        imprimirDestino(raiz);
    }
    buscarDestino(raiz->esq, destino);
    buscarDestino(raiz->dir, destino);

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
    printf("1 - Vender passagem\n");
    printf("2 - Imprimir árvore\n");
    printf("3 - Buscar por destino\n");
    printf("4 - Relatório\n");
    printf("0 - Sair\n\n");
    printf("Informe a opção: ");
}

void infoPais(){
    printf("\nINFORME O PAÍS:\n");
    printf("\n\t1 - Brasil");
    printf("\n\t2 - Argentina\n");
    printf("\nInforme a opção: ");
}

int main (void){
    srand(time(NULL));

    int opc = 0, pais = 0;
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
            printf("\nopção escolhida: VENDER PASSAGEM\n");
            infoPais();
            scanf("%d", &pais);
            getchar();
            switch (pais){
            case 1:
                inserir_raiz(&(root->raizBr));
                break;
            case 2:
                inserir_raiz(&(root->raizArg));
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\n\nOpção inválida!\n");
                break;
            }
            break;
        case 2:
            printf("\nopção escolhida: IMPRIMIR ÁRVORE\n");
            infoPais();
            scanf("%d", &pais);
            getchar();
            switch (pais){
            case 1:
                printf("\n**********BRASIL***********\n");
                imprimirPre(root->raizBr);
                break;
            case 2:
                printf("\n*********ARGENTINA*********\n");
                imprimirPre(root->raizArg);
                break;
            default:
                printf("\n\nOpção inválida!\n");
                break;
            }
            break;
        case 3:
            printf("\nopção escolhida: BUSCAR POR DESTINO\n");
            printf("\nInforme o destino:\n");
            scanf("%30[^\n]", &destino);
            
            printf("\n---------------------------\n");
            printf("|    Resultado da busca   |");
            printf("\n---------------------------\n");
            printf("\n**********BRASIL***********\n");
            buscarDestino(root->raizBr, destino);
            printf("\n*********ARGENTINA*********\n");
            buscarDestino(root->raizArg, destino);
            break;
        case 4:
            printf("\nopção escolhida: RELATÓRIO\n");
            infoPais();
            scanf("%d", &pais);
            getchar();

            printf("\n---------------------------\n");
            printf("|        Relatório        |");
            printf("\n---------------------------\n");

            switch (pais){
            case 1:
                printf("\nBRASIL:\n");
                printf("Passagens vendidas: %d\n", tamanho(root->raizBr));
                printf("Valor arrecadado: R$ %.2f\n", valorArrecadado(root->raizBr));
                break;
            case 2:
                printf("\nARGENTINA:\n");
                printf("Passagens vendidas: %d\n", tamanho(root->raizArg));
                printf("Valor arrecadado: R$ %.2f\n", valorArrecadado(root->raizArg));
                break;
            default:
                printf("\n\nOpção inválida!\n");
                break;
            }
            break;
        }
        printf("\n");
    } while (opc != 0);
}