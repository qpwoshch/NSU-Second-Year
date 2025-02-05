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

void plus(const float* matrix1, const float* matrix2, float* res) {
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            res[i*N + j] = matrix1[i*N + j] + matrix2[i*N + j];
        }
    }
}

void minus(const float* matrix1, const float* matrix2, float* res) {
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            res[i*N + j] = matrix1[i*N + j] - matrix2[i*N + j];
        }
    }
}

void mul(const float* matrix1, const float* matrix2, float* res) {
    memset(res, 0, N * N * sizeof(float));
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            const size_t index = i*N +j;
            for(size_t k = 0; k < N; ++k){
                res[i*N + k] += matrix1[index] * matrix2[j*N + k];
            }
        }
    }
}

void scalar_mul(const float* matrix, const float scalar, float* res) {
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            res[j*N + i] = matrix[j*N + i] * scalar;
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
    float* I = init_single();
    transpose(A, B);
    scalar_mul(B, 1.0f / (max_collumn(A) * max_row(A)), B);
    mul(B, A, R);
    minus(I, R, R);
    const size_t size = N * N * sizeof(float);
    float* tmp = init_single();
    for (size_t i = 0; i < M; ++i) {
        plus(tmp, res, res);
        memset(A, 0, size);
        mul(tmp,R, A);
        memcpy(tmp, A, size);
    }
    memset(A, 0, size);
    mul(res, B, A);
    memcpy(res, A, size);
    free(tmp);
    free(B);
    free(R);
    free(I);
}

int main() {
    float* A = init_single();
    float* res = init_single();
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    inverse(10, A, res);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Время выполнения default: %lf sec.\n", (end.tv_sec-start.tv_sec) + 0.000000001*(end.tv_nsec-start.tv_nsec));
    free(A);
    free(res);
    return 0;
}