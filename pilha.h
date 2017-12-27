//=====================================================
// Arquivo: pilha.h
//
// Autores: Ana Paula Fernandes de Souza
//          Renata Caroline Cunha
// Data: 31/07/2016
// Disciplina: Programacao II - AED
//=====================================================

#ifndef PILHA_H
#define	PILHA_H

typedef struct pilha *Pilha;

Pilha criaPilha(void);//Pilha indexada de 1.

void destroiPilha(Pilha p);

void inserePilha(Pilha p,int x);

int retiraPilha(Pilha p);

int vaziaPilha(Pilha p); //Retorna 1 se a lista estiver vazia.

int tamanhoPilha(Pilha p);

int consultaPilha(Pilha p); //Consulta o topo da pilha.

#endif	/* PILHA_H */
