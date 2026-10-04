#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    const int N = 10000000;

    std::vector<double> A(N);
    std::vector<double> B(N);
    std::vector<double> C(N);

    for (int i = 0; i < N; ++i) {
        A[i] = i * 0.5;
        B[i] = i * 0.25;
    }

    for (int threads : {1, 2, 4}) {
        omp_set_num_threads(threads);

        double start = omp_get_wtime();

        #pragma omp parallel for
        for (int i = 0; i < N; ++i) {
            C[i] = 2.0 * A[i] + B[i];
        }

        double finish = omp_get_wtime();
        std::cout << "Threads: " << threads << " Time: " << finish - start << " seconds" << std::endl;
    }

    return 0;
}