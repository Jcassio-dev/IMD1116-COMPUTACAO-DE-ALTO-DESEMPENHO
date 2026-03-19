#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

int main(int argc, char *argv[]) {
    char *opt_level = (argc > 1) ? argv[1] : "O_Desconhecido";
    
    FILE *fp = fopen("data/resultados.csv", "a");
    if (fp == NULL) {
        printf("Erro ao abrir CSV.\n");
        return 1;
    }

    printf("Rodando testes com otimização: -%s\n", opt_level);

    for (long long N = 10000000; N <= 100000000; N += 10000000) {
        double *vetor = (double *)malloc(N * sizeof(double));
        double t_inicio, t_fim;

        t_inicio = get_time();
        for (long long i = 0; i < N; i++) vetor[i] = i * 1.5;
        t_fim = get_time();
        double tempo_init = t_fim - t_inicio;

        // 2. SOMA ACUMULATIVA 
        double soma_dependente = 0.0;
        t_inicio = get_time();
        for (long long i = 0; i < N; i++) {
            soma_dependente += vetor[i];
        }
        t_fim = get_time();
        double tempo_acum = t_fim - t_inicio;

        //SOMA COM ILP 
        double soma1 = 0.0, soma2 = 0.0, soma3 = 0.0, soma4 = 0.0;
        t_inicio = get_time();
        for (long long i = 0; i < N; i += 4) {
            soma1 += vetor[i];
            soma2 += vetor[i+1];
            soma3 += vetor[i+2];
            soma4 += vetor[i+3];
        }
        double soma_ilp = soma1 + soma2 + soma3 + soma4;
        t_fim = get_time();
        double tempo_ilp = t_fim - t_inicio;

        fprintf(fp, "%s,%lld,%.6f,%.6f,%.6f\n", opt_level, N, tempo_init, tempo_acum, tempo_ilp);

        if (soma_dependente == -1.0 && soma_ilp == -1.0) {
            printf("Somas: %f %f\n", soma_dependente, soma_ilp);
        }

        free(vetor);
    }

    fclose(fp);
    return 0;
}