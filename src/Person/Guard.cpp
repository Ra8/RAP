/**
 * Guard call implementationn
 */
#include "Guard.h"
#include "iostream"
using namespace std;
Guard::Guard()
:Person()
{}

Guard::Guard(Map *_map,Building* building)
:Person(_map,false,Qt::yellow,Qt::gray)
{
	this->building=building;
	canFollowRobber=false;
}

/**
 * Allows the Guard the track the robber through the map when he is close enough
 * \param QPointF robberPos
 */
void Guard::track(QPointF robberPos){
	if(!canFollowRobber) return;
	double dis=distanceTo(robberPos);
	if(dis<100){
		shortDistanceMove(robberPos);
		if(!pathToFollow->empty()){
			delete pathToFollow;
			pathToFollow=new stack<QPointF>();
		}
	} else {
		if(pathToFollow->empty()){
			longDistanceMoveTo(this->building->getGuardInitPos(),map->graph);
		}
		if(!pathToFollow->empty()){
			QPointF nextPos=pathToFollow->top();
			if(nextPos.x()==pos().x() && nextPos.y()==pos().y()){
				pathToFollow->pop();
				if(!pathToFollow->empty())
					nextPos=pathToFollow->top();
				else return;
			}
			shortDistanceMove(nextPos);
		}
	}
}
