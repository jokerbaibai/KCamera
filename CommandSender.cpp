#include "CommandSender.h"
#include <iostream>
#include <cstring>
#include <pcap.h>
//#include <arpa/inet.h>


//构造函数
CommandSender::CommandSender(pcap_t* handle){
    this->handle=handle;
}

//发送原始数据包
bool CommandSender::sendRawPacket(int identifier, int r, int g, int b) {
    unsigned char packet[8000]; // 14字节以太网头部 + 4字节标识符 + 数据
    memset(packet, 0, sizeof(packet));

    // 设置目标 MAC 地址为广播地址
    memset(packet, 0xff, 6);

    // 设置源 MAC 地址（这里使用默认值）
    memcpy(packet + 6, "\x00\x00\x00\x00\x00\x00", 6);

    // 填写以太网类型字段（0x0800 表示 IP 协议）
    packet[12] = 0x00;
    packet[13] = 0x00;

    // 填写自定义标识符
    int* identifier1 = (int*)(packet + 14);
    identifier1[0] = htonl(identifier);

    // 填写数据部分
    if (identifier == CUSTOM_IDENTIFIER_START || identifier == CUSTOM_IDENTIFIER_MODIFY) {
        packet[14 + 4] = static_cast<uint8_t>(r);
        packet[14 + 5] = static_cast<uint8_t>(g);
        packet[14 + 6] = static_cast<uint8_t>(b);
    }

    // 发送数据包
    if (pcap_sendpacket(handle, packet, 8000) != 0) {
        std::cerr << "Error sending packet: " << pcap_geterr(handle) << std::endl;
        return false;
    }
    std::cout<<"send!"<<std::endl;
    //pcap_close(handle);
    //pcap_freealldevs(alldevs);
    return true;
}
//发送查询数据包
bool CommandSender::sendInquiryCommand() {
    std::cout<<"Inquiry!"<<std::endl;
    return sendRawPacket(CUSTOM_IDENTIFIER_INQUIRY);
}
//发送开始数据包
bool CommandSender::sendStartCommand(int r, int g, int b) {
    std::cout<<"Start!"<<r<<g<<b<<std::endl;
    return sendRawPacket(CUSTOM_IDENTIFIER_START, r, g, b);
}
//发送停止数据包
bool CommandSender::sendStopCommand() {
    std::cout<<"Stop!"<<std::endl;
    return sendRawPacket(CUSTOM_IDENTIFIER_STOP);
}
//发送参数修改数据包
bool CommandSender::sendModifyCommand(int id,int value) {
    std::cout<<"Modify!"<<std::endl;
    return sendRawPacket(CUSTOM_IDENTIFIER_MODIFY,id,value);
}


