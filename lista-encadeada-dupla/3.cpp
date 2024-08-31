#include <stdio.h>
#include <stdlib.h>

typedef struct no{

    // NULL <- 3 -><- 4 -><- 5 -> NULL
    int valor;
    struct no *proximo;
    struct no *anterior;
}No;

void ler_valor(No *no){

    printf("\nInforme um Valor: ");
    scanf("%d", &no->valor);
}

void imprimir_valor(int valor){

    printf(" <- %d -> ", valor);
}

// Função para Inserir no Inicio.
void inserir_no_inicio(No **lista){

    //No *novo = (No*)malloc(sizeof(No));
    No *novo = new No;

    ler_valor(novo);

    // NULL <- 5 -> NULL
    novo->proximo = *lista;
    novo->anterior = NULL;

    // NULL <- 2 -><- 5 -> NULL
    if(*lista != NULL){

        (*lista)->anterior = novo;
    }

    *lista = novo;
}

// Função para Inserir no Fim.
void inserir_no_fim(No **lista){

    No *aux, *novo = (No*) malloc(sizeof(No));

    ler_valor(novo);

    novo->proximo = NULL;

    // Verificando se não há Ninguem na Lista.
    //  NULL <- 5 -> NULL
    if(*lista == NULL){

        *lista = novo;
        novo->anterior = NULL;
    }
    else{

        aux = *lista;

        // 4 5 5 -> NULL
        while(aux->proximo != NULL){

            aux = aux->proximo;
        }
        // aux 5
        // novo 2
        // NULL <- 4 -><- 5 -><- 2 -> NULL
        aux->proximo = novo;
        novo->anterior = aux;
    }
}

// Função para Inserir no Meio.
void inserir_no_meio(No **lista, int ant){

    No *aux, *novo = (No*)malloc(sizeof(No));

    ler_valor(novo);

    // Verificando se a Lista esta Vazia.
    if(*lista == NULL){

        //  NULL <- 5 -> NULL
        novo->proximo = NULL;
        novo->anterior = NULL;

        *lista = novo;
    }
    else{

        aux = *lista;
        // ant 6
        // aux 6
        // 2, 5, 6, 8, NULL
        while(aux->valor != ant && aux->proximo != NULL){

            aux = aux->proximo;
        }

        // novo 7
        // aux 6
        // 2, 5, 6, 8 NULL
        // Nova Lista: 2 -><- 5 -><- 6 -><- 7 -><- 8
        novo->proximo = aux->proximo;

        if(aux->proximo != NULL){

            aux->proximo->anterior = novo;
        }

        novo->anterior = aux;
        aux->proximo = novo;
    }
}

// Função para Remover um No.
No* remover_no(No **lista, int valor){

    No *aux, *remover = NULL;

    if(*lista != NULL){

        // valor 4
        // 4, 5, 8, 9, NULL
        if((*lista)->valor == valor){

            // remover 4
            // 4, 5, 8, 9, NULL
            // nova Lista: 5, 8, 9, NULL
            remover = *lista;
            *lista = remover->proximo;

            // nova Lista: NULL, 5, 8, 9, NULL
            if(*lista != NULL){

                (*lista)->anterior = NULL;
            }
        }
        else{

            aux = *lista;

            // valor 8
            // 4, 5, 8, 9, NULL
            // aux 9
            while(aux->proximo != NULL && aux->proximo->valor != valor){

                aux = aux->proximo;
            }

            // valor 8
            // 4, 5, 8, 9, NULL
            // aux 5
            if(aux->proximo != NULL){

                // remover 8
                // NULL, 4 -><- 5 -><- 9, NULL
                remover = aux->proximo;
                aux->proximo = remover->proximo;

                if(aux->proximo != NULL){

                    aux->proximo->anterior = aux;
                }
            }
        }
    }
}

// Função para Imprimir a Lista.
void imprimir_lista(No *lista){

    printf("\n\t--------------------------------------------------------\n\t");

    printf("NULL");

    while(lista != NULL){

        imprimir_valor(lista->valor);

        lista = lista->proximo;
    }

    printf("NULL");

    printf("\n\t--------------------------------------------------------\n");
}

// Função que Encontra o Ultimo Nó.
No* ultimo_no(No **lista){

    No *aux = *lista;

    while(aux->proximo != NULL){

        aux = aux->proximo;
    }

    // aux 6
    // 2, 3, 6, NULL
    return aux;
}

// Função para Imprimir a Lista Inversamente.
void imprimir_lista_inversa(No *lista){

    printf("\n\t--------------------------------------------------------\n\t");

    printf("NULL");

    while(lista != NULL){

        imprimir_valor(lista->valor);

        // NULL 2, 3, 6, NULL
        lista = lista->anterior;
    }

    printf("NULL");

    printf("\n\t--------------------------------------------------------\n");
}

int main(){

    No *remover, *lista = NULL;
    int opcao, ant;

    do{
        printf("\n\t1 - Inseir no Inicio\n\t2 - Inseir no Fim\n\t3 - Inseir no Meio\n\t4 - Imprimir\n\t5 - Imprimir Inversa\n\t6 - Remover\n\t0 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:

            inserir_no_inicio(&lista);

            break;
        case 2:

            inserir_no_fim(&lista);

            break;
        case 3:

            if(lista != NULL){

                printf("\nInforme o Anterior: ");
                scanf("%d", &ant);

                inserir_no_meio(&lista, ant);
            }
            else{

                printf("\n\tLISTA VAZIA!\n");
            }

            break;
        case 4:

            if(lista != NULL){

                imprimir_lista(lista);
            }
            else{

                printf("\n\tLISTA VAZIA!\n");
            }

            break;
        case 5:

            if(lista != NULL){

                imprimir_lista_inversa(ultimo_no(&lista));
            }
            else{

                printf("\n\tLISTA VAZIA!\n");
            }

            break;
        case 6:

            if(lista != NULL){

                printf("\nInforme o Valor a Remover: ");
                scanf("%d", &ant);

                remover = remover_no(&lista, ant);
            }
            else{

                printf("\n\tLISTA VAZIA!\n");
            }

            break;
        default:

            if(opcao != 0){

                printf("\n\tOpcao Invalida!\n");
            }
        }

    }while(opcao != 0);

    return 0;
}