/**
 * Header of class viewwindow
 */
#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H
#include "QtGui"
#include <QtCore>
#include <QTimer>
#include "Person.h"
#include "Police.h"
#include "Robber.h"
#include "Guard.h"
#include "circletri.h"
#include "Building.h"
#include "map.h"
#include "iostream"
#include "vector"
#include "QObject"
#include "QTimer"
#include "cmath"
#include "map"
#include "Flag.h"
#include "StatsPanel.h"
#include "MainMenu.h"
extern map<int,int> pressedKeys;
extern const int ROBBER_ROLE;
extern const int POLICE_ROLE;
extern QRectF boundary;
class ViewWindow: public QObject
{
   Q_OBJECT


public:
    enum{MAINMENU,GAME};
    QGraphicsView* view;
    QGraphicsScene* scene;
    StatsPanel* statsPanel;
    MainMenu* mainMenu;
    QTimer timer;
    QTimer robberTimer;
    QTimer policeTimer;
    Map* map;
    bool gamePaused;
    int role; // 0=robber, 1=police
    int inview;
    ViewWindow();
    
    bool eventFilter(QObject *obj, QEvent *event);
  
public slots:
    void startGame(string filename, int role, string accountID);
    void togglePause();
};

#endif // VIEWWINDOW_H
