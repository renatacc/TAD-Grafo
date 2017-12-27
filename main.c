//=====================================================
// Arquivo: main.c
//
// Autores: Ana Paula Fernandes de Souza
//          Renata Caroline Cunha
// Data: 31/07/2016
// Disciplina: Programacao II - AED
//=====================================================
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include "busca.h"

int main(int argc, char const *argv[])
{
     // Grafo g=GGcarregaGrafo("grafo1.txt");

     Grafo g = GGcriaGrafo();
	 GVcriaVertice(g);
	 GVcriaVertice(g);
	 GVcriaVertice(g);
	 GVcriaVertice(g);
	 GVcriaVertice(g);
     GVcriaVertice(g);
    
	 GAcriaAresta(g,6,1);
	 GAcriaAresta(g,6,3);
	 GAcriaAresta(g,3,6);
     GAcriaAresta(g,1,3);
     GAcriaAresta(g,1,2);
	 GAcriaAresta(g,2,3);    
	 GAcriaAresta(g,2,2);    
     GAcriaAresta(g,5,4);    

     printf("Busca por Largura: \n\n");
     buscaLargura(g,1);
     printf("\n\n");

	 printf("Busca por Profundidade: \n\n");
     buscaProfundidade(g,1);    
     printf("\n\n");

     printf("Coloração Gulosa: \n\n");
     coloracaoGulosa(g,6);
   	 printf("\n\n");

     GGdestroiGrafo(g);

	 return 0;
}
     
