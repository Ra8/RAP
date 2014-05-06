/**
 * Person class implementation, contains the common attributes to police
 * and robber
 */
#include "Person.h"
using namespace std;
Person::Person()
:CircleTri()
{
    pathToFollow=new stack<QPointF>();
    movingStep=1;
    this->isPolice=false;
}

/**
 * Constructor allows to specify whether person isPolice or Robber
 */
Person::Person(Map *_map, bool isPolice, QColor triColor,QColor circleColor)
:CircleTri(triColor,circleColor)
{
    pathToFollow=new stack<QPointF>();
    map=_map;
    movingStep=1;
    this->isPolice=isPolice;
}
/**
 * Move person on keypress event
 * \param QKeyEvent event
 */
bool Person::move(){
    QPointF currentPos=pos();
    bool hasMoved=false;
    if(pressedKeys[Qt::Key_Right] && !hasMoved){
        setPos(pos().x()+movingStep, pos().y());
        hasMoved=true;
        if(!onMap()){
            setPos(currentPos);
            hasMoved=false;
        }
        currentPos=pos();
    }

    if(pressedKeys[Qt::Key_Left] && !hasMoved){
        setPos(pos().x()-movingStep, pos().y());
        hasMoved=true;
        if(!onMap()){
            setPos(currentPos);
            hasMoved=false;
        }
        currentPos=pos();
    }

    if(pressedKeys[Qt::Key_Up] && !hasMoved){
        setPos(pos().x(), pos().y()-movingStep);
        hasMoved=true;
        if(!onMap()){
            setPos(currentPos);
            hasMoved=false;
        }
        currentPos=pos();
    }

    if(pressedKeys[Qt::Key_Down] && !hasMoved){
        setPos(pos().x(), pos().y()+movingStep);
        hasMoved=true;
        if(!onMap()){
            setPos(currentPos);
            hasMoved=false;
        }
        currentPos=pos();
    }
    
    return hasMoved;
}
void Person::randomWalk(){
    int x,y;
    srand(time(0));
    while(true){
        x=rand()%500;
        y=rand()%500;
        if(map->graph[x][y]==1)
            break;
    }
    longDistanceMoveTo(QPointF(x*25+25,y*25+25),map->graph);
}
/**
 * returns the direction in which the person has to move
 * to arrive to his new position
 */
void Person::longDistanceMoveTo(QPointF newPos, int graph[][500]){
    int dp[500][500];
    pair<int,int> parents[500][500];
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            dp[i][j]=-1;
        }
    }
    pair<int,int> oldIndexs = map->getClosestIndexes(pos());
    pair<int,int> newIndexs = map->getClosestIndexes(newPos);
    // cout << oldIndexs.first << ", " << oldIndexs.second << " \t " << newIndexs.first << ", " << newIndexs.second << endl;
    int dx[]={1,0,-1,0};
    int dy[]={0,-1,0,1};
    dp[oldIndexs.first][oldIndexs.second]=0;
    parents[oldIndexs.first][oldIndexs.second]=make_pair(-1,-1);
    queue<pair<int,int> > q;
    q.push(oldIndexs);
    bool found=false;
    while(!q.empty()){
        pair<int,int> curr=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int nx=curr.first+dx[i];
            int ny=curr.second+dy[i];
            if(nx>=0 && ny>=0 && nx<500 && ny<500)
            if(graph[nx][ny]==1 && dp[nx][ny]==-1){
                q.push(make_pair(nx,ny));
                parents[nx][ny]=make_pair(curr.first,curr.second);
                if(nx==newIndexs.first && ny==newIndexs.second){
                    found=true;
                }
            }
            dp[nx][ny]=0;
        }
        if(found)break;
    }
    pair<int,int> currIndex=newIndexs;
    pair<int,int> nextIndex=newIndexs;
    stack<QPointF>* newPath=new stack<QPointF>();
    if(found){
        while(true){//backtracking
            newPath->push(QPointF(currIndex.first*25+25,currIndex.second*25+25));
            nextIndex=currIndex;
            currIndex=parents[currIndex.first][currIndex.second];
            if(currIndex.first==-1 && currIndex.second==-1)break;
        }
    }
    delete pathToFollow;
    pathToFollow=newPath;
}
bool Person::cmpDoublePoint(pair<double,QPointF> p1, pair<double,QPointF> p2){
    return p1.first<p2.first;
}
bool Person::shortDistanceMove(QPointF newPos){
    QPointF myPos=pos();
    pair<double,QPointF> newDistances[4];
    newDistances[0]=make_pair(distanceBetween(newPos,QPointF(myPos.x()+movingStep,myPos.y())),QPointF(myPos.x()+movingStep,myPos.y()));
    newDistances[1]=make_pair(distanceBetween(newPos,QPointF(myPos.x()-movingStep,myPos.y())),QPointF(myPos.x()-movingStep,myPos.y()));
    newDistances[2]=make_pair(distanceBetween(newPos,QPointF(myPos.x(),myPos.y()+movingStep)),QPointF(myPos.x(),myPos.y()+movingStep));
    newDistances[3]=make_pair(distanceBetween(newPos,QPointF(myPos.x(),myPos.y()-movingStep)),QPointF(myPos.x(),myPos.y()-movingStep));
    sort(newDistances,newDistances+4,cmpDoublePoint);

    bool hasMoved=false;
    for(int i=0;i<4 && hasMoved==false;i++){
        hasMoved=tryToMoveTo(newDistances[i].second);
    }
    return hasMoved;
}
/**
 * Moves person to specified location if possible
 * \return true if can be moved, false ow
 */
bool Person::tryToMoveTo(QPointF newPos){
    QPointF currentPos= pos();
    setPos(newPos);
    if(!onMap()){
        // if(false){
        setPos(currentPos);
        return false;
    }
    return true;
}
/**
 * Function overloading of tryToMoveTo but take position as x and y coordinates
 * \return tryToMoveTo(newPos);
 */
bool Person::tryToMoveTo(qreal x, qreal y){
    QPointF newPos(x,y);
    return tryToMoveTo(newPos);
}
/**
 * Calculates distance from current point to specified point
 * \param QPointF p2
 * \return distanceBetween(this->pos(),p2);
 */
double Person::distanceTo(QPointF p2){
    return distanceBetween(this->pos(),p2);
}
/**
 * Calculates distance between 2 points
 * \param QPointF point1
 * \param QPointF point2
 * \return distance
 */
double Person::distanceBetween(QPointF p1, QPointF p2){
    double x1=p1.x();
    double y1=p1.y();
    double x2=p2.x();
    double y2=p2.y();
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
bool Person::onMap()
{
    for(unsigned int i =0; i<map->roads.size(); i++){
        if(collidesWithItem(map->roads[i],Qt::ContainsItemShape)){
            return true;
        }
    }
    return false;
}