#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

// Data
typedef struct
{
  int dia, mes, ano;
} date;

// Medicamento
typedef struct
{
  char cod[20];
  char nome[30];
  date *data;
  int qtd;
  float preco;
} medicamento;

// Página da árvore B+
typedef struct page
{
  int qnt;
  bool folha;
  int codigos[N - 1];
  struct page *pai;
  medicamento *medicamentos[N - 1];
  struct page *filhos[N];
  struct page *prox;
} pagina;

pagina *criar_pagina()
{
  pagina *nova_pagina = new pagina;
  nova_pagina->qnt = 0;
  nova_pagina->folha = false;
  nova_pagina->pai = NULL;
  nova_pagina->prox = NULL;

  for (int i = 0; i < N; i++)
  {
    nova_pagina->filhos[i] = NULL;
  }

  return nova_pagina;
}

void inserir_medicamento(pagina **raiz, medicamento *novo_medicamento)
{
  if (*raiz == NULL)
  { // se vazia
    pagina *nova_pagina = criar_pagina();
    nova_pagina->folha = true;
    nova_pagina->medicamentos[0] = novo_medicamento;
    nova_pagina->qnt++;
    *raiz = nova_pagina;
  }
  else
  {
    pagina *pagina_atual = *raiz;
    while (!pagina_atual->folha)
    {
      int i = 0;
      while (i < pagina_atual->qnt && strcmp(novo_medicamento->cod, pagina_atual->medicamentos[i]->cod) >= 0)
      {
        i++;
      }
      pagina_atual = pagina_atual->filhos[i];
    }

    // Buscar o medicamento na página folha
    int i = 0;
    while (i < pagina_atual->qnt && strcmp(novo_medicamento->cod, pagina_atual->medicamentos[i]->cod) > 0)
    {
      i++;
    }

    if (i < pagina_atual->qnt && strcmp(novo_medicamento->cod, pagina_atual->medicamentos[i]->cod) == 0)
    {
      // Se já existe, apenas incrementar a quantidade
      pagina_atual->medicamentos[i]->qtd += novo_medicamento->qtd;
      free(novo_medicamento); // Liberar a memória alocada para o medicamento não utilizado
    }
    else
    {
      // Inserir na página folha
      int j = pagina_atual->qnt - 1;
      while (j >= 0 && strcmp(novo_medicamento->cod, pagina_atual->medicamentos[j]->cod) < 0)
      {
        pagina_atual->medicamentos[j + 1] = pagina_atual->medicamentos[j];
        j--;
      }
      pagina_atual->medicamentos[j + 1] = novo_medicamento;
      pagina_atual->qnt++;

      if (pagina_atual->qnt == N)
      { // se pag cheia
        int meio = (N - 1) / 2;
        pagina *nova_pagina = criar_pagina();
        nova_pagina->folha = true;
        nova_pagina->prox = pagina_atual->prox;
        pagina_atual->prox = nova_pagina;

        for (int k = meio + 1; k < N; k++)
        {
          nova_pagina->medicamentos[k - meio - 1] = pagina_atual->medicamentos[k];
          nova_pagina->qnt++;
          pagina_atual->qnt--;
        }

        // Atualizar filhos da página pai
        nova_pagina->pai = pagina_atual->pai;
        nova_pagina->folha = pagina_atual->folha;

        for (int k = 0; k < N; k++)
        {
          nova_pagina->filhos[k] = pagina_atual->filhos[k + meio + 1];
          pagina_atual->filhos[k + meio + 1] = NULL;
        }

        inserir_medicamento(&pagina_atual->pai, nova_pagina->medicamentos[0]);
      }
    }
  }
}

