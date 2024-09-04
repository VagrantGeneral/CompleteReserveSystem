#ifndef EVENTRW_HPP
#define EVENTRW_HPP
#include <event.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "EventObj.hpp"

namespace SER {
    class EventRW : public EventObj {
    private:
        int m_connfd;

    public:
        EventRW(int fd);

        ~EventRW();

        virtual void messageCallBack() override;
    };
}

#endif