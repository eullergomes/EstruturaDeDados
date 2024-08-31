#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
  int conteudo;
  struct cel *prox;
} celula;

celula *ultimo(celula *head) {
  if (head == NULL) return NULL;
  celula *tail = head;
  while (tail->prox != head) {
    tail = tail->prox;
  }
  return tail;
}

//remove o primeiro elemento
void remover(celula **head) {
  if (*head == NULL) {
    return;
  }

  if ((*head)->prox == *head) {
    free(*head);
    *head = NULL;
    return;
  }

  celula *tail = ultimo(*head);
  tail->prox = (*head)->prox;
  free(*head);
  *head = tail->prox;
}

void inserirInicio(celula **head, int valor) {
  celula *nova = (celula *)malloc(sizeof(celula));
  nova->conteudo = valor;

  if (*head == NULL) {
    *head = nova;
    nova->prox = *head;
    return;
  }

  nova->prox = *head;
  celula *tail = ultimo(*head);
  tail->prox = nova;
  *head = nova;
}

void imprimir(celula *head) {
  celula *aux = head;
  if (aux != NULL) {
    while (aux->prox != head) {
      printf("%d -> ", aux->conteudo);
      aux = aux->prox;
    }
    printf("%d -> ", aux->conteudo);
  }
  printf("HEAD\n");
}

void menu(){
    printf("\n*********************************\n");
    printf("*\t1 - inserir no inicio\t*\n");
    printf("*\t2 - Imprimir\t\t*\n");
    printf("*\t3 - Remover\t\t*\n");
    printf("*\t0 - Sair\t\t*\n\n");
}

int main(void) {
  celula *cabeca = NULL;
    int opc = 0, valor = 0;

    do{
        menu();
        scanf("%d", &opc);
        switch (opc){
        case 1:
            printf("Digite um valor:\n");
            scanf("%d", &valor);
            inserirInicio(&cabeca, valor);
            break;
        case 2:
            imprimir(cabeca);
            break;
        case 3:
            remover(&cabeca);
            break;
        case 0:
            printf("Finalizando...\n");
            break;
        default:
            break;
        }
        
    } while (opc != 0);

  return 0;
}