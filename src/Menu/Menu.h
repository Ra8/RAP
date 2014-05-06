/**
 * Menu class header file
 */
#ifndef MENU_H
#define MENU_H
#include "QtGui"
#include <QtCore>
#include <vector>
#include "map"
#include "iostream"
using namespace std;
class Menu: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
	Menu(vector<string> list, int fontSize=30, int space=-1, QFont font=QFont("lucida", 30, QFont::Bold, false), QColor highlight=QColor(QString("#0A8AC9")), QColor defaultColor=QColor(QString("#000")));
	vector<QGraphicsSimpleTextItem*> list;
	int selected;
	int space;
	QFont font;
	QColor highlight;
	QColor defaultColor;
	int isHighlight;
	int loopAround;
	void select(int direction);
	void selectUp();
	void selectDown();
	int getSelected();
	void enableHighlight();
	void disableHighlight();
	void enableLoopAround();
	void disableLoopAround();
};
#endif