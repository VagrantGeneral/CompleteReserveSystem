
#include <string>
#include "Logger.hpp"

namespace LOG {
    LOG::LOG_LEVEL InitLogLevel() {
        //DuQu env BianLiang
        if (::getenv("LOG::LOG_TRACE")) {
            return LOG::LOG_LEVEL::TRACE;
        }
        else if (getenv("LOG::LOG_DEBUG")) {
            return LOG::LOG_LEVEL::DEBUG;
        }
        else {
            return LOG::LOG_LEVEL::INFO;
        }
    }

    void defaultOutput(const std::string& msg) {
        size_t n = fwrite(msg.c_str(), sizeof(char), msg.size(), stdout);
    }

    void defaultFlush() {
        fflush(stdout);
    }

    Logger::OutputFunc Logger::s_output_ = defaultOutput;

    Logger::FlushFunc Logger::s_flush_ = defaultFlush;

    void Logger::setOutput(OutputFunc out) {
        s_output_ = out;
    }

    void Logger::setFlush(FlushFunc flush) {
        s_flush_ =  flush;
    }

    LOG_LEVEL Logger::s_level_ = InitLogLevel();

    LOG_LEVEL Logger::getLogLevel() {
        return s_level_;
    }

    void Logger::setLogLevel(const LOG_LEVEL& level) {
        s_level_ = level;
    }

    Logger::Logger(const LOG_LEVEL& level,
               const std::string& filename,
               const std::string& funcname,
               const int line) 
               : impl_(level, filename, funcname, line) {
        //create
    }

    Logger::~Logger() {
        impl_ << '\n';
        s_output_(impl_.toString());
        if (impl_.getLogLevel() == LOG::LOG_LEVEL::FATAL) {
            s_flush_();
            fprintf(stderr, "Process exit!!!\n");
            exit(1);
        }
    }

    LogMessage& Logger::stream() {
        return impl_;
    }

}