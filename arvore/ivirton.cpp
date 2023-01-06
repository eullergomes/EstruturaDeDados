#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<strings.h>
float preco_Brasil_Argentiva = 3121;
float preco_Argentina_Brasil = 2869;

typedef struct pass{
    int localizador;
    int dia,mes,ano;
    char destino[20];
    float preco;
    pass *esquerda, *direita;
}Passagem;

typedef struct anos{
    int ano;
    pass *passagem;
    anos *esquerda,*direita;
}Anos;

Passagem *raizArgentina;
Passagem *raizBrasil;
Anos *anosAnteriores;
pass *terceira;

int anoAtual = 2022;

void  imprimir(pass *raiz, int tab = 0) {
    if (raiz == NULL) return;
    imprimir(raiz->direita, tab + 1);
    for (int i = 0; i < tab; i++) printf("\t");
   
    printf("[%d R$:%1.2f %s %d/%d/%d]\n", raiz->localizador,raiz->preco,raiz->destino,raiz->dia,raiz->mes,raiz->ano);
    imprimir(raiz->esquerda, tab + 1);
}
void  imprimirReduzido(pass *raiz){
if (raiz == NULL) return;
    imprimirReduzido(raiz->direita);
    printf("[%d R$:%1.2f %s %d/%d/%d]\n", raiz->localizador,raiz->preco,raiz->destino,raiz->dia,raiz->mes,raiz->ano);
    imprimirReduzido(raiz->esquerda);         
}
void  limparTerminal(){
    system("cls");
    //system("cleaner");
}
int   menu(){
    printf("\n1 - Vender Passagem");
    printf("\n2 - Imprimir Arvores");
    printf("\n3 - Buscar por Destino");
    printf("\n4 - Relatorio de voos e valor arrecadado");
    printf("\n5 - Combinar Arvores");
    printf("\n6 - Anos Anteriores:");
    printf("\n0 - Sair");
    printf("\n>");
    int op = 0;
    scanf("%d",&op);
    return op;
}
float precoTotal(pass *raiz) {
    if(raiz == NULL)return 0;    
    else return raiz->preco + precoTotal(raiz->esquerda) + precoTotal(raiz->direita);
}
int tamanho(pass *raiz) {
    if(raiz == NULL) return 0; 
    else return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);