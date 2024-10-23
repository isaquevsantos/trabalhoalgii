#include <stdio.h>
#include <stdlib.h>

/* --------------- ESTRUTURA DE DADOS --------------- */
typedef struct {
  int codigo;
  char servico[40];
  int previsaoMin;
  float custo;
} regServicos;

typedef struct {
  char tipoNave[30];
  int prioridade;
} regTipoNave;

/* Estrutura para representar uma nave */
typedef struct {
  int nin;
  char tipoNave[30];
  int *servicoSolicitado;
  int totalServicos;
  int tempoEspera;
  float custoTotal;
} naves;

/* Estrutura para a fila de espera */
typedef struct {
  naves *naves;
  int tMaxFila;
  int inicio;
  int fim;
} filaEspera;

/* Função para inicializar a fila */
void inicializarFila(filaEspera *fila, int capacidade) {
  fila->naves = (naves *)malloc(capacidade * sizeof(naves));
  fila->tMaxFila = capacidade;
  fila->inicio = 0;
  fila->fim = 0;
}

/* Função principal */
int main() {

  int tMin, dMin, tempoPrioridade, qntTipoServico, qntTipoNave, i;
  /*
  - tMin é o tempo que a nave está na estação;
  - dMin é o tempo de descanso da equipe para iniciar a próxima manutenção;
  */

  regServicos *servico;
  regTipoNave *nave;

  FILE *entrada = fopen("entrada.txt", "r");
  if (entrada == NULL) {
    printf("Erro ao abrir o arquivo de entrada.\n");
    return 1;
  }

  /* ******** Dados Padrão ******** */
  fscanf(entrada, "%d", &tempoPrioridade);
  fscanf(entrada, "%d", &dMin);
  fscanf(entrada, "%d", &qntTipoServico);

  /* Alocação de memória para os serviços */
  servico = (regServicos *)malloc(qntTipoServico * sizeof(regServicos));
  if (servico == NULL) {
    printf("Erro ao alocar memória para os serviços.\n");
    fclose(entrada);
    return 1;
  }

  /* ******** Entrada dos Serviços ******** */
  for (i = 0; i < qntTipoServico; i++) {
    fscanf(entrada, "%d %s %d %f", &servico[i].codigo, servico[i].servico, &servico[i].previsaoMin, &servico[i].custo);
  }
  /* ------- Entrada dos Serviços ------- */

  fscanf(entrada, "%d", &qntTipoNave);

  /* Alocação de memória para os tipos de nave */
  nave = (regTipoNave *)malloc(qntTipoNave * sizeof(regTipoNave));
  if (nave == NULL) {
    printf("Erro ao alocar memória para os tipos de nave.\n");
    free(servico);
    fclose(entrada);
    return 1;
  }

  /* ******** Entrada dos Tipos de Nave ******** */
  for (i = 0; i < qntTipoNave; i++) {
    fscanf(entrada, "%s %d", nave[i].tipoNave, &nave[i].prioridade);
  }
  /* ------- Entrada dos Tipos de Nave ------- */

  /* Liberação de memória e fechamento do arquivo */
  free(servico);
  free(nave);
  fclose(entrada);

  return 0;
}