#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    char ean[14];
    char nome[50];
    float preco;
    float peso;
    char tipo[20]; 
} Produto;

typedef struct NoProduto {
    Produto produto;
    struct NoProduto* proximo;
} NoProduto;

#endif