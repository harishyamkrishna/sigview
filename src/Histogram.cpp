#include "Histogram.hpp"
#include <algorithm>
#include <numeric>

Histogram::Histogram(double mn, double mx, int nb)
    : binMin(mn), binMax(mx), nBins(nb),
      binWidth((mx - mn) / nb), counts(nb, 0) {}

void Histogram::fill(double value) {
    if (value < binMin) {
        ++underflow;
        return;
    }
    if (value >= binMax) {
        ++overflow;
        return;
    }

    int bin = static_cast<int>((value - binMin) / binWidth);

    // Safety check for floating point edge cases
    if (bin >= 0 && bin < nBins) {
        ++counts[bin];
    } else {
        ++overflow;
    }
}

double Histogram::binCenter(int i) const {
    return binMin + (i + 0.5) * binWidth;
}

long long Histogram::maxCount() const {
    if (counts.empty()) return 0;
    return *std::max_element(counts.begin(), counts.end());
}

long long Histogram::totalFilled() const {
    return std::accumulate(counts.begin(), counts.end(), 0LL);
}