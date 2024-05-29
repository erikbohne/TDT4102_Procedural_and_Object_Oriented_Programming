#include "Stopwatch.h"
#include "optimizationTask.h"
#include "Templates.h"
#include "MyArray.h"
#include <array>
#include <vector>

void timeTask1();
void timeTask2();
void timeTask3();
void testTemplates();
void testMyArray();

constexpr int size = 10000;
constexpr int N = 1000000000;

int main() {
    
    // Task 1
    // timeTask1();

    // Task 2
    // timeTask2();

    // Task 3
    // timeTask3();

    // Task 4
    // testTemplates();

    // Task 5
    testMyArray();

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
    vec.reserve(1000000);
    // vec.resize(1000000);
    for (int i = 0; i < 1000000; ++i) {
        vec.push_back(i);
    }

    // ----- END OF CODE TO TIME ----- //

    double time = stopwatch.stop();
    std::cout << "Time taken: " << time << " seconds" << std::endl;
}

void timeTask3 () {
    Stopwatch stopwatch;
    stopwatch.start();

    // ----- START OF CODE TO TIME ----- //

    // Task 3
    optimizationTask();

    // ----- END OF CODE TO TIME ----- //

    double time = stopwatch.stop();
    std::cout << "Time taken: " << time << " seconds" << std::endl;
}

void testTemplates() {
    // 4a
    std::cout << "maximum(1,2) -> " <<  maximum(1, 2) << std::endl;
    std::cout << "maximum(1.5, 2.5) -> " << maximum(1.5, 2.5) << std::endl;

    // 4b
    std::vector<int> vec = {1, 2, 3, 4, 5};
    shuffle(vec);
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;   
}

void testMyArray() {
    MyArray<int, 5> arr;
    arr.fill(5);
    for (int i = 0; i < arr.getSize(); ++i) {
        std::cout << arr.at(i) << " ";
    }
    std::cout << std::endl;

    try {
        std::cout << "arr.at(4): " << arr.at(4) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}