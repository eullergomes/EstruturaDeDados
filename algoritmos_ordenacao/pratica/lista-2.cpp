#include <stdio.h>
#include <stdlib.h>

/*
Você foi contratado para desenvolver um sistema para controlar a distribuição de ingressos
para eventos gratuitos organizados pela prefeitura municipal. Um dos principais problemas
que este software visa solucionar é a disponibilização de mais de um ingresso para a mesma
pessoa em determinada data, portanto o sistema deve impedir estas duplicidades. Desenvolva
uma solução para este problema considerando os requisitos abaixo:

    A) Cada ingresso deve armazenar o cpf, nome do comprador e a data do evento, para
evitar que a mesma pessoa possua várias entradas na mesma data.

    B) Você deve implementar o armazenamento dos ingressos utilizando uma lista
encadeada simples.
    
    C) Uma opção deve estar disponível para buscar todos os ingressos já emitidos para
um determinado cpf. Neste caso, o sistema deve ordenar a lista utilizando o método
Insertion Sort.
    D)
     Antes de realizar a inserção de um novo ingresso, o sistema deve conferir se existe
algum registro de cpf e data já cadastrado e notificar o usuário.
    E) Ao fim do processo de vendas, uma opção deve ordenar a lista pela data do evento
utilizando o método Quick Sort e informando quantos ingressos foram cadastrados
em cada data.
*/

typedef struct {
    int dia, mes, ano;
} date;

typedef struct ticket{
    int cpf;
    char nome[50];
    date data;
    ticket *prox = NULL;
} Ticket;

typedef struct list{
    int tam = 0;
    Ticket *inicio = NULL;
    Ticket *fim = NULL;
} List;

List *lista = new List;

Ticket *lerDados(){
    Ticket *novo = new Ticket;

    fflush(stdin);
    printf("\nNome: ");
    scanf("%50[^\n]s", novo->nome);
    
    printf("CPF: ");
    scanf("%d", &novo->cpf);

    printf("Data do ingresso (dd/mm/aaaa):\n");
    scanf("%d\n%d\n%d", &novo->data.dia, &novo->data.mes, &novo->data.ano);

    printf("\n");
    return novo;
}

//converte DIA/MES/ANO para DIAS TOTAIS
int diasTotais (Ticket *ingresso){
    int qtdDias = ingresso->data.dia + (ingresso->data.mes*12) + (ingresso->data.ano*365);

    return qtdDias;
}

//cadastra o ingresso e insere na lista
void armazenar_ingresso (List *lst){
    Ticket *ingresso = lerDados();
    if (ingresso->data.dia > 30){
        printf("Erro! O mes tem no maximo 30 dias\n\n");
        return;
    }

    Ticket *aux = lst->inicio;

    //convertendo dd/mm/aa para dias totais
    int dia_cadastrado = diasTotais(ingresso);

    while (aux != NULL){
        int dia_do_evento = diasTotais(aux);

        if (dia_cadastrado == dia_do_evento && ingresso->cpf == aux->cpf){
            printf("ERRO! Um ingresso ja foi registrado para esse dia\n\n");
            return;
        }
        aux = aux->prox;
    }
    
    if (lst->tam == 0) {
        lst->inicio = ingresso;
        lst->fim = ingresso;
        lst->tam = 1;
        ingresso->prox = NULL;
        return;
    }

    ingresso->prox = lst->inicio;
    lst->inicio = ingresso;
    lst->tam++;
}

void imprimir(List *lst){
    Ticket *aux = lst->inicio;

    printf("\nINGRESSOS:\n");
    while (aux != NULL){
        printf("----------------------\n");
        printf("Nome: %s\n", aux->nome);
        printf("CPF: %d\n", aux->cpf);
        printf("Data: %.2d / %.2d / %.4d \n", aux->data.dia, aux->data.mes, aux->data.ano);
        printf("----------------------\n");
        aux = aux->prox;
    }
    printf("\n");
}

//ordena pelo CPF
void insertionSort(List *lst) {
    Ticket *newList = NULL; //nova lista ordenada
    Ticket *aux = lst->inicio; //percorre lista original

    while (aux != NULL) {
        Ticket *proximoElem = aux->prox;
        //Inserindo o nó na lista ordenada
        if (newList == NULL || aux->cpf < newList->cpf) {
            aux->prox = newList;
            newList = aux;
            if (newList->prox == NULL){
                lst->fim = newList; //quando a lista tiver apenas um elemento
            }
        } else {
            //percorre a lista ordenada e insere o elemento ordenado
            Ticket *temp = newList;
            while (temp->prox != NULL && aux->cpf > temp->prox->cpf) {
                temp = temp->prox;
            }
            aux->prox = temp->prox;
            temp->prox = aux;

            if (aux->prox == NULL){
                lst->fim = aux; //ultimo elemento da lista
            }
        }
        aux = proximoElem;
    }

    lst->inicio = newList;
    printf("\nLista ordenada com Insertion Sort!\n\n");
}

