#include <stdio.h>
#include <stdlib.h>

// 2 * nº elem = 30
#define TAM 31

/*
HASH TABLE

tamanho da tabela:
T = 2 * nº de elementos
T = nº primo mais próximo do resultado encontrado

fator de carga:
Fc = nº de elementos / T
OBS. 0 < Fc < 1

função de espalhamento:
chave % T
*/

void inicializarTabela(int t[]){
    for (int i = 0; i < TAM; i++){
        t[i] = 0; //vazio
    }
}

int funcaoHash(int chave){
    return chave % TAM;
}

void inserir(int t[], int valor){
    int id = funcaoHash(valor);

    while (t[id] != 0){
        id = funcaoHash(id + 1);
    }
    t[id] = valor;

    printf("\nnumero inserido com sucesso\n\n");
}

int busca(int t[], int chave){
    int id = funcaoHash(chave);

    while (t[id] != 0){
        if (t[id] == chave){
            return id; //retorna o indice
        } else {
            id = funcaoHash(id + 1);
        }
    }
    return 0;
}

void imprimir(int t[]){
    printf("\nINDICE  /   VALOR\n\n");
    for (int i = 0; i < TAM; i++){
        printf("%d  =   %d\n", i, t[i]);
    }
    printf("\n");
    
}

void menu(){
    printf("MENU\n");
    printf("1. Inserir\n");
    printf("2. Buscar\n");
    printf("3. Imprimir\n");
    printf("0. SAIR\n");
    printf("\nInforme a opcao: ");
}

int main (){
    int tabela[TAM];
    inicializarTabela(tabela);

    int opc = 0, num = 0, retorno = 0;

    do{
        menu();
        scanf("%d", &opc);

        switch (opc){
        case 1:
            printf("\nDigite um numero inteiro: ");
            scanf("%d", &num);
            inserir(tabela, num);
            break;

        case 2:
            printf("\nDigite o valor a ser buscado: ");
            scanf("%d", &num);
            retorno = busca(tabela, num);
            if (retorno == 0)
                printf("\nValor nao encontrado\n\n");
            else
                printf("\nIndice: %d    /   valor: %d\n\n", retorno, num);
            break;

        case 3:
            imprimir(tabela);
            break;
        case 0:
            printf("\nSAINDO...\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente\n\n");
        }

    } while (opc != 0);
    


    return 0;
}

