#include "dsp_core.h"

namespace  DSP {

class MovingAverage : public Filter {
public:
    MovingAverage(int windowSize);
    void process(const std::vector<double>& input, std::vector<double>& output) override;

private:
    std::vector<double> m_buffer;
};

}