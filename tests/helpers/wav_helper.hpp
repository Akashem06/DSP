#pragma once

#include <vector>
#include <string>

void read_wav(const std::string& filename, std::vector<double>& data);
void write_wav(const std::string& filename, const std::vector<double>& data, int sampleRate);