#pragma once

#include <vector>
#include <complex>

namespace DSP {

class DSPObject {
public:
    virtual ~DSPObject() = default;
    virtual void process(const std::vector<double>& input, std::vector<double>& output) = 0;
};

class Filter : public DSPObject {
public:
    Filter(int order);
    virtual ~Filter() = default;

protected:
    int m_order;
    std::vector<double> m_coefficients;
};

}