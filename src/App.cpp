#include <utility>

#include "App.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/canvas.hpp"
#include "ftxui/component/component.hpp"

using namespace ftxui;

void SigView::RunInterface(const Histogram& hist, const std::string& filename) {
    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer([&] {
        // We use a canvas for high-resolution Braille plotting
        auto c = Canvas(200, 100); 
        long long max_freq = hist.maxCount();
        //double fwhm = hist.calculateFWHM(); // Use the method we added earlier

        for (int i = 0; i < hist.nBins; i++) {
            // Normalize height to the canvas (100 units high)
            int h = (max_freq > 0) ? (hist.counts[i] * 100) / max_freq : 0;
            
            // Draw lines using Braille dots (i*2 spreads them out slightly)
            c.DrawBlockLine(i * 2, 100, i * 2, 100 - h, Color::Blue);
        }

        return vbox({
            text(" SigView - " + filename) | bold | center | color(Color::Cyan),
            separator(),
            canvas(std::move(c)) | border | flex,
            hbox({
                text(" Range: [" + std::to_string(hist.binMin) + " : " + std::to_string(hist.binMax) + "]"),
                filler(),
                text(" FWHM: " /*+ std::to_string(fwhm)*/) | color(Color::Green) | bold,
            }) | border
        });
    });

    screen.Loop(renderer);
}