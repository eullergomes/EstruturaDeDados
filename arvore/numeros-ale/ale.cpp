#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
RAND - gera um numero entre 0 e uma constante (RAND_MAX)
SRAND - semente para a sequencia 
SRAND(TIME(NULL)) - total de seg. desde 01/01/1970
*/

int main(void){
    float aleatorio2 = 0.0f;
    int aleatorio = 0;
    srand(time(NULL)); //semente para os números serem aleatorios

    for (int i = 0; i < 100; i++){
        aleatorio = rand() % 100; // entre 0 e 100 - 1 (0, 99)
        // aleatorio = 10 + rand() % 91; // entre 10 e 100
        printf("%d ", aleatorio);
    }

    printf("\n\n");

    //entre 0 e 1 - ponto flutuante
    //RAND MAX == 1
    for (int i = 1; i < 100; i++){
        aleatorio2 = (float)rand() / RAND_MAX;
        printf("%.1f ",  aleatorio2);
    }
    
    return 0;
}
