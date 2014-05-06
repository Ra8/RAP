/**
 * Class header of person
 */
#ifndef PERSON
#define PERSON
#include "circletri.h"
#include "QtGui"
#include "QRectF"
#include "map"
#include "iostream"
#include "cmath"
#include "queue"
#include "stack"
#include "algorithm"
#include "ctime"
#include "cstdlib"
class Map;
extern std::map<int,int> pressedKeys;
using namespace std;
class Person:public CircleTri{
	Q_OBJECT
public:
    Person();
    Person(Map* _map, bool isPolice,QColor triColor,QColor circleColor);
    Map* map;
    int movingStep;
    bool isPolice;
    stack<QPointF>* pathToFollow;
    // virtual void track(QPointF pos)=0;
    static bool cmpDoublePoint(pair<double,QPointF> p1, pair<double,QPointF> p2);
    void randomWalk();
    void longDistanceMoveTo(QPointF newPos, int graph[][500]);
    bool shortDistanceMove(QPointF newPos);
    bool tryToMoveTo(QPointF newPos);
    bool tryToMoveTo(qreal x, qreal y);
    double distanceTo(QPointF p2);
    double distanceBetween(QPointF p1, QPointF p2);
    bool move();
    bool onMap();
};
#include "map.h"
#endif
