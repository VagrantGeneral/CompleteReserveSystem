#ifndef MYEVENT_HPP
#define MYEVENT_HPP
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <event.h>
#include <iostream>
#include "Acceptor.hpp"
#include "EventRW.hpp"
#include "Logger.hpp"
#include "EventObj.hpp"

namespace SER {
    class Acceptor;
    
    class EventObj;

    class MyEvent {
    protected:
        struct event_base* m_pbase;

        Acceptor* m_accept;

        int m_fd;

        std::string m_SerIP;

        int m_SerPORT;

    protected:
        static void eventCallBack(int fd, short ev, void* arg);//
    
    public:
        bool InitListenfd();

        bool InitEvent(int fd);

        bool AddEvent(int fd, EventObj* pobj);

        bool DelEvent();

        bool DespactchEvent();

    public:
        struct event_base* getEventBase();

    public:
        MyEvent(const std::string& ip, const short port);

        ~MyEvent();

        void Run();
    };
}

#endif