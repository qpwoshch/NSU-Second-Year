#include <iostream>
#include <cmath>
#include <vector>
#include <omp.h>
#define Nx 35
#define Ny 45
#define N (Nx*Ny)
using namespace std;


double scalyar(vector<double>& y, vector<vector<double>>& A, vector<double>& multi) {
    double numerator = 0;
    double denominator = 0;

#pragma omp parallel for reduction(+:numerator, denominator)
    for (int i = 0; i < N; i++) {
        multi[i] = 0;
        for (int j = 0; j < N; j++) {
            multi[i] += A[i][j] * y[j];
        }
        numerator += y[i] * multi[i];
        denominator += multi[i] * multi[i];
    }
    return numerator/denominator;
}





void intialize(vector<vector<double>>& A, vector<double>& b) {


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
        if (i % 2 == 0) {
            b[i] = (i + 63) % 50;
        } else {
            b[i] = -(i + 63) % 50;
        }

    }
}





void start() {
    double epsilon = 1e-5;
    vector<vector<double>> A(N, vector<double>(N, 0.0));
    vector<double> b(N, 0.0);
    vector<double> x(N, 0.0);
    double  tau = 0;
    intialize(A, b);
    double test = pow(10, 10);
    vector<double> multi(N, 0);
    vector<double> y(N, 0);
    vector<double> help(N, 0);
#pragma omp parallel
    {
        while (epsilon < test) {
            double local_num = 0, local_den = 0, numerator = 0, denominator = 0;
#pragma omp single
            {
#pragma omp taskloop
                for (int i = 0; i < N; i++) {
                    y[i] = 0;
                    for (int j = 0; j < N; j++) {
                        y[i] += A[i][j] * x[j];
                    }
                    y[i] -= b[i];
                }
            }
#pragma omp single
            {
                tau = scalyar(y, A, multi);
            }
#pragma omp for
                for (int i = 0; i < N; i++) {
                    x[i] -= y[i] * tau;
                }
#pragma omp single
            {
#pragma omp taskloop
                for (int i = 0; i < N; i++) {
                    help[i] = 0;
                    for (int j = 0; j < N; j++) {
                        help[i] += A[i][j] * x[j];
                    }
                    help[i] -= b[i];
                }
            }
#pragma omp for
            for (int i = 0; i < N; i++) {
                local_num += help[i] * help[i];
                local_den += b[i] * b[i];
            }

#pragma omp critical
            {
                numerator += local_num;
                denominator += local_den;
            }

#pragma omp barrier
#pragma omp single
            test = sqrt(numerator) / sqrt(denominator);
        }
    }
//    cout << endl << "x" << endl;
//    for (int i = 0; i < N; i++) {
//        cout << x[i] << " ";
//    }
    cout << endl << "all is good" << endl;
}



int main() {
    double startTime = omp_get_wtime();
    start();
    double endTime = omp_get_wtime();
    cout << "Время выполнения: " << (endTime - startTime) << " с" << endl;
    return 0;
}
