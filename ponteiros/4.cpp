#include <stdio.h>
#include <stdlib.h>

void preencher_notas(float *v, int n){
    for(int i = 0; i < n; i++){
        printf("Digite a nota do aluno %d: \n", i + 1);
        scanf("%f", &v[i]);
    }
}

float calcular_media(float *v, int n){
    float total = 0.0f;
    for(int i = 0; i < n; i++){
        total += v[i];
    }
    return (total/n);
}

int main(void){
    
    int qtd = 0;

    printf("Digite a quantidade de alunos da turma:\n");
    scanf("%d", &qtd);

    float *notas = (float*) malloc(sizeof(float) * qtd);

    preencher_notas(notas, qtd);

    float media = calcular_media(notas, qtd);

    printf("Média da turma = %.2f", media);

    free(notas);
    

    return 0;
}
