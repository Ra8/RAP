/**
 * Accounts class header file
 */
#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <QtCore>
#include "json.h"
#include "Account.h"
#include "iostream"
using namespace std;
class Accounts
{
public:
	Accounts();
	QMap<QString, QVariant> allData;
	vector<Account*> getList();
	void addUser(QString username);
	vector<Account*> list;
	void updateSelected(int id);
	int getSelected();
	string getSelectedStr();
};
#endif