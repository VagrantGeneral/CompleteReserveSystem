#include "EventObj.hpp"

namespace SER {
    EventObj::EventObj() 
        : pEvent(nullptr)
        , pMyEvent(nullptr){
        /*create*/
    }
        
    EventObj::~EventObj() { 
        /*delete*/ 
    }

    event* EventObj::getEvent() {
        return pEvent;
    }

    void EventObj::setEvent(event* p) {
        pEvent = p;
    }    

    MyEventLoop* EventObj::getMyEvent() {
        return pMyEvent;
    }

    void EventObj::SetMyEvent(MyEventLoop* p) {
        pMyEvent = p;
    }
}