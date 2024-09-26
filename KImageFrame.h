#ifndef KIMAGEFRAME_H
#define KIMAGEFRAME_H
#include <cstdint>
#include <QObject>
#include "KDataProcessor.h"
class KImageFrame:public QObject ,public KDataProcessor{
    Q_OBJECT
public:
    KImageFrame();
    KImageFrame(int,int,int);
    ~KImageFrame();

    bool addPacket(const uint8_t* packet, int length) override;
    bool isComplete() const override;
    void reset() override;
    uint8_t* getData() const;
signals:
    void imageReady(uint8_t* data, int width, int height, int channels);
private:
    int width;         //宽
    int height;        //高
    int channels;      //通道数
    int size;          //大小

    uint8_t* buffer;   //数据缓冲区
    uint8_t* copy;     //数据副本
    int line;          //已读行数
    bool complete;     //一帧是否读完
};

#endif // KIMAGEFRAME_H
