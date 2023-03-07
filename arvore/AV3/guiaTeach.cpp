#include <stdio.h> 
#include <stdlib.h> 
 
typedef struct NO { 
	int info; 
	struct NO *esquerda, *direita; 
} node, *arvore; 
 
arvore root = NULL;
 
arvore pesquisar(arvore, int); 
int proxmaior(int); 
void inserir(arvore *, int); 
void imprimir(arvore, int); 
void range(arvore, int, int); 
int excluir_menor(void); 
void excluir(arvore *, int); 
void del(arvore *, arvore *); 
 
void percorre_preordem(node *); 
void percorre_posordem(node *); 
void percorre_emordem(node *); 
int maior(node * ); 
int menor(node * ); 
 
int main(void) 
{ 
	int x, y, opcao; 
 
	do
	{ 
		printf("\nEntre com a opcao:"); 
		printf("\n ---1:inserir"); 
		printf("\n ---2:pesquisar"); 
		printf("\n ---3:excluir o menor"); 
		printf("\n ---4:excluir"); 
		printf("\n ---5:procurar o maior que"); 
		printf("\n ---6:imprimir a arvore"); 
		printf("\n ---7:mostrar nos do intervalo"); 
		printf("\n ---8:percorrer"); 
		printf("\n ---9:maior e menor"); 
		printf("\n ---10:sair do programa\n"); 
		printf("\n-> "); 
		fflush(stdin); 
		scanf("%d", &opcao); 
		switch(opcao) 
		{
			case 1: 
			{
				printf("\n Informe o valor ->"); 
				scanf("%d", &x); 
				inserir(&root, x); 
				imprimir(root, 0); 
				break; 
			} 
			case 2: 
			{ 
				printf("\n Informe o valor ->"); 
				scanf("%d", &x); 
				if(pesquisar(root, x) != NULL) 
				{ 
					printf(" Encontrado\n"); 
				} 
				else 
				{ 
					printf(" Nao encontrado!\n"); 
				}
				break; 
			} 
			case 3:
			{ 
				printf(" Excluido o menor = %d\n", excluir_menor()); 
				imprimir(root, 0); 
				break; 
			} 
			case 4: 
			{ 
				printf("\n Informe o valor ->"); 
				scanf("%d", &x); 
				excluir(&root, x); 
				imprimir(root, 0); 
				break; 
			} 
			case 5: 
			{ 
				printf("\n Informe o valor ->"); 
				scanf("%d", &x); 
				imprimir(root, 0); 
				printf("\n --- proximo maior que = %d", proxmaior(x)); 
				break; 
			} 
			case 6: 
			{ 
				imprimir(root, 0); 
				break; 
			}
			case 7: 
			{ 
				printf("\n Informe [min, max]"); 
				scanf("%d %d",&x, &y); 
				range(root, x, y); 
				break; 
			} 
			case 8: 
			{ 
				printf("\nPercorrendo em ordem ->"); 
				percorre_emordem(root); 
				printf("\nPercorrendo em pre ordem ->"); 
				percorre_preordem(root); 
				printf("\nPercorrendo em pos ordem ->"); 
				percorre_posordem(root); 
				break; 
			} 
			case 9: 
			{ 
				printf("\nMaior = %d", maior(root)); 
				printf("\nMenor = %d", menor(root)); 
				break; 
			} 
		} 
	} while(opcao!=10); 
}
 
arvore pesquisar(arvore v, int chave) 
{ 
	if( v == NULL) 
	{ 
		return NULL; 
	} 
	if(v->info == chave) 
	{ 
		return v; 
	} 
	else if(v->info < chave) 
	{ 
		return pesquisar(v->direita, chave); 
	} 
	else
	{ 
		return pesquisar(v->esquerda, chave); 
	} 
} 
 
/* maior no próximo elemento informado */ 
int proxmaior(int chave) 
{ 
	arvore p=NULL, v; 
 
	v = root; 
	while( v != NULL && v->info != chave) 
	{ 
		if(v->info < chave) 
		{ 
			v = v->direita; 
		} 
		else
		{ 
			p = v; 
			v = v->esquerda; 
		} 
	} 
	if(v == NULL) 
	{ 
		printf("\n Elemento nao encontrado"); 
		return -1; 
	} 
	if( v->direita != NULL ) 
	{ 
		v = v->direita; 
		while(v->esquerda != NULL) 
		{ 
			v = v->esquerda; 
		} 
		return v->info; 
	} 
	if(p != NULL) 
	{ 
		return p->info; 
	} 
	else 
	{ 
		return -1; 
	} 
} 
 
