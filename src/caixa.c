#include <stdio.h>
#include <stdlib.h>
#include "caixa.h"

static void exibirEvento(int tempo, const char *mensagem, int id) {
    printf("[Tempo %d s] ", tempo);
    printf(mensagem, id);
}

static int gerarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

static int gerarTempoParaParar(void) {
    return gerarNumeroAleatorio(TEMPO_MIN_ATE_INOPERANCIA,
                                TEMPO_MAX_ATE_INOPERANCIA);
}

static int gerarTempoParaRetornar(void) {
    return gerarNumeroAleatorio(TEMPO_MIN_INOPERANTE, TEMPO_MAX_INOPERANTE);
}

void inicializarCaixas(Caixa caixas[]) {
    for (int i = 0; i < NUM_CAIXAS; i++) {
        caixas[i].id = i + 1;
        caixas[i].status = CAIXA_OPERANTE;
        caixas[i].tempo_para_parar = gerarTempoParaParar();
        caixas[i].tempo_para_voltar = 0;
        caixas[i].vezes_inoperante = 0;
        caixas[i].tempo_total_inoperante = 0;
        caixas[i].clientes_atendidos = 0;
        caixas[i].produtos_processados = 0;
    }
}

void atualizarCaixa(Caixa *caixa, int tempo) {
    if (caixa->status == CAIXA_OPERANTE) {
        caixa->tempo_para_parar--;

        if (caixa->tempo_para_parar <= 0) {
            caixa->status = CAIXA_INOPERANTE;
            caixa->tempo_para_voltar = gerarTempoParaRetornar();
            caixa->vezes_inoperante++;

            exibirEvento(tempo,
                         "Caixa %d ficou INOPERANTE. Retorno em breve.\n",
                         caixa->id);
        }
    } else {
        caixa->tempo_para_voltar--;
        caixa->tempo_total_inoperante++;

        if (caixa->tempo_para_voltar <= 0) {
            caixa->status = CAIXA_OPERANTE;
            caixa->tempo_para_parar = gerarTempoParaParar();

            exibirEvento(tempo, "Caixa %d voltou a operar.\n", caixa->id);
        }
    }
}

void atualizarCaixas(Caixa caixas[], int tempo) {
    for (int i = 0; i < NUM_CAIXAS; i++) {
        atualizarCaixa(&caixas[i], tempo);
    }
}

int caixaEstaOperante(Caixa caixa) {
    return caixa.status == CAIXA_OPERANTE;
}

void registrarAtendimento(Caixa *caixa, int quantidade_produtos) {
    if (caixa->status == CAIXA_OPERANTE) {
        caixa->clientes_atendidos++;
        caixa->produtos_processados += quantidade_produtos;
    }
}

void exibirStatusCaixas(FILE *destino, Caixa caixas[], int tempo) {
    fprintf(destino, "\n[Tempo %d s] ********* STATUS DOS CAIXAS *********\n",
            tempo);

    for (int i = 0; i < NUM_CAIXAS; i++) {
        fprintf(destino, "Caixa %d | %s",
                caixas[i].id,
                caixas[i].status == CAIXA_OPERANTE ? "Operante" : "Inoperante");

        if (caixas[i].status == CAIXA_INOPERANTE) {
            fprintf(destino, " | Retorno em breve");
        }

        fprintf(destino, "\n");
    }

    fflush(destino);
}

void exibirRelatorioCaixas(FILE *destino, Caixa caixas[], int tempo) {
    fprintf(destino, "\n===== RELATORIO FINAL APOS %d SEGUNDOS =====\n",
            tempo);

    for (int i = 0; i < NUM_CAIXAS; i++) {
        fprintf(destino, "Caixa %d\n", caixas[i].id);
        fprintf(destino, "Quantidade de inoperancias: %d\n",
                caixas[i].vezes_inoperante);
        fprintf(destino, "Tempo total inoperante: %d segundos\n",
                caixas[i].tempo_total_inoperante);
        fprintf(destino, "Clientes atendidos: %d\n",
                caixas[i].clientes_atendidos);
        fprintf(destino, "Produtos processados: %d\n\n",
                caixas[i].produtos_processados);
    }

    fflush(destino);
}
