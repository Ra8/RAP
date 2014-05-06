#include "MainMenu.h"

MainMenu::MainMenu(){
	vector<string> mainList{
		"Start Game",
		"Change Map",
		"Change account",
		"New account",
		"Instructions",
		"Load saved game"
	};
	vector<string> selectPlayerList{"Robber", "Police", "Go back"};
	vector<string> instructionList{
		"Play as Police or as Robber",
		"Press arrow keys to move",
		"Press \'F\' to toggle flags",
		"Press \'P\' to pause game",
		"Press \'X\' to save a game",
		"If you are a robber press \'S\' to steal",
		"If you are a robber press \'E\' to escape",
		"If you are a police press \'N\' to change police",
		"",
		"Press \'B\' to go back"
	};
	centerX=(boundary.x() + boundary.width())/2-40;
	main=new Menu(mainList);
	main->setPos(centerX,0);
	instructions=new Menu(instructionList,14);
	instructions->disableHighlight();
	instructions->setPos(centerX,0);
	selectPlayer=new Menu(selectPlayerList);
	selectPlayer->setPos(centerX,0);
	addToGroup(main);
	inview=MAIN;
	role=0;
	filename="maps/map1";

	accounts= new Accounts();
	accountList=accounts->getList();
	for(unsigned int i=0;i<accountList.size();i++){
		accountsStrings.push_back(accountList[i]->username);
	}
	accountsMenu = new Menu(accountsStrings,14);
	accountsMenu->setPos(centerX,0);

	mapList = getAllMaps();
	maps = new Menu(mapList,14);
	maps->setPos(centerX,0);
}
vector<string> MainMenu::getAllMaps(){
	vector<string> ret;
	QDir mapsDir(QString("maps"));
	mapsDir.setSorting(QDir::Name);
	mapsDir.setFilter(QDir::Files);
	QStringList QmapList = mapsDir.entryList();
	for(int i=0;i<QmapList.size();i++){
		string temp=QmapList.at(i).toStdString();
		ret.push_back(temp);
	}
	return ret;
}
void MainMenu::mainFunctions(int selected){
	switch(selected){
		case 0:
			inview=SELECT;
			removeFromGroup(main);
			scene()->removeItem(main);
			addToGroup(selectPlayer);
		break;
		case 1:
			inview=MAPS;
			removeFromGroup(main);
			scene()->removeItem(main);
			addToGroup(maps);
		break;
		case 2:
			inview=CHANGEACCOUNT;
			removeFromGroup(main);
			scene()->removeItem(main);
			addToGroup(accountsMenu);
		break;
		case 3: {
			bool ok;
    		QString text = QInputDialog::getText(new QWidget(), QString("New Account"),QString("Enter account name: "),QLineEdit::Normal, QString("Player 1") ,&ok);
    		accounts->addUser(text);
			accountList=accounts->getList();
			accountsStrings.push_back(text.toStdString());
			delete accountsMenu;
			accountsMenu = new Menu(accountsStrings,14);
			accountsMenu->setPos(centerX,0);
    	}
		break;
		case 4:
			inview=INSTRUCTIONS;
			removeFromGroup(main);
			scene()->removeItem(main);
			addToGroup(instructions);
		break;
		case 5:
			string fname="accounts/savedGames/"+accounts->getSelectedStr();
			QFile Fout(fname.c_str());
			if(!Fout.exists()) {       
			} else {
				emit STARTGAMESIGNAL("accounts/savedGames/",-1,accounts->getSelectedStr());
			}
		break;
	}
}
void MainMenu::selectFunctions(int selected){
	switch(selected){
		case 0:
			inview=MAIN;
			removeFromGroup(selectPlayer);
			scene()->removeItem(selectPlayer);
			role=0;
			emit STARTGAMESIGNAL(filename,role,accounts->getSelectedStr());
		break;
		case 1:
			inview=MAIN;
			removeFromGroup(selectPlayer);
			scene()->removeItem(selectPlayer);
			role=1;
			emit STARTGAMESIGNAL(filename,role,accounts->getSelectedStr());
		break;
		case 2:
			inview=MAIN;
			removeFromGroup(selectPlayer);
			scene()->removeItem(selectPlayer);
			addToGroup(main);
		break;
	}

}
void MainMenu::changeAccountsFunctions(int selected){
	accounts->updateSelected(selected);
	inview=MAIN;
	removeFromGroup(accountsMenu);
	scene()->removeItem(accountsMenu);
	addToGroup(main);
}
void MainMenu::mapsFunctions(int selected){
	filename="maps/"+mapList[selected];
	inview=MAIN;
	removeFromGroup(maps);
	scene()->removeItem(maps);
	addToGroup(main);
}

void MainMenu::acceptKeyEvent(QKeyEvent* event){
	if(event->key()==Qt::Key_Up || event->key()==Qt::Key_Down){
		int dir=(event->key()==Qt::Key_Up);
		switch(inview){
			case MAIN:
				main->select(dir);
			break;
			case SELECT:
				selectPlayer->select(dir);
			break;
			case MAPS:
				maps->select(dir);
			break;
			case CHANGEACCOUNT:
				accountsMenu->select(dir);
			break;
		}
	}else if(event->key()==Qt::Key_Enter || event->key()==Qt::Key_Return){
		// int selected;
		switch(inview){
			case MAIN:
				mainFunctions(main->getSelected());
			break;
			case SELECT:
				selectFunctions(selectPlayer->getSelected());
			break;
			case MAPS:
				mapsFunctions(maps->getSelected());
			break;
			case CHANGEACCOUNT:
				changeAccountsFunctions(accountsMenu->getSelected());
			break;
		}
	} else if(event->key()==Qt::Key_B){
		switch(inview){
			case SELECT:
				removeFromGroup(selectPlayer);
				scene()->removeItem(selectPlayer);
				addToGroup(main);
				inview=MAIN;
			break;
			case MAPS:
				removeFromGroup(maps);
				scene()->removeItem(maps);
				addToGroup(main);
				inview=MAIN;
			break;
			case INSTRUCTIONS:
				removeFromGroup(instructions);
				scene()->removeItem(instructions);
				addToGroup(main);
				inview=MAIN;
			break;
			case CHANGEACCOUNT:
				removeFromGroup(accountsMenu);
				scene()->removeItem(accountsMenu);
				addToGroup(main);
				inview=MAIN;
			break;
		}
	}
}

QRectF MainMenu::boundingRect() const{
	return boundary;
}