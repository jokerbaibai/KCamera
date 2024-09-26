#include "crosslineitem.h"

CrossLineItem::CrossLineItem(int width, int height, int xOffset, int yOffset, QColor color, int thickness, QGraphicsItem* parent)
    : QGraphicsItem(parent),
    crosslineWidth(width),
    crosslineHeight(height),
    crosslineXoffset(xOffset),
    crosslineYoffset(yOffset),
    crossLineColor(color),
    crossLineThickness(thickness) {}

void CrossLineItem::setHeight(int height){
    crosslineHeight=height;
};
void CrossLineItem::setWidth(int width){
    crosslineWidth=width;
};
void CrossLineItem::setXOffset(int len){
    crosslineXoffset=len;
};
void CrossLineItem::setYOffset(int len){
    crosslineYoffset=len;
};
void CrossLineItem::setThickness(int thick){
    crossLineThickness=thick;
};
void CrossLineItem::setColor(QColor color){
    crossLineColor=color;
};
void CrossLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)  {
    painter->setPen(QPen(crossLineColor, crossLineThickness));
    painter->drawLine(-int(crosslineWidth / 6), 0, int(crosslineWidth / 6), 0);  // 水平线
    painter->drawLine(0, -int(crosslineHeight /6), 0, int(crosslineHeight /6));  // 垂直线
}
QRectF CrossLineItem::boundingRect()const  {
    return QRectF(-crosslineWidth / 2 + crosslineXoffset, -crosslineHeight / 2 + crosslineYoffset, crosslineWidth, crosslineHeight);
}
