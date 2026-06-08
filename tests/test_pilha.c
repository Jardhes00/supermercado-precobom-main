#include <stdio.h>
#include <assert.h>
#include "pilha_carrinhos.h"

int main() {
    printf("--- Iniciando Testes da Pilha de Carrinhos ---\n\n");

    PilhaCarrinhos pilha;
    Carrinho c;
    int sucesso;

    // 1. Teste de Inicializacao
    printf("1. Testando inicializacao...\n");
    inicializarPilha(&pilha, 3);
    assert(pilha.topo == 2); // Como o índice começa em 0, 3 elementos significa topo = 2
    printf("   [OK] Pilha inicializada com 3 carrinhos.\n");

    // 2. Teste de Retirada (Pop)
    printf("2. Testando retirada de carrinho...\n");
    sucesso = retirarCarrinho(&pilha, &c);
    assert(sucesso == 1);    // Tem que retornar sucesso (1)
    assert(pilha.topo == 1); // O topo tem que descer
    printf("   [OK] Carrinho ID %d retirado. Restam 2.\n", c.id);

    // 3. Teste de Pilha Vazia (Underflow)
    printf("3. Testando limite de pilha vazia...\n");
    retirarCarrinho(&pilha, &c); // Resta 1
    retirarCarrinho(&pilha, &c); // Resta 0
    sucesso = retirarCarrinho(&pilha, &c); // Essa tentativa DEVE falhar
    assert(sucesso == 0);
    printf("   [OK] Bloqueio de pilha vazia funcionando corretamente.\n");

    // 4. Teste de Pilha Cheia (Overflow)
    printf("4. Testando limite de pilha cheia...\n");
    // Vamos encher a pilha até o limite definido em MAX_CARRINHOS
    for(int i = 0; i < MAX_CARRINHOS; i++) {
        c.id = 100 + i; // IDs fictícios
        devolverCarrinho(&pilha, c);
    }
    // Tentar adicionar mais UM carrinho além do máximo
    sucesso = devolverCarrinho(&pilha, c);
    assert(sucesso == 0); // Essa tentativa DEVE falhar
    printf("   [OK] Bloqueio de pilha cheia funcionando corretamente.\n");

    printf("\n--- Todos os testes passaram com SUCESSO! ---\n");
    return 0;
}