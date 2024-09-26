#ifndef COMMANDSENDER_H
#define COMMANDSENDER_H

#include <pcap.h>

#define WIDTH 1024
#define HEIGHT 1024
#define CUSTOM_IDENTIFIER_START 0x12345678
#define CUSTOM_IDENTIFIER_MODIFY 0x12345679
#define CUSTOM_IDENTIFIER_STOP 0x12345680
#define CUSTOM_IDENTIFIER_INQUIRY 0x12345681

class CommandSender{
public:
    CommandSender(pcap_t* handle);    //构造函数

    bool sendRawPacket(int identifier, int r = 0, int g = 0, int b = 0); //构造原始数据包并发送

    bool sendInquiryCommand();                    //发送查询数据包的接口
    bool sendStartCommand(int r, int g, int b);   //发送开始数据包的接口
    bool sendStopCommand();                       //发送停止数据包的接口
    bool sendModifyCommand(int id,int val);       //发送修改数据包的接口

private:
    pcap_t* handle;
};
#endif // COMMANDSENDER_H
