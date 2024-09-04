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

void ProgressBar_Num() {
  indicators::ProgressBar p;
  p.set_option(option::BarWidth{0});
  p.set_option(option::PrefixText{"Reading Data... "});
  p.set_option(option::Start{""});
  p.set_option(option::Fill{""});
  p.set_option(option::Lead{""});
  p.set_option(option::Remainder{""});
  p.set_option(option::End{""});
  p.set_option(option::ForegroundColor{indicators::Color::white});
  p.set_option(option::ShowPercentage{false});
  p.set_option(option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}});
  auto job = [&p]() {
    while (true) {
      p.set_option(option::PrefixText{"Reading Data... " + std::to_string(p.current()) + "% "});

      if (p.current() + 2 >= 100) {
        p.set_option(option::PrefixText{"Reading Data... Done"});
      }
      p.tick();
      if (p.is_completed()) {
        break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
  };
  std::thread thread(job);
  thread.join();
}


void ProgressBar_Back() {
  indicators::ProgressBar p{
    option::BarWidth{50},
    option::ProgressType{ProgressType::decremental},
    option::Start{"["},
    option::Fill{"■"},
    option::Lead{"■"},
    option::Remainder{"-"},
    option::End{" ]"},
    option::ForegroundColor{indicators::Color::white},
    option::PostfixText{"System Back!!!"},
    option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};

    auto job = [&p]() {
      while (true) {
        p.tick();
        if (p.is_completed()) {
          //p.set_option(option::PostfixText{"System Back Complate!!!"});
          break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
    };

    std::thread thread(job);
    thread.join();
}

#endif 