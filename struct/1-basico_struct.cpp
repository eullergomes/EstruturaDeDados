#include <stdio.h>
#include <stdlib.h>

//Criando uma estrutura com o nome FICHA_ALUNO
typedef struct {
    char nome[40];
    int numero;
    float nota;
}ficha_aluno;

int main (void){
    //variavel aluno1 do tipo ficha_aluno
    ficha_aluno aluno1;

    printf("\n-----------Cadastro do aluno 1-----------\n\n");

    printf("Nome do aluno: ");
    scanf("%40[^\n]s", aluno1.nome);

    printf("Digite o numero do aluno: ");
    scanf("%d", &aluno1.numero);

    printf("Informe a nota do aluno: ");
    scanf("%f", &aluno1.nota);

    printf("\n\n-----------Imprimindo os dados da struct-------------\n\n");
    printf("Nome: %s\n", aluno1.nome);
    printf("Numero: %d\n", aluno1.numero);
    printf("Nota: %.2f\n", aluno1.nota);

    return 0;
}