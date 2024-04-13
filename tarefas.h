#ifndef TAREFAS_H
#define TAREFAS_H

#define TAMANHO_CATEGORIA 100
#define TAMANHO_DESCRICAO 300
#define TOTAL 100

#include <stdio.h>

typedef struct {
    int prioridade;
    char categoria[TAMANHO_CATEGORIA];
    char descricao[TAMANHO_DESCRICAO];
    char estado[20]; 
} Tarefa;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER, PRIORIDADE_INVALIDA, OPERACAO_INVALIDA} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS exportar(Tarefa tarefas[], int *pos);

ERROS gerenciarArquivo(Tarefa tarefas[], int *pos, char* nomeArquivo, int operacao);

void clearBuffer();

#endif
