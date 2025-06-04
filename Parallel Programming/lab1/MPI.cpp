#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h>

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


void method(std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>& b, std::vector<int> size, std::vector<int> shift, int rank) {
    std::vector<double> mpi_x(N, 0);
    MPI_Allgatherv(x.data() + shift[rank], size[rank], MPI_DOUBLE, mpi_x.data(), size.data(), shift.data(), MPI_DOUBLE, MPI_COMM_WORLD);
    std::vector<double> y(N, 0);
    for (int i = 0; i < size[rank]; i++) {
        int global_index = shift[rank] + i;
        for (int j = 0; j < N; j++) {
            y[global_index] += A[i][j] * mpi_x[j];
        }
        y[global_index] -= b[global_index];
    }
    double tau = scalyar(y, A, size, shift, rank);
    for (int i = 0; i < size[rank]; i++) {
        x[i+shift[rank]] -= y[i+shift[rank]] * tau;
    }
}


double get_test(std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>& b, std::vector<int> size, std::vector<int> shift, int rank) {
    std::vector<double> help(N, 0);
    std::vector<double> mpi_x(N, 0);
    MPI_Allgatherv(x.data() + shift[rank], size[rank], MPI_DOUBLE, mpi_x.data(), size.data(), shift.data(), MPI_DOUBLE, MPI_COMM_WORLD);
    for (int i = 0; i < size[rank]; i++) {
        int global_index = i + shift[rank];
        for (int j = 0; j < N; j++) {
            help[global_index] += A[i][j] * mpi_x[j];
        }
        help[global_index] -= b[global_index];
    }
    double local_numerator = 0, local_denominator = 0;
    for (int i = 0; i < N; i++) {
        local_numerator += pow(help[i], 2);
        local_denominator += pow(b[i], 2);
    }
    double global_numerator = 0, global_denominator = 0;
    MPI_Allreduce(&local_numerator, &global_numerator, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&local_denominator, &global_denominator, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    double global_test = sqrt(global_numerator) / sqrt(global_denominator);

    return global_test;
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

    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            b[i] = (i + 63) % 50;
        } else {
            b[i] = -(i + 63) % 50;
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
    std::vector<double> b(N, 0.0);
    std::vector<double> x(N, 0.0);
    initialize(A, b, rows[rank], shift[rank]);
    double test = 1e10;
    int a = 0;
    while (test > epsilon) {
        method(A, x, b, rows, shift, rank);
        test = get_test(A, x, b, rows, shift, rank);
        a++;
    }
//    std::cout << std::endl << "x" << std::endl;
//    for (int i = 0; i < N; i++) {
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
