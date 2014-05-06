#include "Menu.h"
Menu::Menu(vector<string> list, int fontSize, int space, QFont font, QColor highlight, QColor defaultColor){
	this->highlight=highlight;
	this->defaultColor=defaultColor;
	this->font=font;
	this->font.setPointSize(fontSize);
	font=this->font;
	if(space!=-1)
		this->space=space;
	else
		this->space=space=fontSize*4;

	int currentSpace=0;

	for(unsigned int i=0;i<list.size();i++){
		QGraphicsSimpleTextItem* temp=new QGraphicsSimpleTextItem(QString(list[i].c_str()));
		temp->setFont(font);
		int centerX=temp->boundingRect().center().x();
		temp->setPos(-centerX,currentSpace);
		
		currentSpace+=space;
		addToGroup(temp);
		this->list.push_back(temp);
	}
	selected=0;
	isHighlight=true;
	loopAround=false;
	this->list[0]->setBrush(highlight);
}
void Menu::select(int direction){
	if(direction==0)
		selectDown();
	else selectUp();
}
void Menu::selectDown(){
	if(!isHighlight)return;

	list[selected]->setBrush(defaultColor);
	selected++;
	if((unsigned int)selected==list.size()){
		if(loopAround)
			selected=0;
		else selected--;
	}
	list[selected]->setBrush(highlight);
}
void Menu::selectUp(){
	if(!isHighlight)return;

	list[selected]->setBrush(defaultColor);
	selected--;
	if(selected==-1){
		if(loopAround)
			selected=list.size()-1;
		else selected++;
	}
	list[selected]->setBrush(highlight);
}
int Menu::getSelected(){
	return selected;
}
void Menu::enableHighlight(){
	isHighlight=true;
	for(unsigned int i=0;i<list.size();i++){
		list[i]->setBrush(defaultColor);
	}
	selected=0;
	list[0]->setBrush(highlight);
}
void Menu::disableHighlight(){
	isHighlight=false;
	for(unsigned int i=0;i<list.size();i++){
		list[i]->setBrush(defaultColor);
	}
	selected=0;
}
void Menu::enableLoopAround(){
	loopAround=true;
}
void Menu::disableLoopAround(){
	loopAround=false;
}