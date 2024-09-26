#include "DisplayArea.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>
#include <iostream>

//DisplayArea构造函数
DisplayArea::DisplayArea(QWidget *parent)
    : QWidget(parent),isFullScreen(false), nextViewIndex(0) {
    //布局初始化
        //主布局
        mainLayout=new QVBoxLayout();        //创建主布局
        setLayout(mainLayout);               //设置主布局
        setAcceptDrops(true);                //启用拖放操作，允许拖放事件在该窗口中发生

        //工具栏
        toolbar=new QToolBar();
        showAction=new QAction(QIcon(":/images/hide"),tr("&取消预览"),this);           //显示/隐藏
        fullscreenAction=new QAction(QIcon(":/images/fullscreen"),tr("&全屏"),this);  //全屏
        photoAction=new QAction(QIcon(":/images/photo"),tr("&抓拍"),this);            //抓拍图像
        crosslineAction=new QAction(QIcon(":/images/crossline"),tr("&十字线"),this);  //十字线
        gridlineAction=new QAction(QIcon(":/images/gridline"),tr("&网格线"),this);    //网格线
        toolbar->addAction(showAction);
        toolbar->addAction(fullscreenAction);
        toolbar->addAction(photoAction);
        toolbar->addAction(crosslineAction);
        toolbar->addAction(gridlineAction);
        connect(showAction,&QAction::triggered,this,&DisplayArea::onShowClicked);
        connect(fullscreenAction,&QAction::triggered,this,&DisplayArea::setFullScreen);
        connect(photoAction,&QAction::triggered,this,&DisplayArea::photo);
        connect(crosslineAction,&QAction::triggered,this,&DisplayArea::crossline);
        connect(gridlineAction,&QAction::triggered,this,&DisplayArea::gridline);
        mainLayout->addWidget(toolbar);

        //相机窗口布局
        gridLayout = new QGridLayout();  //创建一个网格布局管理器，并将其设置为当前窗口的布局
        mainLayout->addLayout(gridLayout);

        //状态栏
        statusBar=new QStatusBar();
        mainLayout->addWidget(statusBar);

            //R坐标
            rValue=new QLabel("R:");
            rValue->setMinimumWidth(150);
            statusBar->addWidget(rValue);
            //G坐标
            gValue=new QLabel("G:");
            gValue->setMinimumWidth(150);
            statusBar->addWidget(gValue);
            //B坐标
            bValue=new QLabel("B:");
            bValue->setMinimumWidth(150);
            statusBar->addWidget(bValue);
            //采集帧率
            fps=new QLabel("采集帧率:");
            fps->setMinimumWidth(150);
            statusBar->addWidget(fps);
            //分辨率
            resolution=new QLabel("分辨率:");
            resolution->setMinimumWidth(150);
            statusBar->addWidget(resolution);

    //数据初始化
        //初始化相机窗口：预先创建9个CameraView对象并添加到cameraViews列表中
        for (int i = 0; i < 9; ++i) {
            CameraView* view=new CameraView(this);
            view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 设置为可扩展

            view->setVisible(false);
            cameraViews.append(view);
        }
        //默认为单窗口布局模式
        setSingleLayout();
        //建立与键鼠信号的关联
        connect(cameraViews[0],&CameraView::mouseMovePoint,this,&DisplayArea::on_mouseMovePoint);
        connect(cameraViews[0],&CameraView::mouseClicked,this,&DisplayArea::on_mouseClicked);
        connect(cameraViews[0],&CameraView::mouseDoubleClick,this,&DisplayArea::on_mouseDoubleClick);
        connect(cameraViews[0],&CameraView::keyPress,this,&DisplayArea::on_keyPress);
        connect(cameraViews[0],&CameraView::resolution_info,this,&DisplayArea::on_resolution_info);
        connect(cameraViews[0],&CameraView::fps_info,this,&DisplayArea::on_fps_info);
}
//绑定相机
void DisplayArea::setCameraView(int index, KVirtualCamera* camera) {
    if (index >= 0 && index < cameraViews.size()) {
        std::cout<<"set camera"<<index<<std::endl;
        if(cameraViews[index]!=nullptr)
            cameraViews[index]->setCamera(camera);  // 设置指定的CameraView绑定到相机

    }
}


