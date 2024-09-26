#include "InterfaceListWidget.h"
#include <QStandardItem>
#include <QMessageBox>
#include <iostream>
//构造函数
InterfaceListWidget::InterfaceListWidget(QWidget *parent)
    : QTreeView(parent){

    //初始化接口与设备列表
    interfaceList = new InterfaceList();

    //设置模型与委托
    model=new QStandardItemModel(this);
    setModel(model);
    delegate = new DeviceDelegate(this);
    setItemDelegate(delegate);
    connect(delegate, &DeviceDelegate::connectClicked, this, &InterfaceListWidget::onConnectClicked);
    connect(selectionModel(), &QItemSelectionModel::selectionChanged, this, &InterfaceListWidget::itemchanged);
//加载接口
    loadInterfaces();
    //允许拖放操作
    setAcceptDrops(true);
    havefree=0;
    havebusy=0;
}
//加载接口信息
void InterfaceListWidget::loadInterfaces() {
    //清空当前模型中的所有项
    model->clear();
    //设置模型的水平表头标签
    model->setHorizontalHeaderLabels(QStringList() << "Gige");
    //将所有接口项添加到模型中
    for (InterfaceItem* item : interfaceList->getList()) {
        //为当前item创建一个QStandardItem对象
        QStandardItem *interfaceItem = new QStandardItem(QString::fromStdString(item->getDescription()));
        // 如果设备名不为"null"，则在接口项下添加设备项
        if (item->getDeviceName() != "null") {
            QStandardItem *deviceItem = new QStandardItem(QString::fromStdString(item->getDeviceName()));
            deviceItem->setData(QVariant::fromValue(reinterpret_cast<void*>(item)), Qt::UserRole);
            interfaceItem->appendRow(deviceItem);
        }
        model->appendRow(interfaceItem);
    }
    //展开所有项目以显示设备名称
    //treeView->expandAll();
    expandAll();
}
//选中设备的连接与断开
void InterfaceListWidget::onConnectClicked() {
    QModelIndex index = currentIndex();
    if (index.isValid() && index.parent().isValid()) {  // 确保这是第二级（设备信息）
        InterfaceItem* item = reinterpret_cast<InterfaceItem*>(index.data(Qt::UserRole).value<void*>());
        if (item) {
            // 如果已存在，则断开连接
            if (cameraMap.contains(item)) {
                KVirtualCamera* camera = cameraMap[item];
                if(camera->isrunning()){
                    havebusy--;
                }
                havefree--;
                cameraMap[item]->stopCapture();
                cameraMap.remove(item);
                delete camera;  // 删除camera对象，释放资源
                QMessageBox::information(this, "Disconnect", QString::fromStdString(item->getDescription()) + " disconnected.");
            } else {
                // 连接设备：创建对应相机控制器，并加入已连接列表
                KVirtualCamera* camera =new KVirtualCamera(item);
                cameraMap[item] = camera;
                havefree++;//空闲设备数加一
                // 发送信号给 MainWindow，通知连接设备
                emit deviceConnected(camera);
                QMessageBox::information(this, "Connect", QString::fromStdString(item->getDescription()) + " connected.");
            }
            itemchanged();
        }
    }
}
//选中设备的采集控制
void InterfaceListWidget::onCaptureClicked() {
    //QModelIndex index = treeView->currentIndex(); // 获取当前选中的项的索引
    QModelIndex index = currentIndex();
    if (index.isValid() && index.parent().isValid()) {  // 确保这是第二级（设备信息）
        InterfaceItem* item = reinterpret_cast<InterfaceItem*>(index.data(Qt::UserRole).value<void*>());
        if (item) {
            KVirtualCamera* camera = cameraMap.value(item, nullptr); // 获取与该设备对应的相机对象

            if (camera!=nullptr) {
                if (camera->isrunning()) {  // 如果相机正在捕获
                    camera->stopCapture();   // 停止捕获
                    havefree++;
                    havebusy--;
                    //captureButton->setText("Capture");  // 更新按钮文本为 "Capture"
                    QMessageBox::information(this, "Capture Stopped", QString::fromStdString(item->getDeviceName()) + " stopped capturing.");
                } else {  // 如果相机未在捕获
                    camera->startCapture();  // 开始捕获
                    havefree--;
                    havebusy++;
                    //captureButton->setText("Stop");  // 更新按钮文本为 "Stop"
                    QMessageBox::information(this, "Capture Started", QString::fromStdString(item->getDeviceName()) + " started capturing.");
                }
                itemchanged();
            } else {
                QMessageBox::warning(this, "No Camera", "No camera associated with this device.");
            }
        }
    } else {
        QMessageBox::warning(this, "No Device Selected", "Please select a device to capture.");
    }
}
//批量采集,所有已连接相机开始采集
void InterfaceListWidget::onGlobalCaptureStartClicked() {
    for (KVirtualCamera *camera : cameraMap) {
        camera->startCapture();
        havefree--;
        havebusy++;
    }
    itemchanged();
}
//批量停止
void InterfaceListWidget::onGlobalCaptureStopClicked() {
    for (KVirtualCamera *camera : cameraMap) {
        camera->stopCapture();
        havefree++;
        havebusy--;
    }
    itemchanged();
}

