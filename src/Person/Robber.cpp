/**
 * Class implementation of robber
 */
#include "Robber.h"
Robber::Robber()
:Person(){
}

Robber::Robber(Map *_map)
:Person(_map,false,Qt::black,Qt::green){
}
bool Robber::cmpDoublePointEscape(pair<double,QPointF> p1, pair<double,QPointF> p2){
    return p1.first>p2.first;
}
void Robber::winGame(vector<QPointF> avoidPoints){
    int modifiedGraph[500][500];
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            modifiedGraph[i][j]=map->graph[i][j];
        }
    }
    int dx[]={0,1,1,0,-1,-1,-1,0,1,2,2,2,2,2,1,0,-1,-2,-2,-2,-2,-2,-1,0,1};
    int dy[]={0,0,-1,-1,-1,0,1,1,1,2,1,0,-1,-2,-2,-2,-2,-2,-1,0,1,2,2,2,2};
    int nx,ny;
    for(unsigned int j=0;j<avoidPoints.size();j++){
        pair<int,int> indexs=map->getClosestIndexes(avoidPoints[j]);
        for(int i=0;i<25;i++){
            nx=indexs.first+dx[i];
            ny=indexs.second+dy[i];
            if(nx>=0 && ny>=0 && nx<500 && ny<500)
                modifiedGraph[nx][ny]=0;
        }
    }
    pair<int,int> robberIndex=map->getClosestIndexes(pos());
    for(int i=0;i<9;i++){
        nx=robberIndex.first+dx[i];
        ny=robberIndex.second+dy[i];
        if(nx>=0 && ny>=0 && nx<500 && ny<500)
            if(map->graph[nx][ny]==1)
                modifiedGraph[nx][ny]=1;
    }
    int x,y,gateIndex,count=30;
    srand(time(0));
    while(count-->0){
        gateIndex=rand()%map->roads.size();
        if(map->roads[gateIndex]->type==2){
            pair<int,int> indexs=map->getClosestIndexes(map->roads[gateIndex]->sceneBoundingRect().center());
            x=indexs.first;
            y=indexs.second;
            if(modifiedGraph[x][y]==1){
                longDistanceMoveTo(QPointF(x*25+25,y*25+25),modifiedGraph);
                
                stack<QPointF>* tempPath=new stack<QPointF>();
                while(!pathToFollow->empty()){
                    tempPath->push(pathToFollow->top());
                    pathToFollow->pop();
                }
                QPointF gatePoint=map->roads[gateIndex]->sceneBoundingRect().center()+pos();
                pathToFollow->push(gatePoint);
                while(!tempPath->empty()){
                    pathToFollow->push(tempPath->top());
                    tempPath->pop();
                }
                delete tempPath;
                // cout << gateIndex << " " << map->roads[gateIndex]->sceneBoundingRect().center().x() << " " << map->roads[gateIndex]->sceneBoundingRect().center().y() << endl;
                // cout << gateIndex << " " << gatePoint.x() << " " << gatePoint.y() << endl;
                break;
            }
        }
    }
}
void Robber::randomEscape(vector<QPointF> avoidPoints){
    int modifiedGraph[500][500];
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            modifiedGraph[i][j]=map->graph[i][j];
        }
    }
    int dx[]={0,1,1,0,-1,-1,-1,0,1,2,2,2,2,2,1,0,-1,-2,-2,-2,-2,-2,-1,0,1};
    int dy[]={0,0,-1,-1,-1,0,1,1,1,2,1,0,-1,-2,-2,-2,-2,-2,-1,0,1,2,2,2,2};
    int nx,ny;
    for(unsigned int j=0;j<avoidPoints.size();j++){
        pair<int,int> indexs=map->getClosestIndexes(avoidPoints[j]);
        for(int i=0;i<25;i++){
            nx=indexs.first+dx[i];
            ny=indexs.second+dy[i];
            if(nx>=0 && ny>=0 && nx<500 && ny<500)
                modifiedGraph[nx][ny]=0;
        }
    }
    pair<int,int> robberIndex=map->getClosestIndexes(pos());
    for(int i=0;i<9;i++){
        nx=robberIndex.first+dx[i];
        ny=robberIndex.second+dy[i];
        if(nx>=0 && ny>=0 && nx<500 && ny<500)
            if(map->graph[nx][ny]==1)
                modifiedGraph[nx][ny]=1;
    }
    int x,y,count=50;
    srand(time(0));
    while(true){
        x=rand()%500;
        y=rand()%500;
        if(modifiedGraph[x][y]==1){
            longDistanceMoveTo(QPointF(x*25+25,y*25+25),modifiedGraph);
            if(count>30)
                count-=5;
            else if(count>=15)
                count-=2;
            else
                count--;
            if((int)pathToFollow->size()>count || count<2){
                if(!pathToFollow->empty()){
                    if(pathToFollow->top().x()==pos().x() && pathToFollow->top().y()==pos().y())
                        pathToFollow->pop();
                }
                break;
            }
        }
    }
}
void Robber::escapeFrom(vector<QPointF> avoidPoints){
    static int threshold=30;
    double minDis=101;
    for(unsigned int i=0;i<avoidPoints.size();i++){
        minDis=min(minDis,distanceTo(avoidPoints[i]));
    }
    if(minDis<threshold){
        for(unsigned int i=0;i<avoidPoints.size();i++){
            if(distanceTo(avoidPoints[i])>=threshold){
                avoidPoints.erase(avoidPoints.begin()+i);
                i--;
            }
        }
        vector<pair<double,QPointF> > distances;
        QPointF newPoints[4] = {QPointF(pos().x()+movingStep,pos().y()),QPointF(pos().x()-movingStep,pos().y()),QPointF(pos().x(),pos().y()+movingStep),QPointF(pos().x(),pos().y()-movingStep)};
        for(int i=0;i<4;i++){
            distances.push_back(make_pair(1,newPoints[i]));
            for(unsigned int j=0;j<avoidPoints.size();j++){
                double originalDistance=distanceBetween(avoidPoints[j],newPoints[i]);
                distances[i].first=distances[i].first*log(originalDistance/25.0);
            }
        }
        sort(distances.begin(),distances.end(),cmpDoublePointEscape);
        bool hasMoved=false;
        for(int i=0;i<4 && !hasMoved;i++){
            hasMoved=tryToMoveTo(distances[i].second);
        }
        delete pathToFollow;
        pathToFollow=new stack<QPointF>();
    }
    else if(map->statsPanel->getCurrentMoney()>=map->targets[map->level]){
        map->escapeFromGate();
        if(pathToFollow->empty()){
            winGame(avoidPoints);
        }
        if(!pathToFollow->empty()){
            QPointF nextPos=pathToFollow->top();
            if(nextPos.x()==pos().x() && nextPos.y()==pos().y()){
                pathToFollow->pop();
            } else {
                shortDistanceMove(nextPos);
            }
        }
    } else {
        map->stealBuildingAI(avoidPoints.size());
        if(pathToFollow->empty()){
            randomEscape(avoidPoints);
        }
        if(!pathToFollow->empty()){
            QPointF nextPos=pathToFollow->top();
            if(nextPos.x()==pos().x() && nextPos.y()==pos().y()){
                pathToFollow->pop();
            } else {
                shortDistanceMove(nextPos);
            }
        }
    }
}
/**
 * Allows for escape specific movements of robber
 * \param qreal x
 * \param qreal y
 * \param QPointF policePos
 * \param double initDistance
 * \return bool 1 if it is possible to escape to location 0 ow
 */
bool Robber::tryToEscapeTo(qreal x, qreal y, QPointF policePos, double initDistance){
    QPointF newPos(x,y);
    double newDis=distanceBetween(newPos,policePos);
    if(newDis>initDistance){
        return tryToMoveTo(x,y);
    }
    return false;   
}
