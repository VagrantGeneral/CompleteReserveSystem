#include "ProxyData.hpp"

namespace SER {
    // ProxyData : public EventObj
    // int m_connfd;
    ProxyData::ProxyData(int fd, VMyEvent *p)
        : m_connfd(fd)
        , m_serfd(-1)
        , m_seraddr{}
        , tag(0) {
        pMyEvent = p;

        LOG_INFO << "ProxyData::ProxyData(): " << fd;
    }

    ProxyData::~ProxyData() {
        LOG_INFO << "ProxyData::~ProxyData(): " << m_connfd;

        close(m_connfd);
        m_connfd = -1;
        close(m_serfd);
        m_serfd = -1;
    }

    int ProxyData::getFd() const {
        return m_connfd;
    }

    void ProxyData::setPeerAddr(const sockaddr_in &addr) {
        peerAddr = addr;
    }
    
    const sockaddr_in &ProxyData::getPeerAddr() const {
        return peerAddr;
    }

    // read write
    void ProxyData::messageCallBack(int fd, short ev, void *arg) {
        ProxyData *proxy= static_cast<ProxyData *>(arg);
        //cout << "clent_callback..." << endl;
        const int len = 1024;
        char buff[len] = {};
        ssize_t bytes_read = 0;
        // 反射信息
        bytes_read = recv(fd, buff, len - 1, 0);
        if (bytes_read <= 0) {
            if (0 == bytes_read) {
                LOG_DEBUG << "client offline ";
            }
            else {
                if (errno != EINTR) {
                    LOG_DEBUG << "client error : " << strerror(errno);
                }
            }
            proxy->GetMyEvent()->DelProxyConnEvent(proxy);
            //
        }
        else {
            if(!proxy->IsConnSer()) {
                struct sockaddr_in addr = proxy->getPeerAddr();
                std::stringstream ss;
                ss << inet_ntoa(addr.sin_addr);
                ss << " " << ntohs(addr.sin_port);
                std::string key = ss.str(); //"192.168.1.1 3455"
                // Ser pool
                std::string serloop = proxy->GetMyEvent()->getSerPool()->GetVirtualServerIndex(key);
                int pos = serloop.find(' ');
                std::string ip;
                ip.append(serloop, 0, pos); // ip
                std::string port;
                port.append(serloop, pos + 1, 8); // port
                struct sockaddr_in saddr;
                memset(&saddr, 0, sizeof(saddr));
                saddr.sin_family = AF_INET;
                saddr.sin_addr.s_addr = inet_addr(ip.c_str());
                saddr.sin_port = htons(atoi(port.c_str()));
                proxy->SetSerAddr(saddr);
                if(!proxy->ConnSer()) {
                    LOG_DEBUG << "ConnSer fail ...";
                    return; //
                }
            }

            send(proxy->getSerFd(), buff, bytes_read, 0);

            bytes_read = recv(proxy->getSerFd(), buff, len-1, 0);
            
            send(fd, buff, bytes_read, 0); memset(buff, 0, bytes_read);
        }
    }

   // int m_serfd;
   // struct sockaddr_in m_seraddr;

   // int tag; // 1 // ser conn;  0 ser not conn;
    //void setSerAddr(struct sockaddr_in addr);
    void ProxyData::SetSerAddr(struct sockaddr_in addr) {
       // memset(&m_seraddr, 0, sizeof(m_seraddr));
        m_seraddr = addr;
    }

    bool ProxyData::ConnSer() {
        m_serfd = socket(AF_INET, SOCK_STREAM, 0);
        if (-1 == m_serfd) {
            LOG_ERROR << "socket fail ";
            return false;
        }
        //m_seraddr.sin_family = AF_INET;
        //ser_addr.sin_port = htons(ser_Port);
        //ser_addr.sin_addr.s_addr = inet_addr(ser_Ip.c_str());
        int res = ::connect(m_serfd, (struct sockaddr *)&m_seraddr, sizeof(m_seraddr));
        if (-1 == res) {
            LOG_ERROR << "connect fail ";
            return false;
        }
        tag = 1;
        // event_add();
        return true;
    }

    int ProxyData::getSerFd() const {
        return m_serfd;
    }

    bool ProxyData::IsConnSer() const {
        return tag == 1;
    }

} // namespace tulun