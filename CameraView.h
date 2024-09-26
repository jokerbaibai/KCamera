#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <opencv2/opencv.hpp>
#include <QLabel>
#include "KVirtualCamera.h"
#include "crosslineitem.h"
#include "gridlineitem.h"
class CameraView:public QGraphicsView
{
    Q_OBJECT
public:
    CameraView(QWidget* parent=0);
    void setCamera(KVirtualCamera* camera);             //绑定相机
    KVirtualCamera* getCamera() const;                  //获得相机
    QImage getImage();
    //十字线
    void toggleCrossLine();                                        //切换十字线显示状态
    //网格线
    void toggleGridLine();
    //获取像素点的颜色
    QColor getRGBAtPoint(const QPoint& point);
    void adjustCrossLine();
    void adjustGridLine();
protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event)override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;
signals:
    void mouseMovePoint(QPoint point);
    void mouseClicked(QPoint point);
    void mouseDoubleClick(QPoint point);
    void keyPress(QKeyEvent* event);
    void resolution_info(int width,int height);
    void fps_info(double fps);


private:
    //场景与图形项
    QGraphicsScene* scene;            //场景
    QGraphicsPixmapItem* pixmapItem;  //用于显示图像的pixmap图形项
    CrossLineItem* crossline;         //十字线
    bool crosslinestat;               //十字线状态
    GridLineItem* gridline;           //网格线
    bool gridlinestat;                //网格线状态

    KVirtualCamera *camera;             //绑定的相机
    //十字线属性
    int crosslineWidth;     //十字线高度
    int crosslineHeight;    //十字线宽度
    int crosslineXoffset;   //x方向偏移量
    int crosslineYoffset;   //y方向偏移量
    QColor crossLineColor;  //颜色
    int crossLineThickness; //粗细

    //网格线属性
    int gridRows;
    int gridCols;
    QColor gridlineColor;
    int gridlineThickness;

    QImage image;
    //帧率计算
    int frameCount;
    double currentFrameRate;
    QElapsedTimer frameRateTimer;


private slots:
    void displayFrame(uint8_t* data, int width, int height, int channels);
};

#endif // CAMERAVIEW_H
