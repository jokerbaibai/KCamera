#ifndef CROSSLINEITEM_H
#define CROSSLINEITEM_H

#include <QGraphicsItem>
#include <QPainter>

class CrossLineItem : public QGraphicsItem {
public:
    //构造函数
    //CrossLineItem();
    //带参构造函数
    CrossLineItem(int width, int height, int xOffset, int yOffset, QColor color, int thickness, QGraphicsItem* parent = nullptr);

    void setHeight(int height);
    void setWidth(int width);
    void setXOffset(int len);
    void setYOffset(int len);
    void setThickness(int thick);
    void setColor(QColor color);
    // 范围矩形
    QRectF boundingRect() const override;
    //绘制事件
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    int crosslineWidth;         //宽
    int crosslineHeight;        //高
    int crosslineXoffset;       //x偏移量，右为正方向
    int crosslineYoffset;       //y偏移量，上为正方向
    QColor crossLineColor;      //颜色
    int crossLineThickness;     //粗细
};

#endif // CROSSLINEITEM_H
