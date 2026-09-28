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
void fusaoSensores(int n, float sensores_frontais[n][3], float processamento[n][2]);

//Função que calcula a distancia de frenagem para cada amostra
void calcularDistanciaSegura(int sens, float atrito, int n, float velocidades[n][2], float processamento[n][2]);

//Função qua analisa as faixas esquerda e direita
void assistenteFaixa(int n, float velocidades[n][2], float sensores_laterais[n][2], int status[n][3]);

//Função que inicializa as matrizes com 50 registros aleatórios
void carregarDados(int n, float velocidades[n][2], float sensores_frontais[n][3], float sensores_laterais[n][2], float processamento[n][2], int status[n][3]);

//Função que compara a velocidade relativa e verifica se há risco de colisão
void analiseRiscoFrontal(int n, float velocidades[n][2], float processamento[n][2], int status[n][3]);

//Função que exibe o relatório
void exibirRelatorio(int n, float velocidades[n][2], float sensores_frontais[n][3], float sensores_laterais[n][2], float processamento[n][2], int status[n][3]);

//Função principal do programa
int main(){
    
    //Variáveis
    
    float atrito;
    int sensibilidade;
    int op;
    int quantidade_amostras = 0;

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
                carregarDados(REGISTROS, velocidades, sensores_frontais, sensores_laterais, processamento, status);

                quantidade_amostras = REGISTROS;
                
            break;

            //Inserir nova amostra
            case 2:

                if(quantidade_amostras < MAX_AMOSTRAS) {

                    // Velocidades
                    scanf("%f", &velocidades[quantidade_amostras][0]);
                    scanf("%f", &velocidades[quantidade_amostras][1]);

                    // Sensores frontais
                    scanf("%f", &sensores_frontais[quantidade_amostras][0]);
                    scanf("%f", &sensores_frontais[quantidade_amostras][1]);
                    scanf("%f", &sensores_frontais[quantidade_amostras][2]);

                    // Sensores laterais
                    scanf("%f", &sensores_laterais[quantidade_amostras][0]);
                    scanf("%f", &sensores_laterais[quantidade_amostras][1]);

                    // Aumenta a quantidade de amostras
                    quantidade_amostras++;
                 }
                
            break;

            //Processar e Exibir relatório
            case 3:

                if(quantidade_amostras > 0) {
                fusaoSensores(quantidade_amostras, sensores_frontais, processamento);
                calcularDistanciaSegura(sensibilidade, atrito, quantidade_amostras, velocidades, processamento);
                assistenteFaixa(quantidade_amostras, velocidades, sensores_laterais, status);
                analiseRiscoFrontal(quantidade_amostras, velocidades, processamento, status);
                exibirRelatorio(quantidade_amostras, velocidades, sensores_frontais, sensores_laterais, processamento, status);
            break;

                }

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

//Função Assistente de Faixa Dinâmico
void assistenteFaixa(int n, float velocidades[n][2], float sensores_laterais[n][2], int status[n][3]) {
    int i;
    float margem; // Margem mínima de segurança

    //Percorre por todas as amostras de velocidade
    for (i = 0; i < n; i++) {
        margem = 0.50;
        if (velocidades[i][0] > 80.0) {
            // Cálculo da margem mínima de segurança com a soma de margem exigida quando velocidade > 80.0
            margem = margem + (velocidades[i][0] - 80.0) * 0.01; 
        }
// Avaliação da Faixa Esquerda
        if (sensores_laterais[i][0] < margem) {

            //Perigo de invasão
            status[i][1] = 2;
        }
        else if (sensores_laterais[i][0] < margem + 0.20) {

            //Atenção
            status[i][1] = 1;
        }
        else {

        //Situação normal
        status[i][1] = 0;
        }

// Avaliação da Faixa Direita
        if (sensores_laterais[i][1] < margem) {

            //Perigo de invasão
            status[i][2] = 2;
        }
        else if (sensores_laterais[i][1] < margem + 0.20) {

            //Atenção
            status[i][2] = 1;
        }
        else {

        //Situação normal
        status[i][2] = 0;
        }
    }
// Função que carrega os 50 registros aleatórios
void carregarDados(int n, float velocidades[n][2], float sensores_frontais [n][3], float sensores_laterais[n][2], float processamento[n][2], int status[n][3]) {
    int i;

    //Percorre os 50 registros
    for (i = 0; i < n; i++) {

        // Registros das velocidades

        //Velocidade atual entre 30 km/h e 120 km/h
        velocidades[i][0] = rand() % 91 + 30;

        //Velocidade do veículo à frente entre 30 km/h e 120 km/h
        velocidades[i][1] = rand() % 91 + 30;

        // Registros de sensores frontais

        //Radar entre 5 e 50 metros
        sensores_frontais[i][0] = rand() % 46 + 5.0;

        //Lidar entre 5 e 50 metros
        sensores_frontais[i][1] = rand() % 46 + 5.0;

        //Câmera entre 5 e 50 metros
        sensores_frontais[i][2] = rand() % 46 + 5.0;

        // Registros de sensores laterais

        //Faixa Esquerda entre 0.20 e 1.50 metros
        sensores_laterais[i][0] = (rand() % 131) / 100.0 + 0.20;

        //Faixa Direita entre 0.20 e 1.50 metros
        sensores_laterais[i][1] = (rand() % 131) / 100.0 + 0.20;

        // Matriz de processamento
        processamento[i][0] = 0.0;
        processamento[i][1] = 0.0;

        // Matriz de status
        status[i][0] = 0;
        status[i][1] = 0;
        status[i][2] = 0;
    }
}

//Função Análise de Risco Frontal
void analiseRiscoFrontal(int n, float velocidades[n][2], float processamento[n][2], int status[n][3]){
    int i;
    float vel_relativa;

    //Percorre a matriz velocidades e calcula a velocidade relativa
    for (i = 0; i < n; i ++){
        vel_relativa = velocidades[i][0] - velocidades[i][1];

        //Percorre a matriz processamento e compara a distância validada com a distância segura em caso de aproximação

        //Status 0 - Seguro
        if (vel_relativa <= 0 || processamento[i][0] >= processamento[i][1]){
            status[i][0] = 0;
        }
        //Status 1 - Atenção
        else if(processamento[i][0] < processamento[i][1] && processamento[i][0] >= (0.5 * processamento[i][1])){
            status[i][0] = 1;
        } 
        else {
        //Status 2 - Risco de Colisão
            status[i][0] = 2;
        }
    }
}

//Função que exibe o relatório final
void exibirRelatorio(int n, float velocidades[n][2], float sensores_frontais[n][3], float sensores_laterais[n][2], float processamento[n][2], int status[n][3]){
    int i = 0;

    //Imprime os dados de entrada
    for (i = 0; i < n; i++){
        printf("========== AMOSTRA %d ==========", i);

        //Matriz velocidades
        printf("Velocidade atual: %.1f km/h\n", velocidades[i][0]);
        printf("Velocidade do veículo à frente: %.1f km/h\n", velocidades[i][1]);

        //Matriz sensores frontais
        pritnf("Leitura do Radar: %.1f m\n", sensores_frontais[i][0]);
        printf("Leitura do Lidar: %.1f m\n", sensores_frontais[i][1]);
        printf("Leitura da Câmera: %.1f m/\n", sensores_frontais[i][2]);

        //Matriz sensores laterais
        printf("Distância da faixa esquerda: %.1f m\n", sensores_laterais[i][0]);
        printf("Distância da faixa direita: %.1f m\n", sensores_laterais[i][1]);

        //Matriz processamento
        printf("Distância validada: %.1f m\n", processamento[i][0]);
        printf("Distância segura exigida: %.1f m\n", processamento[i][1]);

        //Matris status
        //Status frontal
        if (status[i][0] == 1){
            printf("Status: SEGURO\n");
        } 
        else if (status[i][0] == 2){
            printf("Status: ATENÇÃO\n");
        } 
        else {
            printf("Status: RISCO DE COLISÃO (AEB ACIONADO)\n");
        }

        //Faixas esquerda e direita

        //Faixa esquerda
        if (status[i][1] == 0){
            printf("Faixa Esquerda: NORMAL\n");
        } 
        else if(status[i][1] == 1){
            printf("Faixa Esquerda: ATENÇÃO\n");
        } 
        else {
            printf("Faixa Esquerda: PERIGO DE INVASÃO\n");
        }

        //Faixa direita
        if (status[i][2] == 0){
            printf("Faixa Direita: NORMAL\n");
        } 
        else if (status[i][2] == 1){
            printf("Faixa Direita: ATENÇÃO\n");
        } 
        else {
            printf("Faixa Direita: PERIGO DE INVASÃO\n");
        }

        //Decisão Geral do Sistema
        if ((status[i][0] == 2) || (status[i][1] == 2) || (status[i][2] == 2)){
            printf("STATUS GERAL: INTERVENÇÃO CRIÍTICA EXIGIDA\n");
        } 
        else if ((status[i][0] == 1) || (status[i][1] == 1) || (status[i][2] == 1)){
            printf("STATUS GERAL: ATENÇÃO\n");
        }
        else {
            printf("STATUS GERAL: NORMAL\n");
        }
    }
}
