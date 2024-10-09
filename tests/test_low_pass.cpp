#include <gtest/gtest.h>

#include <cmath>
#include <vector>

#include "core/low_pass.hpp"
#include "helpers/wav_helper.hpp"

using namespace ::testing;

TEST(LowPassTest, FrequencyResponse) {
    const int sample_rate = 44100;
    DSP::LowPass low_pass(50, 1000, sample_rate);

    // Test frequencies
    std::vector<double> frequencies = { 100, 500, 1000, 2000, 4000 };

    for (double freq : frequencies) {
        std::vector<double> input(sample_rate);
        for (int i = 0; i < sample_rate; ++i) {
            double t = static_cast<double>(i) / sample_rate;
            input[i] = std::sin(2.0 * M_PI * freq * t);
        }

        std::vector<double> output;
        low_pass.process(input, output);

        double input_rms = 0.0, output_rms = 0.0;
        for (int i = 0; i < sample_rate; ++i) {
            input_rms += input[i] * input[i];
            output_rms += output[i] * output[i];
        }
        input_rms = std::sqrt(input_rms / sample_rate);
        output_rms = std::sqrt(output_rms / sample_rate);

        double gain_db = 20 * std::log10(output_rms / input_rms);

        if (freq < 1000) {
            EXPECT_GT(gain_db, -3.0) << "Frequency: " << freq << " Hz";
        } else if (freq > 2000) {
            EXPECT_LT(gain_db, -3.0) << "Frequency: " << freq << " Hz";
        }
    }
}

TEST(TestLowPassFilter, WavFileProcessing) {
    WavHelper::WavFile wav_data;
    ASSERT_TRUE(WavHelper::read_wav("low_pass", "harmonics_329.wav", wav_data)) << "Failed to load WAV file";

    std::vector<double> double_data = WavHelper::convert_to_double(wav_data);

    std::vector<double> filtered_data(double_data.size());

    DSP::LowPass low_pass_filter(1, 2000, 44100);

    low_pass_filter.process(double_data, filtered_data);

    std::vector<int16_t> int16_filtered_data = WavHelper::convert_to_int16(filtered_data);

    WavHelper::WavFile filtered_wav_data = wav_data;
    filtered_wav_data.data = int16_filtered_data;
    ASSERT_TRUE(WavHelper::write_wav("low_pass", "harmonics_329.wav", filtered_wav_data)) << "Failed to write WAV file";

    ASSERT_EQ(double_data.size(), filtered_data.size());
}
