#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define N 5000000 

int main() {
    struct timespec start, end;
    double *arr = (double*) malloc(N * sizeof(double));
    double *out = (double*) malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) arr[i] = i + 1.0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double x = arr[i];
        for (int j = 0; j < 150; j++) {
            x = sqrt(x) + exp(log10(x + 1.0)) * sin(x);
        }
        out[i] = x;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double wall_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("Tempo Compute-Bound: %.5f segundos\n", wall_time);

    printf("Amostra dos resultados (primeiros 10): ");
    for (int i = 0; i < 10; i++) {
        printf("%.4f ", out[i]);
    }
    printf("\n------------------------------------\n");

    free(arr); free(out);
    return 0;
}