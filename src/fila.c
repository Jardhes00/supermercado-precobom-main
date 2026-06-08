#include <stdlib.h>
#include "fila.h"
#include "cliente.h"
#include "caixa.h"
#include <stdio.h>

void inicializarFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

void enfileirar(Fila* fila, Cliente cliente) {
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    if (novo == NULL) return;
    novo->cliente = cliente;
    novo->proximo = NULL;

    if (filaVazia(fila)) {
        fila->inicio = novo;
    } else {
        fila->fim->proximo = novo;
    }
    fila->fim = novo;
    fila->tamanho++;
}

Cliente desenfileirar(Fila* fila) {
    if (filaVazia(fila)) {
        return criarClienteVazio(0);
    }

    NoFila* temp = fila->inicio;
    Cliente cliente = temp->cliente;
    
    fila->inicio = fila->inicio->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    free(temp);
    fila->tamanho--;
    return cliente;
}

int filaVazia(Fila* fila) {
    return fila->inicio == NULL;
}