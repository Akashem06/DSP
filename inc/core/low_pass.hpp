#pragma once
#include "dsp_core.hpp"

namespace DSP {
    class LowPass : public Filter {
       public:
        LowPass(int order, double cutoff_frequency, double sample_rate);
        ~LowPass() override = default;
        void process(const std::vector<double>& input, std::vector<double>& output) override;

       private:
        double prev_output;
    };
}  // namespace DSP
