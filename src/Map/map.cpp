/**
 * Map class contains a vector of MapEdges
 */
#include "map.h"

Map::Map()
{
}

void Map::saveToFile(string filename){
    Json json;
    QPointF pos;
    QMap<QString,QVariant> toSave;

    toSave["level"]=level;

    QList<QVariant> targetsData;
    for(unsigned int i=0;i<targets.size();i++){
        targetsData.append(targets[i]);
    }
    toSave["targets"]=targetsData;

    QList<QVariant> roadsData;
    for(unsigned int i=0;i<roads.size();i++){
        QMap<QString,QVariant> temp;
        temp["x"]=roads[i]->x;
        temp["y"]=roads[i]->y;
        temp["w"]=roads[i]->w;
        temp["h"]=roads[i]->h;
        temp["type"]=roads[i]->type;
        roadsData.append(temp);
    }
    toSave["roads"]=roadsData;

    QList<QVariant> buildingsData;
    for(unsigned int i=0;i<buildings.size();i++){
        QMap<QString,QVariant> temp;
        QMap<QString,QVariant> guardData;
        pos=buildings[i]->scenePos()-this->pos();
        temp["x"]=pos.x();
        temp["y"]=pos.y();
        temp["isHome"]=(buildings[i]->isHome)?"true":"false";
        temp["type"]=(buildings[i]->type<3)?buildings[i]->type:3;
        temp["money"]=buildings[i]->money;
        
        int guardNum=buildings[i]->getGuardNum();
        if(guardNum!=-1){
            pos=guards[guardNum]->scenePos()-this->pos();
            guardData["x"]=pos.x();
            guardData["y"]=pos.y();
            guardData["canFollowRobber"]=(guards[guardNum]->canFollowRobber)?"true":"false";
            temp["guard"]=guardData;
        }
        buildingsData.append(temp);
    }
    toSave["buildings"]=buildingsData;

    QMap<QString,QVariant> robberPosData;
    pos=robber->scenePos()-this->pos();
    robberPosData["x"]=pos.x();
    robberPosData["y"]=pos.y();
    toSave["robberPos"]=robberPosData;

    QList<QVariant> policeData;
    for(unsigned int i=0;i<polices.size();i++){
        QMap<QString,QVariant> temp;
        pos=polices[i]->scenePos()-this->pos();
        temp["x"]=pos.x();
        temp["y"]=pos.y();
        policeData.append(temp);
    }
    toSave["policePos"]=policeData;

    QList<QVariant> flagsData;
    for(unsigned int i=0;i<flags.size();i++){
        QMap<QString,QVariant> temp;
        pos=flags[i]->scenePos()-this->pos();
        temp["x"]=pos.x();
        temp["y"]=pos.y();
        flagsData.append(temp);
    }
    toSave["flags"]=flagsData;

    QMap<QString,QVariant> statsData;
    statsData["timeElapsed"]=statsPanel->getCurrentTime();
    statsData["money"]=statsPanel->getCurrentMoney();
    toSave["stats"]=statsData;

    toSave["role"]=role;

    QString data=json.encode(toSave);
    QFile file(filename.c_str());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        cout <<"error"<<endl;;
    file.write(data.toLocal8Bit().data());

}
void Map::loadSavedFile(string filename){
    QFile file(filename.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        cout <<"error"<<endl;;
    QString all= file.readAll();

    Json json;
    QMap<QString, QVariant> mapData=json.decode(all);
    QList<QVariant> targetsData=mapData["targets"].toList();
    QList<QVariant> roadsData=mapData["roads"].toList();
    QList<QVariant> buildingsData=mapData["buildings"].toList();
    QList<QVariant> flagsData=mapData["flags"].toList();
    vector<bool> guardCanFollowRobber;
    level=mapData["level"].toInt();

    for(int i=0;i<targetsData.size();i++){
        int singleTarget;
        singleTarget=targetsData[i].toInt();
        targets.push_back(singleTarget);
    }

    for(int i=0;i<roadsData.size();i++){
        int x,y,w,h,type;
        QMap<QString, QVariant> singleRoad;
        singleRoad = roadsData[i].toMap();
        x=singleRoad["x"].toInt();
        y=singleRoad["y"].toInt();
        w=singleRoad["w"].toInt();
        h=singleRoad["h"].toInt();
        type=singleRoad["type"].toInt();
        roads.push_back(new Road(x,y,w,h,type));
    }
    for(int i=0;i<flagsData.size();i++){
        int x,y;
        QMap<QString, QVariant> singleFlag;
        singleFlag = flagsData[i].toMap();
        x=singleFlag["x"].toInt();
        y=singleFlag["y"].toInt();
        flags.push_back(new Flag(QPointF(x,y)));
    }

    for(int i=0;i<buildingsData.size();i++){
        int money,x,y,type;
        bool isHome;
        QMap<QString, QVariant> singleBuilding;
        singleBuilding = buildingsData[i].toMap();
        money=singleBuilding["money"].toInt();
        x=singleBuilding["x"].toInt();
        y=singleBuilding["y"].toInt();
        type=singleBuilding["type"].toInt();
        isHome=singleBuilding["isHome"].toBool();
        if(singleBuilding.contains("guard")){
            int guardX,guardY;
            guardX=singleBuilding["guard"].toMap()["x"].toInt();
            guardY=singleBuilding["guard"].toMap()["y"].toInt();
            buildings.push_back(new Building(money,x,y,isHome,type,guardX,guardY));
            guardCanFollowRobber.push_back(singleBuilding["guard"].toMap()["canFollowRobber"].toBool());
        } else {
            buildings.push_back(new Building(money,x,y,isHome,type));
        }
    }
    int robberX, robberY, policeX, policeY;
    robberX = mapData["robberPos"].toMap()["x"].toInt();
    robberY = mapData["robberPos"].toMap()["y"].toInt();
    for(int i=0;i<mapData["policePos"].toList().size();i++){
        policeX = mapData["policePos"].toList()[i].toMap()["x"].toInt();
        policeY = mapData["policePos"].toList()[i].toMap()["y"].toInt();
        policeInitPos.push_back(QPointF(policeX,policeY));
    }
    
    robberInitPos=QPointF(robberX,robberY);

    for(int i=0; i<(int)roads.size(); i++){
        addToGroup(roads[i]);
    }
    for(unsigned int i=0; i<buildings.size(); i++){
        addToGroup(buildings[i]);
        if(buildings[i]->hasGuard){
            guards.push_back(new Guard(this,buildings[i]));
            int guardNum=guards.size()-1;
            guards[guardNum]->setPos(buildings[i]->getGuardInitPos());
            guards[guardNum]->canFollowRobber=guardCanFollowRobber[guardNum];
            addToGroup(guards[guardNum]);
            buildings[i]->setGuardNum(guardNum);
        }
    }
    for(unsigned int i=0;i<flags.size();i++){
        addToGroup(flags[i]);
    }
    //Robber instantiation
    robber = new Robber(this);
    robber->setPos(robberInitPos);
    addToGroup(robber);

    //Police instantiation
    for(unsigned int i=0;i<policeInitPos.size();i++){
        polices.push_back(new Police(this));
        polices[i]->setPos(policeInitPos[i]);
        addToGroup(polices[i]);
    }
    statsPanel->setCurrentMoney(mapData["stats"].toMap()["money"].toInt());
    statsPanel->setCurrentTime(mapData["stats"].toMap()["timeElapsed"].toInt());
    role=mapData["role"].toInt();
}
void Map::loadFile(string filename){
	QFile file(filename.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        cout <<"error"<<endl;;
    QString all= file.readAll();

    Json json;
    QMap<QString, QVariant> mapData=json.decode(all);
    QList<QVariant> targetsData=mapData["targets"].toList();
    QList<QVariant> roadsData=mapData["roads"].toList();
    QList<QVariant> buildingsData=mapData["buildings"].toList();

    for(int i=0;i<targetsData.size();i++){
        int singleTarget;
        singleTarget=targetsData[i].toInt();
        targets.push_back(singleTarget);
    }

    for(int i=0;i<roadsData.size();i++){
        int x,y,w,h,type;
        QMap<QString, QVariant> singleRoad;
        singleRoad = roadsData[i].toMap();
        x=singleRoad["x"].toInt();
        y=singleRoad["y"].toInt();
        w=singleRoad["w"].toInt();
        h=singleRoad["h"].toInt();
        type=singleRoad["type"].toInt();
        roads.push_back(new Road(x,y,w,h,type));
    }

    for(int i=0;i<buildingsData.size();i++){
        int money,x,y,type;
        bool isHome;
        QMap<QString, QVariant> singleBuilding;
        singleBuilding = buildingsData[i].toMap();
        money=singleBuilding["money"].toInt();
        x=singleBuilding["x"].toInt();
        y=singleBuilding["y"].toInt();
        type=singleBuilding["type"].toInt();
        isHome=singleBuilding["isHome"].toBool();
        if(singleBuilding.contains("guard")){
            int guardX,guardY;
            guardX=singleBuilding["guard"].toMap()["x"].toInt();
            guardY=singleBuilding["guard"].toMap()["y"].toInt();
            buildings.push_back(new Building(money,x,y,isHome,type,guardX,guardY));
        } else {
            buildings.push_back(new Building(money,x,y,isHome,type));
        }
    }
    int robberX, robberY, policeX, policeY;
    robberX = mapData["robberPos"].toMap()["x"].toInt();
    robberY = mapData["robberPos"].toMap()["y"].toInt();
    for(int i=0;i<mapData["policePos"].toList().size();i++){
        policeX = mapData["policePos"].toList()[i].toMap()["x"].toInt();
        policeY = mapData["policePos"].toList()[i].toMap()["y"].toInt();
        policeInitPos.push_back(QPointF(policeX,policeY));
    }
    
    robberInitPos=QPointF(robberX,robberY);

    for(int i=0; i<(int)roads.size(); i++){
        addToGroup(roads[i]);
    }
    for(int i=0; i<(int)buildings.size(); i++){
        addToGroup(buildings[i]);
        if(buildings[i]->hasGuard){
            guards.push_back(new Guard(this,buildings[i]));
            // guards.push_back(new Guard(buildings[i]));
            int guardNum=guards.size()-1;
            guards[guardNum]->setPos(buildings[i]->getGuardInitPos());
            addToGroup(guards[guardNum]);
            buildings[i]->setGuardNum(guardNum);
        }
    }
    //Robber instantiation
    robber = new Robber(this);
    robber->setPos(robberInitPos);
    addToGroup(robber);

    //Police instantiation
    for(unsigned int i=0;i<policeInitPos.size();i++){
        polices.push_back(new Police(this));
        polices[i]->setPos(policeInitPos[i]);
        addToGroup(polices[i]);
    }
}
/**
 * Map constructor taking a filename, a link to the statistics and a role
 */
Map::Map(string filename, StatsPanel* statsPanel, int role, string accountID){ // for new games
    this->filename=filename;
    this->role=role;
    this->statsPanel=statsPanel;
    this->accountID=accountID;
	loadFile(filename);
    showBuildingMoney();
    initGraph();
    if(role==0)
        level=0;
    else level=targets.size()-1;
    this->statsPanel->showTarget(targets[level]);
}
Map::Map(string filename, StatsPanel* statsPanel){ //for saved games
    this->statsPanel=statsPanel;
    loadSavedFile(filename);
    showBuildingMoney();
    initGraph();
    this->statsPanel->showTarget(targets[level]);
}
pair<int,int> Map::getClosestIndexes(QPointF p){
    int x=(p.x()-25)/25;
    int y=(p.y()-25)/25;

    int dx[]={1,0,-1,0};
    int dy[]={0,-1,0,1};
    int nx,ny;
    if(graph[x][y]==0){
        for(int i=0;i<4;i++){
            nx=x+dx[i];
            ny=y+dy[i];
            if(nx>=0 && ny>=0 && nx<500 && ny<500)
                if(graph[nx][ny]==1){
                    return make_pair(nx,ny);
                }
        }
    }
    return make_pair(x,y);
}
void Map::initGraph(){
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            graph[i][j]=0;
            for(unsigned int k=0;k<roads.size();k++){
                QPointF tmps[5];
                tmps[0]=QPointF(i*25+25,j*25+25);
                tmps[1]=QPointF(i*25+15,j*25+25);
                tmps[2]=QPointF(i*25+35,j*25+25);
                tmps[3]=QPointF(i*25+25,j*25+15);
                tmps[4]=QPointF(i*25+25,j*25+35);
                bool containsIt=true;
                for(int a=0;a<5;a++){
                    if(!roads[k]->sceneBoundingRect().contains(tmps[a])){
                        containsIt=false;
                    }
                }
                if(containsIt)
                   graph[i][j]=1;
            }
        }
    }
}
void Map::acceptKeyEvent(QKeyEvent* event){
    if(event->key()==Qt::Key_F){
        toggleFlag();
    } else if(event->key()==Qt::Key_N && role>0){
        role=role%polices.size()+1;
    } else if(event->key()==Qt::Key_X){
        string fn="accounts/savedGames/"+accountID;
        cout << fn << endl;
        saveToFile(fn);
    } else if(event->key()==Qt::Key_P) {
        emit TOGGLEPAUSESIGNAL();
    } else if(event->key()==Qt::Key_E) {
        escapeFromGate();
    }
}
void Map::doKeys(int isPolice){
    bool nearby=false;
    tryToArrestRobber();
    for(unsigned int i=0;i<polices.size();i++){
        nearby=nearby||(robber->distanceTo(polices[i]->pos())<200);
    }
    if(!nearby){
        statsPanel->removeWarning();
    } else {
        statsPanel->setWarning(role);
    }
    if(isPolice==0){//Police to move
        if(role!=0){//is the user, the police?
            polices[role-1]->move();
            hideBuildingMoney();
        } else {//Police AI
            for(unsigned int i=0;i<polices.size();i++){
                polices[i]->track(robber->pos());
            }
            for(unsigned int i=0;i<guards.size();i++){
                guards[i]->track(robber->pos());
            }
        }
    } else {//Robber to move
        if(role==0){
            robber->move();
            if(pressedKeys[Qt::Key_S]){
                stealBuilding();
            }
            showBuildingMoney();
        } else {
            vector<QPointF> avoidPoints;
            for(unsigned int i=0;i<polices.size();i++){
                // robber->track(polices[i]->pos());
                if(robber->distanceTo(polices[i]->pos())<350){
                    avoidPoints.push_back(polices[i]->pos());
                }
            }
            for(unsigned int i=0;i<guards.size();i++){
                // robber->track(polices[i]->pos());
                if(robber->distanceTo(guards[i]->pos())<350 && guards[i]->canFollowRobber){
                    avoidPoints.push_back(guards[i]->pos());
                }
            }
            // robber->track(polices);
            robber->escapeFrom(avoidPoints);
        }
    }
    centerMap();
}
void Map::centerMap(){
    Person* person;
    if(role==0) // police
        person=robber;
    else
        person=polices[role-1];
        

    QPointF realPos=person->scenePos();
    QPointF center(650/2,650/2);
    QPointF newPos(pos()+(center-realPos));
    setPos(newPos);
}
void Map::hideBuildingMoney(){
    for(unsigned int i=0;i<buildings.size();i++){
        buildings[i]->hideMoney();
    }
}
void Map::showBuildingMoney(){    
    //only for Robber
    for(unsigned int i=0;i<buildings.size();i++){
        QPointF buildingPos=buildings[i]->pos();
        double dis=robber->distanceTo(buildingPos);
        if(dis<100)
            buildings[i]->showMoney();
        else
            buildings[i]->hideMoney();
    }
}
void Map::stealBuilding(){
    int mn=0,bestDistance=1000;
    for(unsigned int i=1;i<buildings.size();i++){
        QPointF buildingPos=buildings[i]->pos();
        QPointF best=buildings[mn]->pos();
        if(robber->distanceTo(best)>robber->distanceTo(buildingPos)){
            mn=i;
        }
    }
    bestDistance=robber->distanceTo(buildings[mn]->pos());
    if(bestDistance<60){
        int money=buildings[mn]->getStolen();
        if(money>0 && buildings[mn]->isHome){
            for(unsigned int i=0;i<polices.size();i++){
                polices[i]->longDistanceMoveTo(robber->pos(),graph);
                // polices[i]->track(robber->pos());
            }
        }
        if(buildings[mn]->hasGuard){
            int guardNum=buildings[mn]->getGuardNum();
            guards[guardNum]->canFollowRobber=true;
        }
        int currentMoney=statsPanel->getCurrentMoney();
        statsPanel->setCurrentMoney(currentMoney+money);
        // int currentMoney=robberMoney->toPlainText().toInt();
        // robberMoney->setPlainText(QString::number(currentMoney+money));
    }
}
void Map::stealBuildingAI(int policeCount){
    int mn=0,bestDistance=1000;
    for(unsigned int i=1;i<buildings.size();i++){
        QPointF buildingPos=buildings[i]->pos();
        QPointF best=buildings[mn]->pos();
        if(robber->distanceTo(best)>robber->distanceTo(buildingPos)){
            mn=i;
        }
    }
    bestDistance=robber->distanceTo(buildings[mn]->pos());
    if(bestDistance<60 &&(!buildings[mn]->isHome || policeCount==0) && !buildings[mn]->hasGuard){
        int money=buildings[mn]->getStolen();
        if(money>0 && buildings[mn]->isHome){
            emit TOGGLEPAUSESIGNAL();
            previousRole=role;
            role=0;
            centerMap();
            QTimer::singleShot(2000, this, SLOT(returnPreviousRole()));
        }
        if(buildings[mn]->hasGuard){
            int guardNum=buildings[mn]->getGuardNum();
            guards[guardNum]->canFollowRobber=true;
        }
        int currentMoney=statsPanel->getCurrentMoney();
        statsPanel->setCurrentMoney(currentMoney+money);
        // int currentMoney=robberMoney->toPlainText().toInt();
        // robberMoney->setPlainText(QString::number(currentMoney+money));
    }
}
void Map::toggleFlag(){
    Person* person;
    if(role==1) // police
        person=polices[role-1];
    else
        person=robber;
    for(unsigned int i=0;i<flags.size();i++){
        if(person->collidesWithItem(flags[i])){
            removeFromGroup(flags[i]);
            flags[i]->scene()->removeItem(flags[i]);
            flags.erase(flags.begin()+i);
            return;
        }
    }
    flags.push_back(new Flag());
    addToGroup(flags[flags.size()-1]);
}
void Map::escapeFromGate(){
    bool escaped=false;
    for(unsigned int i =0; i<roads.size(); i++){
        if(roads[i]->type==2 && robber->collidesWithItem(roads[i],Qt::ContainsItemShape)){
            escaped= true;
        }
    }
    if(escaped){
        emit TOGGLEPAUSESIGNAL();
        QMessageBox msgBox;
        if(role==0){
            if(statsPanel->getCurrentMoney()>=targets[level]){
                msgBox.setText("You WON!\nYou succesfully escaped!!");
                increaseLevel();
            }
            else
                msgBox.setText("You LOST!\nYou have escaped without getting the target");
        } else {
            if(statsPanel->getCurrentMoney()>=targets[level])
                msgBox.setText("You LOST!\nThe robber escaped and got his target!!");
            else{
                msgBox.setText("You WON!\nThe robber escaped without getting his target");
                increaseLevel();
            }
        }
        msgBox.exec();
    }
}
void Map::tryToArrestRobber(){
    double minDis=100;

    for(unsigned int i=0;i<polices.size();i++){
        minDis=min(minDis,robber->distanceTo(polices[i]->pos()));
    }
    for(unsigned int i=0;i<guards.size();i++){
        if(guards[i]->canFollowRobber)
            minDis=min(minDis,robber->distanceTo(guards[i]->pos()));
    }
    if(minDis<20){
        emit TOGGLEPAUSESIGNAL();
        QMessageBox msgBox;
        if(role==0)
            msgBox.setText("You LOST!\nThe police caught you!!");
        else{
            msgBox.setText("You WON!\nYou caught the robber!!");
            increaseLevel();
        }
        msgBox.exec();
    }
}
void Map::returnPreviousRole(){
    role=previousRole;
    centerMap();
    emit TOGGLEPAUSESIGNAL();
}
void Map::increaseLevel(){
    return;
    if(role==0){
        level++;
        if(level==(int)targets.size()){
            QMessageBox msgBox;
            msgBox.setText("You WON all levels!!");
            msgBox.exec();
            return;
        }
    } else {
        level--;
        if(level==-1){
            QMessageBox msgBox;
            msgBox.setText("You WON all levels!!");
            msgBox.exec();
            return;
        }
    }
    for(unsigned int i=0;i<flags.size();i++){
        scene()->removeItem(flags[i]);
    }
    for(unsigned int i=0;i<polices.size();i++){
        scene()->removeItem(polices[i]);
    }
    for(unsigned int i=0;i<guards.size();i++){
        scene()->removeItem(guards[i]);
    }
    for(unsigned int i=0;i<roads.size();i++){
        scene()->removeItem(roads[i]);
    }
    for(unsigned int i=0;i<buildings.size();i++){
        scene()->removeItem(buildings[i]);
    }
    scene()->removeItem(robber);
    flags.clear();
    polices.clear();
    guards.clear();
    roads.clear();
    buildings.clear();
    policeInitPos.clear();
    delete robber;
    loadFile(filename);
    emit TOGGLEPAUSESIGNAL();
    showBuildingMoney();
    initGraph();
}