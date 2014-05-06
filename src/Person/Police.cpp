/**
 * Police call implementationn
 */
#include "Police.h"
Police::Police():Person(){}


Police::Police(Map *_map)
:Person(_map,false,Qt::blue,Qt::red){}

/**
 * Allows the police the track the robber through the map when he is close enough
 * \param QPointF robberPos
 */
void Police::track(QPointF robberPos){
	double dis=distanceTo(robberPos);
	if(dis<100){
		shortDistanceMove(robberPos);
		if(!pathToFollow->empty()){
			delete pathToFollow;
			pathToFollow=new stack<QPointF>();
		}
	} else {
		if(pathToFollow->empty()){
			randomWalk();
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
