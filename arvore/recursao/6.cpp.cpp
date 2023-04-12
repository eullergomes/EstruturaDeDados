#include <stdio.h>

//Imprimir os números de 0 até N

void imprimir (int n){
    if (n == 0){
        printf("%d ", n);
        return;
    } else {
        imprimir(n - 1);
        printf("%d ", n);
    }
}


int main(void){
    int n = 0;
    printf("Digite um numero: ");
    scanf("%d", &n);

    imprimir(n);

    return 0;
}
