#include <stdio.h>
#include <stdlib.h>

//Problema: imprimir todos os números de N até 0


void imprimir (int x){
    if (x == 0) // condição de parada
        printf("%d", x);
    else {
        printf("%d ", x);
        imprimir(x - 1); //pois já imprimi o valor de X e isso se repete até que X == 0
    }
}

int main(void){
    int n = 0;

    printf("Digite um valor positivo: ");
    scanf("%d", &n);

    imprimir(n);

    return 0;
}