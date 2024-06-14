#ifndef TAREFAS_H
#define TAREFAS_H

#define TAM_CATEGORIA 50
#define TAM_DESCRICAO 100

typedef struct {
    char categoria[TAM_CATEGORIA];
    char descricao[TAM_DESCRICAO];
    int prioridade;
} Tarefa;

void remover_quebra_linha(char *str);
void criar_tarefa(Tarefa *tarefa, const char *categoria, const char *descricao, int prioridade);
void listar_tarefas(Tarefa *tarefas, int num_tarefas, const char *categoria);
void salvar_tarefas_bin(Tarefa *tarefas, int num_tarefas, const char *nome_arquivo);
int carregar_tarefas_bin(Tarefa *tarefas, const char *nome_arquivo);
void deletar_tarefa(Tarefa *tarefas, int *num_tarefas, const char *categoria, const char *descricao);
void exportar_tarefas_txt(Tarefa *tarefas, int num_tarefas, const char *categoria, const char *nome_arquivo);

#endif 
