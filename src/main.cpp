#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


#include "Histogram.hpp"
#include "App.hpp"
#include "DatParser.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: sigview <datafile.dat>" << std::endl;
        return 1;
    }

    std::string inputFile  = argv[1];
    std::ifstream file(inputFile);
    if (!file) {
        std::cerr << "Error: cannot open file: " << inputFile << "\n";
        return 1;
    }

    // ---- Configuration -----------------------------------------
    // Histogram range and bin count.
    static const double HIST_MIN   = -2.0;   // This is in pC
    static const double HIST_MAX   = 30.0;   // This is in pC
    static const int    HIST_BINS  = 200;    // number of bins


    Histogram hist(HIST_MIN, HIST_MAX, HIST_BINS);

    // Statistics accumulators
    long long totalEvents    = 0;
    long long completeEvents = 0;  // the number of events with both CH0 and CH1 present
    long long skippedEvents  = 0;  // number of events missing one channel

    double sumQ   = 0.0;
    double sumQ2  = 0.0;  // to add square of te number
    double minQ   =  1e18;
    double maxQ   = -1e18;

    // Parser state
    bool   inEvent = false;
    double ch0_charge = 0.0, ch1_charge = 0.0;
    bool   hasCH0 = false, hasCH1 = false;
    int    currentEvent = 0;

    auto processEvent = [&]() {
        if (!inEvent) return;
        if (hasCH0 && hasCH1) {
            double qtotal = ch0_charge + ch1_charge;
            hist.fill(qtotal);
            sumQ  += qtotal;
            sumQ2 += qtotal * qtotal;
            if (qtotal < minQ) minQ = qtotal;
            if (qtotal > maxQ) maxQ = qtotal;
            ++completeEvents;
        } else {
            ++skippedEvents;
        }
    };
    

    //to parse the file into channel data
    std::string line;
    while (std::getline(file, line)) {
        // Strip Windows-style carriage return
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (isEventHeader(line)) {
            // Finalise previous event
            processEvent();

            // Start new event
            inEvent = true;
            hasCH0  = false;
            hasCH1  = false;
            ch0_charge = 0.0;
            ch1_charge = 0.0;
            double _unused = 0.0;
            parseEventHeader(line, currentEvent, _unused);
            ++totalEvents;

        } else if (inEvent && !line.empty() && line[0] != '=') {
            ChannelData ch;
            if (parseChannelLine(line, ch)) {
                if (ch.channelNb == 0) { ch0_charge = ch.charge; hasCH0 = true; }
                if (ch.channelNb == 1) { ch1_charge = ch.charge; hasCH1 = true; }
            }
        }
    }
    // Finalise last event
    processEvent();

    // Summary statistics
    double mean   = (completeEvents > 0) ? sumQ / completeEvents : 0.0;
    double var    = (completeEvents > 0) ? sumQ2 / completeEvents - mean * mean : 0.0;
    double stddev = (var > 0) ? std::sqrt(var) : 0.0;
    double fwhm = (stddev>0) ? 2.355*stddev : 0.0;

    SigView::RunInterface(hist, argv[1],fwhm );

    return 0;

}
