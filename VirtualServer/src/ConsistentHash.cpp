#include "ConsistentHash.hpp"

namespace SER {
    int ConsistentHash::FNV1_32_HASH(const std::string& key) {
        const int p = 16777619;
        int hash = 2166136261;
        for (int idx = 0; idx < key.size(); idx++) {
            hash = (hash ^ key[idx]) * p;
        }
        hash += hash << 13;
        hash ^= hash >> 7;
        hash += hash << 3;
        hash ^= hash >> 17;
        hash += hash << 5;

        if (hash < 0) {
            hash = -hash;
        }
        return hash;
    }
    
    int ConsistentHash::getMaxVirtualNodeNum() const {
        return m_MaxVirtualNodeNum;
    }

    int ConsistentHash::getCurVirtualNodeNum() const {
        return m_VirtualServerNodes.size();
    }

    int ConsistentHash::getCurPhysicaNodeNum() const {
        return m_PhysicalServerNodes.size();
    }

    void ConsistentHash::setMaxVirtualNodeNum(int num) {
        m_MaxVirtualNodeNum = num;
    }

    
    ConsistentHash::ConsistentHash()
        : m_MaxVirtualNodeNum(initvirtualnum) {
        /*create*/
    }

    ConsistentHash::~ConsistentHash() {

    }

    std::set<std::string>& ConsistentHash::GetPhysicalNodes() {
        return  m_PhysicalServerNodes;
    }

    void ConsistentHash::AddNewPhysicalNode(const std::string& nodeip) {
        //  nodeip ==> EventRW ==>
        auto iter = m_PhysicalServerNodes.insert(nodeip);
        if (iter.second) {
            for (int i = 0; i < m_MaxVirtualNodeNum; i++) {
                std::stringstream nodekey;
                nodekey << nodeip << "#VN" << i;
                int parition = FNV1_32_HASH(nodekey.str());
                m_VirtualServerNodes.insert({parition, nodeip});
            }
        }
    }

    void ConsistentHash::DelPhysicalNode(const std::string& nodeip) {
        auto iter = m_PhysicalServerNodes.erase(nodeip);
        if (iter == 1) {
            for (int i = 0; i < m_MaxVirtualNodeNum; i++) {
                std::stringstream nodekey;
                nodekey << nodeip << "#VN" << i;
                int parition = FNV1_32_HASH(nodekey.str());
                m_VirtualServerNodes.erase(parition);
            }
        }
    }

    std::string ConsistentHash::GetVirtualServerIndex(const std::string& key) {
        int parition = FNV1_32_HASH(key);
        auto it = m_VirtualServerNodes.lower_bound(parition);
        if(it == m_VirtualServerNodes.end()) {
            if(m_VirtualServerNodes.empty()) {
                LOG_ERROR << "no ser nodes ...";
                return std::string();
            }
            return m_VirtualServerNodes.begin()->second;
        }
        return it->second;
    }



}