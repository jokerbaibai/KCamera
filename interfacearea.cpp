#include "interfacearea.h"

InterfaceArea::InterfaceArea(QWidget* parent):QDockWidget(parent) {
    setWindowTitle("设备列表");
    mainLayout=new QVBoxLayout();
    // 创建一个 QWidget 作为 QDockWidget 的内容区域
    dockContent = new QWidget();
    toolbar = new QToolBar(this);
    connectAction=new QAction(QIcon(":/images/connect"),tr("&连接设备"),this);
    connectAction->setCheckable(true);
    captureAction=new QAction(QIcon(":/images/start"),tr("&开始捕获"),this);
    captureAction->setCheckable(true);
    batchCaptureAction=new QAction(QIcon(":/images/bstart"),tr("&批量捕获"),this);
    batchCaptureAction->setCheckable(true);
    batchStopAction=new QAction(QIcon(":/images/bstop"),tr("&批量停止"),this);
    batchStopAction->setCheckable(true);
    toolbar->addAction(connectAction);
    toolbar->addAction(captureAction);
    toolbar->addAction(batchCaptureAction);
    toolbar->addAction(batchStopAction);
    toolbar->setEnabled(false);

    interfacelist=new InterfaceListWidget(this);
    mainLayout->addWidget(toolbar);
    mainLayout->addWidget(interfacelist);
    dockContent->setLayout(mainLayout);
    //设置样式表
    //dockContent->setStyleSheet("border: 1px solid black;");

    setWidget(dockContent);
    connect(connectAction,&QAction::triggered,interfacelist,&InterfaceListWidget::onConnectClicked);
    connect(captureAction,&QAction::triggered,interfacelist,&InterfaceListWidget::onCaptureClicked);
    connect(batchCaptureAction,&QAction::triggered,interfacelist,&InterfaceListWidget::onGlobalCaptureStartClicked);
    connect(batchStopAction,&QAction::triggered,interfacelist,&InterfaceListWidget::onGlobalCaptureStopClicked);
    connect(interfacelist,&InterfaceListWidget::changed,this,&InterfaceArea::on_itemchanged);
}
void InterfaceArea::on_itemchanged(bool type,bool connect,bool running,bool havefree,bool havebusy){
    //不是设备类型，则失效工具栏
    if(type==false){
        toolbar->setEnabled(false);
    }
    else{
        toolbar->setEnabled(true);
        if(connect==true){
            connectAction->setIcon(QIcon(":/images/disconnect"));
            connectAction->setText(tr("&断开设备"));
            captureAction->setEnabled(true);
        }
        //如果未连接，则不能采集
        else{
            connectAction->setIcon(QIcon(":/images/connect"));
            connectAction->setText(tr("&连接设备"));
            captureAction->setEnabled(false);
        }
        if(running==true){
            captureAction->setIcon(QIcon(":/images/stop"));
            captureAction->setText(tr("&停止捕获"));
        }
        else{
            captureAction->setIcon(QIcon(":/images/start"));
            captureAction->setText(tr("&开始捕获"));
        }
        if(havefree){
            batchCaptureAction->setEnabled(true);
        }
        else{
            batchCaptureAction->setEnabled(false);
        }
        if(havebusy){
            batchStopAction->setEnabled(true);
        }
        else{
            batchStopAction->setEnabled(false);
        }

    }
}
InterfaceListWidget* InterfaceArea::getList(){
    return interfacelist;
}
