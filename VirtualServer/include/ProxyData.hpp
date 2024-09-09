#ifndef PROXYDATA_HPP
#define PROXYDATA_HPP
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Logger.hpp"
#include "EventObj.hpp"
#include "VMyEvent.hpp"
#include "ConsistentHash.hpp"

namespace SER {
    class VMyEvent;

    class ProxyData : public EventObj {
    
    private:
        int m_connfd;

        struct sockaddr_in peerAddr;

    public:
        int m_serfd;

        struct sockaddr_in m_seraddr;

        int tag;

    public:
        static void messageCallBack(int fd, short ev, void *arg);

    public:
        void SetSerAddr(struct sockaddr_in addr);

        bool ConnSer();

        //void setSerFd(int fd);

        int getSerFd() const;

        bool IsConnSer() const;

        ProxyData(int fd, VMyEvent *p);

        ~ProxyData();

        int getFd() const;

        void setPeerAddr(const sockaddr_in &addr);
        
        const sockaddr_in &getPeerAddr() const;
    };
}

#endif