#ifndef MYTOOLS_HPP
#define MYTOOLS_HPP
#include <cursor_control.hpp>
#include <progress_bar.hpp>
#include <progress_spinner.hpp>
#include <vector>
#include <string>
using namespace indicators;

void ProgressBar_Load() {
    indicators::ProgressBar p{
        option::BarWidth{50},
        option::Start{"["},
        option::Fill{"■"},
        option::Lead{"■"},
        option::Remainder{" "},
        option::End{" ]"},
        option::ForegroundColor{indicators::Color::yellow},
        option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
    };

    std::atomic<size_t> index{0};

    auto job = [&p, &index]() {
      while (true) {
        if (p.is_completed()) {
          break;
        }
        p.set_option(option::PostfixText{"load"});
        p.set_progress(index);
        index += 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
      }
    };

    std::thread thread(job);
    thread.join();
}


void ProgressBar_Load(const std::string& text) {
    indicators::ProgressBar p{
        option::BarWidth{50},
        option::Start{"["},
        option::Fill{"■"},
        option::Lead{"■"},
        option::Remainder{" "},
        option::End{" ]"},
        option::ForegroundColor{indicators::Color::yellow},
        option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
    };

    std::atomic<size_t> index{0};

    auto job = [&p, &index, &text]() {
      while (true) {
        if (p.is_completed()) {
          break;
        }
        p.set_option(option::PostfixText{text});
        p.set_progress(index);
        index += 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
      }
    };

    std::thread thread(job);
    thread.join();
}



#endif 