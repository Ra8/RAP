/**
 * Flags class header file
 */
#ifndef FLAG_H
#define FLAG_H
#include "QtGui"
#include "QRectF"
#include "iostream"
extern QRectF boundary;
class Flag:public QGraphicsObject
{
    Q_OBJECT

public:
    Flag();
    Flag(QPointF position);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) ;
private:
    int x,y,w,h;
};

#endif // CIRCLETRI_H