//设置布局模式
void DisplayArea::setLayoutMode(int mode) {
    gridLayout->setSpacing(5);  // 设置网格布局项之间的间隔为 5 像素

    // 清空当前布局中的所有控件

    while (QLayoutItem *item = gridLayout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {  // 如果布局项中包含控件
            widget->setParent(nullptr);          // 将控件从父布局中移除，但不销毁控件
        }
        delete item;                             // 删除布局项对象，释放内存
    }

    // 根据选择的模式，调整布局
    if (mode == 1) {
        // 显示按钮布局和状态栏中的所有控件
        toolbar->setVisible(true);
        statusBar->setVisible(true);
        // 单画面模式

        gridLayout->addWidget(cameraViews[0],0,0,1,1);  // 将第一个 CameraView 放置在网格布局的第 0 行第 0 列

        cameraViews[0]->setMinimumSize(1024, 840);  // 单窗口模式的初始大小
        cameraViews[0]->setVisible(true);
    } else if (mode == 4) {
        // 隐藏按钮布局和状态栏
        toolbar->setVisible(false);
        statusBar->setVisible(false);
        // 四画面模式
        for (int i = 0; i < 4 && i < cameraViews.size(); ++i) {  // 循环添加 4 个 CameraView 到布局中

            gridLayout->addWidget(cameraViews[i], i / 2, i % 2, 1, 1);  // 将每个 CameraView 添加到 2x2 的网格布局中
            cameraViews[i]->setMinimumSize(512, 450);  // 每个 CameraView 的初始大小
            cameraViews[i]->setVisible(true);
        }
        for (int i = 0; i < 2; ++i) {
            gridLayout->setRowStretch(i, 1);
        }
        for (int j = 0; j < 2; ++j) {
            gridLayout->setColumnStretch(j, 1);
        }

    } else if (mode == 9) {
        // 隐藏按钮布局和状态栏
        toolbar->setVisible(false);
        statusBar->setVisible(false);
        // 九画面模式
        for (int i = 0; i < 9 && i < cameraViews.size(); ++i) {  // 循环添加 9 个 CameraView 到布局中

            gridLayout->addWidget(cameraViews[i], i / 3, i % 3, 1, 1);  // 将每个 CameraView 添加到 3x3 的网格布局中
            cameraViews[i]->setMinimumSize(340, 300);  // 每个 CameraView 的初始大小
            cameraViews[i]->setVisible(true);
        }
        for (int i = 0; i < 3; ++i) {
            gridLayout->setRowStretch(i, 1);
        }
        for (int j = 0; j < 3; ++j) {
            gridLayout->setColumnStretch(j, 1);
        }
    }
    mainLayout->update();  // 更新布局，使更改生效
}
void DisplayArea::setSingleLayout(){
    setLayoutMode(1);
}
void DisplayArea::setFourLayout(){
    setLayoutMode(4);
}
void DisplayArea::setNineLayout(){
    setLayoutMode(9);
}

void DisplayArea::on_resolution_info(int width,int height){
    resolution->setText(QString::asprintf("分辨率: %d*%d", width,height));
}
void DisplayArea::on_fps_info(double fps_info){
    fps->setText(QString::asprintf("采集帧率: %lf", fps_info));
}
bool DisplayArea::isFirstViewAvailable(){
    if(nextViewIndex==0)
        return true;
    return false;
};

