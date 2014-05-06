/**
 * Class header file of Robber
 */
#ifndef ROBBER
#define ROBBER
#include "QtGui"
#include "QRectF"
#include "Person.h"
#include "iostream"
#include "vector"
using namespace std;
class Robber:public Person{
public:
    Robber();
    Robber(Map* _map);
    static bool cmpDoublePointEscape(pair<double,QPointF> p1, pair<double,QPointF> p2);
    void randomEscape(vector<QPointF> avoidPoints);
    void winGame(vector<QPointF> avoidPoints);
    void escapeFrom(vector<QPointF> avoidPoints);
    bool tryToEscapeTo(qreal x, qreal y, QPointF policePos, double initDistance);
};

#endif
