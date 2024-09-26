 #include "InterfaceList.h"

#include <iostream>
InterfaceList::InterfaceList() {
    /*
    pcap_if_t* alldevs, * d;
    int i = 0;
    char errbuf[PCAP_ERRBUF_SIZE];

    // 获取所有网络设备列表
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
        return;
    }

    // 打印设备列表,初始化数组
    for (d = alldevs; d; d = d->next) {
        std::cout << ++i << ". " << d->name;
        InterfaceItem *item = new InterfaceItem(d->name, d->description);
        list.push_back(item);
        if (d->description)
            std::cout << " (" << d->description << ")\n";
        else
            std::cout << " (No description available)\n";
    }

    if (i == 0) {
        std::cout << "No interfaces found! Make sure libpcap is installed." << std::endl;
        return;
    }*/
    pcap_if_t* alldevs, * d;
    int i = 0;
    char errbuf[PCAP_ERRBUF_SIZE];

    // 获取所有网络设备列表
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
        return;
    }

    // 遍历设备列表，筛选出真实的网卡
    for (d = alldevs; d; d = d->next) {
        bool isRealInterface = true;  // 假设默认是一个真实网卡

        // 检查设备名称或描述是否包含虚拟或环回的关键词
        std::string devName(d->name);
        std::string devDescription = (d->description) ? std::string(d->description) : "";

        if (devDescription.find("VM") != std::string::npos ||
            devDescription.find("Loopback") != std::string::npos ||
            devDescription.find("Virtual") != std::string::npos ||
            devDescription.find("VPN") != std::string::npos||
            devDescription.find("UU") != std::string::npos
            ) {
            isRealInterface = false;  // 排除虚拟网卡
        }

        // 进一步检查网卡地址，确保存在非环回IP地址
        pcap_addr_t* addr;
        bool hasValidIp = false;
        for (addr = d->addresses; addr; addr = addr->next) {
            if (addr->addr->sa_family == AF_INET || addr->addr->sa_family == AF_INET6) {
                // 检查是否是环回地址
                if (addr->addr->sa_family == AF_INET) {
                    struct sockaddr_in* ipv4 = (struct sockaddr_in*)addr->addr;
                    if (ipv4->sin_addr.s_addr != htonl(INADDR_LOOPBACK)) {
                        hasValidIp = true;
                        break;
                    }
                } else if (addr->addr->sa_family == AF_INET6) {
                    // 对于IPv6，可以检查是否是环回地址（例如：::1）
                    struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)addr->addr;
                    if (!IN6_IS_ADDR_LOOPBACK(&ipv6->sin6_addr)) {
                        hasValidIp = true;
                        break;
                    }
                }
            }
        }

        if (!hasValidIp) {
            isRealInterface = false;  // 排除没有有效IP的接口
        }

        if (isRealInterface) {
            std::cout << ++i << ". " << d->name;
            InterfaceItem* item = new InterfaceItem(d->name, d->description);
            list.push_back(item);
            if (d->description)
                std::cout << " (" << d->description << ")\n";
            else
                std::cout << " (No description available)\n";
        }
    }

    if (i == 0) {
        std::cout << "No real interfaces found! Make sure libpcap is installed." << std::endl;
    }

    // 释放设备列表内存
    pcap_freealldevs(alldevs);
}
std::vector<InterfaceItem*> InterfaceList::getList(){
    return list;
}
