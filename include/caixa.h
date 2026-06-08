#ifndef CAIXA_H
#define CAIXA_H

#include <stdio.h>
#include "config.h"
#include "fila.h"       
#include "cliente.h"    

typedef enum {
    CAIXA_OPERANTE,
    CAIXA_INOPERANTE
} StatusCaixa;

typedef struct {
    int id;
    StatusCaixa status;

    int tempo_para_parar;
    int tempo_para_voltar;

    int vezes_inoperante;
    int tempo_total_inoperante;
    int clientes_atendidos;
    int produtos_processados;

    // --- NOVOS CAMPOS ADICIONADOS ---
    Fila fila;                  
    Cliente cliente_atual;      
    int tempo_atendimento;      
} Caixa;

void inicializarCaixas(Caixa caixas[]);
void atualizarCaixa(Caixa *caixa, int tempo);
void atualizarCaixas(Caixa caixas[], int tempo);

int caixaEstaOperante(Caixa caixa);

void registrarAtendimento(Caixa *caixa, int quantidade_produtos);

void exibirStatusCaixas(FILE *destino, Caixa caixas[], int tempo);
void exibirRelatorioCaixas(FILE *destino, Caixa caixas[], int tempo);

#endif