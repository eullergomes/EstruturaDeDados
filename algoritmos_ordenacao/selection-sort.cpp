/*Busca o menor elemento da lista e põe na primeira posição v[0]
Depois o segundo menor elemento da lista e põe na segunda posição v[1]
E assim por diante...
Similar a ordenação de letras do alfabeto por crianças,
onde elas começam pelo menor elemento A, depois o segundo menor B e assim por diante
*/

#include <stdio.h>
#include <stdlib.h>

void findMin (int *v, int n){
    int min_index = 0; //indice menor valor

    for (int i = 0; i < n; i++) { //percorre o vetor
        if (v[i] < v[min_index]){
            min_index = i;
        }
    }

    printf("MINIMO\nvalor = %d\nposicao = %d", v[min_index], min_index);
    
}

void imprimir (int *v, int n){
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
}

void selectionSort (int *v, int n){
    for (int i = 0; i < n - 1; i++){
        int min_index = i;
        for (int j = i + 1; j < n; j++){
            if (v[j] < v[min_index]){ //encontra o menor elemento
                min_index = j; //posicao do menor elemento
            }
        }
        int temp = v[min_index];
        v[min_index] = v[i];
        v[i] = temp;
    }
}



int main(void){
    int v[5] = {7, 5, 1, 8, 3};

    findMin(v, 5);

    printf("\n\nANTES:\n");
    imprimir(v, 5);

    printf("\n\nDEPOIS:\n");
    selectionSort(v, 5);
    imprimir(v, 5);

    return 0;
}