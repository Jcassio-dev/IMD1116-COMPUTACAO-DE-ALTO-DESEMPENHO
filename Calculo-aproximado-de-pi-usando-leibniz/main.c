#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

double calcula_pi(long long iteracoes) {
    double pi_parcial = 0.0;
    double sinal = 1.0;

    for (long long i = 0; i < iteracoes; i++) {
        pi_parcial += sinal * (1.0 / (2.0 * i + 1.0));
        sinal = -sinal; 
    }
    
    return pi_parcial * 4.0; 
  }

int main() {
    long long testes[] = {1000, 10000, 100000, 1000000, 10000000};
    int num_testes = 5;

    FILE *fp = fopen("data/resultados.csv", "w");
    if (fp == NULL) {
        printf("Erro ao abrir CSV.\n");
        return 1;
    }

    fprintf(fp, "Iteracoes,PI_Calculado,Erro_Absoluto,Tempo\n");

    printf("Resultados do Calculo Aproximado de PI (Valor real: %.10f)\n", M_PI);
    printf("------------------------------------------------------------------\n");
    printf("%-12s | %-15s | %-15s | %-10s\n", "Iteracoes", "PI Calculado", "Erro Absoluto", "Tempo (s)");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < num_testes; i++) {
        long long iteracoes = testes[i];
        
        double tempo_inicio = get_time();
        double pi_calculado = calcula_pi(iteracoes);
        double tempo_fim = get_time();
        
        double tempo_total = tempo_fim - tempo_inicio;
        double erro = fabs(M_PI - pi_calculado); 

        printf("%-12lld | %.13f | %.13f | %.6f\n", iteracoes, pi_calculado, erro, tempo_total);
        fprintf(fp, "%lld,%.13f,%.13f,%.6f\n", iteracoes, pi_calculado, erro, tempo_total);
    }

    fclose(fp);
    return 0;
}