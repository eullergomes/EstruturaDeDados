#include <stdio.h>

typedef struct cel {
  int num;
  cel *ant;
  cel *prox;
} celula;

typedef struct list {
  celula *inicio;
  celula *fim;
  int tamanho;
} lista;

void anexar_fim(lista *nova, lista *lista) {
  nova->tamanho += lista->tamanho;
  nova->fim->prox = lista->inicio;
  lista->inicio->ant = nova->fim;
  nova->fim = lista->fim;
  delete lista;
}

void divide(lista *lista1, lista *lista2) {
  int tam_metade = lista1->tamanho / 2;
  celula *inicio2 = lista1->inicio;
  for (int i = 0; i < tam_metade; i++) {
    inicio2 = inicio2->prox;
  }

  celula *fim1 = inicio2->ant;
  fim1->prox = NULL;
  inicio2->ant = NULL;

  lista2->inicio = inicio2;
  lista2->fim = lista1->fim;
  lista2->tamanho = lista1->tamanho - tam_metade;

  lista1->fim = fim1;
  lista1->tamanho = tam_metade;
}

lista *merge(lista *lista1, lista *lista2) {
  lista *nova = new lista;

  while ((lista1->tamanho > 0) && (lista2->tamanho > 0)) {
    int num1 = lista1->inicio->num;
    int num2 = lista2->inicio->num;
    celula *elemento;
    if (num1 < num2) {
      elemento = remover_inicio(lista1);
    } else {
      elemento = remover_inicio(lista2);
    }
    inserir_fim(nova, elemento);
  }
  if (lista1->tamanho > 0) {
    inserir_fim(nova, lista1->inicio);
  }

  if (lista2->tamanho > 0) {
    anexar_fim(nova, lista2);
  }

  return nova;
}

int main(int argc, char const *argv[]) {
  int vetor[] = {8, 7, 3, 9, 2, 5, 6, 1, 4, 10};
  divide(vetor, 0, 9);
  return 0;
}
