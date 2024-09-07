#ifndef ACCEPTOR_HPP
#define ACCEPTOR_HPP
#include <event.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "EventObj.hpp"
#include "Logger.hpp"
//#include "MyEvent.hpp"
#include "EventRW.hpp"

namespace SER {
    class MyEventLoop;

    class Acceptor : public EventObj {
    private:
        int listenfd;

    public:
        static void newConnCallBack(int fd, short ev, void* arg);

    public:
        Acceptor(int fd, MyEventLoop* p);

        ~Acceptor();

        int getFd();

    };
}

#endif 