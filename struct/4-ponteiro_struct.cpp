#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

int main(void){
  Data hoje;
  //atribuindo valores para não ter lixo de memoria
  hoje.dia = 0;
  hoje.mes = 0;
  hoje.ano = 0;

  //ponteiro do tipo Data que aponta a variável 'hoje' do tipo Data
  Data *ptr_data = &hoje;

  ptr_data->dia = 10;
  ptr_data->mes = 9;
  ptr_data->ano = 2022;

  printf("Data: %02d/%02d/%04d\n", ptr_data->dia, ptr_data->mes, ptr_data->ano);

  printf("Digite o dia: ");
  scanf("%d", &ptr_data->dia);

  printf("Digite o mês: ");
  scanf("%d", &ptr_data->mes);

  printf("Digite o ano: ");
  scanf("%d", &ptr_data->ano);

  printf("Hoje: %02d/%02d/%04d\n", ptr_data->dia, ptr_data->mes, ptr_data->ano);

  return 0;
}