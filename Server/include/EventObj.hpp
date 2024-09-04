#ifndef EVENTOBJ_HPP
#define EVENTOBJ_HPP
#include <event.h>
#include "Logger.hpp"

namespace SER {
    class EventObj {
    protected:
        event* pEvent;
        //int fd;

    public:
        EventObj() {
            /*create*/
        }

        event* getEvent() {
            return pEvent;
        }

        void setEvent(event* p) {
            pEvent = p;
        }

    public:
        virtual void messageCallBack() = 0;

        virtual ~EventObj() { /*delete*/ }
    };
}

#endif