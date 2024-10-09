#include "dsp_core.hpp"

namespace DSP {

    class PitchDetector : public DSPObject {
       public:
        PitchDetector(double sampleRate);
        double detect_pitch(const std::vector<double>& input);

       private:
        double m_sample_rate;
    };

}  // namespace DSP
