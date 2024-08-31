#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencher (int *vetor, int tam){
    for (int i = 0; i < tam; i++){
        vetor[i] = rand() % 11; //0-10
    }
}

void imprimir (int *vetor, int tam){
    for (int i = 0; i < tam; i++){
        printf("%d ", vetor[i]);
    }
}

void bubbleSort (int *vetor, int tam){
    for (int i = 0; i < tam - 1; i++){
        for (int j = 0; j < tam - i - 1; j++){ //otimização
            if (vetor[j] > vetor[j+1]){
                int aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }
}

int main(void){
    srand(time(NULL));

    int vetor[10000] = {};

    //preencher vetor
    preencher(vetor, 10000);

    //imprimir
    imprimir(vetor, 10000);

    // printf("\n\n");

    int antes = clock();    

    //Ordena
    bubbleSort(vetor, 10000);

    int depois = clock();
    printf("\n\n\n");

    imprimir(vetor, 10000);

    printf("\n\n\n");

    float tempo = ((float) (depois - antes)) / CLOCKS_PER_SEC; //1000
    printf("Tempo de execucao: %lf segundos", tempo);
    printf("\n\n");
    //imprimir
    

    return 0;
}