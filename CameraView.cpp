 #include "CameraView.h"


CameraView::CameraView(QWidget* parent):QGraphicsView(parent) {
    // 设置初始大小策略
    setDragMode(ScrollHandDrag);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 允许 CameraView 随窗口变化调整大小
    // 禁用滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    camera=nullptr;
    scene=new QGraphicsScene();
    setScene(scene);
    pixmapItem=new QGraphicsPixmapItem();
    scene->addItem(pixmapItem);
    // 初始化十字线和网格线
    // 初始化十字线和网格线
    QRectF viewRect = viewport()->rect();
    crosslinestat=false;
    crossline = new CrossLineItem(viewRect.width(), viewRect.height(), 0, 0, Qt::red, 2);
    scene->addItem(crossline);
    crossline->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    crossline->setVisible(crosslinestat);  // 默认隐藏
    gridlinestat=false;

    gridline = new GridLineItem(viewRect.width(), viewRect.height(),3, 3, Qt::red, 1);
    scene->addItem(gridline);
    gridline->setVisible(gridlinestat);  // 默认隐藏
    gridline->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setMouseTracking(true);
    frameCount=0;
    currentFrameRate=0.0;
    frameRateTimer.start();
}
void CameraView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);
        adjustCrossLine();
        adjustGridLine();
        update();
}
void CameraView::adjustCrossLine() {
    if (crossline && crosslinestat) {
        QRectF viewRect = viewport()->rect();
        QPointF center = viewRect.center();
        //crossline->setPos(center);  // 将十字线设置到中心
        QPointF centerInScene = mapToScene(center.toPoint());  // 转换为场景坐标

        crossline->setPos(centerInScene);  // 将十字线设置到场景的中心
        crossline->setWidth(viewRect.width());
        crossline->setHeight(viewRect.height());        // 根据视图大小调整长度
    }
}

