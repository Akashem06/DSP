#include "dsp_core.h"

namespace  DSP {

class HighPass : public Filter {
public:
    HighPass(int order, double cutoffFrequency, double sampleRate); // TBD the inputs
    void process(const std::vector<double>& input, std::vector<double>& output) override;

private:
    std::vector<double> m_buffer;
};

}