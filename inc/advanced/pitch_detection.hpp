#include "dsp_core.hpp"

namespace DSP {

    class PitchDetector : public DSPObject {
       public:
        PitchDetector(double sampleRate);
        double detectPitch(const std::vector<double>& input);

       private:
        double m_sampleRate;
    };

}  // namespace DSP
