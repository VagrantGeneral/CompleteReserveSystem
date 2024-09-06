#include "MyEvent.hpp"

namespace SER {
    static const int MAXLISTEN = 128;

    void MyEvent::eventCallBack(int fd, short ev, void* arg) {
        EventObj* pObj = (EventObj*)arg;//
        if (pObj == nullptr) {
            LOG_ERROR << "pObj is nullptr";
            return;
        }

        if (ev & EV_READ) {
            pObj->messageCallBack();//Acceptor;EventRW;
        }
    }
    
    bool MyEvent::InitListenfd() {
        m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (m_fd == -1) {
            LOG_DEBUG << "socket error!!!";
            return false;
        }
        struct sockaddr_in addr = {};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(m_SerPORT);
        addr.sin_addr.s_addr = inet_addr(m_SerIP.c_str());

        if (bind(m_fd, (sockaddr*)&addr, sizeof(addr)) == -1) {
            LOG_DEBUG << "bind error!!!";
            return false;
        }

        if (listen(m_fd, MAXLISTEN) == -1) {
            LOG_DEBUG << "listen error!!!";
            return false;
        }

        return true;
    }

    bool MyEvent::InitEvent(int fd) {
        m_pbase = event_base_new();
        if (m_pbase == nullptr) {
            LOG_DEBUG << "libevent init error!!!";
            return false;
        }

        if (!InitListenfd()) {
            LOG_DEBUG << "InitListenfd error!!!";
            return false;
        }

        try {
            m_accept = new Acceptor(m_fd, this);
        }
        catch (const std::exception& e) {
            LOG_DEBUG << "new Acceptor error!!!" << e.what();
        }

        if (!AddEvent(m_fd, m_accept)) {
            LOG_DEBUG << "add event error!!!";
            delete m_accept;
            m_accept = nullptr;
            return false;
        }

        return true;
    }

    bool MyEvent::AddEvent(int fd, EventObj* pobj) {
        if (fd == -1 || pobj == nullptr) {
            LOG_DEBUG << "addevent--->information is error!!!";
            return false;
        }

        event* pev = event_new(m_pbase, fd, EV_READ | EV_PERSIST, &MyEvent::eventCallBack, pobj);
        if (pev == nullptr) {
            LOG_DEBUG << "event_new error!!!";
            return false;
        }

        pobj->setEvent(pev);

        if (event_add(pev, nullptr) == -1) {
            LOG_DEBUG << "event_add error!!!";
            event_free(pev);
            return false;
        }

        return true;
    }

    bool MyEvent::DelEvent() {
        return true;
    }

    bool MyEvent::DespactchEvent() {
        if (event_base_dispatch(m_pbase) == -1) {
            LOG_FATAL << "event base dispatch error!!!";
            return false;
        }
        return true;

    }

    struct event_base* MyEvent::getEventBase() {
        return m_pbase;
    }

    MyEvent::MyEvent(const std::string& ip, const short port) 
        : m_SerIP(ip)
        , m_SerPORT(port) 
        , m_pbase(nullptr)
        , m_accept(nullptr)
        , m_fd(-1) {
        /* create */
    }

    MyEvent::~MyEvent() {
        close(m_fd);
        delete m_accept;
        event_base_free(m_pbase);
    }

    void MyEvent::Run() {
        if (!InitEvent(m_fd)) {
            LOG_DEBUG << "InitEvent error!!!";
            return;
        }
        if (!DespactchEvent()) {
            LOG_DEBUG << "DespactchEvent error!";
            return;
        }
        LOG_INFO << "Server Runing...";

    }
}