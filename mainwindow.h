#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include "DisplayArea.h"
#include "interfacearea.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);//构造函数
    ~MainWindow();                        //析构函数

private slots:
    void setSingleView();           //action:单窗口
    void setFourView();             //action:四窗口
    void setNineView();             //action:九窗口
    void toggleInterfaceList();     //action:切换设备列表显示
    void togglePropertyArea();      //action:切换属性栏显示
    //action:connect
    void onDeviceConnected(KVirtualCamera* camera);
private:
    //主要视图组件
    QMenuBar* menuBar;                  //菜单栏
    QToolBar* toolBar;                  //工具栏
    InterfaceArea* interfacelist;       //设备列表视图
    DisplayArea* displayArea;           //显示区域视图
    QWidget* propertyArea;              //属性区域视图
    QDockWidget* propertyDockWidget;    // 属性区域 DockWidget

    //切换视图动作
    QActionGroup* viewActionGroup;
    QAction* singleViewAction;
    QAction* fourViewAction;
    QAction* nineViewAction;

    //组件隐藏
    QAction* toggleInterfaceAction;  // 显示/隐藏设备列表
    QAction* togglePropertyAction;   // 显示/隐藏属性区域
};

#endif // MAINWINDOW_H
