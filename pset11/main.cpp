#include "Stopwatch.h"
#include <array>

constexpr int size = 10000;
constexpr int N = 1000000000;

int main() {
    Stopwatch stopwatch;
    stopwatch.start();

    // ----- START OF CODE TO TIME ----- //

    for (int i = 0; i < N; i++) {
        // Stack allocation
        std::array<int, size> arr1;

        //Heap allocation
        // std::array<int, size>* arr2 = new std::array<int, size>;
        // delete arr2;
    }

    // ----- END OF CODE TO TIME ----- //

    double time = stopwatch.stop();
    std::cout << "Time taken: " << time << " seconds" << std::endl;
    return 0;
}