medicamento *buscar_medicamento(pagina *raiz, char *codigo)
{
  if (raiz == NULL)
  {
    return NULL;
  }

  pagina *pagina_atual = raiz;
  while (!pagina_atual->folha)
  {
    int i = 0;
    while (i < pagina_atual->qnt && strcmp(codigo, pagina_atual->medicamentos[i]->cod) > 0)
    {
      i++;
    }
    pagina_atual = pagina_atual->filhos[i];
  }

  int i = 0;
  while (i < pagina_atual->qnt && strcmp(codigo, pagina_atual->medicamentos[i]->cod) != 0)
  {
    i++;
  }

  if (i < pagina_atual->qnt)
  {
    return pagina_atual->medicamentos[i];
  }
  else
  {
    return NULL;
  }
}

void retirar_medicamento(pagina** raiz, char* cod, int qtd) {
  if (*raiz == NULL) {
    printf("Árvore vazia. Nenhum medicamento para retirar.\n");
    return;
  }

  pagina* pagina_atual = *raiz;
  while (!pagina_atual->folha) {
    int i = 0;
    while (i < pagina_atual->qnt && strcmp(cod, pagina_atual->medicamentos[i]->cod) >= 0) {
      i++;
    }
    pagina_atual = pagina_atual->filhos[i];
  }

  int i = 0;
  while (i < pagina_atual->qnt && strcmp(cod, pagina_atual->medicamentos[i]->cod) != 0) {
    i++;
  }

  if (i < pagina_atual->qnt) {
    pagina_atual->medicamentos[i]->qtd -= qtd;
    if (pagina_atual->medicamentos[i]->qtd <= 0) {
      free(pagina_atual->medicamentos[i]); // Se qtd for zero, remover o registro da árvore
      for (int j = i + 1; j < pagina_atual->qnt; j++) {
        pagina_atual->medicamentos[j - 1] = pagina_atual->medicamentos[j];
      }
      pagina_atual->qnt--;
    }
    printf("\nMedicamento retirado com sucesso!\n\n");
  } else {
    printf("\nMedicamento nao encontrado.\n\n");
  }
}

date* ler_data() {
  date* nova_data = (date*)malloc(sizeof(date));

  printf("Dia: ");
  scanf("%d", &nova_data->dia);
  printf("Mes: ");
  scanf("%d", &nova_data->mes);
  printf("Ano: ");
  scanf("%d", &nova_data->ano);

  return nova_data;
}

medicamento *ler_medicamento(pagina *raiz)
{
  medicamento *novo_medicamento = new medicamento;
  printf("Codigo do medicamento: ");
  scanf("%s", novo_medicamento->cod);

  // Verificar se o medicamento já existe
  if (buscar_medicamento(raiz, novo_medicamento->cod) != NULL)
  {
    printf("Medicamento ja cadastrado. Informe apenas a quantidade: ");
    scanf("%d", &novo_medicamento->qtd);
    novo_medicamento->nome[0] = '\0';
    novo_medicamento->data = NULL;
    novo_medicamento->preco = 0;
  }
  else
  {
    printf("Nome do medicamento: ");
    scanf("%s", novo_medicamento->nome);
    printf("Quantidade: ");
    scanf("%d", &novo_medicamento->qtd);
    printf("Preco: ");
    scanf("%f", &novo_medicamento->preco);
    novo_medicamento->data = ler_data();
  }

  return novo_medicamento;
}

