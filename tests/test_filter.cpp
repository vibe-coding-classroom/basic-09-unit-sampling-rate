#include <iostream>
#include <cassert>
#include <cmath>
#include "../src/Filter.h"
#include "../src/Filter.cpp"

void testBasicAveraging() {
    std::cout << "--- Testing Basic Averaging ---" << std::endl;
    MovingAverageFilter filter(4); // Small buffer for easy testing
    
    filter.update(10.0);
    // Sum: 10, Avg: 10/4 = 2.5
    assert(std::abs(filter.get() - 2.5f) < 0.001);
    
    filter.update(20.0);
    // Sum: 30, Avg: 30/4 = 7.5
    assert(std::abs(filter.get() - 7.5f) < 0.001);
    
    filter.update(30.0);
    filter.update(40.0);
    // Buffer full: [10, 20, 30, 40], Sum: 100, Avg: 25.0
    assert(std::abs(filter.get() - 25.0f) < 0.001);
    
    std::cout << "Basic averaging passed" << std::endl;
}

void testBufferWrapping() {
    std::cout << "--- Testing Buffer Wrapping ---" << std::endl;
    MovingAverageFilter filter(2);
    
    filter.update(10.0);
    filter.update(20.0);
    // [10, 20], Sum: 30, Avg: 15
    assert(std::abs(filter.get() - 15.0f) < 0.001);
    
    filter.update(30.0);
    // [30, 20], Sum: 50, Avg: 25 (10 was overwritten)
    assert(std::abs(filter.get() - 25.0f) < 0.001);
    
    filter.update(40.0);
    // [30, 40], Sum: 70, Avg: 35 (20 was overwritten)
    assert(std::abs(filter.get() - 35.0f) < 0.001);
    
    std::cout << "Buffer wrapping passed" << std::endl;
}

int main() {
    try {
        testBasicAveraging();
        testBufferWrapping();
        std::cout << "\n✅ All C++ tests passed!" << std::endl;
    } catch (...) {
        std::cerr << "\n❌ Tests failed!" << std::endl;
        return 1;
    }
    return 0;
}
