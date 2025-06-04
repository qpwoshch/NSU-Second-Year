#include <mpi.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

struct Task {
    int repeatNum;
};

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double globalRes = 0.0;
    int iterCounter = 0;

    const int baseLoad = 10000;
    const int baseNumTasks = 1024;
    int tasksCompleted = 0;
    const int maxIter = 100;

    double totalStartTime = MPI_Wtime();

    while (iterCounter < maxIter) {
        iterCounter++;

        int loadFactor = std::abs(rank + 2 - (iterCounter % size));
        int numTasks = baseNumTasks;

        std::vector<Task> taskList;

        for (int t = 0; t < numTasks; ++t) {
            Task task;
            task.repeatNum = baseLoad * (loadFactor + 1) + 10000;
            taskList.push_back(task);
        }



        for (const auto& task : taskList) {
            for (int i = 0; i < task.repeatNum; ++i) {
                globalRes += std::sqrt(i);
                tasksCompleted++;
            }
        }


        MPI_Barrier(MPI_COMM_WORLD);


    }

    double totalEndTime = MPI_Wtime();
    double totalTime = totalEndTime - totalStartTime;

    std::cout << "Process " << rank << " completed " << iterCounter
              << " iterations, performed " << tasksCompleted
              << " tasks in " << totalTime << " seconds. Result: "
              << globalRes << std::endl;


    MPI_Finalize();
    return 0;
}
