#include <stdio.h>
#include <stdlib.h>

void preencher_vetor(int *v, int n){
    printf("Digite %d números inteiros para o vetor:\n");
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }
    printf("\n");
}

void imprimir_vetor(int *v, int n){
    int i;
    printf("Números digitados:\n");
    for(i = 0; i < n; i++){
        printf("%d\n", *(v+i));
    }
}

int main(void){
    
    int n = 0;

    printf("Digite a quantidade de elementos do vetor:\n");
    scanf("%d", &n);

    int *vetor = (int*) malloc(sizeof(int) * n);

    preencher_vetor(vetor, n);
    imprimir_vetor(vetor, n);

    return 0;
}
