#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no
{
    int num;
    int altura;
    no *esq = NULL;
    no *dir = NULL;
} No;

No *criar_no()
{
    No *novo = new No;
    scanf("%d", &novo->num);
    // novo->num = rand() % 101; // 0-100
    novo->altura = 0;
    printf("\nInserido\n");
    return novo;
}

int alturaSub(No *raiz, int altura);
No *buscar_no(No *node, int num);
int alturaArv(No *raiz);

void inserir_no(No *raiz, No *novo)
{
    if (raiz == NULL)
    {
        printf("\nErro\n");
        return;
    }

    if (raiz->num == novo->num)
    {
        printf("\nNumero ja existente!\n");
        return;
    }

    if (novo->num > raiz->num)
    {
        if (raiz->dir == NULL)
        {
            raiz->dir = novo;
            raiz->altura = alturaSub(raiz, raiz->num);
            return;
        }
        inserir_no(raiz->dir, novo);
    }
    else
    {
        if (raiz->esq == NULL)
        {
            raiz->esq = novo;
            raiz->altura = alturaSub(raiz, raiz->num);
            return;
        }
        raiz->altura = alturaSub(raiz, raiz->num);
        inserir_no(raiz->esq, novo);
    }
}

void inserir_raiz(No **raiz)
{
    if (*raiz == NULL)
    { // se raiz vazia
        *raiz = criar_no();
        return;
    }
    No *novo = criar_no();
    inserir_no(*raiz, novo);
    (*raiz)->altura = alturaSub((*raiz), (*raiz)->num); // para a raiz principal4
}

No *buscar_no(No *node, int num)
{
    if (node == NULL)
    {
        return NULL; // nao encontrado
    }
    if (node->num == num)
    {
        return node;
    }
    if (num > node->num)
    {
        return buscar_no(node->dir, num);
    }
    else
    {
        return buscar_no(node->esq, num);
    }
}

void imprimir(No *node, int tab = 0)
{
    if (node == NULL)
        return;

    imprimir(node->dir, tab + 1);
    for (int i = 0; i < tab; i++)
    {
        printf("\t");
    }
    printf("%d\n", node->num);
    imprimir(node->esq, tab + 1);
}

int alturaSub(No *raiz, int altura);

void imprimir_altura(No *node, int tab = 0)
{
    if (node == NULL)
        return;

    imprimir_altura(node->dir, tab + 1);
    for (int i = 0; i < tab; i++)
    {
        printf("\t");
    }
    printf("%d\n", alturaSub(node, node->num));
    imprimir_altura(node->esq, tab + 1);
}

void imprimir_altura2(No *node, int tab = 0)
{
    if (node == NULL)
        return;

    imprimir_altura(node->dir, tab + 1);
    for (int i = 0; i < tab; i++)
    {
        printf("\t");
    }
    printf("%d\n", node->altura);
    imprimir_altura(node->esq, tab + 1);
}

int maior_elem(No *root)
{
    if (root == NULL)
        return NULL;

    else if (root->dir == NULL)
        return root->num;

    else
        return maior_elem(root->dir);
}

int menor_elem(No *root)
{
    if (root == NULL)
        return NULL;

    if (root->esq == NULL)
        return root->num;

    else
        return menor_elem(root->esq);
}

int alturaArv(No *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        int esq = alturaArv(raiz->esq);
        int dir = alturaArv(raiz->dir);
        if (esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}

int alturaSub(No *raiz, int altura)
{
    No *no = buscar_no(raiz, altura);

    if (no != NULL)
        return alturaArv(no);

    else
        return NULL;
}

int soma_elementos(No *raiz)
{
    if (raiz == NULL)
        return 0;

    else
    {
        int elem_esquerda = soma_elementos(raiz->esq);
        int elem_direita = soma_elementos(raiz->dir);

        return raiz->num + elem_esquerda + elem_direita;
    }
}

int qtd_elementos(No *raiz)
{
    if (raiz == NULL)
        return 0;

    else
    {
        int elem_esquerda = qtd_elementos(raiz->esq);
        int elem_direita = qtd_elementos(raiz->dir);

        return 1 + elem_esquerda + elem_direita;
    }
}

float media(No *root)
{
    return soma_elementos(root) / alturaArv(root);
}

void arvore_aleatoria(No **root)
{
    for (int i = 0; i < 10; i++)
    {
        inserir_raiz(root);
    }
}

// retorna a altura do NÓ
int alturaNo(No *node)
{
    if (node == NULL)
        return -1;
    else
        return node->altura;
}

int fb(No *node)
{
    if (node != NULL)
        return (alturaNo(node->esq) - alturaNo(node->dir));
    else
        return 0;
}

// qual sub_arv tem a maior altura
int maior_alt(int esq, int dir)
{
    return (esq > dir) ? esq : dir;
}

No *rotacao_esq(No *root)
{
    No *y = root->dir;
    No *f = y->esq;

    y->esq = root;
    root->dir = f;
    return y;
}

void menu(){
    printf("MENU:\n");
    printf("1. Inserir\n");
    printf("2. Imprimir \n");
    printf("3. Maior, menor e media\n");
    printf("4. Altura sub-arvore\n");
    printf("5. Altura de cada sub-arvore\n");
    printf("6. Altura de cada sub-arvore 2.0\n");
    printf("7. Rotacao esquerda\n");
    printf("\nInforme a opcao: ");
}

int main(void)
{
    srand(time(NULL));

    No *root = NULL;
    int opc = 0, altura = 0;

    do
    {
        menu();
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            inserir_raiz(&root);
            printf("\n\n");
            break;
        case 2:
            imprimir(root);
            break;
        case 3:
            printf("\nMaior: %d", maior_elem(root));
            printf("\nMenor: %d", menor_elem(root));
            printf("\nMedia: %.2f\n\n", media(root));
            break;
        case 4:
            printf("Informe um NO:\n");
            scanf("%d", &altura);

            printf("Altura da sub arv %d: %d", altura, alturaSub(root, altura));
            printf("\n\n");
            break;
        case 5:
            imprimir_altura(root);
            break;
        case 6:
            imprimir_altura2(root);
            break;
        case 7:
            root = rotacao_esq(root);

            break;
        case 0:
            printf("\n\nSaindo...\n");
            exit(0);
            break;
        default:
            printf("\n\nOpcao invalida!\n");
            break;
        }
    } while (opc != 0);

    return 0;
}
