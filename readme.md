# Supermercado Preco Bom

Simulador de operacao de um supermercado desenvolvido em linguagem C.

## Integrantes

| Alunos |
| ---  |
| Bernardo Francisco Coelho Fernandes  |
| Elias Felipe da Silva  |
| Jardhel |
| Pedro Lucas|

## Objetivo

O projeto tem como objetivo simular a rotina de um supermercado. A proposta
inclui o fluxo de clientes, carrinhos, produtos, estoque, prateleiras, filas e
caixas de atendimento.

Ao final da execucao, o programa deve gerar um relatorio consolidado da
atividade realizada durante a simulacao.

# Regras da Simulação (POC)

> Pode mudar

## 1. Caixas de atendimento

O supermercado deverá possuir **6 caixas de atendimento**.

Alguns caixas aleatórios devem ficar momentaneamente **inoperantes**.

---

## 2. Pilha de carrinhos

A pilha de carrinhos deve ser gerada de forma randômica.

Deve existir a possibilidade de retirar um carrinho da pilha.

---

## 3. Cliente

O cliente deve conseguir realizar suas compras.

Os dados da lista de compras dos clientes devem ser gerados de forma randômica.

- Deve conseguir usar uma lista de produtos.
- Entrar na fila para atendimento em um dos caixas disponíveis.
- Os clientes devem ser atendidos conforme a ordem de chegada à fila.

---

## 4. Resultados da simulação

Ao final da execução, o programa deverá exibir:

- O tempo total gasto na simulação;
- A quantidade de clientes atendidos por cada caixa;
- O total de mercadorias processadas em cada caixa;
- O programa deve gerar um `.txt` com um relatório final da execução;
- O programa deve rodar por no mínimo **10 minutos**.

---

## 5. Produtos e prateleiras

O produto deve ser gerado aleatoriamente contendo:

- EAN;
- Nome;
- Preço;
- Peso;
- Tipo.

O relatório deve considerar a diferença de produtos.

### Matrizes de prateleiras

- Cliente deve "andar" pelas prateleiras.

### Estoque de produtos

- Gerar estoque de produtos;
- Múltiplas prateleiras;
- Considerar tipo de produto para organização:
  - Alimento;
  - Limpeza;
  - Bebidas;
- Número limitado de produtos.

## Funcionalidades Implementadas

Esta etapa do projeto implementa a base dos caixas de atendimento:

- Inicializacao de 6 caixas configuraveis.
- Alternancia aleatoria entre os estados operante e inoperante.
- Retorno dos caixas apos um intervalo interno aleatorio.
- Exibicao periodica do estado dos caixas no terminal.
- Encerramento manual ao pressionar `Q`.
- Geracao do resumo final em `build/relatorios/`.

Clientes, carrinhos, filas, estoque, produtos e prateleiras ainda serao
incorporados nas proximas etapas. A duracao minima obrigatoria de 10 minutos
tambem ainda nao e bloqueada pelo programa: nesta etapa, `Q` encerra a
simulacao a qualquer momento.

## Estrutura Do Projeto

```text
supermercado_precobom/
|-- src/                    # Arquivos-fonte em C
|-- include/                # Cabecalhos e configuracoes
|-- build/                  # Objetos e executavel gerados pelo compilador
|-- docs/                   # Documentacao complementar
|-- lib/                    # Bibliotecas externas
|-- tests/                  # Testes automatizados
|-- Makefile                # Automacao da compilacao
|-- regrasdesimulação.txt   # Regras da atividade
`-- readme.md               # Documentacao principal
```

## Compilacao E Execucao

### Requisitos

- Windows
- GCC com MinGW
- GNU Make disponibilizado pelo comando `mingw32-make`

### Comandos

Compile o projeto:

```powershell
mingw32-make
```

Compile e execute:

```powershell
mingw32-make run
```

Remova os arquivos de compilacao:

```powershell
mingw32-make clean
```

## Uso

A simulacao avanca em tempo real. Durante a execucao, pressione `Q` para
encerrar e gerar o relatorio final.

O estado dos caixas aparece periodicamente no terminal. Quando um caixa fica
inoperante, a mensagem informa que o retorno acontecera em breve, sem expor o
intervalo aleatorio utilizado internamente.


### Testes Isolados
## Teste pilhas carrinhos
Para testar o funcionamento independente da estrutura de Carrinhos (Pilha LIFO) sem precisar iniciar toda a simulação do supermercado, utilize os comandos abaixo:

1. Certifique-se de ter a pasta `build` criada no diretório raiz:
   ```bash
   mkdir build

2. Compile o arquivo de testes
gcc tests/test_pilha.c src/pilha_carrinhos.c -Iinclude -o build/test_pilha.exe
3. Execute o teste gerado:
.\build\test_pilha.exe
## Configuracao

Os valores ajustaveis ficam em `include/config.h`:

| Constante | Finalidade |
| --- | --- |
| `NUM_CAIXAS` | Quantidade de caixas |
| `TEMPO_MIN_ATE_INOPERANCIA` | Menor intervalo ate um caixa parar |
| `TEMPO_MAX_ATE_INOPERANCIA` | Maior intervalo ate um caixa parar |
| `TEMPO_MIN_INOPERANTE` | Menor duracao da indisponibilidade |
| `TEMPO_MAX_INOPERANTE` | Maior duracao da indisponibilidade |
| `INTERVALO_EXIBICAO_STATUS` | Intervalo entre atualizacoes no terminal |

## Relatorio Final

Ao executar o programa pela pasta `build` e encerrar corretamente com `Q`, o
programa cria um arquivo com nome similar a
`build/relatorios/simulacao_20260530_142500.txt`.

O resumo apresenta:

- Tempo total da simulacao.
- Quantidade de vezes que cada caixa ficou inoperante.
- Tempo total de indisponibilidade de cada caixa.
- Quantidade de clientes atendidos por caixa.
- Quantidade de produtos processados por caixa.

Enquanto a logica de clientes ainda nao estiver implementada, os dois ultimos
valores permanecerao zerados.
