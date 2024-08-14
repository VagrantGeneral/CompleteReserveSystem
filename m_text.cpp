#include <cursor_control.hpp>
#include <progress_bar.hpp>
#include <progress_spinner.hpp>
#include <vector>
#include <string>
#include "MyTools.hpp"
using namespace indicators;

int main() {

  {
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
    
    // std::string str = "Loading......";
    // std::string str1 = "dddddd";

    // std::vector<std::string> status_text = {str, str, str, str, str, str, str, str, str1};
    // auto job = [&p, &index, &status_text]() {
    //   while (true) {
    //     if (p.is_completed()) {
    //       //p.set_option(option::PostfixText{"Load Successful!!!"});
    //       break;
    //     }
    //     p.set_option(option::PostfixText{status_text[index % status_text.size()]});
    //     p.set_progress(index);
    //     index += 1;
    //     std::this_thread::sleep_for(std::chrono::milliseconds(5));
    //   }
    // };

    auto job = [&p, &index]() {
      while (true) {
        if (p.is_completed()) {
          //p.set_option(option::PostfixText{"Load Successful!!!"});
          break;
        }
        p.set_option(option::PostfixText{"Load..."});
        p.set_progress(index);
        index += 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
      }
      //p.set_option(option::PostfixText{"Load Successful!!!"});
    };

    std::thread thread(job);
    thread.join();
  }
  ProgressBar_Load();
}