/**
 * Class header file of Guard
 */
#ifndef GUARD
#define GUARD
#include "QtGui"
#include "QRectF"
#include "Person.h"
#include "Building.h"
class Guard:public Person{
public:
    Guard();
    Guard(Map* _map, Building* building);
    void track(QPointF robberPos);
    Building* building;
    bool canFollowRobber;
};

#endif
