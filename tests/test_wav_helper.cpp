#include <gtest/gtest.h>
#include <string.h>

#include <vector>

#include "helpers/wav_helper.hpp"

using namespace ::testing;

TEST(WavHelperTest, ReadWavFileValid) {
    WavHelper::WavFile wav_data;
    bool success = WavHelper::read_wav("wav_helper", "wav_helper.wav", wav_data);

    ASSERT_TRUE(success);
    EXPECT_EQ(strncmp(wav_data.header.chunkID, "RIFF", 4), 0);
    EXPECT_EQ(strncmp(wav_data.header.format, "WAVE", 4), 0);
}

TEST(WavHelperTest, ReadWavFileInvalid) {
    WavHelper::WavFile wav_data;
    bool success = WavHelper::read_wav("wav_helper", "invalid_file.wav", wav_data);

    ASSERT_FALSE(success);
}

TEST(WavHelperTest, WriteWavFile) {
    WavHelper::WavFile wav_data;
    WavHelper::read_wav("wav_helper", "wav_helper.wav", wav_data);

    bool success = WavHelper::write_wav("test_output", "output.wav", wav_data);

    ASSERT_TRUE(success);
}

TEST(WavHelperTest, ConvertToDouble) {
    WavHelper::WavFile wav_data;
    WavHelper::read_wav("wav_helper", "wav_helper.wav", wav_data);

    std::vector<double> double_data = WavHelper::convert_to_double(wav_data);

    ASSERT_EQ(double_data.size(), wav_data.data.size());
    for (size_t i = 0; i < double_data.size(); ++i) { EXPECT_NEAR(double_data[i], static_cast<double>(wav_data.data[i]) / 32768.0, 1e-5); }
}

TEST(WavHelperTest, ConvertToInt16) {
    WavHelper::WavFile wav_data;
    WavHelper::read_wav("wav_helper", "wav_helper.wav", wav_data);

    std::vector<double> double_data = WavHelper::convert_to_double(wav_data);
    std::vector<int16_t> int16_data = WavHelper::convert_to_int16(double_data);

    ASSERT_EQ(int16_data.size(), wav_data.data.size());
    for (size_t i = 0; i < int16_data.size(); ++i) { EXPECT_EQ(int16_data[i], wav_data.data[i]); }
}
