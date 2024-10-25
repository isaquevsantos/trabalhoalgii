/******************************************
* *
* Isaque Vilela dos Santos *
* Trabalho Prático *
* Disciplina: Algoritmos e Programação II *
* Professores: Ivone e Ronaldo *
* *
******************************************/

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
/* --------------- ESTRUTURA DE DADOS --------------- */



int main() {
  int tMin, dMin, tempoPrioridade, qntTipoServico, qntTipoNave;
  int i;

  regServicos *servico;
  regTipoNave *tipoNave;
  naves *nave;
  int qntNaves = 0;

  /* Abertura do arquivo de entrada */
  FILE *entrada = fopen("entrada.txt", "r");
  if (entrada == NULL) {
    return 1;
  }

  /*
    Entrada de arquivos de configurações 
    3.1 Arquivo de Configuração 'simulacao.cfg'
  */

  fscanf(entrada, "%d", &tempoPrioridade);
  fscanf(entrada, "%d", &dMin);
  fscanf(entrada, "%d", &qntTipoServico);

  /* Alocação de memória para os serviços */
  servico = (regServicos *)malloc(qntTipoServico * sizeof(regServicos));
  if (servico == NULL) {
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
    free(servico);
    fclose(entrada);
    return 1;
  }

  /* ******** Entrada dos Tipos de Nave ******** */
  for (i = 0; i < qntTipoNave; i++) {
    fscanf(entrada, "%s %d", tipoNave[i].tipoNave, &tipoNave[i].prioridade);
  }

  /* ******** Leitura das Naves Dinamicamente ******** */
  nave = NULL;
  int nin;
  char tipo[30];
  while (fscanf(entrada, "%d %s", &nin, tipo) == 2) {
    nave = (naves *)realloc(nave, (qntNaves + 1) * sizeof(naves));
    if (nave == NULL) {
      free(servico);
      free(tipoNave);
      fclose(entrada);
      return 1;
    }
    nave[qntNaves].nin = nin;
    strcpy(nave[qntNaves].tipoNave, tipo);
    nave[qntNaves].servicoSolicitado = NULL;
    nave[qntNaves].totalServicos = 0;
    nave[qntNaves].tempoEspera = 0;
    nave[qntNaves].custoTotal = 0.0;
    qntNaves++;
  }
  /* ******** Leitura das Naves Dinamicamente ******** */

  /*
    Entrada de arquivos de configurações 
    3.1 Arquivo de Configuração 'simulacao.cfg'
  */

  /* Fechamento do arquivo */
  fclose(entrada);

  /* Liberação de memória */
  free(servico);
  free(tipoNave);
  free(nave);

  return 0;
}
