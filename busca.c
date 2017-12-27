//=====================================================
// Arquivo: busca.c
//
// Autores: Ana Paula Fernandes de Souza
//          Renata Caroline Cunha
// Data: 31/07/2016
// Disciplina: Programacao II - AED
//=====================================================

#include <stdio.h>
#include <stdlib.h>
#include "busca.h"
#include "grafo.h"
#include "fila.h"
#include "pilha.h"

void buscaLargura(Grafo g,int partida)
{
    Grafo copia=GGcopiaGrafo(g);

    if(GBexisteIdVertice(copia,partida)==0)
    {
         return;
    }

    Fila aux=criaFila();  

//=================Trabalhando com os vertices=================//    
    int v=GVultimoVertice(copia);       
    int *vetVert=(int*)malloc((v+1)*sizeof(int));
    
    int i;
    for(i=0;i<=v;i++)
    {
        vetVert[i]=0; //Tornando todos os vertices brancos.        
    }

    v=GVprimeiroVertice(copia);

    while(v!=0)
    {        
        printf("Vertice %d branco \n",v);
        v=GVproximoVertice(copia,v); 
    }
    printf("\n");
//=================Trabalhando com as arestas=================// 
    int a=GVultimaAresta(copia);
    
    for(i=1;i<=a;i++)
    {
        if(GBexisteIdAresta(copia,i))
        {
            printf("Aresta %d não visitada\n",i); 
        }    
    }
//===========================================================//   
    v=partida;   
    printf("\nVertice %d cinza \n",v);
    insereFila(aux,v);   

    //Enquanto tiver elementos na fila,existe vertice cinza.
    while(vaziaFila(aux)!=1)
    {
        v=retiraFila(aux);
        printf("\nVertice %d ativado  \n",v);
        a=GAprimaSaida(copia,v); 
        
        while(a!=0)
        {
             printf("Aresta %d visitada \n",a);

             int w=GVvizinho(copia,a,v);
            
             if(vetVert[w]==0)
             {
                 printf("\nVertice %d cinza \n",w);
                 vetVert[w]=1;
                
                 insereFila(aux,w);             
             }             
             a=GAproxSaida(copia,v,a);            
        }
            
         printf("\nVertice %d preto \n",v);
         printf("Vertice %d desativado \n",v);
         vetVert[v]=2;  
    }

    GGdestroiGrafo(copia);
    destroiFila(aux);
    free(vetVert);
    vetVert=NULL;
    
    return;   
}

void buscaProfundidade(Grafo g,int partida)
{
    Grafo copia=GGcopiaGrafo(g);

    if(GBexisteIdVertice(copia,partida)==0)
    {
         return;
    }

    Pilha aux=criaPilha(); 

//=================Trabalhando com os vertices=================//    
    int v=GVultimoVertice(copia);       
    int *vetVert=(int*)malloc((v+1)*sizeof(int));
    
    int i;
    for(i=0;i<=v;i++)
    {
        vetVert[i]=0; //tornando todos os vertices branco.        
    }

    v=GVprimeiroVertice(copia);

    while(v!=0)
    {        
        printf("Vertice %d branco \n",v);
        v=GVproximoVertice(copia,v); 
    }
    printf("\n");
//==============Trabalhando com as arestas==========================// 
    int a=GVultimaAresta(copia);
    
    for(i=1;i<=a;i++)
    {
        if(GBexisteIdAresta(copia,i))
        {
            printf("Aresta %d não visitada\n",i); 
        }    
    }
//==================================================================   
    v=partida;   
    printf("\nVertice %d cinza \n",v);
    inserePilha(aux,v);   

    //Enquanto tiver elemento na pilha,existe vertice cinza.
    while(vaziaPilha(aux)!=1)
    {
        v=retiraPilha(aux);
        printf("\nVertice %d ativado  \n",v);
        a=GAprimaSaida(copia,v); 
        
        while(a!=0)
        {
             printf("Aresta %d visitada \n",a);

             int w=GVvizinho(copia,a,v);
            
             if(vetVert[w]==0)
             {
                 printf("\nVertice %d cinza \n",w);
                 vetVert[w]=1;
                
                 inserePilha(aux,w);             
             }
             
             a=GAproxSaida(copia,v,a);            
        }
            
         printf("\nVertice %d preto \n",v);
         printf("Vertice %d desativado \n",v);
         vetVert[v]=2;  
    }

    GGdestroiGrafo(copia);
    destroiPilha(aux);
    free(vetVert);
    vetVert=NULL;
    
    return;
}

void coloracaoGulosa(Grafo g,int k)
{    
    Grafo copia=GGcopiaGrafo(g);    
    Pilha aux=criaPilha();
    
    int v=GVultimoVertice(copia);    
    int *vetVert=(int*)malloc((v+1)*(sizeof(int)));    
    
    //Tornando os vertices não coloridos.
    int i;
    for(i=0;i<=v;i++)
    {
        vetVert[i]=0;       
    }

    //fase 1: define ordem da coloração
    int w;
    while(GInumeroVertices(copia)>0)
    {
        w=GVmenorGrau(copia);              
        GVdestroiVertice(copia,w);      
        inserePilha(aux,w);        
    }
    
    //fase 2: Colore os vertices 
    while(vaziaPilha(aux)==0)
    {
       v=retiraPilha(aux);
       
       if(GIpegaGrau(g,v)>=k)
       {
           printf("nao tem solução");
           return;
       }
       else
       {           
           int cor;
           int a=GAprimaAresta(g,v);
           int v1=GVvizinho(g,a,v);
           
           cor=vetVert[v1];
                     
           while(a!=0)
           {
              a=GAproxAresta(g,v,a);   
              v1=GVvizinho(g,a,v);
               
              if(cor<vetVert[v1])
              {
                  cor=vetVert[v1]; 
              }  
           }
         cor++;
         vetVert[v]=cor;               
       }       
    }
    
    int tam=GVultimoVertice(g);
    for(i=1;i<=tam;i++)
    {
        if(vetVert[i]!=0)
        {
            printf("Vertice %d com cor: %d \n",i,vetVert[i]); 
        }        
    }   
}
