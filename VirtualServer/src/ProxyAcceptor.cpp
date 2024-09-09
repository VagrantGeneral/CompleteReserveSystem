#include"ProxyAcceptor.hpp"

namespace SER {

void ProxyAcceptor::newconnCallBack(int fd, short ev, void *arg) {
    if (nullptr == arg) {
        LOG_ERROR << "nullptr == arg";
        return;
    }
    ProxyAcceptor *pacc = static_cast<ProxyAcceptor *>(arg);
    VMyEvent*plvs = pacc->GetMyEvent();
    event_base *pbase = plvs->getEventBase();
    //cout << "accept_callback ...pbase:" << pbase << endl;
    int connfd = -1;
    // 接收客户端连接请求
    struct sockaddr_in peeraddr;
    unsigned int len = sizeof(peeraddr);
    connfd = accept(fd, (sockaddr *)&peeraddr, &len);
    if (-1 == connfd) {
        LOG_DEBUG << "accept fail: ";
        return;
    }
    //cout << "new client ..." << endl;
    ProxyData *pxydata = nullptr;
    try {
        pxydata = new ProxyData(connfd, plvs);
    }
    catch (const std::exception &e) {
        LOG_ERROR << "new EventRW error :" << e.what();
        return;
    }
    pxydata->setPeerAddr(peeraddr);
    if (!plvs->AddProxyConnEvent(pxydata)) {
        delete plvs;
        LOG_ERROR << "add event fail ";
        return;
    }
}
//  int listenfd;

ProxyAcceptor::ProxyAcceptor(int fd, VMyEvent *p)
    : listenfd(fd) {
    SetMyEvent(p);
}
ProxyAcceptor::~ProxyAcceptor() {
    close(listenfd);
}
int ProxyAcceptor::getFd() const {
    return listenfd;
}

} // namespace tulun