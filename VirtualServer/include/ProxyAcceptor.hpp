#ifndef PROXYACCEPTOR_HPP
#define PROXYACCEPTOR_HPP
#include <string.h>
#include <errno.h>
#include "EventObj.hpp"
#include "VMyEvent.hpp"
#include "Logger.hpp"
#include "ProxyData.hpp"

namespace SER {
    class VMyEvent;

    class ProxyAcceptor : public EventObj {
    private:
        int listenfd;
        
    public:
        static void newconnCallBack(int fd, short ev, void *arg);

    public:
        ProxyAcceptor(int fd, VMyEvent *p);

        ~ProxyAcceptor();

        int getFd() const;
    };

}

#endif