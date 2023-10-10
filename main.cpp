#include <iostream>
#include "QQSystem.h"



QQSystem* QQ = new QQSystem(new QQUser(1, "1", "����"));
void test01() {
	QQ->users.push_back(*QQ->currentUser);
	QQ->users.push_back(QQUser(2, "1", "a"));
	QQ->users.push_back(QQUser(3, "1", "b"));
	QQ->users.push_back(QQUser(4, "1", "c"));
	QQ->users.push_back(QQUser(5, "1", "d"));
	QQ->users.push_back(QQUser(6, "1", "e"));
	QQ->users.push_back(QQUser(7, "1", "f"));
	QQ->users.push_back(QQUser(8, "1", "g"));
	QQ->saveUsers();
}

void test02() {
	QQ->friends.push_back({2, "aa"});
	QQ->friends.push_back({3, "bb"});
	QQ->friends.push_back({4, "cc"});
	QQ->tmpFriends.push_back({ 5, "dd", 0});
	QQ->tmpFriends.push_back({ 6, "dd", 2 });
	QQ->tmpFriends.push_back({ 7, "dd", 0 });
	QQ->saveFriends();
}

int main() {
	//test01();
	//test02();
	QQ->readUsers();
	QQ->readFriends();
	//QQ->showFriend();
	//QQ->addFriend();
	QQ->newFriend();
	system("pause");
	return 0;
}