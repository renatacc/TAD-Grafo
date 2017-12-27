//=====================================================
// Arquivo: grafo.c
//
// Autores: Ana Paula Fernandes de Souza
//          Renata Caroline Cunha
// Data: 31/07/2016
// Disciplina: Programacao II - AED
//=====================================================

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

struct estrela{  

    struct estrela *prox;
    struct estrela *ant;
    struct aresta *aresta;
};

struct vert{

    int ind; //identificador do vertice
    struct vert *prox;
    struct vert *ant;
    struct estrela *estrelaVert;
};

struct aresta {

    struct aresta *prox;
    struct aresta *ant;
    int ind; // identificador de aresta.
    struct vert *v1;
    struct vert *v2;    
};

struct grafo {

    int ultimoVert, numVertices;
    int ultimaAresta, numArestas;
    struct vert *PVinicio;
    struct vert *PVfim;    
    struct aresta *PAinicio;
    struct aresta *PAfim;
};

typedef struct vert *Vertice;
typedef struct aresta *Aresta;

Vertice GPprocuraVertice(Grafo p,int v1);
void GEcriaEstrela(Vertice pv,Aresta pa);
void GEdestroiEstrela(Vertice pv,Aresta pa);

Grafo GGcriaGrafo(void) 
{
    Grafo aux;

    aux=(struct grafo*)malloc(sizeof(struct grafo));

    aux->ultimaAresta=0;
    aux->ultimoVert=0;
    aux->numArestas=0;
    aux->numVertices=0;
    
    aux->PVinicio=NULL;
    aux->PAinicio=NULL;
    aux->PVfim=NULL;
    aux->PAfim=NULL;

    return (aux);
}

Grafo GGdestroiGrafo(Grafo p) 
{
   if(p==NULL)
   {
      return(0);        
   }
    
   while(p->PVinicio!=NULL)
   {
      GVdestroiVertice(p,(p->PVinicio)->ind);       
   }
   
   free(p); 
   p=NULL;

   return(p);
}

int GVcriaVertice(Grafo p) 
{
 //Se a lista de vertices estiver vazia. 
   if(p->numVertices==0)
   {
      struct vert *novo=(struct vert*)malloc(sizeof(struct vert)); 

      p->ultimoVert++;    
         
      novo->ant=NULL;
      novo->prox=NULL;
      novo->estrelaVert=NULL; 
      novo->ind=p->ultimoVert;
         
      p->PVinicio=novo;
      p->PVfim=novo;
      p->numVertices++;

      return(novo->ind);
   }
   //Outros casos: Inserir sempre no final.       
   struct vert *novo=(struct vert*)malloc(sizeof(struct vert));   
      
   p->ultimoVert++;    
       
   novo->ant=p->PVfim;
   (p->PVfim)->prox=novo;
   novo->prox=NULL;
   novo->estrelaVert=NULL; 
   novo->ind=p->ultimoVert;
       
   p->PVfim=novo;
   p->numVertices++;

   return(novo->ind);  
 }

int GAcriaAresta(Grafo p, int v1,int v2)
{
 if((GBexisteIdVertice(p,v1)==0) || (GBexisteIdVertice(p,v2)==0))
 {    
   return (0);
 }   

 //Se os 2 vertices existirem deverá criar a aresta.   
 if(p->numArestas==0)
 {
    struct aresta *novo=(struct aresta*)malloc(sizeof(struct aresta));
    
    p->ultimaAresta++;
 
    novo->ant=NULL;
    novo->prox=NULL;
    novo->ind=p->ultimaAresta;
    
    p->PAinicio=novo;
    p->PAfim=novo;
    p->numArestas++;

    //Se aresta for um laço vai criar apenas uma estrela.
    if(v1==v2)
    {
       novo->v1=GPprocuraVertice(p,v1);
       novo->v2=novo->v1; 

       GEcriaEstrela(novo->v1,novo); 
       
       return(p->ultimaAresta);       
    }
    
    novo->v1=GPprocuraVertice(p,v1);
    novo->v2=GPprocuraVertice(p,v2);    
    
    GEcriaEstrela(novo->v1,novo);
    GEcriaEstrela(novo->v2,novo);    
 
    return(p->ultimaAresta);  
 }
    //Outros casos:Inserir no final.
    struct aresta *novo=(struct aresta*)malloc(sizeof(struct aresta));
    
    p->ultimaAresta++;

    novo->ant=p->PAfim;
    novo->prox=NULL;
    novo->ind=p->ultimaAresta;

    (p->PAfim)->prox=novo;
    p->PAfim=novo;
    p->numArestas++;

    //Se aresta for um laço vai criar apenas uma estrela.
    if(v1==v2)
    {
       novo->v1=GPprocuraVertice(p,v1);
       novo->v2=novo->v1; 

       GEcriaEstrela(novo->v1,novo); 
       
       return(p->ultimaAresta);        
    }
    
    novo->v1=GPprocuraVertice(p,v1);
    novo->v2=GPprocuraVertice(p,v2);    
  
    GEcriaEstrela(novo->v1,novo);
    GEcriaEstrela(novo->v2,novo);    
 
    return(p->ultimaAresta);      
}

