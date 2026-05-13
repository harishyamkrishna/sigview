#include <utility>

#include "App.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/canvas.hpp"
#include "ftxui/component/component.hpp"

using namespace ftxui;

void SigView::RunInterface(const Histogram& hist, const std::string& filename, const double& fwhm) {
    auto screen = ScreenInteractive::TerminalOutput();
    std::string filenamenew;

    auto renderer = Renderer([&] {
        
        auto c = Canvas(hist.nBins * 2, 100); // canvas to draw the Histogram 
        long long max_freq = hist.maxCount();
        

        for (int i = 0; i < hist.nBins; i++) {
           
            int h = (max_freq > 0) ? (hist.counts[i] * 100) / max_freq : 0;
            
            
            c.DrawBlockLine(i * 2, 100, i * 2, 100 - h, Color::Blue);
        }

        return vbox({
            text(" SigView - " + filename) | bold | center | color(Color::Cyan) | border,
            canvas(std::move(c)) | border, 
            hbox({
                text(" Range: [" + std::to_string(hist.binMin) + " : " + std::to_string(hist.binMax) + "]"),
                filler(),
                text(" FWHM: "+ std::to_string(fwhm)) | color(Color::Green) | bold,
            }) | border
        });
    });

    screen.Loop(renderer);
}
