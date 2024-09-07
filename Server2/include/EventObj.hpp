#ifndef EVENTOBJ_HPP
#define EVENTOBJ_HPP
#include <event.h>
#include <unistd.h>
#include "Logger.hpp"
#include "MyEvent.hpp"

namespace SER {
    class MyEventLoop;

    class EventObj {
    protected:
        event* pEvent;
        //int fd;
        MyEventLoop* pMyEvent;

    public:
        EventObj();
        
        ~EventObj();

        event* getEvent();

        void setEvent(event* p);

        MyEventLoop* getMyEvent();

        void SetMyEvent(MyEventLoop* p);
    };
}

#endif