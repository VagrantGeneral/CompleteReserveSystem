#ifndef LOGFILE_HPP
#define LOGFILE_HPP
#include <iostream>
#include <string>
#include <mutex>
#include <memory>
#include <time.h>
#include "Timestamp.hpp"
#include "AppendFile.hpp"

namespace LOG {
    class LogFile {
    private:
        const std::string basename_;

        const size_t rollSize_;     //HuiGunSize

        const int flushInterval_;   //3s

        const int checkEveryN_;

        int count_;

    private:
        time_t startOfPeriod_;

        time_t lastOfRoll_;

        time_t lastOfFlush_;

    private:
        std::unique_ptr<std::mutex> mutex_;

        std::unique_ptr<LOG::AppendFile> file_;

    private:
        static const int kRollPerSeconds_ = 60 * 60 * 24;   //one day s
    
    private:
        void append_unlocked(const char* info, const size_t len);
        
        static std::string getLogFileName(const std::string& basename, const LOG::Timestamp& now);

    public:
        LogFile(const std::string& basename,
                size_t roollSize = 1024 * 1024 *10,
                int threadSafe = true,
                int flushInterval = 3,
                int checkEvent = 20);

        ~LogFile();

        void append(const std::string& info);

        void append(const char* info, const size_t len);

        void flush();

        bool rollFile();


    };
}


#endif