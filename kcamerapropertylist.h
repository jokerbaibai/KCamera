#ifndef KCAMERAPROPERTYLIST_H
#define KCAMERAPROPERTYLIST_H
#include "camerapropertylist.h"
#include "KICTypeDef.h"
class KCameraPropertyList:public CameraPropertyList
{
    Q_OBJECT
public:
    KCameraPropertyList(QWidget* parent);
private:
    QToolBar* toolbar;      //工具栏
    QTabWidget* tabwidget;  //标签页模块
    QTreeWidget* page1;
    QLabel* label1;
    QTreeWidget* page2;
    QLabel* label2;
    QTreeWidget* page3;
    QLabel* label3;
    QTreeWidget* page4;
    QLabel* label4;

    //可配置参数
    void set_frame_rate(int);           //设置相机参数
    void set_exposure_mode(int);        //设置曝光模式
    void set_exposure_time(int);        //设置曝光时间
    void set_frame_size(int);           //设置帧大小
    void set_pixel_format(int);         //像素格式
    void set_image_format(int);         //图像格式
    void set_trigger_mode(int);         //触发模式


    void set_digit_gain(int);           //数字增益
    void set_rdigit_gain(int);          //r数字增益
    void set_gdigit_gain(int);          //g数字增益
    void set_bdigit_gain(int);          //b数字增益

    void set_analog_gain(int);          //模拟增益
    void set_rwbalance_gain(int);       //r白平衡增益
    void set_gwbalance_gain(int);       //g白平衡增益
    void set_bwbalance_gain(int);       //b白平衡增益

    void set_camera_delay(int);         //相机触发延迟
    void set_light_delay(int);          //光源触发延迟
    void set_light_pulse(int);          //光源脉冲宽度



signals:
    void propertychanged(int type,int value);

};

#endif // KCAMERAPROPERTYLIST_H

