#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#define Nx 2
#define Ny 3
#define N (Nx*Ny)

double scalyar(std::vector<double>& y, std::vector<double>& A) {
    std::vector<double> multi(N, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            multi[i]+=A[i*N+j]*y[j];
        }
    }
    double numerator = 0;
    for (int i = 0; i < N; i++) {
        numerator += (y[i]*multi[i]);
    }
    double denominator = 0;
    for (int i = 0; i < N; i++) {
        denominator += (multi[i] * multi[i]);
    }
    return numerator/denominator;
}

void method(std::vector<double>& A, std::vector<double>& x, std::vector<double>& b) {
    std::vector<double> y(N, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            y[i]+=A[i*N + j]*x[j];
        }
        y[i]-=b[i];
    }
    double tau = scalyar(y, A);
    for (int i = 0; i < N; i++) {
        x[i]-=y[i]*tau;
    }
}

double get_test(std::vector<double>& A, std::vector<double>& x, std::vector<double>& b) {
    std::vector<double> help(N, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            help[i]+=A[i*N+j]*x[j];
        }
        help[i]-=b[i];
    }
    double numerator = 0.0, denominator = 0.0;
    for (int i = 0; i < N; i++) {
        numerator += pow(help[i], 2);
        denominator += pow(b[i], 2);
    }
    numerator = pow(numerator, 0.5);
    denominator = pow(denominator, 0.5);
    return numerator/denominator;
}

void intialize(std::vector<double>& A, std::vector<double>& b) {

    for (int i = 0; i < N; i++) {
        A[i * N + i] = -4.0;
        if (i % Nx != 0) {
            A[i * N + (i - 1)] = 1.0;
        }
        if ((i + 1) % Nx != 0) {
            A[i * N + (i + 1)] = 1.0;
        }
        if (i >= Nx) {
            A[i * N + (i - Nx)] = 1.0;
        }
        if (i < N - Nx) {
            A[i * N + (i + Nx)] = 1.0;
        }
    }
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            b[i] = (i + 63) % 50;
        }
        else {
            b[i] = -((i + 63) % 50);
        }
    }
}





void start() {
    double epsilon = 1e-5;
    std::vector<double> A(N*N, 0.0);
    std::vector<double> b(N, 0.0);
    std::vector<double> x(N, 0.0);
    intialize(A, b);
    double test = pow(10, 10);
    while (epsilon < test) {
        method(A, x, b);
        test = get_test(A, x, b);
    }
    std::cout << std::endl << "x" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl << "all is good" << std::endl;
}



int main() {
    start();
    return 0;
}
