#ifndef EVENTOBJ_HPP
#define EVENTOBJ_HPP
#include <event.h>
#include <unistd.h>
#include "Logger.hpp"
//#include "MyEvent.hpp"

namespace SER {
    //class MyEventLoop;

    class VMyEvent;

    class EventObj {
    protected:
        event* pEvent;
        //int fd;
        VMyEvent* pMyEvent;

    public:
        EventObj();
        
        ~EventObj();

        event* getEvent();

        void setEvent(event* p);

        VMyEvent* GetMyEvent();

        void SetMyEvent(VMyEvent* p);

    };
}

#endif