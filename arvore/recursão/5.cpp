#include <stdio.h>
#include <stdlib.h>

//Problema: desenvolva uma função recursiva que calcule a soma dos números inteiros de 1 a N

int soma(int n){
    if (n == 0)
        return 0;
    else 
        return n + soma(n - 1);
}

int main(void){
    int n = 0;

    printf("Digite um número: ");
    scanf("%d", &n);

    printf("Soma de de 1 até %d = %d", n, soma(n));
    
    return 0;
}