int GBexisteIdVertice(Grafo p,int v)
{
  struct vert *aux=p->PVinicio;
  
  if(aux->ind==v)
  {
     return(1);      
  }
  
  int valorRetorno=0;  
  while(aux->prox!=NULL)
  {
      aux=aux->prox;

      if(aux->ind==v)
      {
        valorRetorno=1;             
      }    
  }
  
  return(valorRetorno);
}

int GBexisteIdAresta(Grafo p,int a)
{
  struct aresta *aux=p->PAinicio;
  
  if(aux->ind==a)
  {
     return(1);      
  }
  
  int valorRetorno=0;  
  while(aux->prox!=NULL)
  {
      aux=aux->prox;
      
      if(aux->ind==a)
      {
        valorRetorno=1;             
      }    
  }
  
  return(valorRetorno);   
}

int GBexisteArestaDir(Grafo p,int v1,int v2)
{    
     struct aresta *auxAresta=p->PAinicio;
     
     if((auxAresta->v1)->ind==v1 && (auxAresta->v2)->ind==v2)
     {
        return(1);
     }
     
     int valorRetorno=0;
     while(auxAresta->prox!=NULL)
     {
        auxAresta=auxAresta->prox;
        if((auxAresta->v1)->ind==v1 && (auxAresta->v2)->ind==v2)
        {
            valorRetorno=1;
        }
     }
     
     return(valorRetorno);
}

int GBexisteAresta(Grafo p,int v1,int v2)
{
   if((GBexisteArestaDir(p,v1,v2)==1) || (GBexisteArestaDir(p,v2,v1)==1))
   {
      return(1);
   }
   
   return(0);      
}

//Se não existir os vertices passados irá retornar valor zero na aresta.
int GApegaArestaDir(Grafo p,int v1,int v2)
{
    struct aresta *aux=p->PAinicio;  
    
    if((aux->v1)->ind==v1 && (aux->v2)->ind==v2)
    {
        return(aux->ind);         
    }
       
    int valorRetorno=0;    
    while(aux->prox!=NULL)
    {
      aux=aux->prox;  
      if((aux->v1)->ind==v1 && (aux->v2)->ind==v2)  
      {  
          valorRetorno=aux->ind;
      }    
    }
    
    return(valorRetorno);   
}

int GApegaAresta(Grafo p,int v1, int v2)
{
   if(GApegaArestaDir(p,v1,v2)!=0)
   {
       return(GApegaArestaDir(p,v1,v2));      
   }

   if(GApegaArestaDir(p,v2,v1)!=0)
   {
       return(GApegaArestaDir(p,v2,v1));              
   }   

   return(0);     
}

int GVprimeiroVertice(Grafo p)
{
   if(p->numVertices==0)
   {
      return(0);       
   }
   
   return((p->PVinicio)->ind);    
}

int GVproximoVertice(Grafo p,int v1)
{
   struct vert *aux=p->PVinicio;
   
   if(aux->ind==v1 && aux->prox!=NULL)
   {
      return((aux->prox)->ind);       
   }
       
   int indRetorno=0;
   while(aux->prox!=NULL)
   {
      aux=aux->prox;      
      if(aux->ind==v1 && aux->prox!=NULL)
      {
        indRetorno=(aux->prox)->ind;       
      }                 
   } 
    
   return(indRetorno); 
}

int GAprimeiraAresta(Grafo p)
{
   if(p->numArestas==0)
   {
      return(0);
   }
  
   return((p->PAinicio)->ind);  
}

int GAproximaAresta(Grafo p,int a1)
{
   struct aresta *aux=p->PAinicio;
   
   if(aux->ind==a1 && aux->prox!=NULL)
   {
      return((aux->prox)->ind);       
   }
    
   int indRetorno=0;
   while(aux->prox!=NULL)
   {
      aux=aux->prox;
      if(aux->ind==a1 && aux->prox!=NULL)
      {
        indRetorno=(aux->prox)->ind;       
      }      
   }
    
   return(indRetorno);      
}

