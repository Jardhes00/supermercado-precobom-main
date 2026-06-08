#include <conio.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "config.h"
#include "caixa.h"
#include "pilha_carrinhos.h"
#include "cliente.h"
#include "fila.h"

static int encerramentoSolicitado(void) {
    if (!_kbhit()) {
        return 0;
    }
    int tecla = _getch();
    return tecla == 'q' || tecla == 'Q';
}

static FILE *abrirRelatorio(char caminho[], size_t tamanho) {
    time_t agora = time(NULL);
    struct tm horario;
    horario = *localtime(&agora);
    _mkdir("relatorios");
    strftime(caminho, tamanho, "relatorios/simulacao_%Y%m%d_%H%M%S.txt", &horario);
    return fopen(caminho, "w");
}

int main(void) {
    char caminho_relatorio[128];
    srand((unsigned int) time(NULL));

    Caixa caixas[NUM_CAIXAS];
    int tempo = 0;
    int id_cliente_seq = 1;

    PilhaCarrinhos pilha;
    int qtd_carrinhos_inicial = MIN_CARRINHOS_INICIAIS + rand() % (MAX_CARRINHOS_INICIAIS - MIN_CARRINHOS_INICIAIS + 1);
    
    inicializarPilha(&pilha, qtd_carrinhos_inicial);
    inicializarCaixas(caixas);

    printf("Simulacao iniciada. Pressione Q para encerrar ou aguarde os 10 minutos (600s).\n");
    printf("Foram disponibilizados %d carrinhos no supermercado hoje.\n\n", qtd_carrinhos_inicial); 

    while (tempo < 600 && !encerramentoSolicitado()) {
        Sleep(1000);
        tempo++;

        atualizarCaixas(caixas, tempo);

        for (int i = 0; i < NUM_CAIXAS; i++) {
            if (caixaEstaOperante(caixas[i])) {
                if (caixas[i].cliente_atual.id == 0 && !filaVazia(&caixas[i].fila)) {
                    caixas[i].cliente_atual = desenfileirar(&caixas[i].fila);
                }
                
                if (caixas[i].cliente_atual.id != 0) {
                    caixas[i].cliente_atual.tempo_atendimento--;
                    caixas[i].tempo_atendimento = caixas[i].cliente_atual.tempo_atendimento;
                    
                    if (caixas[i].cliente_atual.tempo_atendimento <= 0) {
                        registrarAtendimento(&caixas[i], caixas[i].cliente_atual.total_itens);
                        devolverCarrinho(&pilha, caixas[i].cliente_atual.carrinho_usado);
                        liberarComprasCliente(&caixas[i].cliente_atual);
                        
                        caixas[i].cliente_atual = criarClienteVazio(0); 
                    }
                }
            }
        }

        if (rand() % 100 < 40) { 
            Carrinho carrinho_retirado;
            
            if (retirarCarrinho(&pilha, &carrinho_retirado)) { 
                Cliente novo_cliente = criarClienteVazio(id_cliente_seq++);
                novo_cliente.carrinho_usado = carrinho_retirado;
                
                novo_cliente.total_itens = 1 + rand() % 30;
                novo_cliente.tempo_atendimento = novo_cliente.total_itens * 1; 

                int melhor_caixa = -1;
                int menor_tamanho_fila = 999999;

                for (int i = 0; i < NUM_CAIXAS; i++) {
                    if (caixaEstaOperante(caixas[i])) {
                        if (caixas[i].fila.tamanho < menor_tamanho_fila) {
                            menor_tamanho_fila = caixas[i].fila.tamanho;
                            melhor_caixa = i;
                        }
                    }
                }

                if (melhor_caixa != -1) {
                    enfileirar(&caixas[melhor_caixa].fila, novo_cliente);
                } else {
                    devolverCarrinho(&pilha, carrinho_retirado);
                    liberarComprasCliente(&novo_cliente);
                    id_cliente_seq--;
                }
            }
        }

        if (tempo % INTERVALO_EXIBICAO_STATUS == 0) {
            exibirStatusCaixas(stdout, caixas, tempo);
            exibirStatusPilha(&pilha); 
            
            printf("--- FILAS INTERNAS (DIAGRAMA) ---\n");
            for(int i = 0; i < NUM_CAIXAS; i++){
                printf("Caixa %d: %d em fila | Atendimento atual ID: %d\n", 
                       caixas[i].id, caixas[i].fila.tamanho, caixas[i].cliente_atual.id);
            }
            printf("----------------------------------------\n\n"); 
        }
    }

    if (tempo >= 600) {
        printf("\nSimulacao concluida com sucesso! (Limite de 10 minutos atingido)\n");
    } else {
        printf("\nSimulacao interrompida pelo utilizador.\n");
    }

    exibirRelatorioCaixas(stdout, caixas, tempo);

    FILE *relatorio = abrirRelatorio(caminho_relatorio, sizeof(caminho_relatorio));
    if (relatorio != NULL) {
        exibirRelatorioCaixas(relatorio, caixas, tempo);
        fclose(relatorio);
        printf("Relatorio final salvo em: %s\n", caminho_relatorio);
    }

    return EXIT_SUCCESS;
}