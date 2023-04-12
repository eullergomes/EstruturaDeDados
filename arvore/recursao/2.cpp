#include <stdio.h>
#include <stdlib.h>

//Problema: calcular o fatorial de um número N digitado pelo usuário

int fatorial (int n){ // 4! = 4 * 3 * 2 * 1 = 24
    if (n == 0 || n == 1){ // condição de parada 1
        return 1;
    } else {
        return n * fatorial (n - 1);
    }
}

int main(void){
    int n = 0;

    printf("Digite um número: ");
    scanf("%d", &n);

    printf("\n%d! = %d", n, fatorial(n));

    return 0;
}


//Escreva uma função recursiva que calcule a soma dos primeiros N números inteiros positivos.

//Escreva uma função recursiva que determine se um número inteiro é primo.