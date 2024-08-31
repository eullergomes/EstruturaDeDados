#include "./circular.h"

int main(void){

    No *lista_inicio = NULL;
    No *lista_fim = NULL;
    int op, ant, valor, tam = 0;

    do{
        printf("\n\t1 - Inserir no Inicio\n\t2 - Inserir no Fim\n\t3 - Inserir Ordenado\n");
        printf("\t4 - Inserir no Meio\n\t5 - Imprimir\n\t0 - Sair\n");
        printf("\n\tInforme a Opcao: ");
        scanf("%d", &op);

        switch(op){
        case 0:
            printf("\n\tSAINDO...\n\n");
            break;
        case 1:

            ler_valor(&valor);

            inserir_no_inicio(&lista_inicio, &lista_fim, valor, &tam);

            break;
        case 2:

            ler_valor(&valor);

            inserir_no_fim(&lista_inicio, &lista_fim, valor, &tam);

            break;
        case 3:

            ler_valor(&valor);

            inserir_ordenado(&lista_inicio, &lista_fim, valor, &tam);

            break;
        case 4:

            printf("\n\tInforme o Anterior: ");
            scanf("%d", &ant);

            ler_valor(&valor);

            inserir_no_meio(&lista_inicio, &lista_fim, ant, valor, &tam);

            break;
        case 5:

            if(lista_inicio != NULL){

                imprimir_1(lista_inicio, tam);
            }
            else{
                printf("\n\tLISTA VAZIA!\n");
            }

            break;
        default:
            printf("\n\tOpcao Invalida!\n");
            break;
        }

    }while(op != 0);

    return 0;
}