#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "math.h"
#include "xmmintrin.h"

#define N 2048



float *init() {
    float *matrix = malloc(N*N*sizeof(float));
    memset(matrix, 0, N*N*sizeof(float));
    return matrix;
}

float *init_single() {
    float *matrix = malloc(N*N*sizeof(float));
    memset(matrix, 0, N*N*sizeof(float));
    for (size_t i = 0; i < N; ++i){
        matrix[i*N + i] = 1;
    }
    return matrix;
}

void transpose(const float *matrix, float *res) {
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < N; ++j){
            res[i*N + j] = matrix[j*N + i];
        }
    }
}

void plus(const float *matrix1, const float *matrix2, float *res) {
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j += 4){
            __m128 x = _mm_loadu_ps(&matrix1[i*N + j]);
            __m128 y = _mm_loadu_ps(&matrix2[i*N + j]);
            __m128 sum = _mm_add_ps(x, y);
            _mm_storeu_ps(&res[i*N + j], sum);
        }
    }
}

void minus(const float *matrix1, const float *matrix2, float *res) {
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j += 4){
            __m128 x = _mm_loadu_ps(&matrix1[i*N + j]);
            __m128 y = _mm_loadu_ps(&matrix2[i*N + j]);
            __m128 diff = _mm_sub_ps(x, y);
            _mm_storeu_ps(&res[i*N + j], diff);
        }
    }
}

void mul(const float* matrix1, const float* matrix2, float* res){
    memset(res, 0, N * N * sizeof(float));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            const size_t index = i*N +j;
            __m128 x = _mm_set1_ps(matrix1[index]);
            for (int k = 0; k < N; k += 4){
                __m128 result = _mm_loadu_ps(&res[i*N + k]);
                __m128 y = _mm_loadu_ps(&matrix2[j*N + k]);
                __m128 product = _mm_mul_ps(x, y);
                result = _mm_add_ps(result, product);
                _mm_storeu_ps(&res[i*N + k], result);
            }
        }
    }
}

void scalar_mul(const float *matrix, const float scalar, float *res) {
    const __m128 mmscalar = _mm_set1_ps(scalar);
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < N; j += 4){
            __m128 x = _mm_loadu_ps(&matrix[i*N + j]);
            __m128 product = _mm_mul_ps(x, mmscalar);
            _mm_storeu_ps(&res[i*N + j], product);
        }
    }
}

float max_row(const float *matrix) {
    float max = 0.0f;
    for (size_t i = 0; i < N; ++i){
        float current = 0.0f;
        for (size_t j = 0; j < N; ++j){
            current += fabs(matrix[i*N + j]);
        }
        if (current > max) max = current;
    }
    return max;
}

float max_collumn(const float *matrix) {
    float *tmp = calloc(N*N, sizeof(float));
    transpose(matrix, tmp);
    const float max = max_row(tmp);
    free(tmp);
    return max;
}

void inverse(const size_t M, float *A, float *res) {
    float *B = init();
    float *R = init();
    float *I = init_single();
    transpose(A, B);
    scalar_mul(B, 1.0f/(max_collumn(A)*max_row(A)), B);
    mul(B, A, R);
    minus(I, R, R);
    const size_t size = N*N*sizeof(float);
    float *tmp = init_single();
    for (size_t i = 0; i < M; ++i){
        plus(tmp, res, res);
        memset(A, 0, size);
        mul(tmp, R, A);
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
    float *A = init_single();
    float *res = init_single();
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    inverse(10, A, res);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Время выполнения vectorized: %lf sec.\n", (end.tv_sec-start.tv_sec) + 0.000000001*(end.tv_nsec-start.tv_nsec));
    free(A);
    free(res);
    return 0;
}