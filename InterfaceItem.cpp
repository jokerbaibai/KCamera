#include "InterfaceItem.h"
#include <iostream>
//构造函数
InterfaceItem::InterfaceItem(std::string name,std::string description) {
    //初始化接口名与描述
    this->name=name;
    this->description=description;

    //设备名默认为null
    d_name="null";

    //创建句柄,设置参数并激活
    handle=nullptr;
    char errbuf[PCAP_ERRBUF_SIZE];
    handle = pcap_create(name.c_str(), errbuf);
    if (pcap_set_snaplen(handle, 9000) != 0) {
        std::cerr << "Failed to set snapshot length: " << pcap_geterr(handle) << std::endl;
    }
    if (pcap_set_promisc(handle, 1) != 0) {
        std::cerr << "Failed to set promiscuous mode: " << pcap_geterr(handle) << std::endl;
    }
    if (pcap_set_timeout(handle, 1) != 0) {
        std::cerr << "Failed to set timeout: " << pcap_geterr(handle) << std::endl;
    }
    if (pcap_set_buffer_size(handle, 1024 * 1024 * 16) != 0) {
        std::cerr << "Failed to set buffer size: " << pcap_geterr(handle) << std::endl;
    }
    if (pcap_set_immediate_mode(handle, 0) != 0) {
        std::cerr << "Failed to set immediate mode: " << pcap_geterr(handle) << std::endl;
    }
    pcap_activate(handle);

    //初始化命令控制器
    sender=new CommandSender(handle);

    findDeviceName();
}
//查找设备名
bool InterfaceItem::findDeviceName() {
    if (handle == nullptr) return false;

    captureThread = std::thread([this]() {
        pcap_loop(handle, 0, get_name, reinterpret_cast<u_char*>(this));
    });
    if(sender->sendInquiryCommand()==false){
        pcap_breakloop(handle);
        if (captureThread.joinable()) {
            captureThread.join();
        }
        return false;
    }
    if (captureThread.joinable()) {
        captureThread.join();
    }
    return true;
}
//对应回调函数
void InterfaceItem::get_name(u_char* user, const pcap_pkthdr* header, const u_char* packet) {
    InterfaceItem* item = reinterpret_cast<InterfaceItem*>(user);
    const uint32_t target_identifier = 0x22222222;
    uint32_t identifier;

    // Assuming the identifier is located at a specific offset in the packet
    // The offset 12 is used as an example, adjust as necessary
    std::memcpy(&identifier, packet + 14, sizeof(identifier));

    if (identifier == target_identifier) {
        // Target packet found
        std::cout << "Target packet received!" << std::endl;

        // Assuming the device name starts right after the identifier (at offset 16)
        const char* device_name = reinterpret_cast<const char*>(packet + 18);

        // Print the device name
        std::cout << "Device Name: " << device_name << std::endl;

        // Optionally store the device name in the InterfaceItem object
        item->d_name = std::string(device_name);

        // Stop capturing
        pcap_breakloop(item->handle);
    }
}
//开始接收数据
void InterfaceItem::startCapture(){
    captureThread = std::thread([this]() {
        pcap_loop(handle, 0, packet_handler, reinterpret_cast<u_char*>(this));
    });
    sender->sendStartCommand(99,125,66);


};
//停止接收数据
void InterfaceItem::stopCapture(){
    sender->sendStopCommand();
    pcap_breakloop(handle);
    if (captureThread.joinable()) {
        captureThread.join();
    }
};
//修改属性
void InterfaceItem::modify(int id,int val){
    sender->sendModifyCommand(id,val);
}
//对应回调函数
void InterfaceItem::packet_handler(u_char* user, const pcap_pkthdr* header, const u_char* packet){
    InterfaceItem* item = reinterpret_cast<InterfaceItem*>(user);

    if (header->len == 8000) {
        // 将数据包传递给数据处理器
        if (item->getProcessor() != nullptr) {
            if (!item->getProcessor()->addPacket(packet, header->len)) {
                std::cerr << "Failed to process packet." << std::endl;
            }
        } else {
            std::cerr << "No data processor available." << std::endl;
        }
    } else {
        std::cout << "Ignored packet with size " << header->len << std::endl;
    }
};
//获得接口描述
std::string InterfaceItem::getDescription(){
    return description;
}
//获得设备名
std::string InterfaceItem::getDeviceName(){
    return d_name;
}
//获得接口名
std::string InterfaceItem::getName(){
    return name;
}
//设置数据处理器
void InterfaceItem::setProcessor(KDataProcessor* k){
    dataProcessor=k;
}

KDataProcessor* InterfaceItem::getProcessor(){
    return dataProcessor;
}
