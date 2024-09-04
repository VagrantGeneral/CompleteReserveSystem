
#include <jsoncpp/json/json.h>
#include "Logger.hpp"
#include "CUser.hpp"


namespace CLI{
    CUser::CUser() 
        : name_{},
          tel_{},
          tagReg_{0},
          tagLogIn_{0},
          tagConn_{0} {
        //create
    }

    CUser::~CUser() {
        //delete
    }

    bool CUser::ConnectToSer(const std::string &ip, const int port) {
        client.reset(new CLI::SocketClient(ip, port));
        bool res = client->Connect();
        tagConn_ = res; // 1
        if (!res) {
            LOG_DEBUG << "Connect ser Failed!!!" << ip << port;
        }
        return res;
    }

    int CUser::Register(const std::string &name, const std::string &pws, const std::string &tel) {
        int res = 1;
        if (tagConn_) {
            Json::Value regobj;
            regobj["utype"] = 2; // REGISTER;
            regobj["name"] = name;
            regobj["tel"] = tel;
            regobj["password"] = pws;
            Json::FastWriter fw;
            std::string str = fw.write(regobj);
            if (client->SendToServer(str) < 0) {
                LOG_DEBUG << "send regobj" << str;
                res = 2;
            }
            else {
                std::string retstr = client->ReadFromServer();
                // retstr={"utype":"RETREG","RetCode":1} // 1ok 2tel
                if (!retstr.empty()) {
                    Json::Value retobj;
                    Json::Reader read;
                    read.parse(retstr, retobj);
                    if (retobj["RetCode"].asInt() == 1) {
                        tagReg_ = 1;
                        name_ = name;
                        tel_ = tel;
                        res = 0;
                    }
                    else {
                        res = 3;
                    }
                }
                else {
                    res = 2;
                }
            }
        }
        return res;
    }

    int CUser::LogIn(const std::string &tel, const std::string &pws) {
        int res = 1;
        if(tel.compare(tel_) != 0) {
            return 3;
        }
        if (tagConn_) {
            Json::Value loginobj;
            loginobj["utype"] = 1; // LOGIN
            loginobj["tel"] = tel;
            loginobj["password"] = pws;
            Json::FastWriter fw;
            std::string str = fw.write(loginobj);
            if (client->SendToServer(str) < 0) {
                LOG_DEBUG << "send loginobj" << str;
                res = 2;
            }
            else {
                std::string retstr = client->ReadFromServer();
                // retstr={"utype":"LONIN","RetCode":2} // 0 ok  1 tel // 2 paw
                if(!retstr.empty()) {
                    Json::Value retobj;
                    Json::Reader read;
                    read.parse(retstr, retobj);
                    if(retobj["RetCode"].asInt() == 0) {
                        res = 0;
                    }
                    else if (retobj["RetCode"].asInt() == 1) {
                        res = 3;
                    }
                    else {
                        res = 4;
                    }
                }
                else {
                    res = 2;
                }
            }
        }
        return res;
    }

}
