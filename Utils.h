#pragma once
#include <random>
#include <thread>
#include <chrono>
#include <string>
#include <iostream>

// Prints text piece by piece with delay
inline void animateText(const std::string& text, int delayMs = 150) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << "\n";
}

// Random engine (shared)
inline std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

// Constants
constexpr int TRAIN_MIN = 5;
constexpr int TRAIN_MAX = 15;
constexpr int STAT_CAP_PER_STAGE = 20;
//constexpression will never change the values and can be fully resolved when program compiles.

// Helpers
inline int rollStatGain() {
    std::uniform_int_distribution<> dist(TRAIN_MIN, TRAIN_MAX);
    return dist(rng());
}