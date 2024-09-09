#ifndef VMYEVENT_HPP
#define VMYEVENT_HPP
#include <map>
#include <event.h>

#include <iostream>
#include <string>
#include <csignal>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <event.h>
#include "Logger.hpp"
#include "ProxyAcceptor.hpp"
#include "ProxyData.hpp"
#include"ConsistentHash.hpp"

namespace SER {
    class ProxyData;

    class ProxyAcceptor;

    class VMyEvent {
    protected:
        static void exitCallBack(int fd, short ev, void *arg);

        static void stdinCallBack(int fd, short ev, void *arg);

    protected:
        struct event_base *m_pbase;

        struct event *psignal;

        struct event *ev_stdin;

        ProxyAcceptor *m_accept;

        std::string m_SerIp;

        int m_SerPort;

        std::map<int, ProxyData *> m_proxydatas;
        
        ConsistentHash m_SerPool;

        int InitListenfd();

        bool InitEvent();

        bool DispactchEvent();

        bool Loopbreak();

    public:
        VMyEvent(const std::string &ip = "127.0.0.1", const int port = 8011);

        ~VMyEvent();

        bool AddAcceptEvent(ProxyAcceptor *pacc);

        bool AddProxyConnEvent(ProxyData *prw);

        bool DelProxyConnEvent(ProxyData *prw);

        bool AddExitSignalEvent();

        bool AddStdinEvent();  

        struct event_base *getEventBase();

        void Run();

        int getConnNum() const;

        ConsistentHash * getSerPool() { return &m_SerPool; }
    };

}

#endif