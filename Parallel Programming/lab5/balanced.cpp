#include <mpi.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>
#include <mutex>
#include <atomic>
#include <algorithm>

struct Task {
    int repeatNum;
    bool isRemote = false;
    int ownerRank = -1;
};

struct ThreadData {
    int rank;
    int size;
    int maxIter;
    double* globalRes;
    std::vector<Task>* taskList;
    std::mutex* taskMutex;
    std::atomic<bool>* done;
    std::atomic<int>* completedTasks;
};

const int TASK_REQUEST = 1;
const int TASK_RESPONSE = 2;
const int TASK_RESULT = 3;

void* computeThreadFunc(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    int rank = data->rank;
    int size = data->size;
    int maxIter = data->maxIter;
    double* globalRes = data->globalRes;
    auto& taskList = *(data->taskList);
    auto& mutex = *(data->taskMutex);

    const int baseLoad = 10000;
    const int baseNumTasks = 1024;

    int iterCounter = 0;

    while (iterCounter < maxIter) {
        iterCounter++;

        int loadFactor = std::abs(rank + 2 - (iterCounter % size));
        int numTasks = baseNumTasks;

        mutex.lock();
        taskList.clear();
        for (int t = 0; t < numTasks; ++t) {
            taskList.push_back({baseLoad * (loadFactor + 1) + 10000, false, rank});
        }
        mutex.unlock();

        while (true) {
            mutex.lock();
            if (taskList.empty()) {
                mutex.unlock();
                break;
            }
            Task task = taskList.back();
            taskList.pop_back();
            mutex.unlock();

            double localSum = 0.0;
            for (int i = 0; i < task.repeatNum; ++i) {
                localSum += std::sqrt(i);
            }

            if (task.isRemote) {
                MPI_Send(&localSum, 1, MPI_DOUBLE, task.ownerRank, TASK_RESULT, MPI_COMM_WORLD);
            } else {
                *globalRes += localSum;
            }
            (*data->completedTasks)++;
        }

        MPI_Barrier(MPI_COMM_WORLD);
    }

    *(data->done) = true;
    pthread_exit(nullptr);
}

void* requestThreadFunc(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    int rank = data->rank;
    int size = data->size;
    auto& taskList = *(data->taskList);
    auto& mutex = *(data->taskMutex);
    std::atomic<bool>* done = data->done;

    MPI_Status status;

    while (!done->load()) {
        bool needHelp = false;
        mutex.lock();
        needHelp = taskList.empty();
        mutex.unlock();

        if (needHelp) {
            bool gotTask = false;
            for (int i = 0; i < size && !gotTask && !done->load(); ++i) {
                if (i == rank) continue;

                MPI_Send(nullptr, 0, MPI_CHAR, i, TASK_REQUEST, MPI_COMM_WORLD);
                int taskCount = 0;
                MPI_Request countReq;
                MPI_Irecv(&taskCount, 1, MPI_INT, i, TASK_RESPONSE, MPI_COMM_WORLD, &countReq);

                double startWait = MPI_Wtime();
                while (!done->load()) {
                    int flag = 0;
                    MPI_Test(&countReq, &flag, &status);
                    if (flag) break;
                    if (MPI_Wtime() - startWait > 0.1) {
                        MPI_Cancel(&countReq);
                        MPI_Request_free(&countReq);
                        break;
                    }
                    usleep(1000);
                }

                if (!done->load() && taskCount > 0) {
                    std::vector<int> recvBuf(taskCount);
                    MPI_Recv(recvBuf.data(), taskCount, MPI_INT, i, TASK_RESPONSE, MPI_COMM_WORLD, &status);

                    mutex.lock();
                    for (int val : recvBuf) {
                        taskList.push_back({val, true, i});
                    }
                    mutex.unlock();

                    gotTask = true;
                }
            }
        } else {
            usleep(1000);
        }
    }

    pthread_exit(nullptr);
}

void* serveThreadFunc(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    int rank = data->rank;
    int size = data->size;
    auto& taskList = *(data->taskList);
    auto& mutex = *(data->taskMutex);
    std::atomic<bool>* done = data->done;

    MPI_Status status;

    while (!done->load()) {
        int flag = 0;
        MPI_Iprobe(MPI_ANY_SOURCE, TASK_REQUEST, MPI_COMM_WORLD, &flag, &status);

        if (flag) {
            int sender = status.MPI_SOURCE;
            MPI_Recv(nullptr, 0, MPI_CHAR, sender, TASK_REQUEST, MPI_COMM_WORLD, &status);

            std::vector<int> toSend;

            mutex.lock();
            int localTasks = std::count_if(taskList.begin(), taskList.end(),
                                           [](const Task& task) { return !task.isRemote; });

            int numToSend = std::max(1, localTasks / 2);

            for (auto it = taskList.begin(); it != taskList.end();) {
                if (!it->isRemote && toSend.size() < (size_t)numToSend) {
                    toSend.push_back(it->repeatNum);
                    it = taskList.erase(it);
                } else {
                    ++it;
                }
            }

            mutex.unlock();

            int count = static_cast<int>(toSend.size());
            MPI_Send(&count, 1, MPI_INT, sender, TASK_RESPONSE, MPI_COMM_WORLD);
            if (count > 0) {
                MPI_Send(toSend.data(), count, MPI_INT, sender, TASK_RESPONSE, MPI_COMM_WORLD);
//                std::cout << "Send " << count << " tasks from: " << rank << " to: " << sender << std::endl;
            }
        } else {
            usleep(1000);
        }
    }

    pthread_exit(nullptr);
}

void* resultThreadFunc(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    std::atomic<bool>* done = data->done;
    double* globalRes = data->globalRes;

    MPI_Status status;

    while (!done->load()) {
        int flag = 0;
        MPI_Iprobe(MPI_ANY_SOURCE, TASK_RESULT, MPI_COMM_WORLD, &flag, &status);

        if (flag) {
            double receivedVal = 0.0;
            MPI_Recv(&receivedVal, 1, MPI_DOUBLE, status.MPI_SOURCE, TASK_RESULT, MPI_COMM_WORLD, &status);
            *globalRes += receivedVal;
        } else {
            usleep(1000);
        }
    }

    pthread_exit(nullptr);
}

int main(int argc, char** argv) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    if (provided < MPI_THREAD_MULTIPLE) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int maxIter = 100;
    double globalRes = 0.0;
    std::vector<Task> taskList;
    std::mutex taskMutex;
    std::atomic<bool> done(false);

    double totalStartTime = MPI_Wtime();

    pthread_t computeThread, requestThread, serveThread, resultThread;
    std::atomic<int> completedTasks(0);
    ThreadData data = {rank, size, maxIter, &globalRes, &taskList, &taskMutex, &done, &completedTasks};


    pthread_create(&computeThread, nullptr, computeThreadFunc, &data);
    pthread_create(&requestThread, nullptr, requestThreadFunc, &data);
    pthread_create(&serveThread, nullptr, serveThreadFunc, &data);
    pthread_create(&resultThread, nullptr, resultThreadFunc, &data);

    pthread_join(computeThread, nullptr);
    done = true;
    pthread_join(requestThread, nullptr);
    pthread_join(serveThread, nullptr);
    pthread_join(resultThread, nullptr);

    double totalEndTime = MPI_Wtime();
    double totalTime = totalEndTime - totalStartTime;

    std::cout << "Process " << rank << " completed in "
              << totalTime << " seconds. Result: " << globalRes
              << ". Tasks done: " << completedTasks.load() << std::endl;

    MPI_Finalize();
    return 0;
}
