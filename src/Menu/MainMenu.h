/**
 * MainMenu class header file
 */
#ifndef MAINMENU_H
#define MAINMENU_H
#include "map.h"
#include <vector>
#include "QPointF"
#include "json.h"
#include "map"
#include "Menu.h"
#include "Accounts.h"
#include "QInputDialog"
#include "QWidget"
using namespace std;
extern map<int,int> pressedKeys;
extern QRectF boundary;
class MainMenu: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
	enum{MAIN,SELECT,INSTRUCTIONS,MAPS,CHANGEACCOUNT,NEWACCOUNT};
    MainMenu();
    int role;
    string filename;
    
    QFont* font;

    int centerX;
    Accounts* accounts;
    vector<Account*> accountList;
    Menu* main;
    Menu* selectPlayer;
    Menu* maps;
    Menu* instructions;
    Menu* accountsMenu;
    int inview;
    vector<string> accountsStrings, mapList;
    vector<string> getAllMaps();

    void mainFunctions(int selected);
    void selectFunctions(int selected);
    void mapsFunctions(int selected);
    void changeAccountsFunctions(int selected);

	void acceptKeyEvent(QKeyEvent* event);
    QRectF boundingRect() const;
signals:
	void STARTGAMESIGNAL(string filename, int role, string accountID);
};
#endif