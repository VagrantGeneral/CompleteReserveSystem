
#include "LogMessage.hpp"
#include "Timestamp.hpp"
#include "LogCommon.hpp"

namespace LOG {

    //std::string header_;
    //std::string text_;
    //LOG::LOG_LEVEL level_;

    LOG::LOG_LEVEL LogMessage::getLogLevel() const {
        return level_;
    }

    LogMessage::LogMessage(const LOG::LOG_LEVEL& level, 
                           const std::string& filename, 
                           const std::string& funcname, 
                           const int line) 
        : header_{},
          text_{},
          level_(level) {
        //create
        std::stringstream ss;
        ss << "[" << LOG::Timestamp::Now().toFormattedString() << "] ";
        ss << LOG::LLtoStr[static_cast<int>(level)] << " ";
        const size_t pos = filename.find_last_of('/');
        const std::string fname = filename.substr(pos + 1);
        ss << fname << " ";
        ss << funcname << " ";
        ss << line << " ";
        header_ = ss.str();
        //
    }

    LogMessage::~LogMessage() {
        //delete
    }

    const std::string LogMessage::toString() const {
        return header_ + text_;
    }

}