//=====================================================
// Arquivo: grafo.h 
//
// Autores: Ana Paula Fernandes de Souza 
//          Renata Caroline Cunha
// Data: 31/07/2016
// Disciplina: Programacao II - AED
//=====================================================

#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo *Grafo; 

Grafo GGcriaGrafo(void);

Grafo GGdestroiGrafo(Grafo p);

int GVcriaVertice(Grafo p);

int GAcriaAresta(Grafo p, int v1,int v2);

int GBexisteIdVertice(Grafo p,int v);

int GBexisteIdAresta(Grafo p,int a);

int GBexisteArestaDir(Grafo p,int v1,int v2);

int GBexisteAresta(Grafo p,int v1,int v2);

int GApegaArestaDir(Grafo p,int v1,int v2);

int GApegaAresta( Grafo p,int v1, int v2);

int GVprimeiroVertice(Grafo p);

int GVproximoVertice(Grafo p,int v1);

int GAprimeiraAresta(Grafo p);

int GAproximaAresta(Grafo p,int a1);

int GInumeroVertices(Grafo p);

int GInumeroVerticesMax(Grafo p);

int GInumeroArestas(Grafo p);

int GInumeroArestasMax(Grafo p);

Grafo GGcarregaGrafo(char* nome);

int GBsalvaGrafo(Grafo p, char* nome);

int GIpegaGrau(Grafo p, int v);

int GAprimaAresta(Grafo p,int v);

int GAproxAresta(Grafo p,int v,int a1);

int GAprimaEntrada(Grafo p,int v);

int GAproxEntrada(Grafo p,int v, int a1);

int GAprimaSaida(Grafo p,int v);

int GAproxSaida(Grafo p,int v,int a1);

int GBarestaLaco(Grafo p,int a);

int GValfa(Grafo p,int a);

int GVomega(Grafo p,int a);

int GVvizinho(Grafo p,int a, int v);

int GVdestroiVertice(Grafo p,int v);

int GAdestroiAresta(Grafo p,int a);

Grafo GGcopiaGrafo(Grafo p);

int GVultimoVertice(Grafo p);

int GVultimaAresta(Grafo p);

int GVmenorGrau(Grafo p);

#endif /* GRAFO_H */