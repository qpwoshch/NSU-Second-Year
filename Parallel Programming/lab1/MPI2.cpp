#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h>
#include <chrono>

#define Nx 30
#define Ny 50
#define N (Nx * Ny)


double scalyar(std::vector<double>& y, std::vector<std::vector<double>>& A, std::vector<int> size, std::vector<int> shift, int rank) {
    std::vector<double> multi(N, 0);
    for (int i = 0; i < size[rank]; i++) {
        int global_index = shift[rank] + i;
        for (int j = 0; j < N; j++) {
            multi[global_index] += A[i][j] * y[j];
        }
    }

    double local_numerator = 0, local_denominator = 0;
    for (int i = 0; i < N; i++) {
        local_numerator += y[i] * multi[i];
        local_denominator += multi[i] * multi[i];
    }

    double global_numerator = 0, global_denominator = 0;
    MPI_Allreduce(&local_numerator, &global_numerator, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&local_denominator, &global_denominator, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    double global_tau = global_numerator / global_denominator;
    return global_tau;
}


void method(std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>& b, std::vector<int> size, std::vector<int> shift, int rank, int num_procs) {
    std::vector<double> y(size[rank], 0);
    for (int src = 0; src < num_procs; src++) {
        std::vector<double> local_x(size[src]);
        if (rank == src) {
            local_x = x;
        }
        MPI_Bcast(local_x.data(), size[src], MPI_DOUBLE, src, MPI_COMM_WORLD);
        for (int i = 0; i < size[rank]; i++) {
            for (int j = 0; j < size[src]; j++) {
                y[i] += A[i][shift[src] + j] * local_x[j];
            }
        }
    }
    for (int i = 0; i < size[rank]; i++) {
        y[i] -= b[i];
    }

    double tau = scalyar(y, A, size, shift, rank);
    for (int i = 0; i < size[rank]; i++) {
        x[i] -= y[i] * tau;
    }
}



double get_test(std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>& b, std::vector<int> size, std::vector<int> shift, int rank, int num_procs) {
    std::vector<double> help(size[rank], 0);
    for (int src = 0; src < num_procs; src++) {
        std::vector<double> local_x(size[src]);
        if (rank == src) {
            local_x = x;
        }
        MPI_Bcast(local_x.data(), size[src], MPI_DOUBLE, src, MPI_COMM_WORLD);
        for (int i = 0; i < size[rank]; i++) {
            for (int j = 0; j < size[src]; j++) {
                help[i] += A[i][shift[src] + j] * local_x[j];
            }
        }
    }
    for (int i = 0; i < size[rank]; i++) {
        help[i] -= b[i];
    }
    double local_numerator = 0, local_denominator = 0;
    for (int i = 0; i < size[rank]; i++) {
        local_numerator += pow(help[i], 2);
        local_denominator += pow(b[i], 2);
    }

    double global_numerator = 0, global_denominator = 0;
    MPI_Allreduce(&local_numerator, &global_numerator, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&local_denominator, &global_denominator, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    return sqrt(global_numerator) / sqrt(global_denominator);
}



void initialize(std::vector<std::vector<double>>& A, std::vector<double>& b, int size, int shift) {
    for (int i = 0; i < size; i++) {
        int global_index = i + shift;
        A[i][global_index] = -4.0;
        if (global_index % Nx != 0) {
            A[i][global_index - 1] = 1.0;
        }
        if ((global_index + 1) % Nx != 0) {
            A[i][global_index + 1] = 1.0;
        }
        if (global_index >= Nx) {
            A[i][global_index - Nx] = 1.0;
        }
        if (global_index < N - Nx) {
            A[i][global_index + Nx] = 1.0;
        }
    }

    for (int i = 0; i < size; i++) {
        if ((i+shift) % 2 == 0) {
            b[i] = (i + 63 + shift) % 50;
        } else {
            b[i] = -(i + 63 + shift) % 50;
        }
    }
}


std::vector<int> getRows(int size) {
    std::vector<int> rows(size);
    int count1 = N / size;
    int count2 = N % size;
    for (int i = 0; i < size; ++i) {
        rows[i] = count1 + (i < count2);
    }
    return rows;
}

std::vector<int> getShift(int size, std::vector<int>& rows) {
    std::vector<int> shift(size);
    int count = 0;
    for (int i = 0; i < size; i++) {
        shift[i] = count;
        count+=rows[i];
    }
    return shift;
}

void start(int rank, int size) {
    double epsilon = 1e-5;
    std::vector<int> rows = getRows(size);
    std::vector<int> shift = getShift(size, rows);
    std::vector<std::vector<double>> A(rows[rank], std::vector<double>(N, 0.0));
    std::vector<double> b(rows[rank], 0.0);
    std::vector<double> x(rows[rank], 0.0);
    initialize(A, b, rows[rank], shift[rank]);
    double test = 1e10;
    int a = 0;
    while (test > epsilon) {
        method(A, x, b, rows, shift, rank, size);
        test = get_test(A, x, b, rows, shift, rank, size);
        a++;
    }
//    std::cout << "Rank: " << rank << std::endl << "x" << std::endl;
//    for (int i = 0; i < rows[rank]; i++) {
//        std::cout << x[i] << " ";
//    }
//    std::cout << std::endl;
}



int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    auto startTime = MPI_Wtime();
    start(rank, size);
    auto endTime = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Время выполнения: " << (endTime-startTime) << " с" << std::endl;
    }
    MPI_Finalize();
    return 0;
}
