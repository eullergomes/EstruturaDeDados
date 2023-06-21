#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

enum Cor{
    VERMELHO,
    PRETO
};

typedef struct Node{
    int num = 0;
    int altura = 0;
    Cor cor = VERMELHO;
    struct Node *esq = NULL, *dir = NULL, *pai = NULL;
} Node;

Node *criar_no(){
    Node *novo = (Node *)malloc(sizeof(Node));

    printf("\nDigite um numero para inserir: ");
    scanf("%d", &novo->num);
    novo->cor = VERMELHO;
    novo->altura = 0;
    novo->esq = novo->dir = novo->pai = NULL;
    return novo;
}

int altura(Node *node){
    if (node == NULL)
        return 0;
    if (node->cor == VERMELHO){
        return fmax(altura(node->esq), altura(node->dir));
    } else {
        return fmax(altura(node->esq), altura(node->dir)) + 1;
    }
}

void rotacao_esq(Node **raiz, Node *node){
    Node *filho_dir = node->dir;
    node->dir = filho_dir->esq;
    if (node->dir != NULL){
        node->dir->pai = node;
    }
    filho_dir->pai = node->pai;
    if (node->pai == NULL){
        *raiz = filho_dir;
    }
    else if (node == node->pai->esq){
        node->pai->esq = filho_dir;
    } else {
        node->pai->dir = filho_dir;
    }
    filho_dir->esq = node;
    node->pai = filho_dir;
}

void rotacao_dir(Node **raiz, Node *node){
    Node *filho_esq = node->esq;
    node->esq = filho_esq->dir;
    if (node->esq != NULL){
        node->esq->pai = node;
    }
    filho_esq->pai = node->pai;
    if (node->pai == NULL){
        *raiz = filho_esq;
    }
    else if (node == node->pai->esq){
        node->pai->esq = filho_esq;
    } else {
        node->pai->dir = filho_esq;
    }
    filho_esq->dir = node;
    node->pai = filho_esq;
}

void recolorir(Node **raiz, Node *node){
    Node *pai = NULL;
    Node *avo = NULL;
    while ((node != *raiz) && (node->cor != PRETO) && (node->pai->cor == VERMELHO)){
        pai = node->pai;
        avo = node->pai->pai;
        if (pai == avo->esq){
            Node *tio = avo->dir;
            if ((tio != NULL) && (tio->cor == VERMELHO)){
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                node = avo;
            }else{
                if (node == pai->dir){
                    rotacao_esq(raiz, pai);
                    node = pai;
                    pai = node->pai;
                }
                rotacao_dir(raiz, avo);
                Cor cor_temp = pai->cor;
                pai->cor = avo->cor;
                avo->cor = cor_temp;
                node = pai;
            }
        } else {
            Node *tio = avo->esq;
            if ((tio != NULL) && (tio->cor == VERMELHO)){
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                node = avo;
            } else {
                if (node == pai->esq){
                    rotacao_dir(raiz, pai);
                    node = pai;
                    pai = node->pai;
                }
                rotacao_esq(raiz, avo);
                Cor cor_temp = pai->cor;
                pai->cor = avo->cor;
                avo->cor = cor_temp;
                node = pai;
            }
        }
    }
    (*raiz)->cor = PRETO;
}

void inserir_raiz(Node **raiz){
    Node *node = criar_no();
    Node *pai = NULL;
    Node *aux = *raiz;
    // percorre a arv
    while (aux != NULL){
        pai = aux;
        if (node->num < aux->num){
            aux = aux->esq;
        } else {
            aux = aux->dir;
        }
    }

    node->pai = pai;
    node->altura = 0; //
    if (pai == NULL){ // sem pai
        *raiz = node;
    } else if (node->num < pai->num) {
        pai->esq = node;
    } else {
        pai->dir = node;
    }
    recolorir(raiz, node);
    node->altura = 1;

    Node *temp = node->pai;
    while (temp != NULL){
        temp->altura = altura(temp);
        temp = temp->pai;
    }
    printf("\n");
}

