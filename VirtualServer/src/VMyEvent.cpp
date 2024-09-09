#include "VMyEvent.hpp"
#define MAXLISTEN 128

namespace SER {

    void VMyEvent::exitCallBack(int fd, short ev, void *arg) {
        auto *pmy = static_cast<VMyEvent*>(arg);
        LOG_DEBUG << "LVSMyEvent loop obj exit";
        pmy->Loopbreak();
    }
    void VMyEvent::stdinCallBack(int fd, short ev, void *arg) {
        auto *plvs = static_cast<VMyEvent*>(arg);
        if (nullptr == plvs) {
            LOG_DEBUG << "nullptr == plvs";
            return;
        }
        const int len = 128;
        char buff[len] = {};
        fgets(buff, len - 1, stdin);
        //cout << "stdincallback: " << fd << " " << buff << endl;
        // AddNewSer 123.45.45.33 8900
        std::stringstream ss;
        std::string comd;
        std::string ip;
        int port = 0;
        ss << buff;
        ss >> comd;
        ss >> ip;
        ss >> port;
        if (comd.compare("exit") == 0) {
            plvs->Loopbreak();
        }
        else if (comd.compare("AddNewSer") == 0) {
            std::string ip_port;
            ip_port += ip;
            ip_port += " ";
            ip_port += std::to_string(port);
            plvs->getSerPool()->AddNewPhysicalNode(ip_port);
        }
        else {
            //cout << "other comd ... " << endl;
        }
    }

    // struct event_base *m_pbase;
    // struct event *psignal;
    // Acceptor *m_accept;
    // std::string m_SerIp;
    // int m_SerPort;
    // std::map<int, ProxyData *> m_proxydatas;
    // ConsistentHash m_SerPool;

    int VMyEvent::InitListenfd() {
        int m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (-1 == m_fd) {
            LOG_DEBUG << "socket fail :" << strerror(errno);
            return false;
        }
        struct sockaddr_in addr = {};
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(m_SerPort);
        addr.sin_addr.s_addr = inet_addr(m_SerIp.c_str());

        if (bind(m_fd, (sockaddr *)&addr, sizeof(addr)) == -1) {
            LOG_DEBUG << "bind fail " << strerror(errno);
            return -1;
        }
        if (listen(m_fd, MAXLISTEN) == -1) {
            LOG_DEBUG << "listen fail " << strerror(errno);
            return -1;
        }
        return m_fd;
    }

    bool VMyEvent::InitEvent() {
        m_pbase = event_base_new(); // libevent;
        if (nullptr == m_pbase) {
            LOG_DEBUG << "libevent init error";
            return false;
        }
        int m_fd = InitListenfd();
        if (-1 == m_fd) {
            LOG_ERROR << "listentf init error ";
            return false;
        }
        try {
            m_accept = new ProxyAcceptor(m_fd, this);
        }
        catch (const std::exception &e) {
            LOG_ERROR << "new Acceptor error : " << e.what();
            return false;
        }

        if (!AddAcceptEvent(m_accept)) {
            LOG_DEBUG << "add event fail ";
            delete m_accept;
            m_accept = nullptr;
            return false;
        }
        return true;
    }

    bool VMyEvent::DispactchEvent() {
        if (event_base_dispatch(m_pbase) == -1) {
            LOG_FATAL << "event base dispatch.." << strerror(errno);
            return false;
        }
        return true;
    }

    bool VMyEvent::Loopbreak() {
        if (event_base_loopbreak(m_pbase) == -1) {
            LOG_FATAL << "event base loopbreak.." << strerror(errno);
            return false;
        }
        return true;
    }

    VMyEvent::VMyEvent(const std::string &ip, const int port)
        : m_pbase(nullptr),
          m_accept(nullptr),
          psignal(nullptr), // stdin;
          ev_stdin(nullptr),
          m_SerIp(ip),
          m_SerPort(port),
          m_proxydatas{},
          m_SerPool{} {

    }

