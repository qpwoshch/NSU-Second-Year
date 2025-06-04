#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

#define Nx 35
#define Ny 45
#define N (Nx * Ny)

using namespace std;

double scalar(vector<double>& y, vector<vector<double>>& A, vector<double>& multi) {
#pragma omp parallel for schedule(dynamic, 4)
    for (int i = 0; i < N; i++) {
        multi[i] = 0;
        for (int j = 0; j < N; j++) {
            multi[i] += A[i][j] * y[j];
        }
    }

    double local_numerator = 0, local_denominator = 0;
#pragma omp parallel for schedule(dynamic, 4) reduction(+:local_numerator, local_denominator)
    for (int i = 0; i < N; i++) {
        local_numerator += y[i] * multi[i];
        local_denominator += multi[i] * multi[i];
    }
    return local_numerator / local_denominator;
}

void method(vector<vector<double>>& A, vector<double>& x, vector<double>& b) {
    vector<double> y(N, 0);
    vector<double> multi(N, 0);

#pragma omp parallel for schedule(dynamic, 4)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
        y[i] -= b[i];
    }

    double tau = scalar(y, A, multi);

#pragma omp parallel for schedule(dynamic, 4)
    for (int i = 0; i < N; i++) {
        x[i] -= y[i] * tau;
    }
}

double get_test(vector<vector<double>>& A, vector<double>& x, vector<double>& b) {
    vector<double> help(N, 0);

#pragma omp parallel for schedule(dynamic, 4)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            help[i] += A[i][j] * x[j];
        }
        help[i] -= b[i];
    }

    double local_numerator = 0, local_denominator = 0;
#pragma omp parallel for schedule(dynamic, 4) reduction(+:local_numerator, local_denominator)
    for (int i = 0; i < N; i++) {
        local_numerator += pow(help[i], 2);
        local_denominator += pow(b[i], 2);
    }
    return sqrt(local_numerator) / sqrt(local_denominator);
}

void initialize(vector<vector<double>>& A, vector<double>& b) {
    for (int i = 0; i < N; i++) {
        A[i][i] = -4.0;
        if (i % Nx != 0) {
            A[i][i - 1] = 1.0;
        }
        if ((i + 1) % Nx != 0) {
            A[i][i + 1] = 1.0;
        }
        if (i >= Nx) {
            A[i][i - Nx] = 1.0;
        }
        if (i < N - Nx) {
            A[i][i + Nx] = 1.0;
        }
        if (i%2 == 0) {
            b[i] = (i+63) % 50;
        }
        else {
            b[i] = -(i+63) % 50;
        }
    }
}

void start() {
    double epsilon = 1e-5;
    vector<vector<double>> A(N, vector<double>(N, 0.0));
    vector<double> b(N, 0.0);
    vector<double> x(N, 0.0);

    initialize(A, b);
    double test = 1e10;
    while (test > epsilon) {
        method(A, x, b);
        test = get_test(A, x, b);
    }
//    std::cout << std::endl << "x" << std::endl;
//    for (int i = 0; i < N; i++) {
//        std::cout << x[i] << " ";
//    }
//    std::cout << std::endl;
    std::cout << "All is good" << std::endl;
}

int main() {
    double startTime = omp_get_wtime();
    start();
    double endTime = omp_get_wtime();
    cout << "Время выполнения: " << (endTime - startTime) << " с" << endl;
    return 0;
}
