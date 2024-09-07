#ifndef MYEVENT_HPP
#define MYEVENT_HPP
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <event.h>
#include <iostream>
#include <string>
#include <map>
#include "Logger.hpp"
//#include "EventObj.hpp"
#include "EventRW.hpp"
#include "Acceptor.hpp"

namespace SER {
    class Acceptor;
    
    //class EventRW;

    class MyEventLoop {
    protected:
        struct event_base* m_pbase;

        Acceptor* m_accept;

        //int m_fd;

        std::map<int, EventRW*> eventrws;

        std::string m_SerIP;

        int m_SerPORT;

    protected:
        //static void eventCallBack(int fd, short ev, void* arg);//
    
    public:
        int InitListenfd();

        bool InitEvent();
        
        bool DespactchEvent();

        bool AddAcceptEvent(Acceptor* pacc);

        bool AddConnEvent(EventRW* prw);

        bool DelConnEvent(EventRW* prw);

        struct event_base* getEventBase();

        void Run();

    public:
        MyEventLoop(const std::string& ip, const short port);

        ~MyEventLoop();

        int getFd();
        
    };
}

#endif