void imprimir(Node *node, int tab = 0){
    if (node == NULL)
        return;

    imprimir(node->dir, tab + 1);
    for (int i = 0; i < tab; i++){
        printf("\t");
    }
    if (node->cor == VERMELHO)
        printf("\033[31m%d\033[0m\n", node->num);
    else
        printf("%d\n", node->num);
    imprimir(node->esq, tab + 1);
}

char verificar_cor(Node *raiz){
    if (raiz->cor == VERMELHO)
        return 'V';

    if (raiz->cor == PRETO)
        return 'P';

    else
        return NULL;
}

void imprimir_cores(Node *node, int tab = 0){
    if (node == NULL)
        return;

    imprimir_cores(node->dir, tab + 1);
    for (int i = 0; i < tab; i++){
        printf("\t");
    }
    printf("%c\n", verificar_cor(node));
    imprimir_cores(node->esq, tab + 1);
}

void imprimir_alturas(Node *node, int tab = 0){
    if (node == NULL)
        return;

    imprimir_alturas(node->dir, tab + 1);
    for (int i = 0; i < tab; i++){
        printf("\t");
    }
    printf("%d\n", node->altura);
    imprimir_alturas(node->esq, tab + 1);
}

Node *buscar_no(Node *node, int num){
    if (node == NULL)
        return NULL;

    if (node->num == num)
        return node;

    if (node->num < num)
        return buscar_no(node->dir, num);

    else
        return buscar_no(node->esq, num);
}

Node *buscar_tio(Node *no){
    if (no->pai->esq == no){
        return no->pai->dir;
    } else if (no->pai->dir == no){
        return no->pai->esq;
    } else {
        return NULL;
    }
}

//menor nó
Node *min_node(Node *node) {
    while (node->esq != NULL) {
        node = node->esq;
    }
    return node;
}

//encontra o sucessor de um nó
Node *tree_successor(Node *node) {
    if (node->dir != NULL) {
        return min_node(node->dir);
    }
    Node *no_sucessor = node->pai;
    while (no_sucessor != NULL && node == no_sucessor->dir) {
        node = no_sucessor;
        no_sucessor = no_sucessor->pai;
    }
    return no_sucessor;
}

void reorganizar_arv(Node **raiz, Node *no_remov, Node *no_sucessor) {
    while (no_remov != *raiz && (no_remov == NULL || no_remov->cor == PRETO)) {
        if (no_remov == no_sucessor->esq) {
            Node *no_backup = no_sucessor->dir;
            if (no_backup->cor == VERMELHO) {
                no_backup->cor = PRETO;
                no_sucessor->cor = VERMELHO;
                rotacao_esq(raiz, no_sucessor);
                no_backup = no_sucessor->dir;
            }
            if ((no_backup->esq == NULL || no_backup->esq->cor == PRETO) &&
                (no_backup->dir == NULL || no_backup->dir->cor == PRETO)) {
                no_backup->cor = VERMELHO;
                no_remov = no_sucessor;
                no_sucessor = no_remov->pai;
            } else {
                if (no_backup->dir == NULL || no_backup->dir->cor == PRETO) {
                    if (no_backup->esq != NULL) {
                        no_backup->esq->cor = PRETO;
                    }
                    no_backup->cor = VERMELHO;
                    rotacao_dir(raiz, no_backup);
                    no_backup = no_sucessor->dir;
                }
                no_backup->cor = no_sucessor->cor;
                no_sucessor->cor = PRETO;
                if (no_backup->dir != NULL) {
                    no_backup->dir->cor = PRETO;
                }
                rotacao_esq(raiz, no_sucessor);
                no_remov = *raiz;
            }
        } else {
            Node *no_backup = no_sucessor->esq;
            if (no_backup->cor == VERMELHO) {
                no_backup->cor = PRETO;
                no_sucessor->cor = VERMELHO;
                rotacao_dir(raiz, no_sucessor);
                no_backup = no_sucessor->esq;
            }
            if ((no_backup->dir == NULL || no_backup->dir->cor == PRETO) &&
                (no_backup->esq == NULL || no_backup->esq->cor == PRETO)) {
                no_backup->cor = VERMELHO;
                no_remov = no_sucessor;
                no_sucessor = no_remov->pai;
            } else {
                if (no_backup->esq == NULL || no_backup->esq->cor == PRETO) {
                    if (no_backup->dir != NULL) {
                        no_backup->dir->cor = PRETO;
                    }
                    no_backup->cor = VERMELHO;
                    rotacao_esq(raiz, no_backup);
                    no_backup = no_sucessor->esq;
                }
                no_backup->cor = no_sucessor->cor;
                no_sucessor->cor = PRETO;
                if (no_backup->esq != NULL) {
                    no_backup->esq->cor = PRETO;
                }
                rotacao_dir(raiz, no_sucessor);
                no_remov = *raiz;
            }
        }
    }
    if (no_remov != NULL) {
        no_remov->cor = PRETO;
    }
}

