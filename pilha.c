//=====================================================
// Arquivo: pilha.c
//
// Autores: Ana Paula Fernandes de Souza
//          Renata Caroline Cunha
// Data: 31/07/2016
// Disciplina: Programacao II - AED
//=====================================================
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

 struct nodo
 {
 	 int valor;
 	 struct nodo *prox;
 };

struct pilha
{
	 int tam;
	 struct nodo *inicio;
};

Pilha criaPilha(void)
{
	 Pilha p=(struct pilha*)malloc(sizeof(struct pilha));

	 p->tam=0;
	 p->inicio=NULL;

	 return(p);
}

void destroiPilha(Pilha p)
{
     int i;
     if(vaziaPilha(p)==0)
     {
       //Retirando todos os elementos da pilha.  
       for(i=1;i<=p->tam;i++)
       {
          retiraPilha(p);            
       }        
     }

     free(p);
     p=NULL;

     return;
}

void inserePilha(Pilha p,int x)
{
     if (vaziaPilha(p)==1)
     {		
        struct nodo *novo=(struct nodo*)malloc(sizeof(struct nodo));

        novo->valor=x;
        novo->prox=NULL;

        p->inicio=novo;
        p->tam++;

	    return;
     } 
     //outros casos
     struct nodo *novo=(struct nodo*)malloc(sizeof(struct nodo));

     novo->valor=x;
     novo->prox=p->inicio;
     
     p->inicio=novo;
     p->tam++;

     return;
}

int retiraPilha(Pilha p)
{
    int retornaValor;

    //Se a pilha tiver apenas um elemento
	if(p->tam==1) 
	{
		 retornaValor=(p->inicio)->valor;
		 free(p->inicio);

		 p->inicio=NULL;
		 p->tam--;

		 return(retornaValor);
	}
    //outros casos
    retornaValor=(p->inicio)->valor;
    
    struct nodo *aux=p->inicio;    
    p->inicio=aux->prox;
    
    free(aux);
    aux=NULL;
    p->tam--;
    
    return(retornaValor);  
}

int vaziaPilha(Pilha p) 
{
    if(p->tam==0)
    {
	 return(1);
    }
    
    return(0);
}

int tamanhoPilha(Pilha p)
{
    return(p->tam);	
}

int consultaPilha(Pilha p)
{
    return((p->inicio)->valor);
}