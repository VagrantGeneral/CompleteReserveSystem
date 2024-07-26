#ifndef LOGMESSAGE_HPP
#define LOGMESSAGE_HPP
#include <iostream>
#include <sstream>
#include <string>
#include "LogCommon.hpp"

namespace LOG {
    class LogMessage {
    private:
        std::string header_;
        std::string text_;
        LOG::LOG_LEVEL level_;

    public:
        LOG::LOG_LEVEL getLogLevel() const;

    public:
        LogMessage(const LOG::LOG_LEVEL& level, 
                   const std::string& filename, 
                   const std::string& funcname, 
                   const int line);

        ~LogMessage();

        const std::string toString() const;

        template<typename T>
        LogMessage& operator<<(const T& text) {
            std::stringstream ss;
            ss << " : " << text;
            text_ += ss.str();
            return *this;
        }

    };


}

#endif