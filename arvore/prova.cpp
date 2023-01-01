#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Uma empresa de transporte aéreo BR decidiu ampliar suas operações para a Argentina. Esta empresa dispôes de um sistema de VENDA DE PASSAGENS que armazena suas operações em uma ArvB ordenada pelo localizador de cada bilhete. A empresa decidiu manter as vendas separadas por país ---> 2 ArvB

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

ArvB *inicializarArvores(){
    ArvB *arv = (ArvB*) malloc(sizeof(ArvB));
    arv->raizBr = NULL;
    arv->raizArg = NULL;
    
    return arv;
}

No *criarNo() {
    No *node = (No*)malloc(sizeof(No));

    printf("\nInforme o dia/mês/ano: ");
    scanf("%d\n%d\n%d", &node->dia, &node->mes, &node->ano);

    printf("\nInforme o preço da passagem: ");
    scanf("%d", &node->preco);

    printf("\nInforme o destino: ");
    scanf("%30[^\n]s", &node->destino);

    node->localizador = rand() %10; //0-9
    printf("Localizador: %d", node->localizador);

    node->esq = NULL;
    node->dir = NULL;

    return node;
}

void inserir_no(No *raiz, No *node) {
    if (raiz == NULL) {
        printf("Erro\n");
        return;
    }

    // if (raiz->num == node->num) {
    //     printf("O número já existe\n");
    //     return;
    // }

    //node->num > raiz->num
    if (node->localizador > raiz->localizador) {
        if (raiz->dir == NULL) { //só executa essa função se não tiver ninguem na direita
            raiz->dir = node;
            return; // a função termina se não tiver ninguem a direita do nó raiz
        }

        inserir_no(raiz->dir, node); // percorrendo a direita da minha raiz
    
    } else { // se node->num < raiz->num
        if (raiz->esq == NULL) {
            raiz->esq = node;
            return;
        }
    inserir_no(raiz->esq, node); // percorrendo a esquerda da minha raiz
    }
}

//o parâmetro é a arvBr ou arvArg
void inserirRaiz(No **raiz) {
    if (*raiz == NULL) { //se não tiver nínguem na raiz
        *raiz = criarNo();
        return;
    }
    //se já tiver elementos na raiz
    No *node = criarNo();
    node->localizador = verificarRadom(*raiz, node);
    inserir_no(*raiz, node);
}

//verifica se o localizador já existe
int verificarRadom (No *raiz, No *node){
    if (raiz == NULL){
        printf("\nErro!\n");
        return NULL;
    }
    if (node->localizador == raiz->localizador){
        node->localizador = rand() % 9;
        return node->localizador; //testar se mesmo com o novo localizador ainda não vai estar duplicado

    } else { //percorre a árvore com funções recursivas até encontrar um localizador diferente
        if (node->localizador > raiz->localizador)
            return verificarRadom(raiz->dir, node);
        if (node->localizador < raiz->localizador)
            return verificarRadom(raiz->esq, node);
    }
    //return node->localizador;
}

void menu() {
    printf("\nMENU\n");
    printf("1-Inserir\n");
    //printf("2-Buscar\n");
    printf("3-Imprimir Árvore\n");
    //printf("4-Remover\n");
    printf("0-Sair\n\n");
    printf("Informe a opção: ");
}

int main(void){
    srand(time(NULL));

    ArvB *root = inicializarArvores();

    int opc = 0, numArv = 0;

    do{
        menu();
        scanf("%d", &opc);

        switch (opc){
        case 0:
            printf("\n\nSaindo...\n");
            break;
        case 1:
            printf("\nEm qual árvore você gostaria de inserir:\n");
            printf("1 - Brasil\n");
            printf("2 - Argentina\n");
            printf("\nInforme a opção: ");
            scanf("%d", &numArv);

            if (numArv == 1){
                //inserirRaiz(&root);
            }
            
            break;
        case 3:
            
            break;
        
        default:
        printf("\n\nOpção inválida!\n");
            break;
        }

    } while (opc != 0);
    

    return 0;
}