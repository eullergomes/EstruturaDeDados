#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//FUNÇÕES DE LISTA ENCADEADA SIMPLES

typedef struct cel {
  int conteudo;
  struct cel *prox;
} celula;

void imprimir(celula *aux) {
  printf("\t");
  while (aux != NULL) {
    printf("%d -> ", aux->conteudo);
    aux = aux->prox;
  }
  printf("NULL\n\n");
}

void inserir_inicio(celula **ptr_cabeca, int valor) {
  celula *nova = (celula *)malloc(sizeof(celula));
  nova->conteudo = valor;
  nova->prox = *ptr_cabeca;
  *ptr_cabeca = nova;
}

void inserir_fim(celula **cabeca, int valor) {
  celula *nova = (celula *)malloc(sizeof(celula));
  nova->conteudo = valor;
  nova->prox = NULL;

  // Caso de lista vazia
  if (*cabeca == NULL) {
    *cabeca = nova;
    return;
  }

  celula *aux = *cabeca;
  while (aux != NULL) {
    if (aux->prox == NULL) {
      aux->prox = nova;
      break;
    }
    aux = aux->prox;
  }
}

celula *buscar(celula *aux, int valor) {
  while (aux != NULL) {
    if (aux->conteudo == valor) {
      return aux;  //"Elemento encontrado"
    }
    aux = aux->prox;
  }
  return NULL;  //"Elemento não encontrado"
}

void remover(celula **ptr_cabeca, int valor) {
  // Remover elemento que é cabeça
  if ((*ptr_cabeca)->conteudo == valor) {
    celula *tmp = *ptr_cabeca;
    *ptr_cabeca = (*ptr_cabeca)->prox;
    free(tmp);
    return;
  }

  // Remover demais elementos
  celula *aux = *ptr_cabeca;
  celula *p = NULL;
  while (aux != NULL) {
    p = aux->prox;
    if ((p != NULL) && (p->conteudo == valor)) {
      aux->prox = p->prox;
      free(p);
      return;
    }
    aux = aux->prox;
  }
}

//modificar para comprar com strings
void inserir_ordenado(celula **ptr_cabeca, celula *nova) {
  if (*ptr_cabeca == NULL) {
    nova->prox = *ptr_cabeca;
    *ptr_cabeca = nova;
  } else {
    celula *aux = *ptr_cabeca;
    celula *ant = NULL;

    while (aux != NULL) {
      if (nova->conteudo < aux->conteudo) {
        if (ant != NULL) {
          ant->prox = nova;
        } else {
          *ptr_cabeca = nova;
        }
        nova->prox = aux;
        return;
      }
      ant = aux;
      aux = aux->prox;
    }
    ant->prox = nova;
    nova->prox = aux;
  }
}

/**
 * Retorna a posição do elemento començando por 0.
 * Retorna -1 se não encontrar o elemento.
 * **/
int posicao(celula *cabeca, int valor) {
  celula *aux = cabeca;
  int pos = 0;
  while (aux != NULL) {
    if (aux->conteudo == valor) {
      return pos;  //"Elemento encontrado"
    }
    aux = aux->prox;
    pos++;
  }
  return -1;  //"Elemento não encontrado"
}

celula *troca_prox(celula *cabeca, int valor) {
  celula *a = NULL;
  celula *c = cabeca;
  celula *p = NULL;

  if (c->conteudo == valor) {
    if (c->prox == NULL) {
      printf("\tO proximo é NULL\n\n");
      return cabeca;
    }
    p = c->prox;
    c->prox = p->prox;
    p->prox = c;
    return p;
  }

  while ((c != NULL) && (c->prox != NULL)) {
    if (c->conteudo == valor) {
      a->prox = p;
      c->prox = p->prox;
      p->prox = c;
      return cabeca;
    }
    a = c;
    c = c->prox;
    p = c->prox;
  }
  return cabeca;
  // return -1;  //"Elemento não encontrado"
}

void concatena(celula *cabeca1, celula *cabeca2) {
  celula *aux = cabeca1;

  while ((aux != NULL) && (aux->prox != NULL)) {  // Encontrar o último
    aux = aux->prox;
  }
  aux->prox = cabeca2;
}

int tamanho(celula *cabeca) {
  if (cabeca == NULL) {
    return 0;
  }

  int tam = 0;
  celula *aux = cabeca;
  while (aux != NULL) {
    aux = aux->prox;
    tam++;
  }
  return tam;
}

celula *divirMetade(celula *cabeca1) {
  int tam1 = ceil(tamanho(cabeca1) / 2.0f);
  printf("\nTAM1: %d\n\n", tam1);
  celula *cabeca2 = NULL;

  celula *aux = cabeca1;
  int i = 0;
  while (i < tam1 - 1) {
    aux = aux->prox;
    i++;
  }

  cabeca2 = aux->prox;
  aux->prox = NULL;

  return cabeca2;
}

celula *dividir(celula *cabeca, int n) {
  celula *aux = cabeca;
  celula *cabeca2 = NULL;

  while (aux != NULL) {
    if (aux->conteudo == n) {
      cabeca2 = aux->prox;
      aux->prox = NULL;
      printf("\nLista 1:\n");
      imprimir(cabeca);
      printf("\nLista 2:\n");
      imprimir(cabeca2);
      return cabeca2;
    }
    aux = aux->prox;
  }

  printf("\nId não encontrado\n");
  return NULL;
}

celula *reverter(celula *cabeca1) {
  celula *aux = cabeca1;
  celula *ant = NULL;
  celula *prox = NULL;

  while (aux != NULL) {
    prox = aux->prox;
    aux->prox = ant;
    ant = aux;
    aux = prox;
  }

  celula *cabeca2 = ant;

  return cabeca2;
}


// int main(int argc, char const *argv[]) {
  // TROCA
  //  celula *cabeca = NULL;
  //  inserir_fim(&cabeca, 5);
  //  inserir_fim(&cabeca, 7);
  //  inserir_fim(&cabeca, 9);
  //  inserir_fim(&cabeca, 12);
  //  printf("Antes\n");
  //  imprimir(cabeca);
  //  cabeca = troca_prox(cabeca, 7);
  //  printf("Depois\n");
  //  imprimir(cabeca);

  // CONCATENA
  // celula *cabeca1 = NULL;
  // celula *cabeca2 = NULL;

  // inserir_fim(&cabeca1, 2);
  // inserir_fim(&cabeca1, 3);
  // inserir_fim(&cabeca1, 5);

  // inserir_fim(&cabeca2, 7);
  // inserir_fim(&cabeca2, 8);

  // printf("Antes\n");
  // imprimir(cabeca1);
  // imprimir(cabeca2);

  // concatena(cabeca1, cabeca2);

  // printf("Depois\n");
  // imprimir(cabeca1);

//OUTROS
//   celula *cabeca1 = NULL;
//   inserir_fim(&cabeca1, 2);
//   inserir_fim(&cabeca1, 3);
//   inserir_fim(&cabeca1, 5);
//   inserir_fim(&cabeca1, 7);
//   inserir_fim(&cabeca1, 9);

//   printf("Antes\n");
//   imprimir(cabeca1);

//   celula *cabeca2 = reverter(cabeca1);

//   printf("Depois\n");
//   imprimir(cabeca2);

//   return 0;
// }