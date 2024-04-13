#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, exportar, salvar}; 

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = gerenciarArquivo(tarefas, &pos, "tarefas.bin", 2); 
    if(erro != OK)
        pos = 0;

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Exportar tarefas para arquivo de texto\n"); 
        printf("5 - Salvar tarefas em arquivo binário\n"); 
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer(); 
        opcao--;
        if(opcao > 5) 
            printf("Opcao invalida\n");
        else if(opcao >= 0 && opcao <= 5)
            fs[opcao](tarefas, &pos);
        else if (opcao == 5) {
            erro = gerenciarArquivo(tarefas, &pos, "tarefas.bin", 1); 
            if (erro != OK)
                printf("Erro ao salvar tarefas.\n");
        } else
            printf("Sair...\n");

    } while(opcao >= 0 && opcao <= 5);

    return 0;
}
