#ifndef CLIENTE_H
#define CLIENTE_H

#include "pilha_carrinhos.h"

// 1. Estrutura para os produtos comprados (Lista Encadeada)
typedef struct Produto {
    int id_produto;
    struct Produto* proximo;
} Produto;

// 2. Estrutura do Cliente
typedef struct {
    int id;
    int total_itens;
    int tempo_atendimento;
    Carrinho carrinho_usado;
    Produto* compras;       // Ponteiro para o início da lista de compras
} Cliente;

// 3. Protótipos das funções exigidas pelo main.c
Cliente criarClienteVazio(int id);
void liberarComprasCliente(Cliente* cliente);

#endif