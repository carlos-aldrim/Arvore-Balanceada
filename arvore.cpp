#include "arvore.h"
#include<stdio.h>
#include <stdlib.h>

void menu(){
	int op;
	float valor;
		
	//--------- iniciando a estrutura --------------------//
	Tno* arvore;
    
    do{    
    //--------------- Exibir menu ---------------------//
        system("cls");
        puts("\n\t\t\t\tARVORE BINARIA BALANCEADA - AVL\n");
        puts("\t1  - INSERIR ELEMENTO\n \t2  - IMPRIMIR ARVORE\n \t0  - SAIR");
        printf("\nINFORME SUA OPCAO:\n");
        scanf("%d", &op);//Escolha da Opção
        
        switch(op)
        {
    		case 1:{
    			printf("Informe um elemento: R$");
    			scanf("%f", &valor);
    			
    			arvore = inserir(arvore, valor);
    			
    			printf("-> PAGAMENTOS: \n");
    			imprime(arvore);
				break;
			}
    		
    		case 2:{
    			printf("-> PAGAMENTOS: \n");
    			imprime(arvore); 
				break;
			}
    			
	    	default:
	    			puts("OPCAO INCORRETA,TENTAR NOVAMENTE.");
					break;
	      
	        }
		getch();
	    }while(op!=0);
}

int altura_AVL(Tno *a){
    int alt_esq=0, alt_dir=0;
    if (a == NULL)
        return 0;
    else{
        alt_esq = altura_AVL(a->esq);
        alt_dir = altura_AVL(a->dir);
        if (alt_esq > alt_dir)
            return (1 + alt_esq);
        else
            return (1 + alt_dir);
    }
}



int calcula_FB(Tno *a){
    return (altura_AVL(a->esq) - altura_AVL(a->dir));
}

Tno* rotacao_simples_esquerda(Tno* a){
  Tno *aux;
  aux = a->dir;
  a->dir = aux->esq;
  aux->esq = a;
  a = aux;
  return a;
}

Tno * rotacao_simples_direita(Tno *a){
  Tno *aux;

  aux = a->esq;
  a->esq = aux->dir;
  aux->dir = a;
  a = aux;
  return a;
}

Tno * balanceio_esquerda(Tno *a){
  int fator = calcula_FB(a->esq);
  if (fator > 0){
    return rotacao_simples_direita(a);
  }
  else if (fator < 0)// Rotação Dupla Direita 
  { 
    a->esq = rotacao_simples_esquerda(a->esq);
    a = rotacao_simples_direita(a); 
	return a;	
  }
  else
  	return a;
}

Tno * balanceio_direita(Tno *a){
  int fator = calcula_FB(a->dir);
  if ( fator< 0 )
  {
    return rotacao_simples_esquerda(a);
  }
  else if (fator > 0 )// Rotação Dupla Esquerda
  { 
    a->dir = rotacao_simples_direita(a->dir);
    a = rotacao_simples_esquerda(a); 
	  return a;
  }
  else
  	return a;
}
Tno* balanceamento(Tno* a){
	int fator = calcula_FB(a);
	if ( fator > 1)
		return balanceio_esquerda(a);
	else if (fator < -1 )
		return balanceio_direita(a);
	return a;
}
Tno* inserir(Tno* a, float elemento){
  if (a == NULL){
    a = (Tno *)malloc(sizeof(Tno));
    a->elemento = elemento;
    a->esq = NULL;
    a->dir = NULL;
    
    return a;
  }
  else 
  	if ( a->elemento > elemento )  {
    	a->esq = inserir(a->esq, elemento);
    	a = balanceamento(a);
	}
    else{
    	a->dir = inserir(a->dir, elemento);
    	a = balanceamento(a);
	}
    
}

void imprime(Tno* a){
    if (a == NULL){
		return;
	}
    else {
    	printf("R$ %.2f", a->elemento);
	 
	    if(a->esq != NULL)
	        printf("(E: R$%.2f)",a->esq->elemento);
	    if(a->dir != NULL)
	        printf("(D: R$%.2f)",a->dir->elemento);
	    printf("\n");
	 
	    imprime(a->esq);
	    imprime(a->dir);
	}
}




