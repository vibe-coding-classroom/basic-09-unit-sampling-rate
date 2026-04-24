#include "Filter.h"

MovingAverageFilter::MovingAverageFilter(size_t size) 
    : _size(size), _index(0), _sum(0.0f), _currentAverage(0.0f), _isFull(false) {
    _buffer = new float[_size];
    reset();
}

MovingAverageFilter::~MovingAverageFilter() {
    delete[] _buffer;
}

void MovingAverageFilter::reset() {
    for (size_t i = 0; i < _size; i++) {
        _buffer[i] = 0.0f;
    }
    _index = 0;
    _sum = 0.0f;
    _currentAverage = 0.0f;
    _isFull = false;
}

float MovingAverageFilter::update(float input) {
    // Subtract the oldest value from sum
    _sum -= _buffer[_index];
    
    // Update buffer with new value
    _buffer[_index] = input;
    
    // Add the new value to sum
    _sum += input;
    
    // Increment index (circular)
    _index = (_index + 1) % _size;
    
    if (!_isFull && _index == 0) {
        _isFull = true;
    }

    // Calculate average
    // If buffer is not full yet, divide by the number of samples added
    // but typically for SMA we can just divide by _size if we initialize with 0
    _currentAverage = _sum / _size;
    
    return _currentAverage;
}