void buscar(List *lst) {
    if ((lst == NULL) || (lst->tam == 0)){
        printf("\n\nLista vazia!\n");
        return;
    }
    Ticket *aux = lst->inicio;

    int cpf = 0;
    printf("\nInforme o CPF a ser buscado: ");
    scanf("%d", &cpf);

    printf("\nINGRESSOS DO CPF %d\n", cpf);
    while (aux != NULL) {
        if (aux->cpf == cpf) {
            printf("---------------------------\n");
            printf("Data: %.2d / %.2d / %.4d\n", aux->data.dia, aux->data.mes, aux->data.ano);
            printf("---------------------------\n");
        }
        aux = aux->prox;
    }
}

Ticket *getLastNode(Ticket* head) {
    Ticket *aux = head;

    while (aux != NULL && aux->prox != NULL) {
        aux = aux->prox;
    }

    return aux;
}

Ticket* particao(Ticket* head, Ticket* tail, Ticket** newHead, Ticket** newTail) {
    Ticket* pivor = tail;
    Ticket* anterior = NULL;
    Ticket* aux = head;
    Ticket* tailNode = pivor;

    while (aux != pivor) {
        if (diasTotais(aux) < diasTotais(pivor)){
            if (*newHead == NULL) {
                *newHead = aux;
            }

            anterior = aux;
            aux = aux->prox;
        } else {
            if (anterior) {
                anterior->prox = aux->prox;
            }

            Ticket* temp = aux->prox;
            aux->prox = NULL;
            tailNode->prox = aux;
            tailNode = aux;
            aux = temp;
        }
    }

    if (*newHead == NULL) {
        *newHead = pivor;
    }

    *newTail = tailNode;

    return pivor;
}

Ticket *quickSort(Ticket* head, Ticket* tail) {
    if (head == NULL || head == tail) {
        return head;
    }

    Ticket* newHead = NULL;
    Ticket* newTail = NULL;
    Ticket* pivor = particao(head, tail, &newHead, &newTail);

    if (newHead != pivor) {
        Ticket* temp = newHead;

        while (temp->prox != pivor) {
            temp = temp->prox;
        }

        temp->prox = NULL;
        newHead = quickSort(newHead, temp);
        temp = getLastNode(newHead);
        temp->prox = pivor;
    }

    pivor->prox = quickSort(pivor->prox, newTail);

    return newHead;
}

void ordenaQuick(list *lst) {
    if ((lst == NULL) || (lst->tam == 0)){
        printf("\n\nLista vazia!\n");
        return;
    } 
    lst->inicio = quickSort(lst->inicio, lst->fim);

    Ticket *aux = lst->fim;

    while (aux != NULL){
      lst->fim = aux;
      aux = aux->prox;
    }
    printf("\nLista ordenada com Quick Sort!\n\n");
}

int length(Ticket *cabeca) {
  Ticket *aux = cabeca;
  int cont = 0;
  while (aux != NULL) {
    aux = aux->prox;
    cont++;
  }
  return cont;
}

Ticket *pos(Ticket *head, int p) {
  Ticket *aux = head;
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

void contarIngressos (list *lst) {
    if (lst->inicio == NULL){
      printf("\nLista vazia!\n\n");
      return;
    }

    int size = length(lst->inicio);
    int cont = 0;
    int qtd = 1;
    int repetido = 0;
    Ticket *cel_atual = lst->inicio;
    while (cont < size) {
        Ticket *min_node = cel_atual; 
        Ticket *next_node = cel_atual->prox;
        while (next_node != NULL) {
            if (diasTotais(next_node) == diasTotais(min_node)) { 
                qtd++;
            }
            next_node = next_node->prox;
        }

        printf("\n%.2d/%.2d/%.4d\t|\t", min_node->data.dia, min_node->data.mes, min_node->data.ano);
        printf("Quantidade: %d", qtd);


        cel_atual = pos(lst->inicio ,cont + 1);
        cont++;
        qtd = 1;
    }

}

void menu (){
    printf("MENU\n");
    printf("1. Cadastrar ingresso\n");
    printf("2. Imprimir ingressos\n");
    printf("3. Buscar ingressos e ordenar lista por CPF (Insertion Sort)\n");
    printf("4. Ingressos vendidos por data e ordenar lista por data (Quick Sort) \n\n");
    printf("Informe a opcao: ");
}

int main (void){

    int opc = 0;

    do{
        menu();
        scanf("%d", &opc);

        switch (opc){
        case 1:
            armazenar_ingresso(lista);
            break;
        case 2:
            imprimir(lista);
            break;
        case 3:
            buscar(lista);
            insertionSort(lista);
            break;
        case 4:
            contarIngressos(lista);
            ordenaQuick(lista);
            break;
        default:
            printf("\n\nOpcao invalida!\n\n");
            break;
        }
    } while (opc != 0);
    
    return 0;
}