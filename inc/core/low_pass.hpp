#include "dsp_core.h"

namespace  DSP {

class LowPass : public Filter {
public:
    LowPass(int order, double cutoffFrequency, double sampleRate);
    void process(const std::vector<double>& input, std::vector<double>& output) override;

private:
    std::vector<double> m_buffer;
};

}