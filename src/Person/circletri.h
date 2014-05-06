/**
 * CircleTri class header file
 */
#ifndef CIRCLETRI_H
#define CIRCLETRI_H
#include "QtGui"
#include "QRectF"

extern QRectF boundary;
class CircleTri:public QGraphicsObject
{
    Q_OBJECT

public:
    CircleTri();
    CircleTri(QColor triColor,QColor circleColor);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) ;
    QColor triColor;
    QColor circleColor;
};
#endif // CIRCLETRI_H
