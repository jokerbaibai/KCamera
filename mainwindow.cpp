#include "MainWindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QAction>
#include<iostream>
//构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //主要组件初始化：分为五个区域，菜单栏、工具栏、设备列表、属性栏、视图区
        //菜单栏
        menuBar = new QMenuBar(this);
        QMenu *viewMenu = menuBar->addMenu(tr("&View"));
        viewMenu->setIcon(QIcon("/images/file"));
        setMenuBar(menuBar);

        //工具栏
        toolBar = new QToolBar(this);
        addToolBar(Qt::TopToolBarArea, toolBar);

        //设备列表
        interfacelist=new InterfaceArea(this);

        //属性栏
        propertyArea=new QWidget(this);

        //视图区
        displayArea=new DisplayArea(this);

    // 添加视图切换功能
    viewActionGroup = new QActionGroup(this);
        //单窗口
    singleViewAction = new QAction(QIcon(":/images/singleview"),tr("Single View"), this);
        singleViewAction->setCheckable(true);
        connect(singleViewAction, &QAction::triggered, this, &MainWindow::setSingleView);
        //四窗口
        fourViewAction = new QAction(QIcon(":/images/fourview"),tr("Four View"), this);
        fourViewAction->setCheckable(true);
        connect(fourViewAction, &QAction::triggered, this, &MainWindow::setFourView);
        //九窗口
        nineViewAction = new QAction(QIcon(":/images/nineview"),tr("Nine View"), this);
        nineViewAction->setCheckable(true);
        connect(nineViewAction, &QAction::triggered, this, &MainWindow::setNineView);
        //添加到动作组
        viewActionGroup->addAction(singleViewAction);
        viewActionGroup->addAction(fourViewAction);
        viewActionGroup->addAction(nineViewAction);
        //添加到菜单与工具栏
        viewMenu->addActions(viewActionGroup->actions());
        toolBar->addActions(viewActionGroup->actions());
        // 默认设置为单画面视图
        singleViewAction->setChecked(true);

    // 设置接口列表与设备管理栏
    interfacelist->setFeatures(QDockWidget::NoDockWidgetFeatures);  // 禁用关闭和移动
    interfacelist->setMinimumWidth(200);
    addDockWidget(Qt::LeftDockWidgetArea, interfacelist);

    // 设置属性区
    propertyDockWidget = new QDockWidget(tr("属性栏"), this);
    propertyDockWidget->setStyleSheet("border: 1px solid black;");
    propertyDockWidget->setWidget(propertyArea);
    propertyDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);  // 禁用关闭和移动
    propertyDockWidget->setMinimumWidth(150);
    addDockWidget(Qt::RightDockWidgetArea, propertyDockWidget);

    //添加组件隐藏动作
        //隐藏设备列表
        toggleInterfaceAction = new QAction(QIcon(":/images/toggleleft"),tr("Toggle Interface List"), this);
        toggleInterfaceAction->setCheckable(true);
        connect(toggleInterfaceAction, &QAction::triggered, this, &MainWindow::toggleInterfaceList);
        //隐藏属性区域
        togglePropertyAction = new QAction(QIcon(":/images/toggleright"),tr("Toggle Property Area"), this);
        togglePropertyAction->setCheckable(true);
        connect(togglePropertyAction, &QAction::triggered, this, &MainWindow::togglePropertyArea);
        //添加到工具栏
        toolBar->addAction(toggleInterfaceAction);
        toolBar->addAction(togglePropertyAction);
    // 设置中央显示区域
    setCentralWidget(displayArea);
    //设置相机绑定窗口
    connect(interfacelist->getList(),&InterfaceListWidget::deviceConnected,this,&MainWindow::onDeviceConnected);


}
//析构函数
MainWindow::~MainWindow() {}
// 切换设备列表显示
void MainWindow::toggleInterfaceList() {
    interfacelist->setVisible(!interfacelist->isVisible());
}

// 切换属性栏显示
void MainWindow::togglePropertyArea() {
    propertyDockWidget->setVisible(!propertyDockWidget->isVisible());
}
//显示区域视图切换控件：单窗口、四窗口、九窗口
void MainWindow::setSingleView() {
    displayArea->setSingleLayout();
}
void MainWindow::setFourView() {
    displayArea->setFourLayout();
}
void MainWindow::setNineView() {
    displayArea->setNineLayout();
}
//绑定选中连接的相机到第一个显示窗口，其他的留给拖放操作
void MainWindow::onDeviceConnected(KVirtualCamera* camera) {
    std::cout<<"Try connecting!"<<std::endl;
    // 绑定相机到第一个显示窗口，其他的留给拖放操作
    if (displayArea->isFirstViewAvailable()) {
        displayArea->setCameraView(0, camera);  // 假设 setCameraWindow 的第一个参数是窗口索引
        propertyDockWidget->setWidget(camera->getList());
    }
}
