#ifndef KBASECAMERA_H
#define KBASECAMERA_H

#include <QObject>
#include <QtCore/QMetaObject>
#include "pcap.h"

class KBaseCamera:public QObject{
    Q_OBJECT
public:

    virtual bool startCapture()=0;  //开始捕获
    virtual bool stopCapture()=0;   //停止捕获
    virtual bool captureFrame()=0;  //抓拍
    //virtual bool startRecord()=0;   //开始录制
    //virtual bool stopRecord()=0;    //停止录制
    //static void packetHandler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet);
};
#endif // KBASECAMERA_H
