#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Calcule o número médio de comparações necessário
para localizar uma chave em um array com 15, 127 e
32.767 registros, utilizando tanto pesquisa sequencial
quanto pesquisa binária
*/

//preenche com valores ordenados
void preencherArray(int *vet, int tam){
    int contador = 0;

    for (int i = 0; i < tam; i++){
        vet[i] = contador;
        contador++;
    }
}

void imprimir(int *vet, int tam){
    for (int i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
}

int buscaSequencial(int vet[], int chave, int tam){
    int contador = 0;

    for (int i = 0; i < tam; i++){
        contador++;
        if (vet[i] == chave){
            return contador; // valor encontrado
        }
    }
    return -1; // elemento não encontado
}

int buscaBinaria(int vet[], int item, int tam){
    int inicio = 0;  
    int fim = tam;
    int contador = 0;

    while (inicio <= fim){ 
        contador++;

        int i = (inicio + fim) / 2;

        if (vet[i] == item){ 
            return contador;
        }

        if (vet[i] < item){ 
            inicio = i + 1;
        }
        else { // vector[i] > item
            fim = i;
        }
    }

    return -1;
}

int main(void){
    srand(time(NULL));

    int vet1[15] = {};
    int vet2[127] = {};
    int vet3[32767] = {};

    preencherArray(vet1, 15);
    preencherArray(vet2, 127);
    preencherArray(vet3, 32767);

    printf("ARRAY - 1\n");
    imprimir(vet1, 15);

    printf("\n\nARRAY - 2\n");
    imprimir(vet2, 127);

    printf("\n\nARRAY - 3\n");
    imprimir(vet2, 127);
    printf("... 32767\n");

    printf("\n\nPESQUISA:\n");

    printf("\nBUSCA SEQUENCIAL\nTotal de buscas:\n");
    printf("V1 - %d\n", buscaSequencial(vet1, 6, 15));
    printf("V2 - %d\n", buscaSequencial(vet2, 100, 127));
    printf("V3 - %d", buscaSequencial(vet3, 2000, 32767));

    printf("\n------------------------------------------------------\n");

    printf("BUSCA BINARIA\nTotal de buscas:\n");
    printf("V1 - %d\n", buscaBinaria(vet1, 6, 15));
    printf("V2 - %d\n", buscaBinaria(vet2, 100, 127));
    printf("V3 - %d\n\n", buscaBinaria(vet3, 2000, 32767));

    return 0;
}