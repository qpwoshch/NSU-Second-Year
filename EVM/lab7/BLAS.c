#include "cblas.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "math.h"

#define N 2048

float* init() {
    float* matrix = calloc(N*N, sizeof(float));
    return matrix;
}

float* init_single() {
    float* matrix = calloc(N*N, sizeof(float));
    for(size_t i = 0; i < N; ++i){
        matrix[i*N + i] = 1;
    }
    return matrix;
}

void transpose(const float* matrix, float* res) {
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            res[i*N + j] = matrix[j*N + i];
        }
    }
}

float max_row(const float* matrix) {
    float max = 0.0f;
    for(size_t i = 0; i < N; ++i){
        float current = 0.0f;
        for(size_t j = 0; j < N; ++j){
            current += fabs(matrix[i*N + j]);
        }
        if(current > max) max = current;
    }
    return max;
}

float max_collumn(const float* matrix) {
    float* tmp = calloc(N * N, sizeof(float));
    transpose(matrix, tmp);
    const float max = max_row(tmp);
    free(tmp);
    return max;
}

void inverse(const size_t M, float* A, float* res){
    float* B = init();
    float* R = init();
    float* I_ = init_single();
    transpose(A, B);
    cblas_sscal(N * N, 1.0f / (max_collumn(A) * max_row(A)), B, 1);
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, -1.0f, B, N, A, N, 0, R, N);
    cblas_saxpy(N * N, 1.0f, I_, 1, R, 1);
    const size_t size = N * N * sizeof(float);
    float* tmp = init_single();
    for (size_t i = 0; i < M; i++) {
        cblas_saxpy(N * N, 1.0f, tmp, 1, res, 1);
        memset(A , 0 , size);
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0f, tmp, N, R, N, 0, A, N);
        memcpy(tmp, A, size);
    }
    memset(A, 0, size);
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0f, res, N, B, N, 1.0f, A, N);
    memcpy(res, A, size);
    free(tmp);
    free(B);
    free(R);
    free(I_);
}

int main() {
    float* A = init_single();
    float* res = init_single();
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    inverse(10, A, res);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Время выполнения BLAS: %lf sec.\n", (end.tv_sec-start.tv_sec) + 0.000000001*(end.tv_nsec-start.tv_nsec));

    free(A);
    free(res);
    return 0;
}