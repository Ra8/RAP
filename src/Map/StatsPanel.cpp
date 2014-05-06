#include "StatsPanel.h"
StatsPanel::StatsPanel(){
	robberMoney2 = new QGraphicsTextItem("Robber's money:");
    robberMoney2->setPos(0,0);
    this->addToGroup(robberMoney2);

    robberMoney = new QGraphicsTextItem("0");
    robberMoney->setPos(120,0);
    this->addToGroup(robberMoney);

    elapsedTime = new QGraphicsTextItem("0");
    elapsedTime->setPos(0,-20);
    this->addToGroup(elapsedTime);

    warningText = new QGraphicsTextItem("");
    warningText->setPos(0,40);
    this->addToGroup(warningText);

    targetText = new QGraphicsTextItem("");
    targetText->setPos(0,20);
    this->addToGroup(targetText);
}
void StatsPanel::updateTime(){
    int currentTime=elapsedTime->toPlainText().toInt();
    elapsedTime->setPlainText(QString::number(currentTime+1));
}
int StatsPanel::getCurrentTime(){
    return elapsedTime->toPlainText().toInt();
}
int StatsPanel::getCurrentMoney(){
	return robberMoney->toPlainText().toInt();
}
void StatsPanel::setCurrentTime(int secs){
    elapsedTime->setPlainText(QString::number(secs));
}
void StatsPanel::setCurrentMoney(int money){
	robberMoney->setPlainText(QString::number(money));
}
void StatsPanel::removeWarning(){
	warningText->setPlainText("");
}

void StatsPanel::setWarning(int role){
	if(role==0){
		warningText->setPlainText("Warning! Police nearby");
	} else {
		warningText->setPlainText("Warning! Robber nearby");
	}
}
void StatsPanel::showTarget(int target){
    targetText->setPlainText(QString("Target: ") + QString::number(target));
}