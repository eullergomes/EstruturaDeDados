#include <stdio.h>
#include <stdlib.h>

int main(void){

    int a = 1, b = 2;

    int *ptr_a = &a;
    int *ptr_b = &b;

    printf("Antes:\n");
    printf("A = %d\nB = %d", a, b);

    *ptr_a = 2;
    *ptr_b = 1;

    printf("\n\nDepois:\n");
    printf("A = %d\nB = %d\n\n", a, b);

    printf("Endereço de A = %d\n", &a);
    printf("Endereço de B = %d\n", &b);

    printf("Endereco de ptr_a = %d\n", &ptr_a);
    printf("Endereco de ptr_b = %d\n", &ptr_b);

    printf("Endereco que ptr_a aponta = %d\n", ptr_a);
    printf("Endereco que ptr_b aponta = %d\n", ptr_b);

    return 0;
}