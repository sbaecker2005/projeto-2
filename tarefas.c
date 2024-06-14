#include <stdio.h>
#include <string.h>
#include "tarefas.h"

void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void criar_tarefa(Tarefa *tarefa, const char *categoria, const char *descricao, int prioridade) {
    strncpy(tarefa->categoria, categoria, TAM_CATEGORIA - 1);
    tarefa->categoria[TAM_CATEGORIA - 1] = '\0';
    strncpy(tarefa->descricao, descricao, TAM_DESCRICAO - 1);
    tarefa->descricao[TAM_DESCRICAO - 1] = '\0';
    tarefa->prioridade = (prioridade >= 1 && prioridade <= 10) ? prioridade : 1;
}

void listar_tarefas(Tarefa *tarefas, int num_tarefas, const char *categoria) {
    int found = 0;
    for (int i = 0; i < num_tarefas; i++) {
        if (strlen(categoria) == 0 || strcmp(tarefas[i].categoria, categoria) == 0) {
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Descrição: %s\n", tarefas[i].descricao);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            found = 1;
        }
    }
    if (!found) {
        printf("Nenhuma tarefa encontrada.\n");
    }
}

void exportar_tarefas_txt(Tarefa *tarefas, int num_tarefas, const char *categoria) {
    FILE *file = fopen("tarefas.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para exportação.\n");
        return;
    }
    int found = 0;
    for (int i = 0; i < num_tarefas; i++) {
        if (strlen(categoria) == 0 || strcmp(tarefas[i].categoria, categoria) == 0) {
            fprintf(file, "Categoria: %s\n", tarefas[i].categoria);
            fprintf(file, "Descrição: %s\n", tarefas[i].descricao);
            fprintf(file, "Prioridade: %d\n", tarefas[i].prioridade);
            fprintf(file, "-------------------\n");
            found = 1;
        }
    }
    if (!found) {
        fprintf(file, "Nenhuma tarefa encontrada.\n");
    }
    fclose(file);
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

int carregar_tarefas_bin(Tarefa *tarefas, const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }
    int num_tarefas = fread(tarefas, sizeof(Tarefa), MAX_TAREFAS, file);
    fclose(file);
    return num_tarefas;
}

void salvar_tarefas_bin(Tarefa *tarefas, int num_tarefas, const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(tarefas, sizeof(Tarefa), num_tarefas, file);
    fclose(file);
}

void atualizar_arquivo_txt(Tarefa *tarefas, int num_tarefas) {
    exportar_tarefas_txt(tarefas, num_tarefas, "");
}
