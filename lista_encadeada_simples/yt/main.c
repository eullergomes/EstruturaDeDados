#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *prox;
} Node;

typedef struct {
    Node *first;
    Node *last;
    int size;
} List;

//initialing the list
void initialize (List *list){
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
}

void insertFirst(List *list, int value){
    Node *new = (Node*) malloc(sizeof(Node));

    if(new == NULL){
        printf("Erro de alocação");
        return;
    } else {
        new->value = value;

        if(list->first == NULL){ // if empty list
            new->prox = NULL;
            list->first = new;
            list->last = new;
        } else {
            new->prox = list->first;
            list->first = new;
        }
        list->size++;
    }
}

void insertLast(List *list, int value){
    Node *new = (Node*) malloc(sizeof(Node));

    if (new == NULL){
        printf("Erro de alocação");
        return;
    } else {
        
        new->value = value;
        new->prox = NULL; // the last element will always point to NULL 

        if (list->first == NULL){ // if empty
            list->first = new;
            list->last = new;
        } else {
            list->last->prox = new;
            list->last = new;
        }
        list->size++;
    }
}

//I'm not going to modify the struct
void print(Node *aux){

    while (aux->prox != NULL){
        printf("%d -> ", aux->value);
        aux = aux->prox;
    }
    printf("NULL\n");
}

Node *removeFirst(List *list){
    if (list->first != NULL){
        //with one command: list->first = list->first->prox;
        Node *node = list->first;
        list->first = node->prox;
        list->size--;
        if (list->first == NULL)
            list->last = NULL;
        return node;
    } else {
        return NULL;
    }
}

//searches for the value to be removed
Node *remove (List *list, int value){
    // Node *first = list->first;
    // Node *aRemove = NULL;
    
    //remove at the beginning
    if (list->first != NULL && list->first->value == value){
        list->first = list->first->prox;
        if (list->first == NULL){
            list->last = NULL;
        }
    } else{
        while (list->first != NULL && list->first->prox != NULL && list->first->prox->value != value){
            list->first = list->first->prox;
        }
        if (list->first != NULL && list->first->prox == NULL){
            
        }
        
    }
} 

void menu(){
    printf("MENU\n");
    printf("1 - Inserir no início\n");
    printf("2 - Inserir no fim\n");
    printf("3 - Imprimir Lista\n");
    printf("0 - Sair\n");
    printf("\nInforme o valor: ");
}

int main (void){
    List *list;
    int opc = 0, num = 0;

    initialize (list);

    do{
        menu();
        scanf("%d", &opc);
        switch (opc){
        case 1:
            printf("\nDigite um número: ");
            scanf("%d", &num);

            insertFirst(list, num);
            printf("\n\nInserido no início com sucesso!\n\n");
            break;
        case 2:
            printf("\nDigite um número: ");
            scanf("%d", &num);

            insertLast(list, num);
            printf("\n\nInserido no fim com sucesso!\n\n");
            break;
        // case 3:
        //     printf("\n\nLista:\n");
        //     print(&list);
        //     break;
        
        default:
            printf("\n\nOpção inválida!\n\n");
            break;
        }
    } while (opc != 0);

    return 0;
}
