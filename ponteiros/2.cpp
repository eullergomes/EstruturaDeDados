#include <stdio.h>
#include <stdlib.h>

//Função que troca os valores de duas variáveis

void troca (int *ptr_a, int *ptr_b){
    int temp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = temp;
}

int main(void){
    int a = 0, b = 0;

    printf("Digite dois números:\n");
    scanf("%d %d", &a, &b);

    printf("Antes:\n");
    printf("A = %d\nB = %d\n", a, b);

    troca(&a, &b);

    printf("Depois:\n");
    printf("A = %d\nB = %d\n", a, b);

    return 0;
}
