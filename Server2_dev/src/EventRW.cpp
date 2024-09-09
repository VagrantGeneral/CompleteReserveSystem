#include "EventRW.hpp"

namespace SER {
    void EventRW::messageCallBack(int fd, short ev, void* arg) {
        EventRW* prw = static_cast<EventRW*>(arg);
        
        LOG_INFO << "EventRW StartCallBack...";
        const int len = 1024;
        char buff[len] = {};
        ssize_t byte_read = 0;

        byte_read = recv(fd, buff, len - 1, 0);
        if (byte_read <= 0) {
            if (byte_read == 0) {
                LOG_DEBUG << "client off line";
            }
            else {
                if (errno != EINTR) {
                    LOG_DEBUG << "recv() error!!!";
                }
            }
            prw->getMyEvent()->DelConnEvent(prw);
        }
        else {
            LOG_INFO << "client : " << fd << " : " << buff;
            send(fd, buff, byte_read, 0);
            memset(buff, 0, byte_read);
        }
    }

    EventRW::EventRW(int fd, MyEventLoop* p) 
        : m_connfd(fd)
        , peerAddr{} {
        pMyEvent = p;
    }

    EventRW::~EventRW() {
        close(m_connfd);
    }

    int EventRW::getFd() {
        return m_connfd;
    }

    void EventRW::SetPeerAddr(struct sockaddr_in& peer) {
        peerAddr = peer;
    }

    struct sockaddr_in& EventRW::GetPeerAddr() {
        return peerAddr;
    }

    // void EventRW::messageCallBack() {
    //     event* ev = pEvent;
    //     LOG_INFO << "EventRW StartCallBack...";
    //     const int len = 1024;
    //     char buff[len] = {};
    //     ssize_t byte_read = 0;

    //     byte_read = recv(m_connfd, buff, len - 1, 0);
    //     if (byte_read == 0) {
    //         LOG_DEBUG << "client off line";
    //         event_del(ev);
    //         event_free(ev);
    //         delete(this);
    //     }
    //     else if (byte_read == -1) {
    //         if (errno != EINTR) {
    //             LOG_DEBUG << "recv() error!!!";
    //             event_del(ev);
    //             event_free(ev);
    //             delete(this);
    //         }
    //     }
    //     else {
    //         LOG_INFO << "client : " << m_connfd << " : " << buff;
    //         send(m_connfd, buff, byte_read, 0);
    //         memset(buff, 0, byte_read);
    //     }
    // }
}