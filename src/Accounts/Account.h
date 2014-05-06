/**
 * Account class header file
 */
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QtCore>
using namespace std;
class Account
{
public:
	Account(int id, string username);
	string username;
	int id;
};
#endif