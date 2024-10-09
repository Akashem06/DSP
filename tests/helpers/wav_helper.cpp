#include "wav_helper.hpp"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace WavHelper {

    bool read_wav(const std::string& test_name, const std::string& filename, WavFile& wav_data) {
        std::string full_path = "tests/audio/" + test_name + "/" + filename;
        std::ifstream file(full_path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << full_path << std::endl;
            return false;
        }

        file.read(reinterpret_cast<char*>(&wav_data.header), sizeof(WavHeader));

        if (std::strncmp(wav_data.header.chunkID, "RIFF", 4) != 0 || std::strncmp(wav_data.header.format, "WAVE", 4) != 0) {
            std::cerr << "Not a valid WAV file" << std::endl;
            return false;
        }

        size_t num_samples = wav_data.header.subChunk2Size / (wav_data.header.bitsPerSample / 8);
        wav_data.data.resize(num_samples);

        file.read(reinterpret_cast<char*>(wav_data.data.data()), wav_data.header.subChunk2Size);
        file.close();
        return true;
    }

    bool write_wav(const std::string& test_name, const std::string& filename, const WavFile& wav_data) {
        std::string dir_path = "tests/results/" + test_name;
        std::filesystem::create_directories(dir_path);

        std::string full_path = dir_path + "/" + filename;
        std::ofstream file(full_path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << full_path << std::endl;
            return false;
        }
        file.write(reinterpret_cast<const char*>(&wav_data.header), sizeof(WavHeader));
        file.write(reinterpret_cast<const char*>(wav_data.data.data()), wav_data.header.subChunk2Size);

        file.close();
        return true;
    }

    std::vector<double> convert_to_double(const WavFile& wav_data) {
        std::vector<double> double_data;
        double_data.reserve(wav_data.data.size());

        for (int16_t sample : wav_data.data) { double_data.push_back(static_cast<double>(sample) / 32768.0); }

        return double_data;
    }

    std::vector<int16_t> convert_to_int16(const std::vector<double>& double_data) {
        std::vector<int16_t> int16_data;
        int16_data.reserve(double_data.size());

        for (double sample : double_data) { int16_data.push_back(static_cast<int16_t>(sample * 32768.0)); }

        return int16_data;
    }

}  // namespace WavHelper
