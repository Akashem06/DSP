#include "core/low_pass.hpp"

#include <cmath>

namespace DSP {

    LowPass::LowPass(int order, double cutoff_frequency, double sample_rate) : Filter(order), prev_output(0.0f) {
        m_coefficients.resize(m_order + 1);
        /* Normalize the frequency via cutoffFrequency / Nyquist Frequency */
        double norm_cutoff = cutoff_frequency / (sample_rate / 2.0);

        for (int n = 0; n <= m_order; ++n) {
            // Calculate the sinc function
            if (n == m_order / 2) {
                m_coefficients[n] = 2 * norm_cutoff;  // Center coefficient
            } else {
                m_coefficients[n] = sin(2 * M_PI * norm_cutoff * (n - m_order / 2)) / (M_PI * (n - m_order / 2));
                // Apply Hamming window
                m_coefficients[n] *= 0.54 - 0.46 * cos(2 * M_PI * n / m_order);
            }
        }

        // Normalize coefficients
        double sum = 0.0;
        for (double coef : m_coefficients) { sum += coef; }
        for (double& coef : m_coefficients) {
            coef /= sum;  // Normalize to make the gain at DC equal to 1
        }
    };

    void LowPass::process(const std::vector<double>& input, std::vector<double>& output) {
        output.resize(input.size());

        for (size_t n = 0; n < input.size(); ++n) {
            output[n] = 0.0;

            /* Convolution operation */
            for (int k = 0; k <= m_order; ++k) {
                if (n >= k) { output[n] += m_coefficients[k] * input[n - k]; }
            }
        }
    }

}  // namespace DSP