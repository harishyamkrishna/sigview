#pragma once
#include <vector>
#include <numeric>

struct Histogram {
    double binMin;
    double binMax;
    int    nBins;
    double binWidth;
    std::vector<long long> counts;
    long long underflow = 0;
    long long overflow  = 0;

    Histogram(double mn, double mx, int nb);
    void fill(double value);
    double binCenter(int i) const;
    long long maxCount() const;
    long long totalFilled() const;
};
