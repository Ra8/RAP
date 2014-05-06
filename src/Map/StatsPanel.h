/**
 * Header of class game statspanel
 */
#ifndef STATSPANEL_H
#define STATSPANEL_H
#include "QtGui"
#include <QtCore>
#include <QTimer>
#include "iostream"
#include "QObject"
class StatsPanel: public QObject, public QGraphicsItemGroup
{
   Q_OBJECT

public:
    QGraphicsTextItem* robberMoney;
    QGraphicsTextItem* robberMoney2;
    QGraphicsTextItem* elapsedTime;
    QGraphicsTextItem* warningText;
    QGraphicsTextItem* targetText;
    StatsPanel();
    int getCurrentMoney();
    int getCurrentTime();
    void setCurrentMoney(int money);
    void setCurrentTime(int secs);
    void removeWarning();
    void setWarning(int role);
    void showTarget(int target);
public slots:
    void updateTime();
};

#endif