//拖放功能实现
// 处理拖动进入事件
void DisplayArea::dragEnterEvent(QDragEnterEvent *event) {
    // 检查拖动的对象是否包含 "application/x-device" 格式的数据
    if (event->mimeData()->hasFormat("application/x-device")) {
        event->acceptProposedAction();  // 接受拖动操作
    }
}
// 处理拖动移动事件
void DisplayArea::dragMoveEvent(QDragMoveEvent *event) {
    // 检查拖动的对象是否包含 "application/x-device" 格式的数据
    if (event->mimeData()->hasFormat("application/x-device")) {
        event->acceptProposedAction();  // 接受拖动操作
    }
}
// 处理放置事件
void DisplayArea::dropEvent(QDropEvent *event) {
    // 检查放置的对象是否包含 "application/x-device" 格式的数据
    if (event->mimeData()->hasFormat("application/x-device")) {
        QByteArray camData = event->mimeData()->data("application/x-device");  // 获取 MIME 数据
        QDataStream dataStream(&camData, QIODevice::ReadOnly);
        qintptr camPtr;
        dataStream >> camPtr;

        KVirtualCamera* cam = reinterpret_cast<KVirtualCamera*>(camPtr);  // 将数据转换为 InterfaceItem 指针

        if (!cam) {
            return; // 如果没有找到有效的 InterfaceItem，退出
        }

        // 计算鼠标放置点在哪个 CameraView 中
        int ViewIndex = -1;
        for (int i = 0; i < cameraViews.size(); ++i) {
            if (cameraViews[i]->geometry().contains(event->position().toPoint())) {  // 如果鼠标放置点在某个 CameraView 内
                ViewIndex = i;  // 记录该窗口的索引
                break;  // 退出循环
            }
        }

        if (ViewIndex != -1) {  // 如果找到了合适的窗口
            setCameraView(ViewIndex, cam); // 将相机与 CameraView 绑定
            event->acceptProposedAction();  // 接受放置操作
        }
    }
}



void DisplayArea::onShowClicked(){//显示/隐藏
    if (cameraViews[0]->isVisible()) {
        cameraViews[0]->hide();  // 隐藏所有相机窗口
        showAction->setIcon(QIcon(":/images/show"));
        showAction->setText("预览");  // 更新
    }
    else {
        cameraViews[0]->show();  // 显示所有相机窗口
        showAction->setIcon(QIcon(":/images/hide"));
        showAction->setText("取消预览");  // 更新
    }
};
void DisplayArea::setFullScreen(){//全屏
    isFullScreen=true;
    cameraViews[0]->setParent(nullptr);
    cameraViews[0]->showFullScreen();
};
//抓拍
void DisplayArea::photo(){
    KVirtualCamera* camera = cameraViews[0]->getCamera();
    if (camera != nullptr&&camera->isrunning()) {

        QImage image = cameraViews[0]->getImage();  // 假设 KVirtualCamera 类有 captureImage() 方法
        if (image.isNull()) {
            QMessageBox::warning(this, "Error", "Failed to capture image from camera.");
            return;
        }
        QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Images (*.png *.jpg *.bmp)");
        if (!fileName.isEmpty()) {
            image.save(fileName);  // 保存图像
        }
    } else {
        //QMessageBox::warning(this, "No Camera", "No camera associated with this device.");
    }
};

//十字线状态切换
void DisplayArea::crossline(){
        cameraViews[0]->toggleCrossLine();}  // 假设 CameraView 类有 toggleCrossLine() 方法                   //十字辅助线
//网格线状态切换
void DisplayArea::gridline(){
        cameraViews[0]->toggleGridLine();  // 假设 CameraView 类有 toggleGridLine() 方法
    };                    //网格线

//响应键鼠信号
    //鼠标移动：获取图片像素点的rgb值
    void DisplayArea::on_mouseMovePoint(QPoint point){
        // 获取当前第一个 CameraView 对象
        if (cameraViews.size() > 0 && cameraViews[0] != nullptr) {
            QColor color = cameraViews[0]->getRGBAtPoint(point);  // 获取该点的颜色

            // 更新状态栏显示
            rValue->setText(QString::asprintf("R: %d", color.red()));
            gValue->setText(QString::asprintf("G: %d", color.green()));
            bValue->setText(QString::asprintf("B: %d", color.blue()));
        }
    };
    void DisplayArea::on_mouseClicked(QPoint point){};
    void DisplayArea::on_mouseDoubleClick(QPoint point){};
    void DisplayArea::on_keyPress(QKeyEvent* event){
        if (event->key() == Qt::Key_Escape) {
            std::cout<<"esc"<<std::endl;
            if (isFullScreen) {
                cameraViews[0]->showNormal();  // 退出全屏
                cameraViews[0]->setParent(this); // 恢复为当前窗口的子控件
                gridLayout->addWidget(cameraViews[0]);
                isFullScreen = false;
            }
        }
    };
    void DisplayArea::on_mouseWheel(QWheelEvent* event){
    };
