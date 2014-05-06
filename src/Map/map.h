/**
 * Map class header file
 */
#ifndef MAP_H
#define MAP_H
class Guard;
class Police;
class Robber;
#include "Road.h"
#include "Building.h"
#include "Person.h"
#include "Robber.h"
#include "Police.h"
#include "Guard.h"
#include "Flag.h"
#include "StatsPanel.h"
#include <vector>
#include "QPointF"
#include "json.h"
#include "map"
#include "cmath"
using namespace std;
extern map<int,int> pressedKeys;
class Map: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:

    Map();
    Map(string filename, StatsPanel* statsPanel, int role, string accountID);
    Map(string filename, StatsPanel* statsPanel);
	
    string filename;
    string accountID;
    vector<Road*> roads;
    vector<Building*> buildings;
    QPointF robberInitPos;
    vector<QPointF> policeInitPos;
    int graph[500][500];
    void initGraph();
    pair<int,int> getClosestIndexes(QPointF p);
    
    StatsPanel* statsPanel;
    Robber* robber;
    vector<Police*> polices;
    vector<Guard*> guards;
    vector<Flag*> flags;
    int previousRole;
    int role;
    int level;
    vector<int> targets;

    void increaseLevel();
    void acceptKeyEvent(QKeyEvent* event);
    void centerMap();
    void hideBuildingMoney();
    void showBuildingMoney();
    void stealBuildingAI(int policeCount);
    void stealBuilding();
    void toggleFlag();
    void updatePos();
    void saveToFile(string filename);
    void escapeFromGate();
    void tryToArrestRobber();
signals:
    void TOGGLEPAUSESIGNAL();
private:
    void loadFile(string filename);
    void loadSavedFile(string filename);
public slots:
    void doKeys(int isPolice);
    void returnPreviousRole();
};

#endif // MAP_H
