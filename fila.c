//=====================================================
// Arquivo: fila.c
//
// Autores: Ana Paula Fernandes de Souza
//          Renata Caroline Cunha
// Data: 31/07/2016
// Disciplina: Programacao II - AED
//=====================================================

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct nodo{
               int valor;
               struct nodo *prox;   
};

struct fila{
               int tam;
               struct nodo *inicio;    
};

Fila criaFila(void)
{
   Fila p=(struct fila*)malloc(sizeof(struct fila));
   
   p->tam=0;
   p->inicio=NULL;
    
   return(p); 
}

void destroiFila(Fila s)
{   
    //retirando todos os elementos da fila.
    int i;
    if(vaziaFila(s)==0)
    {
       for(i=1;i<=s->tam;i++)
       {      
           retiraFila(s);         
       }        
    }

    free(s);
    s=NULL;
    
    return;   
}

void insereFila(Fila s,int x)
{
    if(vaziaFila(s)==1)
    {
        struct nodo *novo=(struct nodo*)malloc(sizeof(struct nodo));
        novo->valor=x; 
        novo->prox=NULL;

        s->inicio=novo;
        s->tam++;
        
       return; 
    } 

    struct nodo *novo=(struct nodo*)malloc(sizeof(struct nodo));
    novo->valor=x;
    novo->prox=NULL;

    int i;
    struct nodo *aux=s->inicio;
      
    for(i=1;i<s->tam;i++)
    {       
       aux=aux->prox;            
    }      

    aux->prox=novo;
    s->tam++;
      
    return;   
}
int retiraFila(Fila s)
{
  int x;
  //Possui apenas um elemento.  
  if(s->tam==1)
  { 
      x=(s->inicio)->valor;
      free(s->inicio);
      s->inicio=NULL;
      s->tam--;

      return(x);    
  }
  //outros casos.
  struct nodo *aux=s->inicio;
  x=aux->valor;
  s->inicio=aux->prox;

  free(aux);
  s->tam--;

  return(x);    
}

int vaziaFila(Fila s)
{
  if(s->tam==0)
  {
     return(1);      
  }

  return(0);          
}

int tamanhoFila(Fila s)
{
   return(s->tam);     
}

int consultaFila(Fila s)
{
   return((s->inicio)->valor);    
}