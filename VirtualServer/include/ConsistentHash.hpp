#ifndef CONSISTENTHASH_HPP
#define CONSISTENTHASH_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include "Logger.hpp"

namespace SER {
    class ConsistentHash {
        //ConsistentHash::
    private:
        std::map<int, std::string> m_VirtualServerNodes;
        //------<hash---ip:port-->-------//
        std::set<std::string> m_PhysicalServerNodes;

        int m_MaxVirtualNodeNum;

    private:
        static const int initvirtualnum = 400;

    protected:
        static int FNV1_32_HASH(const std::string& key);

    public:
        int getMaxVirtualNodeNum() const;

        int getCurVirtualNodeNum() const;

        int getCurPhysicaNodeNum() const;

        void setMaxVirtualNodeNum(int num);

    public:
        ConsistentHash();

        ~ConsistentHash();

        std::set<std::string>& GetPhysicalNodes();

        void AddNewPhysicalNode(const std::string& nodeip);

        void DelPhysicalNode(const std::string& nodeip);

        std::string GetVirtualServerIndex(const std::string& key);

        //
    };
}

#endif