int GInumeroVertices(Grafo p)
{
   return(p->numVertices);
}

//Retorna o valor máximo de um inteiro.
int GInumeroVerticesMax(Grafo p)
{
   return(255);
}

int GInumeroArestas(Grafo p)
{
   return(p->numArestas);
}

int GInumeroArestasMax(Grafo p)
{
   return(255);
}

int GBsalvaGrafo(Grafo p, char* nome)
{
   //Se não existir o ponteiro para o grafo não criará o arquivo e retornará 0  
   if(p==NULL)
   {
      return(0); 
   }
    
   FILE *fp;
   fp=fopen(nome,"w");

   fprintf(fp,"%d %d \n",p->numVertices,p->numArestas);
   fprintf(fp,"%d %d \n",p->ultimoVert,p->ultimaAresta);
  
   struct vert *auxVert=p->PVinicio; 

   fprintf(fp,"%d \n",auxVert->ind);
   while(auxVert->prox!=NULL)
   {
      auxVert=auxVert->prox;
      fprintf(fp,"%d \n",auxVert->ind);                
   }
  
   struct aresta *auxAresta=p->PAinicio;

   fprintf(fp,"%d %d %d \n",auxAresta->ind,(auxAresta->v1)->ind,(auxAresta->v2)->ind);
   while(auxAresta->prox!=NULL)
   {
      auxAresta=auxAresta->prox;
      fprintf(fp,"%d %d %d \n",auxAresta->ind,(auxAresta->v1)->ind,(auxAresta->v2)->ind);                
   }
  
   fclose(fp);

   return(1);
}

Grafo GGcarregaGrafo(char* nome)
{
   FILE *fp;
   fp=fopen(nome,"r");

   if(fp==NULL)
   {
      return(NULL);
   }

   int v,a;
   Grafo p=GGcriaGrafo();

   int qtdVert,qtdAresta;
   //quantidade atual de vertices e de arestas.
   fscanf(fp,"%d %d",&qtdVert,&qtdAresta);
   //ultimo vertice e aresta criados.
   fscanf(fp,"%d %d",&v,&a);

   int i,vertCriado;
   for(i=1;i<=qtdVert;i++)
   {      
      fscanf(fp,"%d",&v);
      vertCriado=GVcriaVertice(p);

      while(vertCriado!=v)
      {
         GVdestroiVertice(p,vertCriado);  
         vertCriado=GVcriaVertice(p);   
      }
   } 
  
   int arestaCriada,v2;
   for(i=1;i<=qtdAresta;i++)
   {      
     fscanf(fp,"%d %d %d",&a,&v,&v2);
     arestaCriada=GAcriaAresta(p,v,v2);

     while(arestaCriada!=a)
     {
         GAdestroiAresta(p,arestaCriada);  
         arestaCriada=GAcriaAresta(p,v,v2);      
     }
   }  
  
  fclose(fp);

  return(p);
}

int GIpegaGrau(Grafo p, int v)
{
   struct vert *aux=GPprocuraVertice(p,v);     
   struct estrela *auxEstrela=aux->estrelaVert;
   int cont=0;
   
   if(auxEstrela==NULL)
   {
      return(cont);      
   }

   cont++;//Pois já fez a contagem da primeira caixinha.
   while(auxEstrela->prox!=NULL)
   { 
      auxEstrela=auxEstrela->prox;       
      cont++; 
   }
    
   return(cont);    
}

int GAprimaAresta(Grafo p,int v)
{   //Se o vertice não existir retorna zero.
    if(GBexisteIdVertice(p,v)==0)
    {
       return(0);       
    }
    
    struct vert *aux=GPprocuraVertice(p,v);
    
    if(aux->estrelaVert==NULL)
    {
        return(0);
    }    

    return((((aux->estrelaVert)->ant)->aresta)->ind);        
}

