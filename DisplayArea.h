#ifndef DISPLAYAREA_H
#define DISPLAYAREA_H

#include <QWidget>
#include <QGridLayout>
#include <QStatusBar>
#include <QVector>
#include <QPushButton>
#include <QMessageBox>
#include <QToolBar>
#include "CameraView.h"
#include <QFileDialog>
/*
 *显示区域类：负责管理摄像机窗口，处理视图的切换
*/
class DisplayArea : public QWidget {
    Q_OBJECT

public:
    explicit DisplayArea(QWidget *parent = nullptr);

    //设置布局模式
    void setLayoutMode(int mode);                           //主实现
    void setSingleLayout();                                 //单窗口
    void setFourLayout();                                   //四窗口
    void setNineLayout();                                   //九窗口
    //为指定窗口设置相机
    void setCameraView(int index, KVirtualCamera* camera);
    bool isFirstViewAvailable();
protected:
    //void keyPressEvent(QKeyEvent* event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;   //拖入操作
    void dragMoveEvent(QDragMoveEvent *event) override;     //拖动操作
    void dropEvent(QDropEvent *event) override;             //释放操作

private slots:
    void onShowClicked();                   //显示/隐藏
    void setFullScreen();                   //全屏
    void photo();                           //抓拍
    void crossline();                       //十字辅助线
    void gridline();                        //网格线
    void on_resolution_info(int width,int height);
    void on_fps_info(double fps);
    void on_mouseMovePoint(QPoint point);
    void on_mouseClicked(QPoint point);
    void on_mouseDoubleClick(QPoint point);
    void on_keyPress(QKeyEvent* event);
    void on_mouseWheel(QWheelEvent* event);

private:
    //布局组件
        //主布局：设置为垂直布局
        QVBoxLayout* mainLayout;              //主布局

        bool isFullScreen;  //是否全屏
        //工具栏
        QToolBar* toolbar;
        QAction* showAction;        //显示/隐藏
        QAction* fullscreenAction;  //全屏
        QAction* photoAction;       //抓拍图像
        QAction* crosslineAction;   //十字线
        QAction* gridlineAction;    //网格线


        //相机窗口的表格布局
        QGridLayout *gridLayout;

        //状态栏
        QStatusBar* statusBar;  //状态栏
        QLabel* rValue;         //r值
        QLabel* gValue;         //g值
        QLabel* bValue;         //b值
        QLabel* fps;            //采集帧率
        QLabel* resolution;     //图像分辨率

    //数据对象
        QVector<CameraView*> cameraViews;
        int nextViewIndex;


};

#endif // DISPLAYAREA_H