    VMyEvent::~VMyEvent() {
        event_del(psignal);
        event_free(psignal);
        psignal = nullptr;

        event_del(ev_stdin);
        event_free(ev_stdin);
        ev_stdin = nullptr;

        event_del(m_accept->getEvent());
        event_free(m_accept->getEvent());
        delete m_accept;
        m_accept = nullptr;

        event_base_free(m_pbase);
        m_pbase = nullptr;
        
    }

    bool VMyEvent::AddAcceptEvent(ProxyAcceptor *pAcc) {
        if (nullptr == pAcc) {
            LOG_ERROR << "nullptr == pAcc";
            return false;
        }
        int fd = pAcc->getFd();
        event *pev = event_new(m_pbase, fd, EV_READ | EV_PERSIST,
                               &ProxyAcceptor::newconnCallBack, pAcc);
        if (nullptr == pev) {
            LOG_ERROR << "event_new fail " << strerror(errno);
            return false;
        }
        pAcc->setEvent(pev);
        if (event_add(pev, nullptr) == -1) {
            LOG_DEBUG << "event_add fail: " << strerror(errno);
            event_free(pev);
            return false;
        }
        return true;
    }

    bool VMyEvent::AddProxyConnEvent(ProxyData *proxy) {
        if (nullptr == proxy) {
            LOG_ERROR << "nullptr == proxy";
            return false;
        }
        int fd = proxy->getFd();
        event *pev = event_new(m_pbase, fd, EV_READ | EV_PERSIST,
                               &ProxyData::messageCallBack, proxy);
        if (nullptr == pev) {
            LOG_ERROR << "event_new fail " << strerror(errno);
            return false;
        }
        proxy->setEvent(pev);
        if (event_add(pev, nullptr) == -1) {
            LOG_DEBUG << "event_add fail: " << strerror(errno);
            event_free(pev);
            pev = nullptr;
            return false;
        }
        m_proxydatas[fd] = proxy;
        return true;
    }

    bool VMyEvent::DelProxyConnEvent(ProxyData *proxy) {
        if (nullptr == proxy) {
            LOG_DEBUG << "nullptr == proxy";
            return false;
        }
        event *ev = proxy->getEvent();
        event_del(ev);
        event_free(ev);
        if (0 == m_proxydatas.erase(proxy->getFd())) {
            LOG_DEBUG << "m_proxydatas.erase 0";
            return false;
        }
        delete proxy;
        return true;
    }

    bool VMyEvent::AddExitSignalEvent() {
        psignal = evsignal_new(m_pbase, SIGINT,
                               &VMyEvent::exitCallBack, this);
        if (nullptr == psignal) {
            LOG_ERROR << "evsignal_new error " << strerror(errno);
            return false;
        }
        if (event_add(psignal, nullptr) == -1) {
            LOG_DEBUG << "event_add fail: " << strerror(errno);
            event_free(psignal);
            return false;
        }
        return true;
    }

    bool VMyEvent::AddStdinEvent() {
        ev_stdin = event_new(m_pbase, STDIN_FILENO, EV_READ | EV_PERSIST,
                             &VMyEvent::stdinCallBack, this);
        if (nullptr == ev_stdin) {
            LOG_ERROR << "event_new fail " << strerror(errno);
            return false;
        }
        if (event_add(ev_stdin, nullptr) == -1) {
            LOG_ERROR << "event_add fail" << strerror(errno);
            event_free(ev_stdin);
            ev_stdin = nullptr;
            return false;
        }
        return true;
    }

    struct event_base *VMyEvent::getEventBase() {
        return m_pbase;
    }

    void VMyEvent::Run() {
        if (!InitEvent()) {
            LOG_DEBUG << "InitEvent fail ..";
            return;
        }
        if (!AddExitSignalEvent()) {
            LOG_DEBUG << "AddExitSignalEvent fail";
            return;
        }
        if (!AddStdinEvent()) {
            LOG_DEBUG << "AddStdinEvent fail";
            return;
        }
        if (!DispactchEvent()) {
            LOG_DEBUG << "Dispatch  event ... ";
            return;
        }
        LOG_INFO << "LVS Server close ...";
    }

    int VMyEvent::getConnNum() const {
        return m_proxydatas.size();
    }

} // namespace tulun