int GAproxAresta(Grafo p,int v,int a1)
{
    int indRetorno=0; 
    //Se o vertice não existir retorna zero.
    if(GBexisteIdVertice(p,v)==0)
    {
       return(indRetorno);       
    }
    
    struct vert *aux=GPprocuraVertice(p,v);
    struct estrela *auxEstrela=aux->estrelaVert;
    
    if(aux->estrelaVert==NULL)
    {
        return(indRetorno);       
    }
    
    if((auxEstrela->aresta)->ind==a1)
    {
        return(indRetorno);        
    }
       
    while(auxEstrela->prox!=NULL)
    {
        auxEstrela=auxEstrela->prox;       
        if((auxEstrela->aresta)->ind==a1)
        {  
            //Precisa ser ant pois é necessário descobrir a próxima 
            //mas a ordem da estrela está ao contrário    
            indRetorno=(((auxEstrela->ant)->aresta)->ind);     
        }              
    }
    
    return(indRetorno);
}

int GAprimaEntrada(Grafo p,int v)
{
  int indRetorno=0;
    
  if(GBexisteIdVertice(p,v)==0)
  {
    return(indRetorno);         
  }
    
  struct vert *auxVert=GPprocuraVertice(p,v);
  struct aresta *auxAresta=p->PAinicio;
  
  if(auxAresta->v2==auxVert)
  {
      return(auxAresta->ind);      
  }
  
  while(auxAresta->prox!=NULL)
  {
     auxAresta=auxAresta->prox;
     
    if(auxAresta->v2==auxVert)
    {
        indRetorno=auxAresta->ind;      
    }           
  }
  
 return(indRetorno); 
}

int GAproxEntrada(Grafo p,int v, int a1)
{
  int indRetorno=0;
  //se o vertice e a aresta não existir retorna 0
  if(GBexisteIdVertice(p,v)==0)
  {
     return(indRetorno);         
  }
  if(GBexisteIdAresta(p,a1)==0)
  {
      return(indRetorno);       
  }  
    
  struct vert *auxVert=GPprocuraVertice(p,v);
  struct aresta *auxAresta=p->PAinicio;
  struct estrela *auxEstrela=auxVert->estrelaVert;

  //Olha se existe alguma estrela.
  if(auxEstrela==NULL)
  {
      return(indRetorno);     
  }
  //A existencia de apenas uma estrela ou seja não irá ter a próxima.
  if(auxEstrela->prox==NULL)
  {
      return(indRetorno);     
  }
  
  while(auxAresta->prox!=NULL || auxAresta->ind==a1)
  {
     auxAresta=auxAresta->prox;     
  }
  
  while(auxAresta->prox!=NULL)
  {
     auxAresta=auxAresta->prox;
     if(auxAresta->v2==auxVert)
     {
         indRetorno=auxAresta->ind;            
     }
  }     
     
 return(indRetorno); 
}

int GAprimaSaida(Grafo p,int v)
{  
    
  int indRetorno=0;  
  if(GBexisteIdVertice(p,v)==0)
  {
    return(indRetorno);         
  }
    
  struct vert *auxVert=GPprocuraVertice(p,v);
  struct aresta *auxAresta=p->PAinicio;
  
  if(auxAresta->v1==auxVert)
  {
      return(auxAresta->ind);      
  }
  
  while(auxAresta->prox!=NULL)
  {
     auxAresta=auxAresta->prox;
     
    if(auxAresta->v1==auxVert)
    {
        indRetorno=auxAresta->ind;
        return(indRetorno);
    }           
  }
  
 return(indRetorno); 
}

int GAproxSaida(Grafo p,int v,int a1)
{
  int indRetorno=0;
  //se o vertice e a aresta não existir retorna 0
  if(GBexisteIdVertice(p,v)==0)
  {
     return(indRetorno);         
  }
  if(GBexisteIdAresta(p,a1)==0)
  {
      return(indRetorno);       
  }  
    
  struct vert *auxVert=GPprocuraVertice(p,v);
  struct aresta *auxAresta=p->PAinicio;
  struct estrela *auxEstrela=auxVert->estrelaVert;

  //Olha se existe alguma estrela.
  if(auxEstrela==NULL)
  {
      return(indRetorno);     
  }
  //A existencia de apenas uma estrela ou seja não irá ter a próxima.
  if(auxEstrela->prox==NULL)
  {
      return(indRetorno);     
  }
  
  if(auxAresta->ind==a1)
  {
    while(auxAresta->prox!=NULL)
    {
       auxAresta=auxAresta->prox;
       if(auxAresta->v1==auxVert)
       {
          indRetorno=auxAresta->ind;
          return(indRetorno);
       }
    }
  }

  //Andar até achar a aresta que foi passada.
  while(auxAresta->ind!=a1)
  {
    auxAresta=auxAresta->prox;        
  }  
  
  while(auxAresta->prox!=NULL)
  {
     auxAresta=auxAresta->prox;
     if(auxAresta->v1==auxVert)
     {
        indRetorno=auxAresta->ind;            
        return(indRetorno); 
     }
  } 

  return(indRetorno); 
}