void CameraView::adjustGridLine() {
    if (gridline && gridlinestat) {
        // 将视图的中心坐标转换为场景坐标

        QRectF viewRect = viewport()->rect();
        //QPointF center = viewRect.center();
        //QPointF centerInScene = mapToScene(center.toPoint());
        gridline->setWidth(viewRect.width());  // 根据视图大小调整网格线大小
        gridline->setHeight(viewRect.height());
        // 获取视图左上角的场景坐标
        QPointF topLeftInScene = mapToScene(viewRect.topLeft().toPoint());

        // 将网格线的位置设置为视图左上角的场景坐标
        gridline->setPos(topLeftInScene);
    }
}
void CameraView::mouseMoveEvent(QMouseEvent* event){
    QPoint pos=event->pos();
    std::cout<<"move"<<std::endl;
    emit mouseMovePoint(pos);
    QGraphicsView::mouseMoveEvent(event);
}
void CameraView::mousePressEvent(QMouseEvent* event){
    if(event->button()==Qt::LeftButton){
        QPoint pos=event->pos();
        emit mouseClicked(pos);
    }
    QGraphicsView::mousePressEvent(event);
}
void CameraView::mouseReleaseEvent(QMouseEvent* event){
    QGraphicsView::mouseReleaseEvent(event);
    adjustCrossLine();
    adjustGridLine();
    // 获取视图中心在场景中的坐标
    QPointF sceneCenter = mapToScene(viewport()->rect().center());

    qDebug() << "当前视图中心在场景中的坐标:" << sceneCenter;
}
void CameraView::mouseDoubleClickEvent(QMouseEvent* event){
    if(event->button()==Qt::LeftButton){
        QPoint pos=event->pos();
        emit mouseDoubleClick(pos);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}
void CameraView::keyPressEvent(QKeyEvent* event){
    emit keyPress(event);
    QGraphicsView::keyPressEvent(event);
}
void CameraView::wheelEvent(QWheelEvent* event){
    const double scaleFactor = 1.15;  // 缩放因子
    static double currentScale = 1.0;  // 当前缩放比例，初始值为1.0表示原始大小

    if (pixmapItem && !pixmapItem->pixmap().isNull()) {
        if (event->angleDelta().y() > 0) {
            // 向上滚动，放大图片
            currentScale *= scaleFactor;  // 更新当前缩放比例
            scale(scaleFactor,scaleFactor);

        } else if (event->angleDelta().y() < 0 && currentScale > 1.0) {
            // 向下滚动，缩小图片，但不能缩小到比原始大小还小
            currentScale /= scaleFactor;  // 更新当前缩放比例
            scale(1/scaleFactor,1/scaleFactor);
        }

        // 限制缩放比例，确保不会比原始图片小
        if (currentScale < 1.0) {
            resetTransform();  // 重置为原始大小
            currentScale = 1.0;  // 将当前缩放比例设置为1.0
            scale(currentScale,currentScale);
        }
        // 设置 `pixmapItem` 的变换
        //QTransform transform;
        //transform.scale(currentScale, currentScale);
        //pixmapItem->setTransform(transform);
    }
    adjustCrossLine();
    adjustGridLine();
    update();
    //QGraphicsView::wheelEvent(event);  // 保留原始的滚轮事件处理
}
void CameraView::displayFrame(uint8_t* data, int width, int height, int channels)
{
    /*
    if (width > 0 && height > 0) {
        std::cout<<"display"<<std::endl;
        int type = (channels == 3) ? CV_8UC3 : CV_8UC1;
        cv::Mat image(height, width, type, data);
        emit resolution_info(width,height);
        if (channels == 3) {
            cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        }
        QImage qimage(image.data, image.cols, image.rows, image.step,
                      (channels == 3) ? QImage::Format_BGR888 : QImage::Format_Grayscale8);
        this->image=qimage.copy();
        QPixmap pixmap = QPixmap::fromImage(qimage);

        pixmapItem->setPixmap(pixmap);  // 设置到QGraphicsPixmapItem中
        //pixmapItem->setOffset(0, 0);  // 将图像定位到左上角
        // 更新场景的大小
        scene->setSceneRect(0, 0, width, height);

        // 调整视图的矩形以匹配场景大小
        //fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        delete[] data;
        update();  // 触发重绘事件，绘制十字线和网格线
        frameCount++;
        if (frameRateTimer.elapsed() >= 1000) {  // 如果超过1秒（1000毫秒）
            currentFrameRate = frameCount / (frameRateTimer.elapsed() / 1000.0);  // 计算帧率
            frameCount = 0;  // 重置计数器
            frameRateTimer.restart();  // 重启计时器
            emit fps_info(currentFrameRate);
        }
    }*/
    if (width > 0 && height > 0 && channels == 3) {
        std::cout << "display" << std::endl;

        int subHeight = height / 3;  // 每个分量占 1/3 的高度
        if (subHeight * 3 != height) {
            std::cerr << "Height is not divisible by 3, data layout might be incorrect." << std::endl;
            return;
        }

        // 创建 Mat 用于存储最终的 RGB 图像
        cv::Mat image(height, width, CV_8UC3);

        // 重新排列像素：从 data 中分别提取 R, G, B，并按顺序重组成 RGB 图像
        uint8_t* rData = data;                       // R 分量开始于 data 的起始
        uint8_t* gData = data + subHeight * width*3;   // G 分量开始于 1/3 高度
        uint8_t* bData = data + 2 * subHeight * width*3; // B 分量开始于 2/3 高度

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // 按照行列顺序，将 R, G, B 三个分量组成一个像素点
                image.at<cv::Vec3b>(y, x)[0] = bData[y * width + x];  // B 分量
                image.at<cv::Vec3b>(y, x)[1] = gData[y * width + x];  // G 分量
                image.at<cv::Vec3b>(y, x)[2] = rData[y * width + x];  // R 分量
            }
        }

        // 发送分辨率信息
        emit resolution_info(width, height);

        // 将 OpenCV 的 BGR 图像转换为 Qt 的 QImage
        QImage qimage(image.data, image.cols, image.rows, image.step, QImage::Format_BGR888);
        this->image = qimage.copy();  // 复制 QImage

        // 将 QImage 转换为 QPixmap 并显示
        QPixmap pixmap = QPixmap::fromImage(qimage);
        pixmapItem->setPixmap(pixmap);  // 设置到 QGraphicsPixmapItem 中

        // 更新场景大小
        scene->setSceneRect(0, 0, width, height);

        delete[] data;  // 删除动态分配的数据

        // 触发重绘事件，绘制十字线和网格线
        update();

        frameCount++;
        if (frameRateTimer.elapsed() >= 1000) {  // 如果超过1秒（1000毫秒）
            currentFrameRate = frameCount / (frameRateTimer.elapsed() / 1000.0);  // 计算帧率
            frameCount = 0;  // 重置计数器
            frameRateTimer.restart();  // 重启计时器
            emit fps_info(currentFrameRate);  // 发送帧率信息
        }
    }
}
//绑定相机
void CameraView::setCamera(KVirtualCamera* cam) {

    //如果已经绑定相机，则进行解绑
    if (camera!=nullptr) {
        std::cout<<"disconnect"<<std::endl;
        disconnect(camera, &KVirtualCamera::frameReady, this, &CameraView::displayFrame);
    }
    //更换绑定的相机
    camera = cam;
    if (camera!=nullptr) {
        std::cout<<"connect"<<std::endl;
        connect(camera, &KVirtualCamera::frameReady, this, &CameraView::displayFrame);
    }
}
//获取相机
KVirtualCamera* CameraView::getCamera() const {
    return camera;
}

QImage CameraView::getImage(){
    return image;
}

//绘制事件

void CameraView::drawForeground(QPainter* painter, const QRectF& rect) {

    QGraphicsView::drawForeground(painter, rect);
    //painter->setPen(QPen(Qt::black, 1));
    //painter->drawRect(rect.adjusted(1 , 1 , -1 , -1 ));
}



//切换十字线显示状态
void CameraView::toggleCrossLine() {
    crosslinestat=!crosslinestat;
    adjustCrossLine();
    crossline->setVisible(crosslinestat);

    update();
}
//切换网格线显示状态
void CameraView::toggleGridLine() {
    gridlinestat=!gridlinestat;
    adjustGridLine();
    gridline->setVisible(gridlinestat);

    update();
}
QColor CameraView::getRGBAtPoint(const QPoint &point) {
    if (!pixmapItem || pixmapItem->pixmap().isNull()) {
        return QColor();  // 如果没有图像，返回默认颜色
    }

    QImage image = pixmapItem->pixmap().toImage();  // 将 pixmap 转换为 QImage
    QPointF scenePos = mapToScene(point);  // 将视图坐标转换为场景坐标
    QPoint imagePos = scenePos.toPoint();  // 将场景坐标转换为图像坐标

    if (!image.rect().contains(imagePos)) {
        return QColor();  // 如果坐标超出图像范围，返回默认颜色
    }

    return QColor(image.pixel(imagePos));  // 返回指定位置的 RGB 颜色值
}
