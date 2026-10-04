#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

int main() {

    // Part 1
    std::cout << "=== Part 1 ===" << std::endl;
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        std::cout << "Hello from thread " << id << " of " << nthreads << std::endl;
    }

    // Part 2
    std::cout << "\n=== Part 2 ===" << std::endl;
    const int N = 1000000;
    std::vector<double> A(N), B(N), C(N);
    for (int i = 0; i < N; ++i) {
        A[i] = i * 0.5;
        B[i] = i * 0.25;
    }
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        C[i] = 2.0 * A[i] + B[i];
    }
    std::cout << "C[0] = " << C[0] << std::endl;
    std::cout << "C[N-1] = " << C[N-1] << std::endl;

    // Part 3
    std::cout << "\n=== Part 3 ===" << std::endl;
    const int N3 = 20;
    #pragma omp parallel for
    for (int i = 0; i < N3; ++i) {
        int id = omp_get_thread_num();
        std::cout << "Iteration " << i << " executed by thread " << id << std::endl;
    }

    // Part 4
    std::cout << "\n=== Part 4 ===" << std::endl;
    std::vector<double> A4(N, 1.0);
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i) {
        sum += A4[i];
    }
    std::cout << "Sum = " << sum << std::endl;

    // Part 5
    std::cout << "\n=== Part 5 ===" << std::endl;
    int counter = 0;
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        counter++;
    }
    std::cout << "Without atomic: " << counter << std::endl;
    counter = 0;
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        #pragma omp atomic
        counter++;
    }
    std::cout << "With atomic: " << counter << std::endl;

    // Part 6
    std::cout << "\n=== Part 6 ===" << std::endl;
    const int N6 = 100000;
    std::vector<double> result(N6);
    double start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N6; ++i) {
        int work = 100 + (i % 1000);
        double value = 0.0;
        for (int k = 0; k < work; ++k) {
            value += std::sqrt(k + 1.0);
        }
        result[i] = value;
    }
    std::cout << "Static time: " << omp_get_wtime() - start << " seconds" << std::endl;
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 10)
    for (int i = 0; i < N6; ++i) {
        int work = 100 + (i % 1000);
        double value = 0.0;
        for (int k = 0; k < work; ++k) {
            value += std::sqrt(k + 1.0);
        }
        result[i] = value;
    }
    std::cout << "Dynamic time: " << omp_get_wtime() - start << " seconds" << std::endl;

    // Part 7
    std::cout << "\n=== Part 7 ===" << std::endl;
    const int N7 = 10000000;
    std::vector<double> A7(N7), B7(N7), C7(N7);
    for (int i = 0; i < N7; ++i) {
        A7[i] = i * 0.5;
        B7[i] = i * 0.25;
    }
    for (int threads : {1, 2, 4}) {
        omp_set_num_threads(threads);
        double t = omp_get_wtime();
        #pragma omp parallel for
        for (int i = 0; i < N7; ++i) {
            C7[i] = 2.0 * A7[i] + B7[i];
        }
        std::cout << "Threads: " << threads << " Time: " << omp_get_wtime() - t << " seconds" << std::endl;
    }

    return 0;
}