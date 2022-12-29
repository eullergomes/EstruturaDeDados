#include <stdio.h>
#include <stdlib.h>

//Problema: fazer uma função que calcula o enésimo termo da sequência de fibonacci

/*
posição:     1 2 3 4 5 6
sequencia:   0 1 1 2 3 5
*/

int fibonacci(int n){ //6
    if (n == 1) // condição de parada
        return 0;
    else {
        if (n == 2)
            return 1;
        else 
            return fibonacci(n - 1) + fibonacci(n - 2); 
    }
}

int main (void){
    int n = 0;

    printf("Digite um número: ");
    scanf("%d", &n);

    printf("Posição: %d\nSequência: %d", n, fibonacci(n));

    return 0;
}