void InterfaceListWidget::itemchanged(){
    bool type=true,connect=true,running=false;
    QModelIndex index = currentIndex();
    if(!index.isValid()||!index.parent().isValid()){  //如果没有选中有效项，则退出
        type=false;
    }
    else{
        InterfaceItem* item = reinterpret_cast<InterfaceItem*>(index.data(Qt::UserRole).value<void*>());
        KVirtualCamera* camera = cameraMap.value(item, nullptr); // 获取与该设备对应的相机对象
        if(camera==nullptr){
            connect=false;
            running=false;
            //havefree=true;
            //havebusy=false;
        }
        else{
            connect=true;
            running=camera->isrunning();
        }

    }
    emit changed(type,connect,running,havefree,havebusy);
}
//拖放机制的实现：源数据
//鼠标点击事件
void InterfaceListWidget::mousePressEvent(QMouseEvent* event){
    if(event->button()==Qt::LeftButton){
        startPos=event->pos();
        std::cout<<"press!"<<std::endl;
    }
    QTreeView::mousePressEvent(event);
};
//鼠标移动事件
void InterfaceListWidget::mouseMoveEvent(QMouseEvent* event){
    if(event->buttons()&Qt::LeftButton){
        int distance=(event->pos()-startPos).manhattanLength();
        if(distance>=QApplication::startDragDistance()){
            std::cout<<"drag!"<<std::endl;
            performDrag();
        }
    }
};
void InterfaceListWidget::performDrag(){
    //QModelIndex index=treeView->currentIndex();       //选中当前项
    QModelIndex index = currentIndex();
    if(!index.isValid()||!index.parent().isValid()){  //如果没有选中有效项，则退出
        return;
    }
    std::cout<<"choose"<<std::endl;
    InterfaceItem* item = reinterpret_cast<InterfaceItem*>(index.data(Qt::UserRole).value<void*>());
    if (!item) {
        return; // 如果没有找到对应的 InterfaceItem，退出
    }
    KVirtualCamera* cam=cameraMap[item];
    QByteArray camData;
    QDataStream dataStream(&camData, QIODevice::WriteOnly);
    dataStream << reinterpret_cast<qintptr>(cam); // 将 InterfaceItem 的指针地址写入到数据流

    QMimeData* mimeData = new QMimeData();
    mimeData->setData("application/x-device", camData); // 设置自定义 MIME 类型数据

    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimeData); // 将 MIME 数据设置到拖动对象中

    // 执行拖动操作
    drag->exec(Qt::CopyAction | Qt::MoveAction);

};
