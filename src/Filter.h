#ifndef FILTER_H
#define FILTER_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stddef.h>
#include <stdint.h>
#endif

/**
 * @brief Moving Average Filter using a FIFO Circular Buffer
 */
class MovingAverageFilter {
public:
    /**
     * @param size The size of the buffer (filter length)
     */
    MovingAverageFilter(size_t size = 12);
    ~MovingAverageFilter();

    /**
     * @brief Add a new sample and return the filtered value
     */
    float update(float input);

    /**
     * @brief Get the current filtered value
     */
    float get() const { return _currentAverage; }

    /**
     * @brief Reset the buffer
     */
    void reset();

private:
    float* _buffer;
    size_t _size;
    size_t _index;
    float _sum;
    float _currentAverage;
    bool _isFull;
};

#endif // FILTER_H