void inserir(arvore *p, int chave) 
{ 
	if( *p == NULL ) 
	{ 
		*p = (arvore) malloc(sizeof(node)); 
		(*p)->info = chave; 
		(*p)->esquerda = NULL; 
		(*p)->direita = NULL; 
	} 
	else if((*p)->info < chave) 
	{ 
		inserir(&((*p)->direita), chave); 
	} 
	else 
	{ 
		inserir(&((*p)->esquerda), chave); 
	} 
	return; 
}
 
void imprimir(arvore v, int nivel) 
{ 
	int i; 
 
	if( v != NULL ) 
	{ 
		imprimir(v->esquerda, nivel+1); 
		for(i=0; i<nivel; i++) 
		{ 
			printf(" "); 
		} 
		printf("%d\n", v->info); 
		imprimir(v->direita, nivel+1); 
	} 
	return; 
}
 
/* mostra os nós de um intervalo informado */ 
void range(arvore v, int x, int y) 
{ 
	if( v == NULL ) 
	{ 
		return; 
	} 
	if(v->info >= x) 
	{ 
		range(v->esquerda, x,y); 
	} 
	if(x <= v->info && v->info <= y) 
	{ 
		printf(" %d", v->info); 
	} 
	if(v->info <= y) 
	{ 
		range(v->direita, x,y); 
	} 
	return; 
}
 
/* excluir o menor */ 
int excluir_menor(void) 
{ 
	int menor; 
	arvore p, v; 
	if(root->esquerda == NULL) 
	{ 
		menor = root->info; 
		root = root->direita; 
	} 
	else
	{ 
		v = root; 
	do 
	{ 
		p = v; 
		v = v->esquerda; 
		} while(v->esquerda != NULL); 
		menor = v->info; 
		p->esquerda = v->direita; 
	} 
	return menor; 
}
 
/* exclusão de elemento da árvore */
void excluir(arvore *p, int chave) 
{ 
	arvore q; 
 
	if(*p == NULL) 
	{ 
		printf("\n Elemento nao existe!"); 
	} 
	else if( chave < (*p)->info ) 
	{ 
		excluir(&((*p)->esquerda), chave); 
	} 
	else if( chave > (*p)->info ) 
	{ 
		excluir(&((*p)->direita), chave); 
	} 
	else 
	{ 
		q = *p; 
		if(q->direita == NULL)
		{
			*p = q->esquerda; 
		}
		else if( q->esquerda == NULL) 
		{ 
			*p = q->direita; 
		} 
		else 
		{ 
			del(&q, &(q->esquerda)); 
		} 
		free(q); 
	} 
	return; 
} 
 
/* procura sucessor para depois excluir */ 
void del(arvore *q, arvore *r) 
{ 
	if((*r)->direita != NULL) 
	{ 
		del(q, &((*r)->direita)); 
	} 
	else 
	{ 
		(*q)->info = (*r)->info; 
		(*q) = *r; 
		*r = (*r)->esquerda; 
	} 
	return; 
}
 
/* percorrer uma árvore utilizando o algoritmo de pré-ordem */ 
void percorre_preordem(node * arvore) 
{ 
	if( arvore == NULL ) 
	{ 
		return; 
	} 
 
	printf(" %d", arvore->info); 
	percorre_preordem(arvore->esquerda); 
	percorre_preordem(arvore->direita); 
	
	return; 
}
 
/* percorrer uma árvore utilizando o algoritmo de pós-ordem */
void percorre_posordem(node * arvore) 
{ 
	if( arvore == NULL ) 
	{ 
		return; 
	} 
 
	percorre_posordem(arvore->esquerda); 
	percorre_posordem(arvore->direita); 
	printf(" %d", arvore->info); 
	return; 
}
 
/* percorrer uma árvore utilizando no modo em-ordem */ 
void percorre_emordem(node * arvore) 
{ 
	if( arvore == NULL ) 
	{ 
		return; 
	} 
	
	percorre_emordem(arvore->esquerda); 
	printf(" %d", arvore->info); 
	percorre_emordem(arvore->direita); 
	
	return; 
}
 
/* pesquisa do maior elemento na árvore */ 
int maior(node * arvore ) 
{ 
	int maior; 
	maior = arvore->info; 
 
	while( arvore != NULL ) 
	{ 
		maior = arvore->info; 
		arvore = arvore->direita; 
	} 
	return maior; 
} 
 
/* pesquisa do menor elemento na árvore */ 
int menor(node * arvore) 
{ 
	int menor; 
	menor = arvore->info; 
	
	while( arvore != NULL ) 
	{ 
		menor = arvore->info; 
		arvore = arvore->esquerda; 
	} 
	return menor; 
}