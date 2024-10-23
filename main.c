#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* Função principal */
int main() {

  int tMin, dMin, tempoPrioridade, qntTipoServico, qntTipoNave, i, j;
  /*
  - tMin é o tempo que a nave está na estação;
  - dMin é o tempo de descanso da equipe para iniciar a próxima manutenção;
  */

  regServicos *servico;
  regTipoNave *tipoNave;
  naves *nave;
  int qntNaves;

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

  fscanf(entrada, "%d", &qntTipoNave);

  /* Alocação de memória para os tipos de nave */
  tipoNave = (regTipoNave *)malloc(qntTipoNave * sizeof(regTipoNave));
  if (tipoNave == NULL) {
    printf("Erro ao alocar memória para os tipos de nave.\n");
    free(servico);
    fclose(entrada);
    return 1;
  }

  /* ******** Entrada dos Tipos de Nave ******** */
  for (i = 0; i < qntTipoNave; i++) {
    fscanf(entrada, "%s %d", tipoNave[i].tipoNave, &tipoNave[i].prioridade);
  }

  /* ******** Leitura das Naves ******** */
  fscanf(entrada, "%d", &qntNaves);
  nave = (naves *)malloc(qntNaves * sizeof(naves));
  if (nave == NULL) {
    printf("Erro ao alocar memória para as naves.\n");
    free(servico);
    free(tipoNave);
    fclose(entrada);
    return 1;
  }

  for (i = 0; i < qntNaves; i++) {
    fscanf(entrada, "%d %s", &nave[i].nin, nave[i].tipoNave);
    nave[i].servicoSolicitado = NULL;
    nave[i].totalServicos = 0;
    nave[i].tempoEspera = 0;
    nave[i].custoTotal = 0.0;
  }

  /* Fechamento do arquivo */
  fclose(entrada);

  /* ******** Saída dos Dados Lidos ******** */
  printf("Dados Padrão:\n");
  printf("Tempo Prioridade: %d\n", tempoPrioridade);
  printf("Tempo Descanso: %d\n", dMin);
  printf("\n");

  printf("Serviços Disponíveis:\n");
  for (i = 0; i < qntTipoServico; i++) {
    printf("Código: %d, Serviço: %s, Previsão (min): %d, Custo: %.2f\n",
           servico[i].codigo, servico[i].servico, servico[i].previsaoMin, servico[i].custo);
  }
  printf("\n");

  printf("Tipos de Nave:\n");
  for (i = 0; i < qntTipoNave; i++) {
    printf("Tipo: %s, Prioridade: %d\n", tipoNave[i].tipoNave, tipoNave[i].prioridade);
  }
  printf("\n");

  printf("Naves:\n");
  for (i = 0; i < qntNaves; i++) {
    printf("NIN: %d, Tipo de Nave: %s\n", nave[i].nin, nave[i].tipoNave);
  }

  /* Liberação de memória */
  free(servico);
  free(tipoNave);
  free(nave);

  return 0;
}
