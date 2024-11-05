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
    int *servicoSolicitado;
    int totalServicos;
    int tempoEspera;
    float custoTotal;
    int prioridade;
} naves;

/* -------------------- FUNÇÕES -------------------- */

void lerArquivoConfiguracao(const char *nomeArquivo, int *tempoPrioridade, int *dMin, regServicos **servicos, int *qntTipoServico,
                            regTipoNave **tipoNave, int *qntTipoNave, naves **nave, int *qntNaves) {
    
    FILE *entrada = fopen(nomeArquivo, "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        exit(1);
    }

    // Leitura das configurações gerais
    fscanf(entrada, "%d", tempoPrioridade); // Tempo para aumentar prioridade
    fscanf(entrada, "%d", dMin); // Tempo de descanso da equipe

    // Leitura da quantidade e alocação de serviços
    fscanf(entrada, "%d", qntTipoServico);
    *servicos = (regServicos *)malloc(*qntTipoServico * sizeof(regServicos));
    if (*servicos == NULL) {
        printf("Erro de memória ao alocar serviços!\n");
        fclose(entrada);
        exit(1);
    }

    // Leitura dos serviços
    for (int i = 0; i < *qntTipoServico; i++) {
        fscanf(entrada, "%d %s %d %f", &(*servicos)[i].codigo, (*servicos)[i].servico,
               &(*servicos)[i].previsaoMin, &(*servicos)[i].custo);
    }

    // Leitura da quantidade e alocação de tipos de nave
    fscanf(entrada, "%d", qntTipoNave);
    *tipoNave = (regTipoNave *)malloc(*qntTipoNave * sizeof(regTipoNave));
    if (*tipoNave == NULL) {
        printf("Erro de memória ao alocar tipos de nave!\n");
        free(*servicos);
        fclose(entrada);
        exit(1);
    }

    // Leitura dos tipos de nave
    for (int i = 0; i < *qntTipoNave; i++) {
        fscanf(entrada, "%s %d", (*tipoNave)[i].tipoNave, &(*tipoNave)[i].prioridade);
    }

    // Leitura das naves
    *nave = NULL;
    *qntNaves = 0;
    int nin;
    char tipo[30];

    while (fscanf(entrada, "%d %s", &nin, tipo) == 2) {
        *nave = (naves *)realloc(*nave, (*qntNaves + 1) * sizeof(naves));
        if (*nave == NULL) {
            printf("Erro de memória ao alocar naves!\n");
            free(*servicos);
            free(*tipoNave);
            fclose(entrada);
            exit(1);
        }
        (*nave)[*qntNaves].nin = nin;
        strcpy((*nave)[*qntNaves].tipoNave, tipo);
        (*nave)[*qntNaves].servicoSolicitado = NULL;
        (*nave)[*qntNaves].totalServicos = 0;
        (*nave)[*qntNaves].tempoEspera = 0;
        (*nave)[*qntNaves].custoTotal = 0.0;

        // Atribui a prioridade com base no tipo de nave
        for (int j = 0; j < *qntTipoNave; j++) {
            if (strcmp((*tipoNave)[j].tipoNave, tipo) == 0) {
                (*nave)[*qntNaves].prioridade = (*tipoNave)[j].prioridade;
                break;
            }
        }
        (*qntNaves)++;
    }

    // Fechamento do arquivo
    fclose(entrada);
}


