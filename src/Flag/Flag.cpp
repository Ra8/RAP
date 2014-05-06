/**
 * Implements the flags functions
 */
#include "Flag.h"

/**
 * Default constructor
 */
Flag::Flag(){
    QPointF center(650/2,650/2);
    setPos(center);
    x=-8;
    y=-40;
    w=h=40;
}

/**
 * Constructor allowing  to position
 */
Flag::Flag(QPointF position){
    setPos(position);
    x=-8;
    y=-40;
    w=h=40;
}

/**
 * Bounding rect shape
 * \return a rectangle shape
 */
QRectF Flag::boundingRect() const{
    return QRectF(x, y, w, h);
}
/**
 * Paint CircleTri
 * \param QPainter painter
 * \param QStyleOptionsGraphicsItem option
 * \param QWidget widget
 */
void Flag::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF clipBox=boundingRect();    
    clipBox.setRect(clipBox.x()+scenePos().x(),clipBox.y()+scenePos().y(),clipBox.width(),clipBox.height());
    clipBox=clipBox.intersected(boundary);
    clipBox.setRect(clipBox.x()-scenePos().x(),clipBox.y()-scenePos().y(),clipBox.width(),clipBox.height());
    painter->setClipRect(clipBox);
    
    QPixmap image("img/flag1.png");
    painter->drawPixmap(x,y,w,h,image);
}