#include "dsp_core.h"

namespace DSP {

class PitchDetector : public DSPObject {
public:
    PitchDetector(double sampleRate);
    double detectPitch(const std::vector<double>& input);

private:
    double m_sampleRate;
};

}
