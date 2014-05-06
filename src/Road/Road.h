/**
 * Class Road used to delimit the map
 */
#ifndef ROAD_H
#define ROAD_H
#include "QtGui"
extern QRectF boundary;
class Road: public QGraphicsItem
{
public:

    Road();
    Road(int x, int y, int w, int h, int type);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    QRectF boundingRect() const;

    QPoint startPoint;
    QPoint endPoint;
    int x,y,w,h,type;
};

#endif // Road_H
