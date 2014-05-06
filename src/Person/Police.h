/**
 * Class header of Police
 */
#ifndef POLICE
#define POLICE
#include "QtGui"
#include "QRectF"
#include "iostream"
#include "Person.h"
using namespace std;

class Police:public Person{
public:
    Police();
    Police(Map* _map);
    void track(QPointF robberPoss);
};

#endif
