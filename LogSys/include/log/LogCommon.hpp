#ifndef LOG_COMMON_HPP
#define LOG_COMMON_HPP

namespace LOG {

    static const int SMALL_BUFF_LEN = 128;
    static const int MEDIAN_BUFF_LEN = 512;
    static const int LARGE_BUFF_LEN = 1024;

    //
    enum class LOG_LEVEL {
        TRACE = 0,              //genzong
        DEBUG,                  //tiaoshi
        INFO,                   //xinxi
        WARN,                   //jinggao
        ERROR,                  //cuowu
        FATAL,                  //zhimingcuowu
        NUM_LOG_LEVELs,         //jibieshu
    };

    //
    static const char* LLtoStr[] = {
        "TRACE",
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR",
        "FATAL",
        "NUM_LOG_LEVELS",
    };

    //

}



#endif