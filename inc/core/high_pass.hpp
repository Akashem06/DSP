#pragma once

#include "dsp_core.hpp"

namespace DSP {

    class HighPass : public Filter {
       public:
        HighPass(int order, double cutoff_frequency, double sample_rate);  // TBD the inputs
        void process(const std::vector<double>& input, std::vector<double>& output) override;

       private:
        std::vector<double> m_buffer;
    };

}  // namespace DSP