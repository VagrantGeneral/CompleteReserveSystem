#include "Acceptor.hpp"

namespace SER {
    Acceptor::Acceptor(int fd, MyEvent* p)
        : listenfd(fd)
        , pMyEvent(p) {
        /* create */
    }

    Acceptor::~Acceptor() {

    }

    void Acceptor::messageCallBack() {
        event_base* pbase = pMyEvent->getEventBase();
        LOG_INFO << "accept_callback......";
        int connfd = -1;
        connfd = accept(this->listenfd, nullptr, nullptr);
        if (connfd == -1) {
            LOG_DEBUG << "accept error!!!";
            return;
        }
        LOG_INFO << "new client......";
        
        std::cout << "new client : fd = " << connfd << std::endl;

        EventRW* evrw = nullptr;
        try {
            evrw = new EventRW(connfd);
        }
        catch (const std::exception& e) {
            LOG_ERROR << "new EventRW error!!!" << e.what();
            return;
        }

        if (!pMyEvent->AddEvent(connfd, evrw)) {
            delete evrw;
            LOG_ERROR << "AddEvent error!!!";
            return;
        }
        
    }
}