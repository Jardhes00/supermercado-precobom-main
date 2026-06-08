#ifndef PILHA_CARRINHOS_H
#define PILHA_CARRINHOS_H

#include "config.h"

// Estrutura do Carrinho
typedef struct {
    int id;
} Carrinho;

// Estrutura da Pilha de Carrinhos
typedef struct {
    Carrinho carrinhos[MAX_CARRINHOS];
    int topo; // Indica a posicao do ultimo carrinho adicionado (-1 se vazia)
} PilhaCarrinhos;

// Prototipos das funcoes
void inicializarPilha(PilhaCarrinhos *pilha, int qtd_inicial);
int retirarCarrinho(PilhaCarrinhos *pilha, Carrinho *c);
int devolverCarrinho(PilhaCarrinhos *pilha, Carrinho c);
void exibirStatusPilha(PilhaCarrinhos *pilha);

#endif