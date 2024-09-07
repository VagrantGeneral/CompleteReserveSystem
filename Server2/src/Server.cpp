#include <iostream>
#include <string>
#include <string.h>
#include "Logger.hpp"
#include "LogFile.hpp"
#include "MyEvent.hpp"
#include "MyTools.hpp"

std::unique_ptr<LOG::LogFile> lfile;

void filewrite(const std::string& msg) {
    //fprintf(stderr, "call filewrite: %s\n", msg.c_str());
    lfile->append(msg);
}

void fileflush() {
    //fprintf(stderr, "call fileflush \n");
    lfile->flush();
}

int main( int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "input ip and port" << std::endl;
        return 1;
    }

    ProgressBar_Load("Server Load");
    
    lfile.reset(new LOG::LogFile("/home/hankangkai/Project2/logfile/ServerLog/Server2Log"));

    LOG::Logger::setOutput(filewrite);
    LOG::Logger::setFlush(fileflush);

    LOG::Logger::setLogLevel(LOG::LOG_LEVEL::TRACE);

    LOG_INFO << "main begin ...";
    
    std::cout << "<<<<<<<<THE   SERVER   HAS   BEEN   STARTED>>>>>>>>>" << std::endl;
    /*
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
    */

    const char* ip = argv[1];
    const int port = atoi(argv[2]);
    SER::MyEventLoop myevent(ip, port);
    myevent.Run();

    //ProgressBar_Back();

    return 0;
}
