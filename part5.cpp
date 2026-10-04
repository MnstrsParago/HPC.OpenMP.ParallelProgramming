#include <iostream>
#include <omp.h>

int main() {
    const int N = 1000000;
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

    return 0;
}