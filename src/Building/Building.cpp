#include "Building.h"
#include "iostream"
using namespace std;

/**
 * Default constructor
 */
Building::Building()
{
    // map=new Map();
    setFlag(QGraphicsItem::ItemIsFocusable, false);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    money=0;
    x=y=0;
    w=h=0;
    guardNum=-1;
    hasGuard=false;
    type=1;
}

/**
 * Constructor allowing use of different colors
 */
Building::Building(int money, int posX, int posY, bool isHome, int type)
{
    // map=_map;
    setFlag(QGraphicsItem::ItemIsFocusable, false);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    this->money=money;
    x=y=-25;
    w=h=50;
    setPos(posX,posY);
    guardNum=-1;
    hasGuard=false;
    this->isHome=isHome;
    this->type=type;
    if(this->type==3){
        this->type+=rand()%4;
    }
}
Building::Building(int money, int posX, int posY, bool isHome, int type, int initGuardX, int initGuardY){
    // map=_map;
    setFlag(QGraphicsItem::ItemIsFocusable, false);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    this->money=money;
    x=y=-25;
    w=h=50;
    setPos(posX,posY);
    hasGuard=true;
    guardNum=-1;
    this->initGuardX=initGuardX;
    this->initGuardY=initGuardY;
    this->isHome=isHome;
    this->type=type;
    if(this->type==3){
        this->type+=rand()%4;
    }
}
int Building::getStolen(){
    int tmp=money;
    money=0;
    update(boundingRect());
    return tmp;
}
void Building::setGuardNum(int guardNum){
    if(!hasGuard)return;
    this->guardNum=guardNum;
}
/**
 * Bounding rect shape
 * \return a rectangle shape
 */
QRectF Building::boundingRect() const{
    return QRectF(x, y, w, h);

}
void Building::showMoney(){
    if(!showM){
        showM=true;
        update(boundingRect());
    }
}
void Building::hideMoney(){
    if(showM){
        showM=false;
        update(boundingRect());
    }
}
QPointF Building::getGuardInitPos(){
    return QPointF(initGuardX,initGuardY);
}
int Building::getGuardNum(){
    return guardNum;
}
/**
 * Paint Building
 * \param QPainter painter
 * \param QStyleOptionsGraphicsItem option
 * \param QWidget widget
 */
void Building::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF clipBox=boundingRect();    
    clipBox.setRect(clipBox.x()+scenePos().x(),clipBox.y()+scenePos().y(),clipBox.width(),clipBox.height());
    clipBox=clipBox.intersected(boundary);
    clipBox.setRect(clipBox.x()-scenePos().x(),clipBox.y()-scenePos().y(),clipBox.width(),clipBox.height());
    painter->setClipRect(clipBox);
    
    painter->setBrush(Qt::black);
    QPixmap* image;
    string imgPath="img/house";
    switch(type){
        case 1:
            imgPath="img/house";
        break;
        case 2:
            imgPath="img/bank";
        break;
        case 3:
            imgPath="img/shop1";
        break;
        case 4:
            imgPath="img/shop2";
        break;
        case 5:
            imgPath="img/shop3";
        break;
        case 6:
            imgPath="img/shop4";
        break;
    }
    if(!isHome){
        imgPath+="_c";
    }
    imgPath+=".png";
    image=new QPixmap(imgPath.c_str());
    painter->drawPixmap(x,y,w,h,*image);
    if(showM){
        if(type>=3){
            painter->setBrush(Qt::black);
            painter->setPen(Qt::black);
        } else {
            painter->setBrush(Qt::white);
            painter->setPen(Qt::white);
        }
        
        painter->drawText(-15,0,QString::number(money));
    }
}
