#pragma once
#include <complex>
#include <vector>

namespace DSP {

    class DSPObject {
       public:
        virtual ~DSPObject() = default;
        virtual void process(const std::vector<double>& input, std::vector<double>& output) = 0;
    };

    class Filter : public DSPObject {
       public:
        explicit Filter(int order) : m_order(order) {}
        ~Filter() override = default;

       protected:
        int m_order;
        std::vector<double> m_coefficients;
    };

}  // namespace DSP