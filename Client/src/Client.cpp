#include <string>
#include "Logger.hpp"
//#include "AsyncLogging.hpp"
#include "CUser.hpp"
#include "Logger.hpp"
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

int main() {
    ProgressBar_Load("Client Load");

    lfile.reset(new LOG::LogFile("/home/hankangkai/Project2/logfile/ClientLog/ClientLog"));

    LOG::Logger::setOutput(filewrite);
    LOG::Logger::setFlush(fileflush);

    LOG::Logger::setLogLevel(LOG::LOG_LEVEL::TRACE);

    LOG_DEBUG << "main begin ...";

    CLI::CUser user;
    // if (!user.ConnectToSer()) {
    //     LOG_FATAL << "connect Ser error ";
    //     return 1;
    // }
    int select = 0;
    std::string name;
    std::string tel;
    std::string pws;
    int ret = 0;
    do {
        std::cout << "<<<<<<<<WELCOME TO THE RESERVATION SYSTEM>>>>>>>>>>>" << std::endl;
        std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
        std::cout << "■                                                  ■" << std::endl;
        std::cout << "■       1.Regist      2.LogIn       0.exit         ■" << std::endl;
        std::cout << "■                                                  ■" << std::endl;
        std::cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << std::endl;
        std::cout << "■ <<<<<<<<<<<  Make your Select?  >>>>>>>>>>>>>>>> ■" << std::endl;
        std::cin >> select;

        switch (select) {
        case 0:
            LOG_INFO << "exit ...";
            ProgressBar_Back();
            break;
        case 1:
            std::cout << "INPUT tel name pws" << std::endl;
            std::cin >> tel >> name >> pws;
            ret = user.Register(name, pws, tel);
            switch (ret) {
            case 0:
                ProgressBar_Num();
                std::cout << "Register success" << std::endl;
                break;
            case 1:
                break;
            case 2:
                break;
            }
            break;
        case 2:
            std::cout << "input tel pws" << std::endl;
            std::cin >> tel >> pws;
            ret = user.LogIn(tel, pws);
            switch (ret) {
            case 0:
                ProgressBar_Num();
                std::cout << "LogIn success" << std::endl;
                break;
            case 1:
                break;
            }
            break;
        }

    } 
    while (select != 0);

    return 0;
}