void remover_node(Node **raiz, int num) {
    Node *pai_no_remov = NULL, *no_remov = NULL, *no_sucessor = NULL;
    pai_no_remov = buscar_no(*raiz, num);
    if (pai_no_remov == NULL) {
        return; 
    }
    if (pai_no_remov->esq == NULL || pai_no_remov->dir == NULL) {
        no_sucessor = pai_no_remov;
    } else {
        no_sucessor = tree_successor(pai_no_remov);
    }
    if (no_sucessor->esq != NULL) {
        no_remov = no_sucessor->esq;
    } else {
        no_remov = no_sucessor->dir;
    }
    if (no_remov != NULL) {
        no_remov->pai = no_sucessor->pai;
    }
    if (no_sucessor->pai == NULL) {
        *raiz = no_remov;
    } else {
        if (no_sucessor == no_sucessor->pai->esq) {
            no_sucessor->pai->esq = no_remov;
        } else {
            no_sucessor->pai->dir = no_remov;
        }
    }
    if (no_sucessor != pai_no_remov) {
        pai_no_remov->num = no_sucessor->num;
    }
    if (no_sucessor->cor == PRETO) {
        reorganizar_arv(raiz, no_remov, no_sucessor->pai);
    }
    free(no_sucessor);
    printf("\n\nNO removido!\n\n");
}

void menu(){
    printf("MENU\n");
    printf("1. Inserir\n");
    printf("2. Imprimir\n");
    printf("3. Remover\n");
    printf("4. Buscar pai, avo, tio\n");
    printf("5. Imprimir cores\n");
    printf("6. Imprimir alturas\n");
    printf("0. SAIR\n");
    printf("\nInforme a opcao: \n");
}

int main(void){
    Node *root = NULL, *no = NULL, *tio = NULL;
    int opc = 0, num = 0;

    do {
        menu();
        scanf("%d", &opc);

        switch (opc){
        case 1:
            inserir_raiz(&root);
            break;

        case 2:
            printf("\n");
            imprimir(root);
            printf("\n");
            break;

        case 3:
            printf("Digite um numero:");
            scanf("%d", &num);
            remover_node(&root, num);
            break;

        case 4:
            printf("Digite um numero para buscar: ");
            scanf("%d", &num);

            no = buscar_no(root, num);
            
            if (no == NULL){
                printf("\nNO nao encontrado\n\n");
                break;
            }

            printf("\nNo Buscado: %d\n", num);
            printf("Pai: %d\n", (no->pai != NULL) ? no->pai->num : 0);

            printf("Avo: %d\n", (no->pai->pai != NULL) ? no->pai->pai->num : 0);

            tio = buscar_tio(no->pai); //se não existir um tio (NULL), o programa simplesmente fecha
            if (tio == NULL){ //
                printf("Tio: 0\n\n");
                break;
            }

            printf("Tio: %d\n\n", tio->num);

            break;

        case 5:
            printf("\n");
            imprimir_cores(root);
            printf("\n");
            break;

        case 6:
            imprimir_alturas(root);
            break;

        case 0:
            printf("\n\nSaindo...\n");
            break;

        default:
            printf("\n\nOpcao invalida!\n\n");
            break;
        }
    } while (opc != 0);
    return 0;
}