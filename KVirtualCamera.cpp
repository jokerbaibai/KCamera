#include "KVirtualCamera.h"
#include <iostream>

//构造函数
KVirtualCamera::KVirtualCamera(InterfaceItem* face){
    isRunning=false;
    kinterface=face;
    imageFrame=new KImageFrame();
    kinterface->setProcessor(imageFrame);
    property=new VirtualCameraProperty();
    // 连接 imageFrame 的信号到自身的信号，以便传递给 CameraWindow
    connect(imageFrame, &KImageFrame::imageReady, this, &KVirtualCamera::getframe);
    connect(property,&VirtualCameraProperty::modify,this,&KVirtualCamera::on_modify);  
}


//启动接收与处理
bool KVirtualCamera::startCapture() {
    if (isRunning) return false; //如果已经在运行，则返回
    isRunning = true;
    kinterface->startCapture();
    return true;
}

bool KVirtualCamera::stopCapture() {
    if (isRunning) {
        isRunning = false;
        kinterface->stopCapture();
        return true;
    }
    return false;
}
//槽函数：接收到图像帧，并转发给显示组件处理
void KVirtualCamera::getframe(uint8_t* data, int width, int height, int channels){
    std::cout<<"get frame!"<<std::endl;
    emit frameReady(data,width,height,channels);
}
//槽函数：接收到属性修改信号，通过接口转发给机器
void KVirtualCamera::on_modify(int id,int val){
    kinterface->modify(id,val);
}

//todo
/*
bool KVirtualCamera::startRecord(){
    return true;
};
bool KVirtualCamera::stopRecord(){
    return true;
};*/
bool KVirtualCamera::captureFrame(){
    return true;
};
bool KVirtualCamera::isrunning(){
    return isRunning;
}
VirtualCameraPropertyList* KVirtualCamera::getList(){
    return property->getList();
}
