#include "EventRW.hpp"

namespace SER {
    EventRW::EventRW(int fd) : m_connfd(fd) {

    }

    EventRW::~EventRW() {
        close(m_connfd);
    }

    void EventRW::messageCallBack() {
        event* ev = pEvent;
        LOG_INFO << "EventRW StartCallBack...";
        const int len = 1024;
        char buff[len] = {};
        ssize_t byte_read = 0;

        byte_read = recv(m_connfd, buff, len - 1, 0);
        if (byte_read == 0) {
            LOG_DEBUG << "client off line";
            event_del(ev);
            event_free(ev);
            delete(this);
        }
        else if (byte_read == -1) {
            if (errno != EINTR) {
                LOG_DEBUG << "recv() error!!!";
                event_del(ev);
                event_free(ev);
                delete(this);
            }
        }
        else {
            LOG_INFO << "client : " << m_connfd << " : " << buff;
            send(m_connfd, buff, byte_read, 0);
            memset(buff, 0, byte_read);
        }
    }
}