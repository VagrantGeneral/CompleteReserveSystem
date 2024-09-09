#ifndef EVENTRW_HPP
#define EVENTRW_HPP
#include <event.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include "EventObj.hpp"
#include "Logger.hpp"
#include "MyEvent.hpp"

namespace SER {
    class MyEventLoop;

    class EventRW : public EventObj {
    private:
        int m_connfd;

        struct sockaddr_in peerAddr;

    public:
        static void messageCallBack(int fd, short ev, void* arg);

    public:
        EventRW(int fd, MyEventLoop* p);

        ~EventRW();

        int getFd();

        void SetPeerAddr(struct sockaddr_in& peer);

        struct sockaddr_in& GetPeerAddr();
    };
}

#endif