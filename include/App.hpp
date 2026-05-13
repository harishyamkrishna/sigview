#pragma once
#include "Histogram.hpp"
#include <string>

namespace SigView {
    void RunInterface(const Histogram& hist, const std::string& filename, const double& fwhm);
}
