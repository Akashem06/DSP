#pragma once

#include "dsp_core.hpp"

namespace DSP {

    class FFT : public DSPObject {
       public:
        FFT(int size);
        void processComplex(const std::vector<double>& input, std::vector<std::complex<double>>& output);
        void inverse(const std::vector<std::complex<double>>& input, std::vector<double>& output);

       private:
        int m_size;
    };

}  // namespace DSP