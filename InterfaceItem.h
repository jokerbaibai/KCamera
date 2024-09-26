#ifndef INTERFACEITEM_H
#define INTERFACEITEM_H
#include <string>
#include <pcap.h>
#include <CommandSender.h>
#include <thread>
#include "KDataProcessor.h"
/*
 * InterfaceItem 类负责管理网络接口的连接、数据包接收和处理。
 * 它只负责数据的传输，不关心数据的具体处理逻辑。
 */
class InterfaceItem
{
public:
    //构造与析构函数
    InterfaceItem(std::string name,std::string description);
    ~InterfaceItem();


    //查找设备名是否存在
    bool findDeviceName();

    //开始与停止接收数据
    void startCapture();
    void stopCapture();
    //修改属性
    void modify(int id,int val);
    //设置数据处理器
    void setProcessor(KDataProcessor*);
    KDataProcessor* getProcessor();
    //相关信息的接口
    std::string getDescription();//获得接口描述
    std::string getName();       //获得接口名
    std::string getDeviceName(); //获得设备名

private:
    std::string name;               //接口名
    std::string description;        //接口描述

    std::string d_name;             //设备名

    pcap_t* handle;                 //句柄
    CommandSender* sender;          //命令发送器
    KDataProcessor* dataProcessor;  // 数据处理器

    std::thread captureThread;
    //回调函数，处理设备名
    static void get_name(u_char* user, const pcap_pkthdr* header, const u_char* packet);
    //回调函数，处理具体数据包
    static void packet_handler(u_char* user, const pcap_pkthdr* header, const u_char* packet);
};

#endif // INTERFACEITEM_H
