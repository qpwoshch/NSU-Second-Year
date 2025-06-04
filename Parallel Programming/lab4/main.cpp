#include <mpi.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define IDX(i, j, k) ((i)*(Ny+2)*(Nz+2) + (j)*(Nz+2) + (k))

const double a = 1e5;
const double epsilon = 1e-8;
const int Nx = 350, Ny = 350, Nz = 350;
const double X0 = -1.0, Y0 = -1.0, Z0 = -1.0;
const double Dx = 2.0, Dy = 2.0, Dz = 2.0;
const double hx = Dx / Nx;
const double hy = Dy / Ny;
const double hz = Dz / Nz;

double exact_solution(double x, double y, double z) {
    return x*x + y*y + z*z;
}

void initialize(vector<double> &phi, vector<double> &rho, int i_start, int i_end) {
    for (int i = i_start; i <= i_end; ++i) {
        double x = X0 + i * hx;
        for (int j = 0; j <= Ny+1; ++j) {
            double y = Y0 + j * hy;
            for (int k = 0; k <= Nz+1; ++k) {
                double z = Z0 + k * hz;
                int idx = IDX(i - i_start + 1, j, k);
                if (i == 0 || i == Nx || j == 0 || j == Ny || k == 0 || k == Nz) {
                    phi[idx] = exact_solution(x, y, z);
                } else {
                    phi[idx] = 0.0;
                }
                rho[idx] = 6.0 - a * (x*x + y*y + z*z);
            }
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    auto startTime = MPI_Wtime();
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk = Nx / size;
    int i_start = rank * chunk;
    int i_end = (rank == size - 1) ? Nx : i_start + chunk;

    int local_Nx = i_end - i_start + 1;
    vector<double> phi((local_Nx+2)*(Ny+2)*(Nz+2), 0.0);
    vector<double> phi_new((local_Nx+2)*(Ny+2)*(Nz+2), 0.0);
    vector<double> rho((local_Nx+2)*(Ny+2)*(Nz+2), 0.0);

    initialize(phi, rho, i_start, i_end);

    int iter = 0;
    double max_diff;
    MPI_Request reqs[4];

    do {
        if (rank > 0) {
            MPI_Isend(&phi[IDX(1, 0, 0)], (Ny+2)*(Nz+2), MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &reqs[0]);
            MPI_Irecv(&phi[IDX(0, 0, 0)], (Ny+2)*(Nz+2), MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &reqs[1]);
        }
        if (rank < size - 1) {
            MPI_Isend(&phi[IDX(local_Nx, 0, 0)], (Ny+2)*(Nz+2), MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, &reqs[2]);
            MPI_Irecv(&phi[IDX(local_Nx+1, 0, 0)], (Ny+2)*(Nz+2), MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &reqs[3]);
        }

        for (int i = 2; i <= local_Nx - 1; ++i)
            for (int j = 1; j < Ny; ++j)
                for (int k = 1; k < Nz; ++k) {
                    int idx = IDX(i, j, k);
                    phi_new[idx] = (
                                           phi[IDX(i+1,j,k)] + phi[IDX(i-1,j,k)] ) / (hx*hx) +
                                   (phi[IDX(i,j+1,k)] + phi[IDX(i,j-1,k)] ) / (hy*hy) +
                                   (phi[IDX(i,j,k+1)] + phi[IDX(i,j,k-1)] ) / (hz*hz) -
                                   rho[idx];
                    phi_new[idx] /= (2.0/hx/hx + 2.0/hy/hy + 2.0/hz/hz + a);
                }

        if (rank > 0) MPI_Wait(&reqs[1], MPI_STATUS_IGNORE);
        if (rank < size - 1) MPI_Wait(&reqs[3], MPI_STATUS_IGNORE);

        for (int i : {1, local_Nx})
            for (int j = 1; j < Ny; ++j)
                for (int k = 1; k < Nz; ++k) {
                    int idx = IDX(i, j, k);
                    phi_new[idx] = (
                                           phi[IDX(i+1,j,k)] + phi[IDX(i-1,j,k)] ) / (hx*hx) +
                                   (phi[IDX(i,j+1,k)] + phi[IDX(i,j-1,k)] ) / (hy*hy) +
                                   (phi[IDX(i,j,k+1)] + phi[IDX(i,j,k-1)] ) / (hz*hz) -
                                   rho[idx];
                    phi_new[idx] /= (2.0/hx/hx + 2.0/hy/hy + 2.0/hz/hz + a);
                }

        max_diff = 0.0;
        for (int i = 1; i <= local_Nx; ++i)
            for (int j = 1; j < Ny; ++j)
                for (int k = 1; k < Nz; ++k) {
                    int idx = IDX(i,j,k);
                    max_diff = max(max_diff, fabs(phi_new[idx] - phi[idx]));
                    phi[idx] = phi_new[idx];
                }

        double global_diff;
        MPI_Allreduce(&max_diff, &global_diff, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
        max_diff = global_diff;
        iter++;

    } while (max_diff > epsilon);

//    double local_error = 0.0;
//    double max_local_error = 0.0;
//
//    for (int i = 1; i <= local_Nx; ++i) {
//        int gi = i_start + i - 1;
//        double x = X0 + gi * hx;
//        for (int j = 1; j < Ny; ++j) {
//            double y = Y0 + j * hy;
//            for (int k = 1; k < Nz; ++k) {
//                double z = Z0 + k * hz;
//                int idx = IDX(i, j, k);
//                double exact = exact_solution(x, y, z);
//                double error = fabs(phi[idx] - exact);
//                local_error += error * error;
//                max_local_error = max(max_local_error, error);
//            }
//        }
//    }

//    double global_error, max_global_error;
//    MPI_Reduce(&local_error, &global_error, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
//    MPI_Reduce(&max_local_error, &max_global_error, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
//        double rms_error = sqrt(global_error / ((Nx - 1.0) * (Ny - 1.0) * (Nz - 1.0)));
        cout << "time: " << MPI_Wtime() - startTime << endl;
//        cout << "Converged in " << iter << " iterations." << endl;
//        cout << "RMS Error: " << rms_error << endl;
//        cout << "Max Error: " << max_global_error << endl;
    }

    MPI_Finalize();
    return 0;
}
