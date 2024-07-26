#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <string>
#include <functional>
#include "LogCommon.hpp"
#include "LogMessage.hpp"

namespace LOG {
    class Logger {
    private:
        LOG::LogMessage impl_;

    private:
        static LOG_LEVEL s_level_;

    public:
        //func--->return null, param string
        using OutputFunc = std::function<void(const std::string& msg)>;
        //func--->return null, param null
        using FlushFunc = std::function<void(void)>;

        static OutputFunc s_output_;

        static FlushFunc s_flush_;

    public:
        Logger(const LOG_LEVEL& level,
               const std::string& filename,
               const std::string& funcname,
               const int line);

        ~Logger();

        LogMessage& stream();

    public:
        static LOG_LEVEL getLogLevel();

        static void setLogLevel(const LOG_LEVEL& level);

        static void setOutput(OutputFunc out);

        static void setFlush(FlushFunc flush);


    };

    #define LOG_TRACE \
        if (LOG::Logger::getLogLevel() <= LOG::LOG_LEVEL::TRACE) \
            LOG::Logger(LOG::LOG_LEVEL::TRACE, __FILE__, __func__, __LINE__).stream()

    #define LOG_DEBUG \
        if (LOG::Logger::getLogLevel() <= LOG::LOG_LEVEL::DEBUG) \
            LOG::Logger(LOG::LOG_LEVEL::DEBUG, __FILE__, __func__, __LINE__).stream()

    #define LOG_INFO \
        if (LOG::Logger::getLogLevel() <= LOG::LOG_LEVEL::INFO) \
            LOG::Logger(LOG::LOG_LEVEL::INFO, __FILE__, __func__, __LINE__).stream()

    #define LOG_WARN \
            LOG::Logger(LOG::LOG_LEVEL::WARN, __FILE__, __func__, __LINE__).stream()

    #define LOG_ERROR \
            LOG::Logger(LOG::LOG_LEVEL::ERROR, __FILE__, __func__, __LINE__).stream()

    #define LOG_FATAL \
            LOG::Logger(LOG::LOG_LEVEL::FATAL, __FILE__, __func__, __LINE__).stream()
       


}




#endif