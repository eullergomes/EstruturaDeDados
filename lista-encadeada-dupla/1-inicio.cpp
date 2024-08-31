#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num;
    struct node *prox;
    struct node *ant;
} Node;

typedef struct {
    int size;
    node *head;
    node *tail;
} List;

List *createdList (){
    List *list = new List;
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node *createdNode (int data){
    Node *no = new Node;
    no->ant = NULL;
    no->prox = NULL;
    no->num = data;
    return no;
}

void inserirInicio (List *list, int data){
    Node *new_no = createdNode(data);

    if (list->head == NULL){ //se lista vazia
        list->head = new_no;
        list->tail = new_no;
    } else {
        new_no->prox = list->head;
        list->head->prox = new_no;
        list->head = new_no;
    }
}

void imprimir (List *list){
    Node *no = list->head;

    while (no != NULL){
        printf("%d -> ", no->num);
        no = no->prox;
    }
}

int main(void){
    List *lista = createdList();

    inserirInicio(lista, 8);
    inserirInicio(lista, 2);
    inserirInicio(lista, 3);
    inserirInicio(lista, 9);
    inserirInicio(lista, 11);
    inserirInicio(lista, 7);

    imprimir(lista);


    return 0;
}
