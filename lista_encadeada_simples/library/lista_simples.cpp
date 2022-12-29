#include "funcoes.h"

void menu(){
    printf("\tMENU\n");
    printf("\t1 - Inserir no inicio\n");
    printf("\t2 - Inserir no fim\n");
    printf("\t3 - Imprimir lista\n");
    printf("\t4 - Remover elemento\n");
    printf("\t5 - Tamanho da lista\n");
    printf("\t6 - Trocar elemento com seu próximo\n");
    printf("\t7 - Buscar elemento\n");
    printf("\t0 - Sair\n\n");
    printf("\tInforme a opção: ");
}

int main(void){
    //duas listas
    celula *cabeca1 = NULL;
    celula *cabeca2 = reverter(cabeca1);

    int opc = 0, valor = 0, tam = 0, troca = 0;

    do{
        menu();
        scanf("%d", &opc);
        system("cls");
        switch (opc){
        case 1:
            printf("\tDigite um número: ");
            scanf("%d", &valor);
            inserir_inicio(&cabeca1, valor);
            printf("\n\tInserido com sucesso!\n\n");
            break;
        case 2: 
            printf("\tDigite um número: ");
            scanf("%d", &valor);
            inserir_fim(&cabeca1, valor);
            printf("\n\tInserido com sucesso!\n\n");
            break;
        case 3:
            imprimir(cabeca1);
            break;
        case 4:
            printf("\tDigite o elemento que deseja remover: ");
            scanf("%d", &valor);
            remover(&cabeca1, valor);
            printf("\n\tNúmero removido\n\n");
            break;
        case 5:
            tam = tamanho(cabeca1);
            printf("\n\tTamanho: %d\n\n", tam);
            break;
        case 6:
            printf("\tDigite o elemento para troca: ");
            scanf("%d", &troca);
            cabeca1 = troca_prox(cabeca1, troca);
            imprimir(cabeca1);
            break;
        case 7:
            
            break;
        case 0:
            printf("\n\tFinalizando...\n\n");
            exit(0);
            break;
        default:
            printf("\n\tOpção inválida!\n\n");
            break;
        }
        system("pause");
        system("cls");
    } while (opc != 0);  

    return 0;
}


  // CONCATENAR DUAS LISTAS (a segunda lista se junta na primeira) 
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