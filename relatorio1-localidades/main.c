#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calcular_tempo(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
}

int main() {
    int n_min = 100, n_max = 5000, passo = 100;
    struct timespec start, end;

    FILE *fp = fopen("data/resultados.csv", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    fprintf(fp, "N,TempoLinha,TempoColuna\n");

    printf("Iniciando testes de performance...\n");

    for (int N = n_min; N <= n_max; N += passo) {
        double **matriz = (double **)malloc(N * sizeof(double *));
        for (int i = 0; i < N; i++) {
            matriz[i] = (double *)malloc(N * sizeof(double));
        }
        double *vetor = (double *)malloc(N * sizeof(double));
        double *resultado = (double *)malloc(N * sizeof(double));

        for (int i = 0; i < N; i++) {
            vetor[i] = (double)rand() / RAND_MAX;
            for (int j = 0; j < N; j++) {
                matriz[i][j] = (double)rand() / RAND_MAX;
            }
        }

        // TESTE 1: ACESSO POR LINHAS
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < N; i++) {
            resultado[i] = 0;
            for (int j = 0; j < N; j++) {
                resultado[i] += matriz[i][j] * vetor[j];
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double tempo_linha = calcular_tempo(start, end);

        // TESTE 2: ACESSO POR COLUNAS
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < N; i++) resultado[i] = 0;
        
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                resultado[i] += matriz[i][j] * vetor[j];
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double tempo_coluna = calcular_tempo(start, end);

        fprintf(fp, "%d,%.6f,%.6f\n", N, tempo_linha, tempo_coluna);
        printf("N = %d | Linha: %.6fs | Coluna: %.6fs\n", N, tempo_linha, tempo_coluna);

        for (int i = 0; i < N; i++) free(matriz[i]);
        free(matriz);
        free(vetor);
        free(resultado);
    }

    fclose(fp);
    printf("Testes concluídos! Dados salvos em 'resultados.csv'.\n");

    return 0;
}