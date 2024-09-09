
#include <iostream>
#include <libgen.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <memory>
#include "Timestamp.hpp"
#include "LogCommon.hpp"
#include "LogMessage.hpp"
#include "Logger.hpp"
#include "LogFile.hpp"
#include "AppendFile.hpp"
#include "ProxyClient.hpp"

int main() {
    std::cout << "fffff" << std::endl;
    
}


#if 0
std::unique_ptr<LOG::LogFile> lfile;

void filewrite(const std::string& msg) {
    fprintf(stderr, "call filewrite: %s\n", msg.c_str());
    lfile->append(msg);
}

void fileflush() {
    fprintf(stderr, "call fileflush \n");
    lfile->flush();
}

int main() {
    lfile.reset(new LOG::LogFile("/home/hankangkai/Project2/bin/log/logfile"));

    LOG::Logger::setOutput(filewrite);
    LOG::Logger::setFlush(fileflush);

    LOG::Logger::setLogLevel(LOG::LOG_LEVEL::TRACE);

    DB::ProxyClient client;
    client.ConnectToMySQLSer();

    if (client.MySQL_TelRegister("18700000001", "HHH", "123456")) {
        std::cout << "Register Successful" << std::endl;
        LOG_INFO << "Register Successful";
    }


    return 0;
}

#endif

#if 0
static FILE* fp;

void filewrite(const std::string& msg) {
    int n = fwrite(msg.c_str(), sizeof(char), msg.size(),fp);
}

void fileflush() {
    fflush(fp);
}

int main() {
    LOG::Logger::setOutput(filewrite);
    LOG::Logger::setFlush(fileflush);
    fp = fopen("/home/hankangkai/Project2/LOG.log", "w");
    if (fp == nullptr) {
        LOG_FATAL << "fp is NULL";
    }

    int a = 10;
    while (a > 0) {
        LOG_INFO << a;
        a--;
    }

    fclose(fp);
    return 0;
}
#endif

#if 0
int main() {
    const char* file = __FILE__;
    char buff[LOG::SMALL_BUFF_LEN] = {};
    strcpy(buff, file);
    char* f = basename(buff);

    LOG::LogMessage logmes(LOG::LOG_LEVEL::DEBUG, f, __func__, __LINE__);
    logmes << "begin main";
    std::cout << logmes.toString() << std::endl;
    return 0;
}

int main() {
    LOG::Timestamp ts;
    ts.now();
    std::cout << ts.toString() << std::endl;
    std::cout << ts.toFormattedFile()  << std::endl;
    std::cout << ts.toFormattedString()  << std::endl;
    std::cout << ts.valid()  << std::endl;
    return 0;
}
#endif