#pragma once

#include <string>
#include <vector>

struct ChannelData {
    int    channelNb;
    double baseline;
    double amplitude;
    double charge;
    double leadingEdge;
    double trailingEdge;
};

struct Event {
    int    eventNumber;
    double unixTime;
    std::vector<ChannelData> channels;
};

bool parseChannelLine(const std::string& line, ChannelData& ch);
bool isEventHeader(const std::string& line);
void parseEventHeader(const std::string& line, int& evNum, double& unixTime);
