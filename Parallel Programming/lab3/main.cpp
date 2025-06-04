#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    auto startTime = MPI_Wtime();

    int n1 = 2400, n2 = 2400, n3 = 2400;
    int proc_rows = 4, proc_cols = 3;

    int dims[2] = {proc_rows, proc_cols};
    int periods[2] = {0, 0};
    MPI_Comm grid_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &grid_comm);

    int coords[2];
    MPI_Cart_coords(grid_comm, rank, 2, coords);
    int i = coords[0], j = coords[1];

    int block_n1 = n1 / proc_rows;
    int block_n2 = n2;
    int block_n3 = n3 / proc_cols;

    std::vector<double> A, B;
    if (rank == 0) {
        A.resize(n1 * n2);
        B.resize(n2 * n3);
        std::srand(std::time(nullptr));

        for (int i = 0; i < n1 * n2; ++i) A[i] = std::rand() % 10;
        for (int i = 0; i < n2 * n3; ++i) B[i] = std::rand() % 10;
    }

    std::vector<double> temp_A(block_n1 * n2);
    std::vector<double> temp_B(n2 * block_n3);

    if (j == 0) {
        if (rank == 0) {
            for (int pi = 0; pi < proc_rows; ++pi) {
                std::vector<double> temp_block(block_n1 * n2);
                for (int row = 0; row < block_n1; ++row) {
                    std::copy(A.begin() + (pi * block_n1 + row) * n2,
                              A.begin() + (pi * block_n1 + row + 1) * n2,
                              temp_block.begin() + row * n2);
                }
                if (pi == 0) {
                    temp_A = temp_block;
                } else {
                    int dest_rank;
                    int coords_send[2] = {pi, 0};
                    MPI_Cart_rank(grid_comm, coords_send, &dest_rank);
                    MPI_Send(temp_block.data(), block_n1 * n2, MPI_DOUBLE, dest_rank, 1, grid_comm);
                }
            }
        } else {
            MPI_Recv(temp_A.data(), block_n1 * n2, MPI_DOUBLE, 0, 1, grid_comm, MPI_STATUS_IGNORE);
        }

        for (int pj = 1; pj < proc_cols; ++pj) {
            int dest_rank;
            int coords_send[2] = {i, pj};
            MPI_Cart_rank(grid_comm, coords_send, &dest_rank);
            MPI_Send(temp_A.data(), block_n1 * n2, MPI_DOUBLE, dest_rank, 3, grid_comm);
        }
    } else {
        MPI_Recv(temp_A.data(), block_n1 * n2, MPI_DOUBLE, MPI_ANY_SOURCE, 3, grid_comm, MPI_STATUS_IGNORE);
    }

    if (i == 0) {
        if (rank == 0) {
            for (int pj = 0; pj < proc_cols; ++pj) {
                std::vector<double> temp_block(n2 * block_n3);
                for (int col = 0; col < block_n3; ++col) {
                    for (int row = 0; row < n2; ++row) {
                        temp_block[row * block_n3 + col] = B[row * n3 + pj * block_n3 + col];
                    }
                }
                if (pj == 0) {
                    temp_B = temp_block;
                } else {
                    int dest_rank;
                    int coords_send[2] = {0, pj};
                    MPI_Cart_rank(grid_comm, coords_send, &dest_rank);
                    MPI_Send(temp_block.data(), n2 * block_n3, MPI_DOUBLE, dest_rank, 2, grid_comm);
                }
            }
        } else {
            MPI_Recv(temp_B.data(), n2 * block_n3, MPI_DOUBLE, 0, 2, grid_comm, MPI_STATUS_IGNORE);
        }

        for (int pi = 1; pi < proc_rows; ++pi) {
            int dest_rank;
            int coords_send[2] = {pi, j};
            MPI_Cart_rank(grid_comm, coords_send, &dest_rank);
            MPI_Send(temp_B.data(), n2 * block_n3, MPI_DOUBLE, dest_rank, 4, grid_comm);
        }
    } else {
        MPI_Recv(temp_B.data(), n2 * block_n3, MPI_DOUBLE, MPI_ANY_SOURCE, 4, grid_comm, MPI_STATUS_IGNORE);
    }

    std::vector<double> local_C(block_n1 * block_n3, 0.0);
    for (int i1 = 0; i1 < block_n1; ++i1)
        for (int k = 0; k < block_n2; ++k)
            for (int j1 = 0; j1 < block_n3; ++j1)
                local_C[i1 * block_n3 + j1] += temp_A[i1 * block_n2 + k] * temp_B[k * block_n3 + j1];

    if (rank == 0) {
        std::vector<double> C(n1 * n3, 0.0);
        for (int row = 0; row < block_n1; ++row)
            for (int col = 0; col < block_n3; ++col)
                C[row * n3 + col] = local_C[row * block_n3 + col];

        for (int pr = 1; pr < size; ++pr) {
            int coords_recv[2];
            MPI_Cart_coords(grid_comm, pr, 2, coords_recv);
            int ii = coords_recv[0], jj = coords_recv[1];
            std::vector<double> temp_C(block_n1 * block_n3);
            MPI_Recv(temp_C.data(), block_n1 * block_n3, MPI_DOUBLE, pr, 5, grid_comm, MPI_STATUS_IGNORE);
            for (int row = 0; row < block_n1; ++row)
                for (int col = 0; col < block_n3; ++col)
                    C[(ii * block_n1 + row) * n3 + jj * block_n3 + col] = temp_C[row * block_n3 + col];
        }

//        std::cout << "Matrix A:\n";
//        for (int i = 0; i < n1; ++i) {
//            for (int j = 0; j < n2; ++j)
//                std::cout << A[i * n2 + j] << " ";
//            std::cout << "\n";
//        }
//
//        std::cout << "\nMatrix B:\n";
//        for (int i = 0; i < n2; ++i) {
//            for (int j = 0; j < n3; ++j)
//                std::cout << B[i * n3 + j] << " ";
//            std::cout << "\n";
//        }
//
//        std::cout << "\nMatrix C = A * B:\n";
//        for (int i = 0; i < n1; ++i) {
//            for (int j = 0; j < n3; ++j)
//                std::cout << C[i * n3 + j] << " ";
//            std::cout << "\n";
//        }

        std::cout << "Время выполнения: " << (MPI_Wtime() - startTime) << " с\n";
    } else {
        MPI_Send(local_C.data(), block_n1 * block_n3, MPI_DOUBLE, 0, 5, grid_comm);
    }

    MPI_Finalize();
    return 0;
}
