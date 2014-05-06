#include <QtGui/QApplication>
#include "viewwindow.h"
#include "map"
#include "Building.h"
#include <QMessageBox>
#include "iostream"
#include "json.h"
Map* ConstructMap();

/**
 * \mainpage 435L Assignment: Chase and Run
 * \author Joseph Mourad
 * \author Rene Adaimi
 * \date 2-2-2014
 */
map<int,int> pressedKeys;
QRectF boundary(-50,-50,700,700);


const int ROBBER_ROLE=0;
const int POLICE_ROLE=1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewWindow vw;
    return a.exec();
}
