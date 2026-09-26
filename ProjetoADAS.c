/*
Integrantes do grupo:
Lucas Notargiacomo Mustaro - RA: 10434914
Pedro Henrique Bettega Trama - RA: 10769933

Turma: 02D11
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_AMOSTRAS (100) // Quantidade máxima de amostras
#define REGISTROS (50) // Amostras registradas aleatoriamente

int main(){
    
    //Variáveis
    
    float atrito;
    int sensibilidade;
    int op;

    //Criação das matrizes

    float velocidades[MAX_AMOSTRAS][2]; // Matriz das velocidades

    float sensores_frontais[MAX_AMOSTRAS][3]; // Matriz sensores frontais

    float sensores_laterais[MAX_AMOSTRAS][2]; // Matriz sensores laterais 

    float processamento[MAX_AMOSTRAS][2]; // Matriz processamento

    int status[MAX_AMOSTRAS][3]; // Matriz status

    //Entrada do valor do atrito
    printf("Insira o valor do atrito da via: ");
    scanf("%f", &atrito);

    //Entrada do valor de sensibilidade
    printf("Insira o valor de sensibilidade do ADAS\n");
    printf("1 - Esportivo\n");
    printf("2 - Normal\n");
    printf("3 - Seguro\n");
    scanf("%d", &sensibilidade);

    //Estrutura de repetição do-while
    do{
        //Exibição do Menu
        printf("========== MENU ==========");
        printf("1 - Carregar dados iniciais\n");
        printf("2 - Inserir nova amostra\n");
        printf("3 - Processar e exibir relatório\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        //Estrutura de decisão switch-case
        switch (op){
            //Carregar dados
            case 1:
            break;

            //Inserir nova amostra
            case 2:
            break;

            //Exibir relatório
            case 3:
            break;

            //Sair
            case 4:
                printf("Encerrando...\n");
            break;
        }

    } while (op != 4);

    return 0;
}