int GBarestaLaco(Grafo p,int a)
{
    int valorRetorno=0;  
    struct aresta *auxAresta=p->PAinicio;    
      
    while(auxAresta->prox!=NULL || auxAresta->ind==a)
    {
       auxAresta=auxAresta->prox;     
    }   

   //Se for um laço retorna valor 1.    
   if(auxAresta->v1==auxAresta->v2)
   {     
      valorRetorno=1;      
   }
      
   return(valorRetorno);       
}

int GValfa(Grafo p,int a)
{
    int valorRetorno=0;  
      
    if(GBexisteIdAresta(p,a)==0)
    {
      return(valorRetorno);  
    }
     
    struct aresta *auxAresta=p->PAinicio; 
    while(auxAresta->ind!=a)
    {
       auxAresta=auxAresta->prox;     
    }
      
    valorRetorno=auxAresta->v1->ind;

    return(valorRetorno);
}   

int GVomega(Grafo p,int a)
{
    int valorRetorno=0;  
      
    if(GBexisteIdAresta(p,a)==0)
    {
      return(valorRetorno);  
    }
     
    struct aresta *auxAresta=p->PAinicio;  
    while(auxAresta->ind!=a)
    {
       auxAresta=auxAresta->prox;     
    }
      
    valorRetorno=auxAresta->v2->ind;

    return(valorRetorno);
}

int GVvizinho(Grafo p,int a, int v)
{
    int valorRetorno=0;
    //Vai retornar zero se a aresta ou o vertice não existir.
    if(GBexisteIdAresta(p,a)==0)
    {
       return(valorRetorno);         
    }  
    if(GBexisteIdVertice(p,v)==0)
    {
       return(valorRetorno);               
    }
    
    struct aresta *auxAresta=p->PAinicio;   
    while(auxAresta->ind!=a)
    {
       auxAresta=auxAresta->prox;     
    }
    
    if(auxAresta->v1->ind==v)
    {
        valorRetorno=auxAresta->v2->ind;      
    }
    
    if(auxAresta->v2->ind==v)
    {
        valorRetorno=auxAresta->v1->ind;      
    }    
    
    return(valorRetorno);        
}

int GVdestroiVertice(Grafo p,int v)
{
    //Se vertice for destruida vai retornar 0.
    //Se vertice não existir vai retornar 1
    if(GBexisteIdVertice(p,v)==0)
    {
       return(1);         
    }

    int a;
    
    struct vert *auxVert=GPprocuraVertice(p,v);    
    while(auxVert->estrelaVert!=NULL)
    {
        a=((auxVert->estrelaVert)->aresta)->ind;
        a=GAdestroiAresta(p,a);               
    }
    
    //Caso Especial:Existe apenas um vertice.    
    if(p->numVertices==1)
    {        
      free(p->PVinicio);
      auxVert=NULL;
      p->PVinicio=NULL;
      p->PAfim=NULL;
      p->numVertices--;  

      return(0);  
    }

    //Caso Especial:Apagar o primeiro da lista.
    if(auxVert==p->PVinicio)
    {
     p->PVinicio=auxVert->prox;
     auxVert->prox->ant=NULL;

     free(auxVert);
     auxVert=NULL;     

     p->numVertices--;  

     return(0);   
    }

    //Caso especial:Apagar o ultimo da lista.
    if(auxVert==p->PVfim)
    {
      p->PVfim=auxVert->ant;
      auxVert->ant->prox=NULL;

      free(auxVert);
      auxVert=NULL;      

      p->numVertices--;

      return(0);  
    }    

    //Outros casos:   
    auxVert->ant->prox=auxVert->prox;
    auxVert->prox->ant=auxVert->ant;
    p->numVertices--;

    free(auxVert);
    auxVert=NULL;

    return(0);        
}

