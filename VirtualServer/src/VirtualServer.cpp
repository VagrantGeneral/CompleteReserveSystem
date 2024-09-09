#include<iostream>
#include<memory>
#include"VMyEvent.hpp"
#include"Logger.hpp"
#include "LogFile.hpp"
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

int main(int argc,char *argv[]) {
    if (argc < 3) {
        std::cout << "input ip and port" << std::endl;
        return 1;
    }

    ProgressBar_Load("Virtual Server Load");

    lfile.reset(new LOG::LogFile("/home/hankangkai/Project2/logfile/ServerLog/VirtualServerLog"));

    LOG::Logger::setOutput(filewrite);
    LOG::Logger::setFlush(fileflush);

    LOG::Logger::setLogLevel(LOG::LOG_LEVEL::TRACE);

    LOG_DEBUG << "main begin ...";

    std::cout << "<<<<<<<<THE VIRTUAL SERVER HAS BEEN STARTED>>>>>>>>>" << std::endl;
    //std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;

    const char *ip = argv[1];
    const int port = atoi(argv[2]);
    SER::VMyEvent LvsMyEventLoop(ip, port);
    LvsMyEventLoop.Run();
    return 0;
}