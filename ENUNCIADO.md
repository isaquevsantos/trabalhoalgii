
Esse projeto é um trabalho de simulação em C para a disciplina de Algoritmos e Programação II. O objetivo é simular o funcionamento de uma Estação de Manutenção Galáctica, onde naves de diferentes tipos e prioridades são atendidas para reparos e manutenções.

Requisitos:
Simulação de Manutenção:

As naves chegam à estação e solicitam um ou mais serviços, que são realizados por uma equipe de técnicos.
As naves são organizadas na fila com base em critérios de prioridade (tipo de nave, tempo previsto de manutenção e ordem de chegada).
O serviço de menor duração é priorizado para cada nave, e após sua conclusão, a nave é realocada na fila se houver mais serviços pendentes.
A equipe descansa por um tempo D minutos após concluir o trabalho em uma nave.
Priorização:

Naves militares ou de defesa têm prioridade sobre naves comerciais.
Naves com maior tempo previsto de manutenção têm prioridade se houver empate na prioridade de tipo de nave.
O desempate é feito pela ordem de chegada se outros critérios ainda estiverem iguais.
A prioridade das naves aumenta a cada T minutos que permanecem na fila.
Entradas e Comandos:

Arquivo de configuração: contém informações dos serviços, tipos de naves e dados das naves.
Comandos para controlar a simulação:
s <i>: avança a simulação por i minutos.
n <i> s <j>: adiciona o serviço j à nave i.
r <i>: gera um relatório (1 para naves atendidas, 2 para pendentes).
x: avança a simulação até esvaziar a fila de atendimento.
Relatórios:

R1: Mostra as naves atendidas com identificação, tipo, quantidade e custo total dos serviços realizados.
R2: Lista as naves pendentes com identificação, tipo, quantidade e custo dos serviços restantes.
Relatório Geral: Gera um resumo final com dados do tempo de simulação, serviços realizados, tempo de ancoragem das naves, etc.
Implementação:

É necessário implementar estruturas para armazenar dados como serviços, naves, e filas de atendimento.
A simulação deve utilizar estruturas de dados apropriadas para gerenciar a fila de atendimento e priorização dinâmica das naves.
As funções de processamento de comandos e geração de relatórios devem seguir o formato especificado.
A implementação requer um bom entendimento de manipulação de arquivos, estruturas de dados e algoritmos de ordenação e simulação em C. Como próximo passo, você pode começar pela definição das estruturas de dados e funções principais, como a leitura do arquivo de configuração e a execução dos comandos da simulação.