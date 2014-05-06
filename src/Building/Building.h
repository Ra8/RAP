/**
 * Building class header file
 */
#ifndef BUILDING_H
#define BUILDING_H
#include "QtGui"
#include "QRectF"
#include "cstdlib"
extern QRectF boundary;

class Building:public QGraphicsObject
{
    Q_OBJECT

public:
    Building();
    Building(int money, int posX, int posY, bool isHome, int type);
    Building(int money, int posX, int posY, bool isHome, int type, int initGuardX, int initGuardY);
    QRectF boundingRect() const;
    void stealBuilding();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) ;
    int getStolen();
    void showMoney();
    void hideMoney();
    void setGuardNum(int guardNum);
    QPointF getGuardInitPos();
    int initGuardX;
    int initGuardY;
    bool hasGuard;
    bool isHome;
    int type;
    int getGuardNum();
    int money;
    bool showM;    
    int x;
    int y;
    int w;
    int h;
    int guardNum;
};

#endif // BUILDING_H
