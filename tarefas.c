#include "tarefas.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void criar_tarefa(Tarefa *tarefa, const char *categoria, const char *descricao, int prioridade) {
    strncpy(tarefa->categoria, categoria, TAM_CATEGORIA);
    remover_quebra_linha(tarefa->categoria);

    strncpy(tarefa->descricao, descricao, TAM_DESCRICAO);
    remover_quebra_linha(tarefa->descricao);

    if (prioridade < 1) {
        tarefa->prioridade = 1;
    } else if (prioridade > 10) {
        tarefa->prioridade = 10;
    } else {
        tarefa->prioridade = prioridade;
    }
}

void listar_tarefas(Tarefa *tarefas, int num_tarefas, const char *categoria) {
    int found = 0;
    for (int i = 0; i < num_tarefas; i++) {
        if (categoria == NULL || strlen(categoria) == 0 || strcmp(tarefas[i].categoria, categoria) == 0) {
            printf("Categoria: %s, Descrição: %s, Prioridade: %d\n", tarefas[i].categoria, tarefas[i].descricao, tarefas[i].prioridade);
            found = 1;
        }
    }
    if (!found) {
        printf("Nenhuma tarefa encontrada para a categoria '%s'\n", categoria);
    }
}

void salvar_tarefas_bin(Tarefa *tarefas, int num_tarefas, const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "wb");
    if (!file) {
        perror("Erro ao abrir o arquivo para salvar");
        return;
    }

    fwrite(tarefas, sizeof(Tarefa), num_tarefas, file);
    fclose(file);
}

int carregar_tarefas_bin(Tarefa *tarefas, const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "rb");
    if (!file) {
        perror("Erro ao abrir o arquivo para carregar");
        return 0;
    }

    int num_tarefas = 0;
    while (fread(&tarefas[num_tarefas], sizeof(Tarefa), 1, file)) {
        num_tarefas++;
    }

    fclose(file);
    return num_tarefas;
}

void deletar_tarefa(Tarefa *tarefas, int *num_tarefas, const char *categoria, const char *descricao) {
    int found = 0;
    for (int i = 0; i < *num_tarefas; i++) {
        if (strcmp(tarefas[i].categoria, categoria) == 0 && strcmp(tarefas[i].descricao, descricao) == 0) {
            found = 1;
            for (int j = i; j < *num_tarefas - 1; j++) {
                tarefas[j] = tarefas[j + 1];
            }
            (*num_tarefas)--;
            break;
        }
    }
    if (!found) {
        printf("Tarefa não encontrada.\n");
    } else {
        printf("Tarefa deletada com sucesso.\n");
    }
}

void exportar_tarefas_txt(Tarefa *tarefas, int num_tarefas, const char *categoria, const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo para exportar");
        return;
    }

    int found = 0;
    for (int i = 0; i < num_tarefas; i++) {
        if (categoria == NULL || strlen(categoria) == 0 || strcmp(tarefas[i].categoria, categoria) == 0) {
            fprintf(file, "Categoria: %s, Descrição: %s, Prioridade: %d\n", tarefas[i].categoria, tarefas[i].descricao, tarefas[i].prioridade);
            found = 1;
        }
    }
    if (!found) {
        fprintf(file, "Nenhuma tarefa encontrada para a categoria '%s'\n", categoria);
    }

    fclose(file);
}
