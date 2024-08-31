#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int dia, mes, ano;
}data;

int main(int argc, char const *argv[]){
    
    int total;
    printf("Digite a quantidade de datas a serem registradas:\n");
    scanf("%d", &total);

    data *datas = (data*) malloc(sizeof(data) * total);

    for(int i = 0; i < total; i++){
        printf("\nDIA %d\n\n", i + 1);

        printf("Dia: ");
        scanf("%d", &datas[i].dia);
        printf("Mês: ");
        scanf("%d", &datas[i].mes);
        printf("Ano: ");
        scanf("%d", &datas[i].ano);
    }

    printf("\nDatas registradas:\n");
    for (int i = 0; i < total; i++){
        printf("%d: %02d/%02d/%04d\n", i + 1, datas[i].dia, datas[i].mes, datas[i].ano);
    }

    return 0;
}
