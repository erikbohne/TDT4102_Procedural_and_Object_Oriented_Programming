# Task 1

The runtime on stack vs heap allocation was significant. Running a for loop with 1 billion iterations and `size = 10000` on the following code:

```cpp
std::array<int, size> arr1;
```

Time taken on 1.000.000.000 iterations: 2.12179 seconds

```cpp
std::array<int, size>* arr2 = new std::array<int, size>;
delete arr2;
```

Time taken on 1.000.000.000 iterations: 20.2793 seconds