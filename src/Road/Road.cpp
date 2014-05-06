/**
 * Implemention of class Road, used to limit map
 */
#include "Road.h"

Road::Road()
{
}

/**
 * Constructor allowing the use of Roads of custom lengths
 */
Road::Road(int x, int y, int w, int h, int type)
{
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
    this->type=type;
}
QRectF Road::boundingRect() const{
    return QRectF(x,y,w,h);
}
/**
 * Painting a Road
 * \param QPainter painter
 * \param QStyleOptionGraphicsItem option
 * \param QWidget widget
 */
void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF clipBox=boundingRect();    
    clipBox.setRect(clipBox.x()+scenePos().x(),clipBox.y()+scenePos().y(),clipBox.width(),clipBox.height());
    clipBox=clipBox.intersected(boundary);
    clipBox.setRect(clipBox.x()-scenePos().x(),clipBox.y()-scenePos().y(),clipBox.width(),clipBox.height());
    painter->setClipRect(clipBox);
    
    painter->setPen(Qt::NoPen);
    switch(type){
        case 1:
            painter->setBrush(Qt::lightGray);
        break;
        case 2:
            painter->setBrush(Qt::yellow);
        break;
        case 3:
            painter->setBrush(Qt::lightGray);
        break;
    }
    
    painter->drawRect(boundingRect());

}
