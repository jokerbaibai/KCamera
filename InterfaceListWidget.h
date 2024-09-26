#ifndef INTERFACELISTWIDGET_H
#define INTERFACELISTWIDGET_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "DeviceDelegate.h"
#include "InterfaceList.h"
#include "KVirtualCamera.h"
#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include <QToolBar>
class InterfaceListWidget : public QTreeView {
    Q_OBJECT

public:
    InterfaceListWidget(QWidget *parent = nullptr);

public slots:
    void onConnectClicked();                           //单个设备的连接/断开
    void onCaptureClicked();                           //单个设备的捕获/停止
    void onGlobalCaptureStartClicked();                //全局的开始捕获
    void onGlobalCaptureStopClicked();                 //全局的停止捕获
    void itemchanged();                                //选择项更改
protected:
    //拖放机制实现
    void mousePressEvent(QMouseEvent* event);     //鼠标点击事件
    void mouseMoveEvent(QMouseEvent* event);      //鼠标移动事件
    void performDrag();                           //执行拖放事件

signals:
    void deviceConnected(KVirtualCamera* camera);
    void changed(bool type,bool connect,bool running,bool havefree,bool havebusy);
private:
    //设备数据
    void loadInterfaces();                              //加载接口信息
    InterfaceList *interfaceList;                       //接口与设备列表
    QMap<InterfaceItem*, KVirtualCamera*> cameraMap;    //已连接设备，接口到相机对象的映射
    //mvc架构
    QStandardItemModel *model;                          //树形模型
    DeviceDelegate* delegate;                           //自定义委托

    //拖放事件需要数据
    QPoint startPos;

    int havefree; //空闲设备数
    int havebusy; //运行设备数


};

#endif // INTERFACELISTWIDGET_H
