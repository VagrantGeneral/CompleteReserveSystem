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

        struct sockaddr_in peeraddr = {};
        size_t len = sizeof(peeraddr);
        // addr.sin_family
        // addr.sin_port
        // addr.sin_addr.s_addr

        connfd = accept(fd, (sockaddr*)&peeraddr, (socklen_t*)&len);
        if (connfd == -1) {
            LOG_DEBUG << "accept error!!!";
            return;
        }
        LOG_INFO << "new client " << peeraddr.sin_addr.s_addr;
        std::cout << peeraddr.sin_addr.s_addr << std::endl;

        EventRW* evrw = nullptr;
        try {
            evrw = new EventRW(connfd, pMyEvent);
        }
        catch (const std::exception& e) {
            LOG_ERROR << "new EventRW error!!!" << e.what();
            return;
        }
        evrw->SetPeerAddr(peeraddr);

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