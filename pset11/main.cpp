#include "Stopwatch.h"
#include <array>
#include <vector>

void timeTask1();
void timeTask2();

constexpr int size = 10000;
constexpr int N = 1000000000;

int main() {
    
    // Task 1
    timeTask1();

    // Task 2
    timeTask2();

    return 0;
}


void timeTask1 () {
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
}

void timeTask2 () {
    Stopwatch stopwatch;
    stopwatch.start();

    // ----- START OF CODE TO TIME ----- //


    // Task a
    // std::vector<int> vec;
    // for (int i = 0; i < 20; ++i) {
    //     vec.push_back(i);
    //     std::cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;
    // }

    // Task b
    // std::vector<int> vec;
    // vec.reserve(20); // Reserver plass
    // for (int i = 0; i < 20; ++i) {
    //     vec.push_back(i);
    //     std::cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;
    // }

    // Task c
    // std::vector<int> vec;
    // vec.resize(20);
    // std::cout << "Initial Size: " << vec.size() << ", Initial Capacity: " << vec.capacity() << std::endl;

    // Task d
    // std::vector<int> vec;
    // for (int i = 0; i < 1000000; ++i) {
    //     vec.push_back(i);
    // }

    // Task e
    std::vector<int> vec;
    // vec.reserve(1000000);
    vec.resize(1000000);
    for (int i = 0; i < 1000000; ++i) {
        vec.push_back(i);
    }

    // ----- END OF CODE TO TIME ----- //

    double time = stopwatch.stop();
    std::cout << "Time taken: " << time << " seconds" << std::endl;
}