void solicitaServico(int codNave, int codServico, int previsaoMin, naves *nave, int qntNaves) {
    for (int i = 0; i < qntNaves; i++) {
        if (nave[i].nin == codNave) {
            nave[i].servicoSolicitado = (int *)realloc(nave[i].servicoSolicitado, (nave[i].totalServicos + 1) * sizeof(int));
            if (nave[i].servicoSolicitado == NULL) {
                printf("Erro ao alocar memória para serviços!\n");
                return;
            }
            nave[i].servicoSolicitado[nave[i].totalServicos] = codServico;
            nave[i].totalServicos += 1;

            // Ordenar serviços por previsão de tempo
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

void simula(int tempoSimulacao, int *tempoRestanteSimulacao, naves *nave, regServicos *servicos, int qntNaves, int qntServicos,
            int *totalNavesAtendidas, int *totalServicosRealizados, float *valorRecebido, int *minutosSimulados) {
    ordenarFila(nave, qntNaves);
    tempoSimulacao += *tempoRestanteSimulacao;
    *minutosSimulados += tempoSimulacao;

    for (int i = 0; i < qntNaves; i++) {
        if (nave[i].totalServicos == 0)
            continue;
        for (int j = 0; j < nave[i].totalServicos; j++) {
            int codServico = nave[i].servicoSolicitado[j];
            int tempoPrevisto = 0;
            float custo = 0.0;
            for (int k = 0; k < qntServicos; k++) {
                if (servicos[k].codigo == codServico) {
                    tempoPrevisto = servicos[k].previsaoMin;
                    custo = servicos[k].custo;
                    break;
                }
            }
            if (tempoSimulacao >= tempoPrevisto) {
                tempoSimulacao -= tempoPrevisto;
                nave[i].tempoEspera += tempoPrevisto;
                nave[i].custoTotal += custo;
                *valorRecebido += custo;
                (*totalServicosRealizados)++;
            } else {
                *tempoRestanteSimulacao = tempoPrevisto - tempoSimulacao;
                return;
            }
        }
        (*totalNavesAtendidas)++;
    }
    *tempoRestanteSimulacao = tempoSimulacao;
}

void geraRelatorio(int parametro, naves *nave, int qntNaves, int totalNavesAtendidas, int totalServicosRealizados, float valorRecebido, int minutosSimulados) {
    printf("Relatório de Naves Atendidas:\n");
    printf("NIN\tTipo\tQtd Serviços\tCusto Total\n");
    ordenarFilaPorNIN(nave, qntNaves);
    for (int i = 0; i < qntNaves; i++) {
        if (nave[i].totalServicos == 0)
            continue;
        printf("%d\t%s\t%d\t%.2f\n",
               nave[i].nin,
               nave[i].tipoNave,
               nave[i].totalServicos,
               nave[i].custoTotal);
    }
    printf("\nResumo da Simulação:\n");
    printf("Minutos Simulados:\t%d\n", minutosSimulados);
    printf("Total de Naves Atendidas:\t%d\n", totalNavesAtendidas);
    printf("Total de Serviços Realizados:\t%d\n", totalServicosRealizados);
    printf("Valor Recebido:\t%.2f\n", valorRecebido);
}

void geraRelatorioPendentes(naves *nave, int qntNaves, int minutosSimulados) {
    int totalNavesPendentes = 0;
    int totalServicosPendentes = 0;
    float valorTotalPendente = 0.0;

    printf("Relatório de Naves com Serviços Pendentes:\n");
    printf("NIN\tTipo\tQtd Serviços Pendentes\tValor Total Pendentes\n");

    for (int i = 0; i < qntNaves; i++) {
        if (nave[i].totalServicos > 0) {
            int qtdServicosPendentes = nave[i].totalServicos;
            float valorPendenteNave = nave[i].custoTotal;

            printf("%d\t%s\t%d\t%.2f\n", nave[i].nin, nave[i].tipoNave, qtdServicosPendentes, valorPendenteNave);

            totalNavesPendentes++;
            totalServicosPendentes += qtdServicosPendentes;
            valorTotalPendente += valorPendenteNave;
        }
    }

    printf("\nResumo dos Serviços Pendentes:\n");
    printf("Minutos Simulados:\t%d\n", minutosSimulados);
    printf("Total de Naves na Fila:\t%d\n", totalNavesPendentes);
    printf("Total de Serviços Pendentes:\t%d\n", totalServicosPendentes);
    printf("Valor Total Pendentes:\t%.2f\n", valorTotalPendente);
}

void ordenarFilaPorNIN(naves *nave, int qntNaves) {
    for (int i = 0; i < qntNaves - 1; i++) {
        for (int j = i + 1; j < qntNaves; j++) {
            if (nave[i].nin > nave[j].nin) {
                naves temp = nave[i];
                nave[i] = nave[j];
                nave[j] = temp;
            }
        }
    }
}

/* Função para ordenar a fila de naves */
void ordenarFila(naves *nave, int qntNaves) {
  int i, j;
  naves temp;
  for (i = 0; i < qntNaves - 1; i++) {
    for (j = i + 1; j < qntNaves; j++) {
      int prioridadeA = nave[i].prioridade;
      int prioridadeB = nave[j].prioridade;
      if (prioridadeA > prioridadeB) {
        temp = nave[i];
        nave[i] = nave[j];
        nave[j] = temp;
      }
      else if (prioridadeA == prioridadeB) {
        if (nave[i].totalServicos < nave[j].totalServicos) {
          temp = nave[i];
          nave[i] = nave[j];
          nave[j] = temp;
        }
        else if (nave[i].totalServicos == nave[j].totalServicos) {
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

void aumentaPrioridadeNaves(naves *nave, int qntNaves, int tempoSimulado, int intervaloPrioridade) {
    for (int i = 0; i < qntNaves; i++) {
        // Calcula quantas vezes o intervalo de aumento de prioridade foi atingido
        int aumento = tempoSimulado / intervaloPrioridade;
        
        // Se a prioridade não é a máxima e já se passaram intervalos suficientes, aumente a prioridade
        if (nave[i].prioridade > 1 && aumento > 0) {
            nave[i].prioridade -= aumento; // Diminui o valor da prioridade
            if (nave[i].prioridade < 1) {  // Garante que a prioridade mínima seja 1
                nave[i].prioridade = 1;
            }
        }
    }

    // colocar um ordena fila aqui
}

/* ---------------------- MAIN ---------------------- */

int main() {
    int tempoPrioridade, dMin, qntTipoServico, qntTipoNave, qntNaves = 0;
    regServicos *servicos = NULL;
    regTipoNave *tipoNave = NULL;
    naves *nave = NULL;

    lerArquivoConfiguracao("entrada.txt", &tempoPrioridade, &dMin, &servicos, &qntTipoServico, &tipoNave, &qntTipoNave, &nave, &qntNaves);

    // Aqui é possível chamar as demais funções, como `simula`, etc.

    FILE *entrada = fopen("simulacao.cmd", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return 1;
    }

    switch (expression)
    {
    case n:
        /* code */
        break;
    case s:
        /* code */
        break;
    case r:
        /* code */
        break;
    case x:
        /* code */
        break;
    
    default:
        break;
    }

    // Liberação da memória
    free(servicos);
    free(tipoNave);
    free(nave);

    return 0;
}

