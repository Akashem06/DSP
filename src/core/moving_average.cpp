#include "core/moving_average.hpp"

namespace DSP {

MovingAverage::MovingAverage(int windowSize) : Filter(windowSize - 1), m_buffer(windowSize) {}

void MovingAverage::process(const std::vector<double>& input, std::vector<double>& output) {
    
}

}