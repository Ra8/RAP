/**
 * Implements the circleTri functions and constructors to display
 * a triangle within a circle
 */
#include "circletri.h"
#include "iostream"
using namespace std;

/**
 * Default constructor, draws a white and yellow CircleTri
 */
CircleTri::CircleTri()
{
    triColor=Qt::white;
    circleColor=Qt::yellow;
    setFlag(QGraphicsItem::ItemIsFocusable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);
    setAcceptDrops(false);
    setAcceptTouchEvents(false);
    setAcceptedMouseButtons(0);

    setFocus();
    setFlag(QGraphicsItem::ItemIsMovable,false);
}

/**
 * Constructor allowing use of different colors
 */
 CircleTri::CircleTri(QColor triColor, QColor circleColor)
{

    this->triColor=triColor;
    this->circleColor=circleColor;
    setFlag(QGraphicsItem::ItemIsFocusable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);
    setAcceptDrops(false);
    setAcceptTouchEvents(false);
    setAcceptedMouseButtons(0);

    setFocus();
    setFlag(QGraphicsItem::ItemIsMovable,false);
}

/**
 * Bounding rect shape
 * \return a rectangle shape
 */
QRectF CircleTri::boundingRect() const{
    return QRectF(-10, -10, 20, 20);

}
/**
 * Paint CircleTri
 * \param QPainter painter
 * \param QStyleOptionsGraphicsItem option
 * \param QWidget widget
 */
void CircleTri::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF clipBox=boundingRect();    
    clipBox.setRect(clipBox.x()+scenePos().x(),clipBox.y()+scenePos().y(),clipBox.width(),clipBox.height());
    clipBox=clipBox.intersected(boundary);
    clipBox.setRect(clipBox.x()-scenePos().x(),clipBox.y()-scenePos().y(),clipBox.width(),clipBox.height());
    painter->setClipRect(clipBox);

    painter->setBrush(circleColor);
    painter->drawEllipse(QPoint(0,0),10,10);

    painter->setBrush(triColor);
    QPolygonF Triangle;
    Triangle.append(QPointF(0,-10));
    Triangle.append(QPointF(8,5));
    Triangle.append(QPointF(-8,5));
    Triangle.append(QPointF(0,-10));

    painter->drawPolygon(Triangle);

}