#include <stdio.h>
#include <stdlib.h>

void insertionSort (int *v, int n){
    for (int i = 1; i < n; i++){ 
        int aux = v[i]; //elem. a ser feito a troca
        int j = i - 1; //elem. anterior
        while ((j >= 0) && (aux < v[j])){
            v[j+1] = v[j];
            j--;
        }
        if (j != i - 1) { //evitar atribuição desnecessária
           v[j + 1] = aux;
       }
    }   
}
 
void imprimir(int *v, int n){
    for (int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
    
}

int main(void){
    int v[] = {2, 5, 7, 1, 9};
    int n = 5;

    imprimir(v, n);
    printf("\n\n");
    insertionSort(v,n);
    imprimir(v, n);

    return 0;
}