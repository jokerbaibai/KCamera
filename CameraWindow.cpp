 #include "CameraWindow.h"
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>

//构造函数
CameraWindow::CameraWindow(QWidget *parent)
    : QLabel(parent) {
    //初始化相机
    camera=nullptr;
    //初始化显示图像
    //imageLabel = new QLabel(this);
    //imageLabel->setAlignment(Qt::AlignCenter);
    setAlignment(Qt::AlignCenter);
    //imageLabel->setText("No Image");
    setText("No Image");
    // 设置 QLabel 的缩放策略，确保它不会因内容改变大小
    //imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //初始化布局
    //layout = new QVBoxLayout(this);
    //layout->addWidget(imageLabel);
    //setLayout(layout);


    //初始化十字线属性
    crosslineEnabled=false;
    crosslineHeight=100;
    crosslineWidth=100;
    crosslineXoffset=0;
    crosslineYoffset=0;
    crossLineColor=Qt::red;
    crossLineThickness=2;
    //初始化
    gridlineEnabled=false;
    gridRows=3;
    gridCols=3;
    gridlineColor=Qt::red;
    gridlineThickness=1;
}

//绑定相机
void CameraWindow::setCamera(KVirtualCamera* cam) {
    //如果已经绑定相机，则进行解绑
    if (camera!=nullptr) {
        disconnect(camera, &KVirtualCamera::frameReady, this, &CameraWindow::displayFrame);
    }
    //更换绑定的相机
    camera = cam;
    if (camera!=nullptr) {
        connect(camera, &KVirtualCamera::frameReady, this, &CameraWindow::displayFrame);
    }
}

//获取相机
KVirtualCamera* CameraWindow::getCamera() const {
    return camera;
}

//显示图像
void CameraWindow::displayFrame(uint8_t* data, int width, int height, int channels) {
    std::cout<<"get image!"<<std::endl;
    if (width > 0 && height > 0) {
        int type = (channels == 3) ? CV_8UC3 : CV_8UC1; //数据类型
        cv::Mat image(height, width, type, data);       //创建Mat对象 
        if (channels == 3) {                            // 将 RGB 图像转换为 BGR
            cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        }
        //QSize labelSize = imageLabel->size();           //获取 QLabel 的大小，用于缩放图像
        QSize labelSize=size();
        cv::Mat resizedImage;
        // 使用 OpenCV 的 resize 函数将图像缩放到 QLabel 的大小
        cv::resize(image, resizedImage, cv::Size(labelSize.width(), labelSize.height()), 0, 0, cv::INTER_LINEAR);
        std::cout<<"width:"<<labelSize.width()<< "height:"<<labelSize.height()<<std::endl;
        // 将 OpenCV 的 cv::Mat 转换为 QImage
        QImage qimage(resizedImage.data, resizedImage.cols, resizedImage.rows, resizedImage.step,
                      (channels == 3) ? QImage::Format_BGR888 : QImage::Format_Grayscale8);
        // 将 QImage 转换为 QPixmap，并设置到 QLabel 中
        QPixmap pixmap = QPixmap::fromImage(qimage);
        //imageLabel->setPixmap(pixmap);
        setPixmap(pixmap);
        // 释放深拷贝的内存
        delete[] data;
        // 重新触发绘制事件，以绘制十字线和网格线
        update();
    }
}

//绘制事件
void CameraWindow::paintEvent(QPaintEvent* event) {
    QLabel::paintEvent(event);

    QPainter painter(this);

    // 绘制十字线
    if (crosslineEnabled) {
        painter.setPen(QPen(crossLineColor, crossLineThickness));
        int centerX = width() / 2 + crosslineXoffset;
        int centerY = height() / 2 + crosslineYoffset;
        painter.drawLine(centerX - crosslineWidth / 2, centerY, centerX + crosslineWidth / 2, centerY); // 水平线
        painter.drawLine(centerX, centerY - crosslineHeight / 2, centerX, centerY + crosslineHeight / 2); // 垂直线
    }

    // 绘制网格线
    if (gridlineEnabled) {
        painter.setPen(QPen(gridlineColor, gridlineThickness));
        int rowHeight = height() / gridRows;
        int colWidth = width() / gridCols;

        // 绘制水平线
        for (int i = 1; i < gridRows; ++i) {
            painter.drawLine(0, i * rowHeight, width(), i * rowHeight);
        }

        // 绘制垂直线
        for (int i = 1; i < gridCols; ++i) {
            painter.drawLine(i * colWidth, 0, i * colWidth, height());
        }
    }
}

//设置十字线属性
void CameraWindow::setCrossLine(bool enabled, int width, int height, int xOffset, int yOffset, QColor color, int thickness) {
    crosslineEnabled = enabled;
    crosslineWidth = width;
    crosslineHeight = height;
    crosslineXoffset = xOffset;
    crosslineYoffset = yOffset;
    crossLineColor = color;
    crossLineThickness = thickness;
    update(); // 重新绘制
}

//设置网格线属性
void CameraWindow::setGridLine(bool enabled, int rows, int cols, QColor color, int thickness) {
    gridlineEnabled = enabled;
    gridRows = rows;
    gridCols = cols;
    gridlineColor = color;
    gridlineThickness = thickness;
    update(); // 重新绘制
}

//切换十字线显示状态
void CameraWindow::toggleCrossLine() {
    crosslineEnabled = !crosslineEnabled;
    update();
}
//切换网格线显示状态
void CameraWindow::toggleGridLine() {
    gridlineEnabled = !gridlineEnabled;
    update();
}
