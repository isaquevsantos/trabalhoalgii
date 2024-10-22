#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char tipoNave[30];
  int prioridade;
} regNave;

typedef struct {
  int codigo;
  char servico[40];
  int previsaoMin;
  float custo;
} regServicos;

/* --------------- FILA --------------- 

A fila é considerada vazia quando meu inicio é igual ao final da fila, ou seja, i = f -> queue is NULL
Se ela é igual ao FMax ela está cheia, neste caso devemos realocar memoria para caber todos as naves.

// como iniciar uma fila
int i , f ;
nave F[MAX] ;
i = 0;
f = 0;

--------------- FILA --------------- */

typedef struct {
  regNave nave;
  int prioridadeTemp;
  int tempoEspera; /* Tempo Estacionado na Estação*/
  int tempoServico; /* Tempo Previsto para Manutenção */
} filaEspera;












int main() {

  int tMin, dMin, tempoPrioridade, qntTipoServico, qntTipoNave, i;
  /*
  - tMIn é o tempo que a nave está na estação;
  - dMin é o tempo de descanso da equipe para iniciar a próxima manutenção;
  */

  regServicos *servico;
  regNave *nave;

  FILE *entrada;
  entrada = fopen("entrada.txt", "r");
  /* ******** Dados Padrão ******** */

  fscanf(entrada, "%d", &tempoPrioridade);
  fscanf(entrada, "%d", &dMin);
  fscanf(entrada, "%d", &qntTipoServico);

  servico = (regServicos *)malloc(qntTipoServico * sizeof(regServicos));

  /* ******** Entrada dos Serviços *********/
  for (i = 0; i < qntTipoServico; i++) {
    fscanf(entrada, "%d %s %d %f", &servico[i].codigo, servico[i].servico,
           &servico[i].previsaoMin, &servico[i].custo);
  }
  /* ------- Entrada dos Serviços ------- */

  fscanf(entrada, "%d", &qntTipoNave);

  /* ******** Tipos de Nave *********/
  nave = (regNave *)malloc(qntTipoNave * sizeof(regNave));
  for (i = 0; i < qntTipoNave; i++) {
    fscanf(entrada, "%s %d", nave[i].tipoNave, &nave[i].prioridade);
  }
  /* ------- Tipos de Nave ------- */

  /* ******** Tipos de Nave ******** */

  return 0;
}