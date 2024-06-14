#include "tarefas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFAS 100

int main() {
    Tarefa tarefas[MAX_TAREFAS];
    int num_tarefas = 0;
    char categoria[TAM_CATEGORIA];
    char descricao[TAM_DESCRICAO];
    int prioridade;
    int opcao;

    while (1) {
        printf("1. Criar tarefa\n");
        printf("2. Listar tarefas\n");
        printf("3. Salvar tarefas\n");
        printf("4. Carregar tarefas\n");
        printf("5. Deletar tarefa\n");
        printf("6. Exportar tarefas para arquivo texto\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                if (num_tarefas >= MAX_TAREFAS) {
                    printf("Número máximo de tarefas alcançado.\n");
                    break;
                }
                printf("Digite a categoria: ");
                fgets(categoria, TAM_CATEGORIA, stdin);
                remover_quebra_linha(categoria);

                printf("Digite a descrição: ");
                fgets(descricao, TAM_DESCRICAO, stdin);
                remover_quebra_linha(descricao);

                printf("Digite a prioridade (1-10): ");
                scanf("%d", &prioridade);
                getchar();  
                
                criar_tarefa(&tarefas[num_tarefas++], categoria, descricao, prioridade);
                break;

            case 2:
                printf("Digite a categoria para listar (ou deixe vazio para listar todas): ");
                fgets(categoria, TAM_CATEGORIA, stdin);
                remover_quebra_linha(categoria);

                listar_tarefas(tarefas, num_tarefas, categoria);
                break;

            case 3:
                {
                    char nome_arquivo[100];
                    printf("Digite o nome do arquivo para salvar: ");
                    fgets(nome_arquivo, 100, stdin);
                    remover_quebra_linha(nome_arquivo);

                    salvar_tarefas_bin(tarefas, num_tarefas, nome_arquivo);
                }
                break;

            case 4:
                {
                    char nome_arquivo[100];
                    printf("Digite o nome do arquivo para carregar: ");
                    fgets(nome_arquivo, 100, stdin);
                    remover_quebra_linha(nome_arquivo);

                    num_tarefas = carregar_tarefas_bin(tarefas, nome_arquivo);
                }
                break;

            case 5:
                printf("Digite a categoria da tarefa a deletar: ");
                fgets(categoria, TAM_CATEGORIA, stdin);
                remover_quebra_linha(categoria);

                printf("Digite a descrição da tarefa a deletar: ");
                fgets(descricao, TAM_DESCRICAO, stdin);
                remover_quebra_linha(descricao);

                deletar_tarefa(tarefas, &num_tarefas, categoria, descricao);
                break;

            case 6:
                {
                    printf("Digite a categoria para exportar (ou deixe vazio para exportar todas): ");
                    fgets(categoria, TAM_CATEGORIA, stdin);
                    remover_quebra_linha(categoria);

                    char nome_arquivo[100];
                    printf("Digite o nome do arquivo texto para exportar: ");
                    fgets(nome_arquivo, 100, stdin);
                    remover_quebra_linha(nome_arquivo);

                    exportar_tarefas_txt(tarefas, num_tarefas, categoria, nome_arquivo);
                }
                break;

            case 7:
                exit(0);

            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
