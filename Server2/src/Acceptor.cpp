#include "Acceptor.hpp"

namespace SER {
    void Acceptor::newConnCallBack(int fd, short ev, void* arg) {
        if (arg == nullptr) {
            LOG_ERROR << "arg if nullptr";
            return;
        }
        Acceptor* pacc = static_cast<Acceptor*>(arg);
        MyEventLoop* pMyEvent = pacc->getMyEvent();
        event_base* base = pMyEvent->getEventBase();

        LOG_INFO << "accept_callback......";
        int connfd = -1;
        connfd = accept(fd, nullptr, nullptr);
        if (connfd == -1) {
            LOG_DEBUG << "accept error!!!";
            return;
        }
        LOG_INFO << "new client......";

        EventRW* evrw = nullptr;
        try {
            evrw = new EventRW(connfd, pMyEvent);
        }
        catch (const std::exception& e) {
            LOG_ERROR << "new EventRW error!!!" << e.what();
            return;
        }

        if (!pMyEvent->AddConnEvent(evrw)) {
            delete evrw;
            LOG_ERROR << "AddEvent error!!!";
            return;
        }
    }

    Acceptor::Acceptor(int fd, MyEventLoop* p)
        : listenfd(fd) {
        /* create */
        pMyEvent = p;
    }

    Acceptor::~Acceptor() {
        close(listenfd);
    }

    int Acceptor::getFd() {
        return listenfd;
    }

    
}