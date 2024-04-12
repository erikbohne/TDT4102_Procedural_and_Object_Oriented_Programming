#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

template <typename T>
T maximum(T x, T y) {
    return x > y ? x : y;
}

template <typename T>
void shuffle(std::vector<T>& vec) {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    for (size_t i = 0; i < vec.size(); ++i) {
        std::uniform_int_distribution<size_t> dist(i, vec.size() - 1);
        std::swap(vec[i], vec[dist(rng)]);
    }
}