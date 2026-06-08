#ifndef FILA_H
#define FILA_H

#include "cliente.h"

typedef struct NoFila {
    Cliente cliente;
    struct NoFila* proximo;
} NoFila;

typedef struct {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
} Fila;

void inicializarFila(Fila* fila);
void enfileirar(Fila* fila, Cliente cliente);
Cliente desenfileirar(Fila* fila);
int filaVazia(Fila* fila);

#endif