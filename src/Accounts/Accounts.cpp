#include "Accounts.h"

Accounts::Accounts(){
	QFile file("accounts/allUsers");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        cout <<"error"<<endl;;
    QString all= file.readAll();

    Json json;
    allData=json.decode(all);
    QList<QVariant> usersData=allData["users"].toList();

    for(int i=0;i<usersData.size();i++){
        int id;
        string username;
        QMap<QString, QVariant> singleUser;
        singleUser = usersData[i].toMap();
        id=singleUser["id"].toInt();
        username=singleUser["username"].toString().toStdString();
        list.push_back(new Account(id,username));
    }
}
vector<Account*> Accounts::getList(){
	return list;
}
void Accounts::addUser(QString username){
    Json json;
    QList<QVariant> usersData=allData["users"].toList();
    QMap<QString, QVariant> newUser;
    int newID=allData["autoID"].toInt();
    newUser["id"]=newID;
    newUser["username"]=username;
    usersData.append(newUser);
    allData["users"]=usersData;
    allData["selected"]=usersData.size()-1;
    allData["autoID"]=newID+1;

    QString data=json.encode(allData);
    QFile file("accounts/allUsers");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        cout <<"error"<<endl;;
    file.write(data.toLocal8Bit().data());
}
void Accounts::updateSelected(int id){
	allData["selected"]=id;
	Json json;
	QString data=json.encode(allData);
    QFile file("accounts/allUsers");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        cout <<"error"<<endl;;
    file.write(data.toLocal8Bit().data());
}
int Accounts::getSelected(){
	return allData["selected"].toInt();
}
string Accounts::getSelectedStr(){
	int sel=allData["selected"].toInt();
	return QString::number(sel).toStdString();
}