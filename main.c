#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefas.h"

#define MAX_TAREFAS 100

void menu() {
    printf("Menu de Opções:\n");
    printf("1. Adicionar Tarefa\n");
    printf("2. Listar Tarefas\n");
    printf("3. Exportar Tarefas para Arquivo de Texto\n");
    printf("4. Deletar Tarefa\n");
    printf("5. Carregar Tarefas de Arquivo Binário\n");
    printf("6. Salvar Tarefas em Arquivo Binário\n");
    printf("7. Atualizar Arquivo de Texto\n");
    printf("0. Sair\n");
}

int main() {
    Tarefa tarefas[MAX_TAREFAS];
    int num_tarefas = 0;
    int opcao;
    char categoria[TAM_CATEGORIA];
    char descricao[TAM_DESCRICAO];
    int prioridade;
    char nome_arquivo[100];

    while (1) {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1:
                printf("Digite a categoria: ");
                fgets(categoria, TAM_CATEGORIA, stdin);
                remover_quebra_linha(categoria);

                printf("Digite a descrição: ");
                fgets(descricao, TAM_DESCRICAO, stdin);
                remover_quebra_linha(descricao);

                printf("Digite a prioridade (1 a 10): ");
                scanf("%d", &prioridade);
                getchar(); 

                if (num_tarefas < MAX_TAREFAS) {
                    criar_tarefa(&tarefas[num_tarefas], categoria, descricao, prioridade);
                    num_tarefas++;
                } else {
                    printf("Número máximo de tarefas atingido.\n");
                }
                break;

            case 2:
                printf("Digite a categoria para listar (ou deixe vazio para todas): ");
                fgets(categoria, TAM_CATEGORIA, stdin);
                remover_quebra_linha(categoria);

                listar_tarefas(tarefas, num_tarefas, categoria);
                break;

            case 3:
                printf("Digite a categoria para exportar (ou deixe vazio para todas): ");
                fgets(categoria, TAM_CATEGORIA, stdin);
                remover_quebra_linha(categoria);

                exportar_tarefas_txt(tarefas, num_tarefas, categoria);
                break;

            case 4:
                printf("Digite a categoria da tarefa a ser deletada: ");
                fgets(categoria, TAM_CATEGORIA, stdin);
                remover_quebra_linha(categoria);

                printf("Digite a descrição da tarefa a ser deletada: ");
                fgets(descricao, TAM_DESCRICAO, stdin);
                remover_quebra_linha(descricao);

                deletar_tarefa(tarefas, &num_tarefas, categoria, descricao);
                atualizar_arquivo_txt(tarefas, num_tarefas);
                break;

            case 5:
                printf("Digite o nome do arquivo binário para carregar: ");
                fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
                remover_quebra_linha(nome_arquivo);

                num_tarefas = carregar_tarefas_bin(tarefas, nome_arquivo);
                atualizar_arquivo_txt(tarefas, num_tarefas); 
                break;

            case 6:
                printf("Digite o nome do arquivo binário para salvar: ");
                fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
                remover_quebra_linha(nome_arquivo);

                salvar_tarefas_bin(tarefas, num_tarefas, nome_arquivo);
                break;

            case 7:
                atualizar_arquivo_txt(tarefas, num_tarefas);
                printf("Arquivo de texto atualizado com sucesso.\n");
                break;

            case 0:
                exit(0);

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
    return 0;
}
