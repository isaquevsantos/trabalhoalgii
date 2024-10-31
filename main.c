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

typedef struct {
  int nin;
  char tipoNave[30];
  int* servicoSolicitado;
  int totalServicos;
  int tempoEspera;
  float custoTotal;
  int prioridade;
} naves;
/* --------------- ESTRUTURA DE DADOS --------------- */

/* -------------------- FUNÇÕES -------------------- */

/*
  Funções que preciso fazer:
    - ordenar fila; Complete 26/10
    - aumentar a prioridade das naves conforme o tempo;
    - operaçoes do arquivo de simulaçao;
*/

void solicitaServico(int codNave, int codServico, int previsaoMin, naves *nave, int qntNaves) {
  for (int i = 0; i < qntNaves; i++) {
    if (nave[i].nin == codNave) {
      nave[i].servicoSolicitado = (int *)realloc(nave[i].servicoSolicitado, (nave[i].totalServicos + 1) * sizeof(int));
      if (nave[i].servicoSolicitado == NULL) {
        return;
      }

      nave[i].servicoSolicitado[nave[i].totalServicos] = codServico;
      nave[i].totalServicos += 1;

      for (int j = nave[i].totalServicos - 1; j > 0 && nave[i].servicoSolicitado[j - 1] > previsaoMin; j--) {
        int temp = nave[i].servicoSolicitado[j];
        nave[i].servicoSolicitado[j] = nave[i].servicoSolicitado[j - 1];
        nave[i].servicoSolicitado[j - 1] = temp;
      }
      return;
    }
  }
  printf("Nave %d não encontrada!\n", codNave);
}

void simula(int tempoSimulacao) {}

void geraRelatorio(){
    /* -> parâmetro R <- */
};
void esvaziaFila(){
    /* -> parâmetro X <- */
};

void ordenarFila(naves *nave, int qntNaves) {
  int i, j;
  naves temp;

  for (i = 0; i < qntNaves - 1; i++) {
    for (j = i + 1; j < qntNaves; j++) {
      int prioridadeA = nave[i].prioridade;
      int prioridadeB = nave[j].prioridade;

      /* Primeiro por prioridade */
      if (prioridadeA > prioridadeB) {
        temp = nave[i];
        nave[i] = nave[j];
        nave[j] = temp;
      } else if (prioridadeA == prioridadeB) {
        if (nave[i].totalServicos < nave[j].totalServicos) {
          temp = nave[i];
          nave[i] = nave[j];
          nave[j] = temp;
        } else if (nave[i].totalServicos == nave[j].totalServicos) {
          /* Terceira pelo tempo de espera */
          if (nave[i].tempoEspera < nave[j].tempoEspera) {
            temp = nave[i];
            nave[i] = nave[j];
            nave[j] = temp;
          }
        }
      }
    }
  }
}

/* Função para exibir a fila de naves 

USADA PARA TESTES

void exibirFila(naves *nave, int qntNaves) {
  printf("\nFila de Naves Ordenada:\n");
  for (int i = 0; i < qntNaves; i++) {
    printf("NIN: %d, Tipo: %s, Prioridade: %d, Total de Serviços: %d, Tempo de "
           "Espera: %d, Custo Total: %.2f\n",
           nave[i].nin, nave[i].tipoNave, nave[i].prioridade,
           nave[i].totalServicos, nave[i].tempoEspera, nave[i].custoTotal);
  }
}
*/

/* -------------------- FUNÇÕES -------------------- */

int main() {
  int tMin, dMin, tempoPrioridade, qntTipoServico, qntTipoNave,
      *tempoRestanteSimulacao = 0;
  int i;
  int *tempoPassado;

  regServicos *servico;
  regTipoNave *tipoNave;
  naves *nave;
  int qntNaves = 0;

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
    fscanf(entrada, "%d %s %d %f", &servico[i].codigo, servico[i].servico,
           &servico[i].previsaoMin, &servico[i].custo);
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

    // Encontrar a prioridade da nave com base no tipo
    for (int j = 0; j < qntTipoNave; j++) {
      if (strcmp(tipoNave[j].tipoNave, tipo) == 0) {
        nave[qntNaves].prioridade = tipoNave[j].prioridade;
        break;
      }
    }
    qntNaves++;
  }

  /* ******** Leitura das Naves Dinamicamente ******** */

  /* Exibir a fila -> Usada para testes
  exibirFila(nave, qntNaves);
  /* Exibir a fila -> Usada para testes */


  /* Fechamento do arquivo */
  fclose(entrada);

  /* Liberação de memória */
  free(servico);
  free(tipoNave);
  free(nave);

  return 0;
}
