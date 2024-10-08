#include <gtest/gtest.h>
#include <vector>

#include "core/low_pass.hpp"
#include "helpers/wav_helper.hpp"

using namespace ::testing;
std::vector<double> test_data = { 1.5, 2.0, 2.2, 4.0, 7.0, 6.0, 5.5, 4.5, 5.0, 10.0 };
std::vector<double> test_output(test_data.size());

TEST(TestLowPassFilter, FirstOrderLowPass) {
    DSP::LowPass low_pass_filter(1, 500, 10000);

    low_pass_filter.process(test_data, test_output);

    ASSERT_EQ(test_data.size(), test_output.size());

    // std::vector<double> expected_output = { /* Fill this with expected values */ };

    // // Check that each output value is close to the expected output
    // for (size_t i = 0; i < expected_output.size(); ++i) {
    //     ASSERT_NEAR(test_output[i], expected_output[i], 1e-5) << "Mismatch at index " << i;
    // }
}

TEST(TestLowPassFilter, ZeroInput) {
    DSP::LowPass low_pass_filter(1, 500, 10000);
    std::vector<double> zero_input(10, 0.0);
    std::vector<double> zero_output;

    low_pass_filter.process(zero_input, zero_output);

    ASSERT_EQ(zero_input.size(), zero_output.size());
    for (double value : zero_output) {
        ASSERT_NEAR(value, 0.0, 1e-5);
    }
}
