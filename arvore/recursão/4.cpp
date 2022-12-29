#include <stdio.h>
#include <stdlib.h>

//Problema: implemente uma função recursiva que, dados dois números inteiros X e N, calcula e retorne o valor de x elevado a n.

int eleva (int x, int n){
    if (n == 0) // condição de parada
        return 1;
    else 
        return x * eleva(x, n - 1);
}

int main(void){

    int x = 0, n = 0;

    printf("Digite o valor de X: ");
    scanf("%d", &x);

    printf("\nDigite o valor de Y: ");
    scanf("%d", &n);

    printf("%d elevado a %d = %d", x, n, eleva(x,n));

    return 0;
}