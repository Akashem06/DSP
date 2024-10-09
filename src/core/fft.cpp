#include "core/fft.hpp"

namespace DSP {

    FFT::FFT(int size) : m_size(size) {};

    void FFT::process_complex(const std::vector<double>& input, std::vector<std::complex<double>>& output) {}

    void FFT::inverse(const std::vector<std::complex<double>>& input, std::vector<double>& output) {}

}  // namespace DSP