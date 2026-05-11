#include "DatParser.hpp"
#include <cstdio>

bool parseChannelLine(const std::string& line, ChannelData& ch) {
    return std::sscanf(line.c_str(), "%d %lf %lf %lf %lf %lf",
                       &ch.channelNb,
                       &ch.baseline,
                       &ch.amplitude,
                       &ch.charge,
                       &ch.leadingEdge,
                       &ch.trailingEdge) == 6;
}

bool isEventHeader(const std::string& line) {
    return line.find("=== Event") != std::string::npos;
}

void parseEventHeader(const std::string& line, int& evNum, double& unixTime) {
    std::sscanf(line.c_str(),
                "=== Event %d UnixTime = %lf",
                &evNum, &unixTime);
}