void imprimir_medicamentos(pagina* raiz) {
  if (raiz == NULL) {
    return;
  }

  // Se a pag for folha
  if (!raiz->folha) {
    for (int i = 0; i < raiz->qnt + 1; i++) {
      imprimir_medicamentos(raiz->filhos[i]);
      if (i < raiz->qnt) {
        printf("------------------------\n");
        printf("Codigo: %s\n", raiz->medicamentos[i]->cod);
        printf("Nome: %s\n", raiz->medicamentos[i]->nome);
        printf("Data de cadastro: %.2d - %.2d - %.4d\n", raiz->medicamentos[i]->data->dia, raiz->medicamentos[i]->data->mes, raiz->medicamentos[i]->data->ano);
        printf("Quantidade: %d\n", raiz->medicamentos[i]->qtd);
        printf("Preco: R$ %.2f\n", raiz->medicamentos[i]->preco);
        printf("------------------------\n");
      }
    }
  } else { // Se não for folha
    for (int i = 0; i < raiz->qnt; i++) {
      printf("------------------------\n");
      printf("Codigo: %s\n", raiz->medicamentos[i]->cod);
      printf("Nome: %s\n", raiz->medicamentos[i]->nome);
      printf("Data de cadastro: %.2d - %.2d - %.4d\n", raiz->medicamentos[i]->data->dia, raiz->medicamentos[i]->data->mes, raiz->medicamentos[i]->data->ano);
      printf("Quantidade: %d\n", raiz->medicamentos[i]->qtd);
      printf("Preco: R$ %.2f\n", raiz->medicamentos[i]->preco);
      printf("------------------------\n");
    }
  }
}

// Libera memória alocada da árvore B+
void liberar_arvore(pagina *raiz)
{
  if (raiz != NULL)
  {
    if (raiz->folha)
    {
      for (int i = 0; i < raiz->qnt; i++)
      {
        free(raiz->medicamentos[i]->data);
        free(raiz->medicamentos[i]);
      }
    }
    else
    {
      for (int i = 0; i < raiz->qnt + 1; i++)
      {
        liberar_arvore(raiz->filhos[i]);
      }
    }
    free(raiz);
    printf("\nEncerrando...\n");
  }
}

void menu()
{
  printf("===== Menu =====\n");
  printf("1. Cadastrar medicamento\n");
  printf("2. Buscar medicamento\n");
  printf("3. Retirar medicamento\n");
  printf("4. Imprimir medicamentos cadastrados\n");
  printf("0. Sair\n");
  printf("\nInforme a opcao: ");
}

int main()
{
  pagina *raiz = NULL;
  int opc = 0;

  do
  {
    menu();
    scanf("%d", &opc);

    switch (opc)
    {
    case 1:
    {
      medicamento *novo_medicamento = ler_medicamento(raiz);
      inserir_medicamento(&raiz, novo_medicamento);
      printf("\nMedicamento cadastrado com sucesso!\n\n");
      break;
    }
    case 2:
    {
      char codigo_busca[20];
      printf("\nDigite o codigo do medicamento a ser buscado: ");
      scanf("%s", codigo_busca);

      medicamento *medicamento_encontrado = buscar_medicamento(raiz, codigo_busca);

      if (medicamento_encontrado != NULL)
      {
        printf("\nMedicamento encontrado:\n");
        printf("Codigo: %s\n", medicamento_encontrado->cod);
        printf("Nome: %s\n", medicamento_encontrado->nome);
        printf("Data de cadastro: %.2d - %.2d - %.4d\n", medicamento_encontrado->data->dia, medicamento_encontrado->data->mes, medicamento_encontrado->data->ano);
        printf("Quantidade: %d\n", medicamento_encontrado->qtd);
        printf("Preco: R$ %.2f\n\n", medicamento_encontrado->preco);
      }
      else
      {
        printf("\nErro: medicamento nao encontrado.\n\n");
      }
      break;
    }
    case 3: {
      char cod_retirada[20];
      int qtd_retirada = 0;

      printf("\nCodigo do medicamento a ser retirado: ");
      scanf("%s", cod_retirada);
      printf("Quantidade a ser retirado: ");
      scanf("%d", &qtd_retirada);

      retirar_medicamento(&raiz, cod_retirada, qtd_retirada);
      break;
    }
    case 4:{
      printf("\nMEDICAMENTOS:\n");
      imprimir_medicamentos(raiz);
      printf("\n");
      break;
    }
    default:
      printf("\nOpcao invalida! Tente novamente.\n\n");
      break;
    }

  } while (opc != 0);

  liberar_arvore(raiz); // libera a memória alocada da arv
  return 0;
}