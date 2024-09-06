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
#include "MyEvent.hpp"
#include "EventRW.hpp"

namespace SER {
    class MyEvent;

    class Acceptor : public EventObj {
    private:
        int listenfd;

        MyEvent* pMyEvent;
    public:
        Acceptor(int fd, MyEvent* p);

        ~Acceptor();

        virtual void messageCallBack() override;
    };
}

#endif 