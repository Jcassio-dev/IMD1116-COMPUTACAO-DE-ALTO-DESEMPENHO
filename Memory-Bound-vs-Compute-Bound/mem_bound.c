#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 100000000 

int main() {
    struct timespec start, end;
    float *v1 = (float*) malloc(N * sizeof(float));
    float *v2 = (float*) malloc(N * sizeof(float));
    float *res = (float*) malloc(N * sizeof(float));

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        v1[i] = i * 1.0f;
        v2[i] = 2.0f;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        res[i] = v1[i] + (v2[i] * 0.5f); 
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double wall_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("Tempo Memory-Bound: %.5f segundos\n", wall_time);
    
    printf("Amostra dos resultados (primeiros 10): ");
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", res[i]);
    }
    printf("\n------------------------------------\n");

    free(v1); free(v2); free(res);
    return 0;
}