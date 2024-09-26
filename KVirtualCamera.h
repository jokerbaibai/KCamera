#ifndef KVIRTUALCAMERA_H
#define KVIRTUALCAMERA_H

#include "KBaseCamera.h"
#include "KImageFrame.h"
#include "InterfaceItem.h"
#include "virtualcameraproperty.h"
#define JUMBOFRAME 8000
#define CUSTOM_IDENTIFIER_IMAGE 0x11111111

class KVirtualCamera:public KBaseCamera{
    Q_OBJECT
public:
    KVirtualCamera(InterfaceItem*); //构造函数

    //控制命令
    bool startCapture() override;  //开始捕获图像
    bool stopCapture() override;   //停止捕获图像
    bool isrunning();              //运行状态

    //数据保存
    //bool startRecord() override;   //开始录制
    //bool stopRecord() override;    //结束录制
    bool captureFrame() override;  //抓拍图像

    //返回属性列表
    VirtualCameraPropertyList* getList();

signals:
    void frameReady(uint8_t* data, int width, int height, int channels);//发送一帧图像
public slots:
    void getframe(uint8_t* data, int width, int height, int channels);//发送一帧图像
    void on_modify(int id,int value);
private:
    InterfaceItem* kinterface;      //对应接口
    bool isRunning;                 //运行状态
    KImageFrame* imageFrame;        //图像数据处理器
    uint8_t* datacopy;              //数据副本
    VirtualCameraProperty* property;//相机属性
};
#endif // KVIRTUALCAMERA_H

