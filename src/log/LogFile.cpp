
#include <sys/types.h> 
#include <unistd.h>   
#include <string>
#include "LogCommon.hpp"
#include "LogFile.hpp"

namespace LOG {
    pid_t pid() {
        return ::getpid();
    }

    const std::string hostname() {
        char buff[SMALL_BUFF_LEN] = {};
        if (::gethostname(buff, SMALL_BUFF_LEN)) {
            buff[SMALL_BUFF_LEN - 1] = '\0';
            return std::string(buff);
        }
        else {
            return std::string("unknowHost");
        }
    }

    void LogFile::append_unlocked(const char* info, const size_t len) {
        file_->append(info, len);
        if (file_->writenBytes() > rollSize_) {
            rollFile();
        }
        else {
            count_+= 1;
            if (count_ >= checkEveryN_) {
                count_ = 0;
                time_t now = ::time(nullptr);
                time_t thisPeriod = (now / kRollPerSeconds_) * kRollPerSeconds_;
                if (thisPeriod != startOfPeriod_) {
                    rollFile();
                }
                else if (now - lastOfFlush_ > flushInterval_) {
                    lastOfFlush_ = now;
                    file_->flush();
                }
            }
        }
    }
        
    std::string LogFile::getLogFileName(const std::string& basename, const LOG::Timestamp& now) {
        std::string filename;
        filename.reserve(basename.size() + SMALL_BUFF_LEN);
        filename = basename;
        filename += now.toFormattedFile();
        filename += LOG::hostname();
        char pidbuff[SMALL_BUFF_LEN] = {};
        snprintf(pidbuff, SMALL_BUFF_LEN, "%d", LOG::pid());
        filename += pidbuff;
        filename += ".log";
        return filename;
    }

    LogFile::LogFile(const std::string& basename,
                size_t roollSize,
                int threadSafe,
                int flushInterval,
                int checkEvent) :
                basename_(basename),
                rollSize_(roollSize),
                flushInterval_(flushInterval),
                checkEveryN_(checkEvent),
                count_(0),
                mutex_{threadSafe ? new std::mutex{} : nullptr},
                startOfPeriod_(0),
                lastOfFlush_(0),
                lastOfRoll_(0) {
        //create
        rollFile();
                
    }

    LogFile::~LogFile() {
        //delete
    }

    void LogFile::append(const std::string& info) {
        append(info.c_str(), info.size());
    }

    void LogFile::append(const char* info, const size_t len) {
        if (mutex_) {
            std::unique_lock<std::mutex> lock(*mutex_);
            append_unlocked(info, len);
        }
        else {
            append_unlocked(info, len);
        }
    }

    void LogFile::flush() {
        if (mutex_) {
            std::unique_lock<std::mutex> lock(*mutex_);
            file_->flush();
        }
        else {
            file_->flush();
        }
    }

    bool LogFile::rollFile() {
        LOG::Timestamp now;
        now.now();
        std::string filename = getLogFileName(basename_, now);
        time_t start = (now.getSecond() / kRollPerSeconds_) * kRollPerSeconds_;
        if (now.getSecond() > lastOfRoll_) {
            lastOfRoll_ = now.getSecond();
            lastOfFlush_ = now.getSecond();
            startOfPeriod_ = start;
            file_.reset(new LOG::AppendFile(filename));
            return true;
        }
        return false;
    }

}