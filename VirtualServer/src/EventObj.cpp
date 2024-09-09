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

    VMyEvent* EventObj::GetMyEvent() {
        return pMyEvent;
    }

    void EventObj::SetMyEvent(VMyEvent* p) {
        pMyEvent = p;
    }
}