#include <stdio.h>
#include "pilha_carrinhos.h"

void inicializarPilha(PilhaCarrinhos *pilha, int qtd_inicial) {
    pilha->topo = -1; // Inicia a pilha vazia

    // Preenche a pilha com a quantidade aleatoria inicial
    for (int i = 0; i < qtd_inicial; i++) {
        Carrinho c;
        c.id = i + 1; // Identificador unico para cada carrinho gerado
        devolverCarrinho(pilha, c); // Reutiliza a funcao de empilhar
    }
}

// Remove (pop) um carrinho da pilha.
// Retorna 1 se sucesso, 0 se a pilha estiver vazia (sem carrinhos).
int retirarCarrinho(PilhaCarrinhos *pilha, Carrinho *c) {
    if (pilha->topo == -1) {
        return 0; // Pilha vazia
    }
    *c = pilha->carrinhos[pilha->topo];
    pilha->topo--;
    return 1;
}

// Adiciona (push) um carrinho na pilha.
// Retorna 1 se sucesso, 0 se a pilha estiver cheia.
int devolverCarrinho(PilhaCarrinhos *pilha, Carrinho c) {
    if (pilha->topo >= MAX_CARRINHOS - 1) {
        return 0; // Pilha cheia
    }
    pilha->topo++;
    pilha->carrinhos[pilha->topo] = c;
    return 1;
}

// Mostra no terminal quantos carrinhos ainda estao disponiveis
void exibirStatusPilha(PilhaCarrinhos *pilha) {
    // Como topo inicia em -1, a quantidade total eh topo + 1
    printf("[Carrinhos] Disponiveis na entrada: %d\n", pilha->topo + 1);
}