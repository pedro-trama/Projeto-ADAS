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

//Protótipo das funções

//Função que recebe a matriz de sensores frontais e extrai a mediana
void fusaoSensores(int n, float sensores[n][3], float process[n][2]);

//Função que calcula a distancia de frenagem para cada amostra
void calcularDistanciaSegura(int sens, float atrito, int n, float velocidades[n][2], float process[n][2]);

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

//Função Fusão de Sensores
void fusaoSensores(int n, float sensores[n][3], float process[n][2]){
    int i, j, temp;

    //Define um vetor que representa cada amostra por linha
    for (i = 0; i < n; i++){
        float vetor[3];

        //Copia os elementos da linha atual
        for (j = 0; j < 3; j++){
            vetor[j] = sensores[i][j];
        }

        //Ordena os elementos usando o método de ordenação Bubble Sort
        for (j = 0; j < 2; j++){
            if(vetor[j] > vetor[j+1]){
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }

        //Armazena a mediana na primeira coluna da matriz de processamento
        process[i][0] = vetor[1];
    }
}

//Função Cálculo de Distância Segura
void calcularDistanciaSegura(int sens, float atrito, int n, float velocidades[n][2], float process[n][2]){
    int i, j;
    float tempo_reacao, vel_kmh, vel_ms, distancia;

    //Verifica o tempo de reação conforme a sensibilidade do ADAS
    if (sens == 1){
        //1 - Esportivo
        tempo_reacao = 1.0;
    } else if(sens == 2){
        //2 - Normal
        tempo_reacao = 1.5;
    } else {
        //3 - Seguro
        tempo_reacao = 2.0;
    }
    
    //Percorre a matriz velocidades e converte cada amostra de km/h para m/s
    for (i = 0; i < n; i++){
        vel_kmh = velocidades[i][0];
        vel_ms = vel_kmh / 3.6;

        //Calcula a distância segura de frenagem
        distancia = (vel_ms * tempo_reacao) + ((vel_ms * vel_ms) / (2 * atrito * 9.81));

        //Armazena a distância na segunda coluna da matriz processamento
        process[i][1] = distancia;
    } 
}  