#ifndef GRIDLINEITEM_H
#define GRIDLINEITEM_H

#include <QGraphicsItem>
#include <QPainter>

class GridLineItem : public QGraphicsItem {
public:
    //带参构造函数
    GridLineItem(int width,int height,int rows, int cols, QColor color, int thickness, QGraphicsItem* parent = nullptr)
        : QGraphicsItem(parent),
        gridwidth(width),
        gridheight(height),
        gridRows(rows),
        gridCols(cols),
        gridlineColor(color),
        gridlineThickness(thickness) {}
    //参数设置并重绘
    void setGridLineProperties(int rows, int cols, QColor color, int thickness) {
        gridRows = rows;
        gridCols = cols;
        gridlineColor = color;
        gridlineThickness = thickness;
        update();  // 触发重新绘制
    }
    void setWidth(int width){
        gridwidth=width;
    }
    void setHeight(int height){
        gridheight=height;
    }
    //范围矩形
    QRectF boundingRect() const override {
        return QRectF(0, 0, gridwidth, gridheight);  // 根据需要调整大小
    }
    //绘制事件
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        painter->setPen(QPen(gridlineColor, gridlineThickness));
        int rowHeight = boundingRect().height() / gridRows;
        int colWidth = boundingRect().width() / gridCols;

        // 绘制水平线
        for (int i = 1; i < gridRows; ++i) {
            painter->drawLine(0, i * rowHeight, boundingRect().width(), i * rowHeight);
        }

        // 绘制垂直线
        for (int i = 1; i < gridCols; ++i) {
            painter->drawLine(i * colWidth, 0, i * colWidth, boundingRect().height());
        }
    }

private:
    int gridwidth;
    int gridheight;
    int gridRows;           //行
    int gridCols;           //列
    QColor gridlineColor;   //颜色
    int gridlineThickness;  //粗细
};


#endif // GRIDLINEITEM_H
