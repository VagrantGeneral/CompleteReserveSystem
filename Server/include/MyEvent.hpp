#ifndef MYEVENT_HPP
#define MYEVENT_HPP
#include <string.h>
#include <string>
#include "Acceptor.hpp"

namespace SER {
    class Acceptor;
    class MyEvent {
    protected:
        static void eventCallback();

    protected:
        struct event_base* m_pbase;

        Acceptor* m_accept;

        int m_fd;

        std::string m_SerIP;

        int m_SerPORT;
    };
}

#endif