#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;


void fill_direct(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        arr[i] = i + 1;
    }
    arr[n - 1] = 0;
}

void fill_reverse(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        arr[i] = i - 1;
    }
    arr[0] = n - 1;
}

void fill_random(std::vector<int>& arr) {
    size_t n = arr.size();


    for (size_t i = 0; i < n; ++i) {
        arr[i] = i;
    }

    for (size_t i = n - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }

    std::vector<int> temp = arr;
    for (size_t i = 0; i < n - 1; ++i) {
        arr[temp[i]] = temp[i + 1];
    }
    arr[temp[n - 1]] = temp[0];
}

long long measure_access_time(const vector<int>& arr, size_t iterations) {
    size_t n = arr.size();
    volatile int k = 0;
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n * iterations; ++i) {
        k = arr[k];
    }
    auto end = chrono::high_resolution_clock::now();
    return duration_cast<chrono::nanoseconds>(end - start).count();
}

int main() {
    const size_t Nmin = 1024 / sizeof(int);
    const size_t Nmax = 32768 * 1024 / sizeof(int);
    const size_t iterations = 1000;

    vector<size_t> sizes;
    for (size_t n = Nmin; n <= Nmax; n *= 2) {
        sizes.push_back(n);
    }

    cout << "Size\tDirect\tReverse\tRandom" << endl;
    cout << fixed << setprecision(6);

    for (size_t n : sizes) {
        vector<int> arr(n);

        fill_direct(arr);
        measure_access_time(arr, 1);
        long long direct_time = measure_access_time(arr, iterations);

        fill_reverse(arr);
        measure_access_time(arr, 1);
        long long reverse_time = measure_access_time(arr, iterations);

        fill_random(arr);
        measure_access_time(arr, 1);
        long long random_time = measure_access_time(arr, iterations);

        cout << n/256 << "KB\t" << (direct_time / (double)(n * iterations)) << "\t"
             << (reverse_time / (double)(n * iterations)) << "\t"
             << (random_time / (double)(n * iterations)) << endl;
    }

    return 0;
}
