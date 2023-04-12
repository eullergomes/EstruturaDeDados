#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Implemente um programa que utilize uma lista encadeada simples para armazenar uma
relação com nomes de pessoas. As funções abaixo devem estar disponíveis no programa:
  a. Adicionar um novo elemento
  b. Imprimir a lista
  c. Embaralhar a lista
  d. Ordenar utilizando Bubble Sort
  e. Ordenar utilizando Selection Sort
  f. Ordenar utilizando Insertion Sort
*/

typedef struct cel {
  char nome[30];
  struct cel *prox;
} celula;

celula *cabeca = NULL; //LISTA DE NOMES

celula *anterior(celula *cel) {
  if (cel == cabeca) {
    return NULL;
  }

  celula *ant = cabeca;
  while (ant != NULL) {
    if (ant->prox == cel) {
      return ant;
    }
    ant = ant->prox;
  }
  return NULL;
}

//trocar 2 nós de posição
void swap(celula *cel1, celula *cel2) {
  if ((cel1 == NULL) || (cel2 == NULL)) return;

  celula *ant1 = NULL;
  celula *ant2 = NULL;

  celula *tmp = NULL;

  if ((cabeca == cel2) || (cel2->prox == cel1)) {
    tmp = cel2;
    cel2 = cel1;
    cel1 = tmp;
  }

  if (cabeca != cel1) {
    ant1 = anterior(cel1);
  }

  ant2 = anterior(cel2);

  if (cel1 != cel2) {
    tmp = cel2->prox;

    if (ant1 != NULL) {
      ant1->prox = cel2;
    }

    if (cel1 != ant2) {
      ant2->prox = cel1;
      cel2->prox = cel1->prox;

      if (cel2->prox == cel1) {
        cel1->prox = cel2;
      } else {
        cel1->prox = tmp;
      }
    } else {
      cel2->prox = cel1;
      cel1->prox = tmp;
    }

    if (cabeca == cel1) {
      cabeca = cel2;
    }
  }
}

void imprimir() {
  celula *aux = cabeca;
  while (aux != NULL) {
    printf("%s -> ", aux->nome);
    aux = aux->prox;
  }
  printf("NULL\n");
}

celula *inserir_inicio(const char *n) {
  celula *nova = (celula *)malloc(sizeof(celula));
  strcpy(nova->nome, n); //copia o nome para a lista e insere
  nova->prox = cabeca;
  cabeca = nova;
  return nova;
}

//qtd de elementos
int length(celula *cabeca) {
  celula *aux = cabeca;
  int cont = 0;
  while (aux != NULL) {
    aux = aux->prox;
    cont++;
  }
  return cont;
}

//retorna o nó na posição P da lista
celula *pos(int p) {
  celula *aux = cabeca;
  int cont = 0;
  while (aux != NULL) {
    if (cont == p) {
      return aux; 
    }
    aux = aux->prox;
    cont++;
  }
  return NULL;
}

//embaralhar nós da lista
void shuffle() {
  int size = length(cabeca);
  for (int i = 0; i < size; i++) {
    //seleciona 2 nós aleatorios para trocar de posição
    celula *cel1 = pos(rand() % size); 
    celula *cel2 = pos(rand() % size);
    swap(cel1, cel2);
  }
}

void bubbleSort() {
  if (cabeca == NULL){
    printf("\nLista vazia!\n\n");
    return;
  }

  int size = length(cabeca);

  for (int i = 0; i < size - 1; i++){
    for (int j = 0; j < size - i - 1; j++){
      celula *cel1 = pos(j);
      celula *cel2 = pos(j+1);

      if (strcmp(cel1->nome, cel2->nome) > 0){ //cel1 > cel2
        swap(cel1, cel2);
      }
    }
  }

  printf("\nBubble sort - ordenado com sucesso!\n\n");
}

void selectionSort () {
    if (cabeca == NULL){
      printf("\nLista vazia!\n\n");
      return;
    }

    int size = length(cabeca);
    int cont = 0;
    celula *cel_atual = cabeca;
    while (cont < size - 1) { //percorre cada nó individualmente
        celula *min_node = cel_atual; 
        celula *next_node = cel_atual->prox;
        while (next_node != NULL) {
            if (strcmp(next_node->nome, min_node->nome) < 0) { 
                min_node = next_node;
            }
            next_node = next_node->prox;
        }
        
        swap(cel_atual, min_node);
        cel_atual = pos(cont + 1);
        cont++;
    }

    printf("\nSelect sort - ordenado com sucesso!\n\n");
}

void insertionSort() {
  if (cabeca == NULL){
    printf("\nLista vazia!\n\n");
    return;
  }

  celula *lista_ordenada = NULL;
  celula *cel_atual = cabeca;

  while (cel_atual != NULL) { //percorre cada nó individualmente
    celula *next_node = cel_atual->prox;

    if (lista_ordenada == NULL || strcmp(cel_atual->nome, lista_ordenada->nome) < 0) { //atual < lista_ord
      cel_atual->prox = lista_ordenada;
      lista_ordenada = cel_atual; //insere no inicio da nova lista
    } else {
      celula *search_node = lista_ordenada;
      while (search_node->prox != NULL && strcmp(cel_atual->nome, search_node->prox->nome) > 0) {
        search_node = search_node->prox; //percorre a nova lista
      }
      cel_atual->prox = search_node->prox;
      search_node->prox = cel_atual; //insere ordenado na nova lista
    }

    cel_atual = next_node; //incremento p/ percorrer a lista antiga
  }

  cabeca = lista_ordenada; //lista principal recebe a nova lista ordenada

  printf("\nInsertion sort - ordenado com sucesso!\n\n");
}

void clearList() {
  celula *aux = cabeca;
  celula *next = NULL;
    
  while (aux != NULL) {
    next = aux->prox;
    free(aux);
    aux = next;
  }
    
  cabeca = NULL;
}

void menu (){
  printf("MENU\n");
  printf("1 - Inserir\n");
  printf("2 - Imprimir\n");
  printf("3 - Embaralhar\n");
  printf("4 - Limpar lista\n");
  printf("5 - Ordenar Bubble Sort\n");
  printf("6 - Ordenar Selection Sort\n");
  printf("7 - Ordenar Insertion Sort\n");
  printf("0 - SAIR\n");
  printf("\nInforme a opcao: ");
}

int main (void) {
  int opc = 0;
  int tam = 0;

  srand(time(NULL));
  
  do{
    menu();
    scanf("%d", &opc);
    getchar();

    switch (opc){
    case 1:
      char nome[30];
      printf("\nDigite o nome: ");
      scanf("%30[^\n]s", nome);
      printf("\n");

      inserir_inicio(nome);
      break;
    case 2:
      tam = length(cabeca);
      imprimir();
      printf("Tamanho: %d\n\n", tam);
      break;
    case 3:
      printf("\nEmbaralhado com sucesso!\n\n");
      shuffle();
      break;
    case 4:
      clearList();
      printf("\nResetado com sucesso!\n\n");
      break;
    case 5:
      bubbleSort();
      break;
    case 6:
      selectionSort();
      break;
    case 7:
      insertionSort();
      break;
    case 0:
      printf("\nEncerrando...\n\n");
      exit(0);
      break;
    
    default:
      printf("\n\nOpcao invalida!\n");
      break;
    }

  } while (opc != 0);
  
}