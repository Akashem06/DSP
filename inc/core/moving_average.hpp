#pragma once

#include "dsp_core.hpp"

namespace DSP {

    class MovingAverage : public Filter {
       public:
        MovingAverage(int windowSize);
        void process(const std::vector<double>& input, std::vector<double>& output) override;

       private:
        std::vector<double> m_buffer;
    };

}  // namespace DSP