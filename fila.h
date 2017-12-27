//=====================================================
// Arquivo: fila.h
//
// Autores: Ana Paula Fernandes de Souza
//          Renata Caroline Cunha
// Data: 31/07/2016
// Disciplina: Programacao II - AED
//=====================================================

#ifndef FILA_H
#define FILA_H

typedef struct fila *Fila;

Fila criaFila(void);//Fila indexada de 1.

void destroiFila(Fila s);

void insereFila(Fila s,int x);

int retiraFila(Fila s);

int vaziaFila(Fila s); //Retorna 1 se a fila tiver vazia.

int tamanhoFila(Fila s);

int consultaFila(Fila s);

#endif /* FILA_H */
