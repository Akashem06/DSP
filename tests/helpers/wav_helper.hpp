#pragma once

#include <string>
#include <vector>

namespace WavHelper {

    // https://www.videoproc.com/resource/wav-file.htm
    typedef struct {
        char chunkID[4];
        uint32_t chunkSize;
        char format[4];
        char subChunk1ID[4];
        uint32_t subChunk1Size;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
        char subChunk2ID[4];
        uint32_t subChunk2Size;
    } WavHeader;

    typedef struct {
        WavHeader header;
        std::vector<int16_t> data;
    } WavFile;

    bool read_wav(const std::string& test_name, const std::string& filename, WavFile& wav_data);
    bool write_wav(const std::string& test_name, const std::string& filename, const WavFile& wav_data);
    std::vector<double> convert_to_double(const WavFile& wav_data);
    std::vector<int16_t> convert_to_int16(const std::vector<double>& double_data);

}  // namespace WavHelper