int GAdestroiAresta(Grafo p,int a)
{   //Se aresta for destruida vai retornar 0.
    //Se aresta não existir vai retornar 1.
    if(GBexisteIdAresta(p,a)==0)
    {
       return(1);         
    }
    
    struct aresta *aux=p->PAinicio;
    //colocar o ponteiro na caixinha que quero apagar.
    while(aux->ind!=a)
    {
        aux=aux->prox;          
    }
    
    if(aux->v1==aux->v2)
    {
        GEdestroiEstrela(aux->v1,aux);     
    }
    else
    {
        GEdestroiEstrela(aux->v1,aux);  
        GEdestroiEstrela(aux->v2,aux);  
    }
    
    //Caso especial:Existir apenas uma aresta.
    if(p->numArestas==1)
    {
        free(p->PAinicio);
        p->PAinicio=NULL;
        p->PAfim=NULL;
        p->numArestas--;
        
        return(0);
    }
    
    //Apagar a primeira aresta
    if(aux==p->PAinicio)
    {
        (aux->prox)->ant=NULL;
        p->PAinicio=aux->prox;
        p->numArestas--;
        
        free(aux);
        aux=NULL;
        
        return(0);
    }
    
    //Apagar a ultima aresta
    if(aux==p->PAfim)
    {
        (aux->ant)->prox=NULL;
        p->PAfim=aux->ant;
        p->numArestas--;
        
        free(aux);
        aux=NULL;
        
        return(0);
    }
        
    //Outros casos
    (aux->prox)->ant=aux->ant;    
    (aux->ant)->prox=aux->prox;
    p->numArestas--; 

    free(aux);
    aux=NULL;
    
    return(0);
}

//Funções criadas pela dupla:
Vertice GPprocuraVertice(Grafo p,int v1)
{
   if(GBexisteIdVertice(p,v1)==0)
   {
       return(0);
   }

   struct vert *aux=p->PVinicio;   
   while(v1!=aux->ind)
   {
       aux=aux->prox;     
   }
   
   return(aux); 
}

 void GEcriaEstrela(Vertice pv,Aresta pa)//pv=ponteiro do vertice //pa=ponterio da aresta
{
   //Caso especial:A Lista vazia 
   if(pv->estrelaVert==NULL)
   {
      struct estrela *novo=(struct estrela*)malloc(sizeof(struct estrela));
      
      novo->ant=novo;//primeiro sempre apontará para ele mesmo.
      novo->prox=NULL;       
      novo->aresta=pa; 
      pv->estrelaVert=novo; 
      
      return; 
   }

   //Outros Casos:Inserir no inicio;    
   struct estrela *aux=pv->estrelaVert;
   struct estrela *novo=(struct estrela*)malloc(sizeof(struct estrela));  
    
   novo->aresta=pa;
   novo->ant=aux->ant;
   novo->prox=aux;     
   aux->ant=novo;     
   pv->estrelaVert=novo;
     
   return;  
}

void GEdestroiEstrela(Vertice pv,Aresta pa)
{
  struct estrela *aux=pv->estrelaVert;  
    
  //Apagar quanto existir apenas uma estrela.  
  if(aux->prox==NULL)
  {
     free(aux);
     aux=NULL;
     pv->estrelaVert=NULL;
     
     return; 
  }

  //Apagar o primeiro elemento da lista.
  if(aux->aresta==pa)
  {      
    (aux->prox)->ant=aux->ant;  
    pv->estrelaVert=aux->prox;
    
    free(aux);
    aux=NULL;
    
    return;
  }

  //Apagar o ultimo elemento.
  if((aux->ant)->aresta==pa)
  {
    aux=aux->ant;
    
    (pv->estrelaVert)->ant=aux->ant;
    (aux->ant)->prox=aux->prox;
    
    free(aux);
    aux=NULL;
    
    return;
  }
  
  //Outros casos:
   while(aux->aresta!=pa)
   {
       aux=aux->prox;    
   }    
  
  (aux->prox)->ant=aux->ant;
  (aux->ant)->prox=aux->prox;
  
  free(aux);
  aux=NULL;
  
  return;  
}

Grafo GGcopiaGrafo(Grafo p)
{    
    GBsalvaGrafo(p,"copia.txt");
    Grafo aux=GGcarregaGrafo("copia.txt"); 
    remove("copia.txt");  
    
    return(aux);   
}

int GVultimoVertice(Grafo p)
{
    return(p->ultimoVert);      
}

int GVultimaAresta(Grafo p)
{
    return(p->ultimaAresta);      
}

int GVmenorGrau(Grafo p)
{   
   int v=GVprimeiroVertice(p);   
   int v_menor=v;
   int menor=GIpegaGrau(p,v);   
      
   while(v!=0)
   {
       v=GVproximoVertice(p,v);
       if(v>0 && GIpegaGrau(p,v)<menor)
       {
         v_menor=v;
         menor=GIpegaGrau(p,v);
       }     
   }
   
   return(v_menor);    
}