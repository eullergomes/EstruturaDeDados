#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Implemente um programa que gere e preencha
randomicamente um array com 15, 127 e 32.767
registros e teste o número médio de comparações
*/

//preenche com valores ordenados
void preencherArray(int *vet, int tam){
    int contador = 0;

    for (int i = 0; i < tam; i++){
        vet[i] = contador;
        contador++;
    }
}

void embaralhar (int *vet, int tam){
    srand(time(NULL)); //semente

    //percorre do fim ao inicio
    for (int i = tam - 1; i > 0; i--){
        int j = rand() % (i + 1); //entre 0 e i

        int temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }
}

void imprimir(int *vet, int tam){
    for (int i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
}

int sorteioBusca (int *vet, int tam){
    int num_sorteado = 0;
    int total_buscas = 0;
    
    //num de vezes que realizará o sorteio
    int n = rand() % 1000 + 1; // 0-1000

    //realiza o sorteio n vezes
    for (int i = 0; i < n; i++){
        num_sorteado = rand() % (tam + 1);

        for (int j = 0; j < tam; j++){
            if (vet[j] == num_sorteado){
                total_buscas += j + 1;
            }
        }
    }
    return (float) total_buscas / n;

}

int main(void){
    srand(time(NULL));

    int vet1[15] = {};
    int vet2[127] = {};
    int vet3[32767] = {};

    preencherArray(vet1, 15);
    preencherArray(vet2, 127);
    preencherArray(vet3, 32767);

    embaralhar(vet1, 15);
    embaralhar(vet2, 127);
    embaralhar(vet3, 32767);

    printf("ARRAY - 1\n");
    imprimir(vet1, 15);

    printf("\n\nARRAY - 2\n");
    imprimir(vet2, 127);

    printf("\n\nARRAY - 3\n");
    imprimir(vet2, 127);
    printf("... 32767\n");

    printf("\nMEDIA DE BUSCAS");
    printf("\nMedia vetor 1: %d\n", sorteioBusca(vet1, 15));
    printf("\nMedia vetor 2: %d\n", sorteioBusca(vet2, 127));
    printf("\nMedia vetor 3: %d\n", sorteioBusca(vet3, 32767));

    return 0;
}