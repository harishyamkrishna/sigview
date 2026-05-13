#pragma once

#include <string>
#include <vector>

// This structure hold the data of each channels
struct ChannelData {
    int    channelNb;
    double baseline;
    double amplitude;
    double charge;
    double leadingEdge;
    double trailingEdge;
};

//Each event is characterised by its event number, the time it is happened.
// There is two channels in a event
struct Event {
    int    eventNumber;
    double unixTime;
    std::vector<ChannelData> channels;
};

// This will parse an event line to corresponding channel data
bool parseChannelLine(const std::string& line, ChannelData& ch);

// This will check if a line is an event header.
bool isEventHeader(const std::string& line);

// This will parse an event header.
void parseEventHeader(const std::string& line, int& evNum, double& unixTime);
