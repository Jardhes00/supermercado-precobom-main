#include <stdlib.h>
#include "../include/cliente.h"

Cliente* criarCliente(int id) {
    Cliente* novo = (Cliente*)malloc(sizeof(Cliente));
    if (novo != NULL) {
        novo->id = id;
        novo->compras = NULL;
        novo->total_itens = 0;
        novo->tempo_atendimento = 0;
    }
    return novo;
}

Cliente criarClienteVazio(int id) {
    Cliente c;
    c.id = id;
    c.total_itens = 0;
    c.tempo_atendimento = 0;
    c.carrinho_usado.id = -1; // Identificador padrão para sem carrinho
    c.compras = NULL;         // Lista de compras começa vazia
    return c;
}

void gerarComprasAleatorias(Cliente* cliente, int min_itens, int max_itens) {
    cliente->total_itens = min_itens + rand() % (max_itens - min_itens + 1);
    
    cliente->tempo_atendimento = cliente->total_itens * 1; 

    for (int i = 0; i < cliente->total_itens; i++) {
        Produto* novo_produto = (Produto*)malloc(sizeof(Produto));
        novo_produto->id_produto = rand() % 1000;
        
        novo_produto->proximo = cliente->compras;
        cliente->compras = novo_produto;
    }
}

void liberarComprasCliente(Cliente* cliente) {
    if (cliente == NULL) return;
    
    Produto* atual = cliente->compras;
    while (atual != NULL) {
        Produto* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(cliente);
}