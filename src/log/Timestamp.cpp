
#include "LogCommon.hpp"
#include "Timestamp.hpp"
#include <ctime>
#include <sys/time.h>

namespace LOG {
    Timestamp::Timestamp() : microsec_(0) {
        //create
    }

    Timestamp::Timestamp(std::int64_t m) : microsec_(m){
        //create
    }

    Timestamp::~Timestamp() {
        //delete
    }

    
    void Timestamp::swap(Timestamp& other) {
        std::swap(this->microsec_, other.microsec_);
    }

    std::string Timestamp::toString() const {
        char buff[SMALL_BUFF_LEN] = {};
        std::int64_t sec = microsec_ / KMicroPerSeconds;
        std::int64_t micro = microsec_ % KMicroPerSeconds;
        sprintf(buff, "%ld.%06ld", sec, micro);
        return std::string(buff);
    }

    std::string Timestamp::toFormattedString(bool showmicro) const {
        char buff[SMALL_BUFF_LEN] = {};
        std::int64_t sec = microsec_ / KMicroPerSeconds;
        std::int64_t micro = microsec_ % KMicroPerSeconds;
        struct tm tm_time;
        //gmtime_r(&sec, &tm_time);
        localtime_r(&sec, &tm_time);

        int len = sprintf(buff, "%04d/%02d/%02d-%02d:%02d:%02d", 
                            tm_time.tm_year + 1900,
                            tm_time.tm_mon + 1,
                            tm_time.tm_mday,
                            tm_time.tm_hour,
                            tm_time.tm_min,
                            tm_time.tm_sec
        );

        if (showmicro) {
            sprintf(buff + len, ".%ldZ", micro);
        }

        return std::string(buff);

    }

    std::string Timestamp::toFormattedFile() const {
        char buff[SMALL_BUFF_LEN] = {};
        std::int64_t sec = microsec_ / KMicroPerSeconds;
        struct tm tm_time;
        //gmtime_r(&sec, &tm_time);
        localtime_r(&sec, &tm_time);

        sprintf(buff, "%04d%02d%02d%02d%02d%02d", 
                            tm_time.tm_year + 1900,
                            tm_time.tm_mon + 1,
                            tm_time.tm_mday,
                            tm_time.tm_hour,
                            tm_time.tm_min,
                            tm_time.tm_sec
        );

        return std::string(buff);
    }

    bool Timestamp::valid() const {
        return microsec_ > 0;
    }

    std::int64_t Timestamp::getMicro() const {
        return microsec_;
    }

    std::int64_t Timestamp::getSecond() const {
        return microsec_ / KMicroPerSeconds;
    }

    const Timestamp & Timestamp::now() {
        *this = Timestamp::Now();
        return *this;
    }  

    //static

    Timestamp Timestamp::Now() {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        std::int64_t seconds = tv.tv_sec;
        return Timestamp(seconds * KMicroPerSeconds + tv.tv_usec);
    }

    Timestamp Timestamp::Invalid() {
        return Timestamp(0);
    }
}