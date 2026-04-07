#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int eh_primo(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n = 5000000; 
    int contagem_seq = 0;
    int contagem_par = 0;
    struct timespec inicio, fim;

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 2; i <= n; i++) {
        if (eh_primo(i)) contagem_seq++;
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo_seq = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    #pragma omp parallel for reduction(+:contagem_par)
    for (int i = 2; i <= n; i++) {
        if (eh_primo(i)) contagem_par++;
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo_par = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("N maximo: %d\n", n);
    printf("Sequencial: %d primos | Tempo: %.4fs\n", contagem_seq, tempo_seq);
    printf("Paralelo:   %d primos | Tempo: %.4fs\n", contagem_par, tempo_par);
    printf("Speedup:    %.2fx\n", tempo_seq / tempo_par);

    return 0;
}