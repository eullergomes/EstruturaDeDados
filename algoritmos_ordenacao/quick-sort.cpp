#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencher(int *vet, int tam){
    for (int i = 0; i < tam; i++){
        vet[i] = i;
    }
}

void imprimir(int *vet, int tam){
    for (int i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
}

void embaralhar (int *vet, int tam){
    srand(time(NULL)); //semente

    //percorre do fim ao inicio
    for (int i = tam - 1; i > 0; i--){
        int j = rand() % (i + 1); //entre 0 e i

        int temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }
}

// função que realiza a troca entre dois elementos
void troca(int vet[], int i, int j){
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}

// particiona e retorna o índice do pivô
int particiona(int vet[], int inicio, int fim){
	int pivo, pivo_indice, i;
	
	pivo = vet[fim]; // o pivô é sempre o último elemento
	pivo_indice = inicio;
	
	for(i = inicio; i < fim; i++)
	{
		// verifica se o elemento é <= ao pivô
		if(vet[i] <= pivo)
		{
			// realiza a troca
			troca(vet, i, pivo_indice);
			// incrementa o pivo_indice
			pivo_indice++;
		}
	}
	
	// troca o pivô
	troca(vet, pivo_indice, fim);
	
	// retorna o índice do pivô
	return pivo_indice;
}

// escolhe um pivô aleatório para evitar o pior caso do quicksort
int particiona_random(int *vet, int inicio, int fim){
	// seleciona um número entre fim (inclusive) e inicio (inclusive)
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	// faz a troca para colocar o pivô no fim
	troca(vet, pivo_indice, fim);
	// chama a particiona
	return particiona(vet, inicio, fim);
}

void quick_sort(int *vet, int inicio, int fim){
	if(inicio < fim) {
		// função particionar retorna o índice do pivô
		int pivo_indice = particiona_random(vet, inicio, fim);
		
		// chamadas recursivas quick_sort
		quick_sort(vet, inicio, pivo_indice - 1);
		quick_sort(vet, pivo_indice + 1, fim);
	}
}

int main (void){
    int vetor[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int n = 10;

    printf("ANTES:\n");
    imprimir(vetor, n);

    embaralhar(vetor, n);
    printf("\nDEPOIS:\n");
    quick_sort(vetor, 0, 10);
    imprimir(vetor, n);

    return 0;
}