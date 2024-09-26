#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include "KVirtualCamera.h"



/*
*摄像机窗口类：用于接收相机传输的帧，并显示图像
*/
class CameraWindow : public QLabel {
    Q_OBJECT

public:
    explicit CameraWindow(QWidget *parent = nullptr);   //构造函数
    void setCamera(KVirtualCamera* camera);             //绑定相机
    KVirtualCamera* getCamera() const;                  //获得相机

    //十字线
    void setCrossLine(bool enabled, int width, int height, int xOffset,
                      int yOffset, QColor color, int thickness);   //设置属性
    void toggleCrossLine();                                        //切换十字线显示状态
    //网格线
    void setGridLine(bool enabled, int rows, int cols,
                     QColor color, int thickness);                 //设置属性
    void toggleGridLine();                                         //切换网格线显示状态
public slots:
    //槽函数，用于接收相机传递的帧并显示
    void displayFrame(uint8_t* data, int width, int height, int channels);
protected:
    void paintEvent(QPaintEvent* event) override; // 重写 paintEvent 以绘制十字线和网格线
private:
    //QLabel *imageLabel;      //显示图像
    //QVBoxLayout *layout;     //垂直布局
    KVirtualCamera *camera;  //绑定的相机

    //十字线属性
    bool crosslineEnabled;  //是否绘制
    int crosslineWidth;     //十字线高度
    int crosslineHeight;    //十字线宽度
    int crosslineXoffset;   //x方向偏移量
    int crosslineYoffset;   //y方向偏移量
    QColor crossLineColor;  //颜色
    int crossLineThickness; //粗细

    //网格线属性
    bool gridlineEnabled;
    int gridRows;
    int gridCols;
    QColor gridlineColor;
    int gridlineThickness;

};

#endif // CAMERAWINDOW_H
