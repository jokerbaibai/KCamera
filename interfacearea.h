#ifndef INTERFACEAREA_H
#define INTERFACEAREA_H
#include "InterfaceListWidget.h"
#include <QDockWidget>
#include <QVBoxLayout>
class InterfaceArea:public QDockWidget
{
public:
    InterfaceArea(QWidget* parent=0);
    InterfaceListWidget* getList();
private:
    QWidget* dockContent;               //内容
    QVBoxLayout* mainLayout;            //主布局
    QToolBar* toolbar;                  //工具栏
    InterfaceListWidget* interfacelist; //设备列表视图


    //相应动作
    QAction* connectAction;
    QAction* captureAction;
    QAction* batchCaptureAction;
    QAction* batchStopAction;
private slots:
    //槽函数：负责响应选择项的更改，来更改action的属性
    //如果不是camra类型，所有action设置为disenabled
    //connect:true设置为断开连接,false设置为开始连接
    //connect:true设置为断开连接,false设置为开始连接
    //havefree:true设置为enabled
    //havebusy:true设置为enabled
    void on_itemchanged(bool type,bool connect,bool running,bool havefree,bool havebusy);
};

#endif // INTERFACEAREA_H
