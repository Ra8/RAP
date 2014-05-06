/**
 * Implementation of class viewindow
 */
#include "viewwindow.h"

using namespace std;
/**
 * ViewWindow constructor
 * adds policeman, robber, scene and map to the viewWindow
 * \param Map _map
 */
ViewWindow::ViewWindow(){
    inview=MAINMENU;
    this->role=role;
    
    scene= new QGraphicsScene;
    scene->setSceneRect(boundary);
    view = new QGraphicsView;
    view->setScene(scene);
    view->setBackgroundBrush(QBrush(QColor(173,255,47,200), Qt::SolidPattern));
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);//QGraphicsView::BoundingRectViewportUpdate);
    view->installEventFilter(this);
    view->show();
    view->showMaximized();

    mainMenu = new MainMenu();
    mainMenu->setPos(0,0);
    scene->addItem(mainMenu);
    QObject::connect(mainMenu, SIGNAL(STARTGAMESIGNAL(string,int,string)), this, SLOT(startGame(string,int,string)));
}

bool ViewWindow::eventFilter(QObject *obj, QEvent *event){
    QKeyEvent *keyEvent;
    if (event->type() == QEvent::KeyPress) {
        keyEvent = static_cast<QKeyEvent *>(event);
        pressedKeys[keyEvent->key()] = true;
        switch(inview){
            case MAINMENU:
                mainMenu->acceptKeyEvent(keyEvent);
            break;
            case GAME:
                map->acceptKeyEvent(keyEvent);
            break;
        }
        return true;
    } else if(event->type() == QEvent::KeyRelease) {
        keyEvent = static_cast<QKeyEvent *>(event);
        pressedKeys[keyEvent->key()] = false;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
 }
 return true;
}
void ViewWindow::togglePause(){
    if(gamePaused){
        timer.start(1000);
        policeTimer.start(10);
        robberTimer.start(8);
    } else {
        timer.stop();
        policeTimer.stop();
        robberTimer.stop();
    }
    gamePaused = !gamePaused;
}
void ViewWindow::startGame(string filename, int role, string accountID){
    inview=GAME;
    gamePaused=true;
    scene->removeItem(mainMenu);

    statsPanel= new StatsPanel();
    statsPanel->setPos(700,0);
    scene->addItem(statsPanel);
    if(role!=-1)
        map=new Map(filename,statsPanel,role, accountID);
    else
       map=new Map("accounts/savedGames/"+accountID,statsPanel); 
    QObject::connect(map, SIGNAL(TOGGLEPAUSESIGNAL()), this, SLOT(togglePause()));
    map->setPos(0,0);
    scene->addItem(map);
    scene->addRect(boundary);

    connect(&timer, SIGNAL(timeout()), statsPanel, SLOT(updateTime()));
    
    // QObject::connect(&policeTimer, SIGNAL(timeout()), map, SLOT(doKeys(int)));
    // QObject::connect(&robberTimer, SIGNAL(timeout()), map, SLOT(doKeys(int)));
    

    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    connect(&policeTimer, SIGNAL(timeout()), signalMapper, SLOT(map())) ;
    connect(&robberTimer, SIGNAL(timeout()), signalMapper, SLOT(map())) ;

    signalMapper-> setMapping(&policeTimer, 0) ;
    signalMapper-> setMapping(&robberTimer, 1) ;

    connect(signalMapper, SIGNAL(mapped(int)), map, SLOT(doKeys(int))) ;
    togglePause();
}




