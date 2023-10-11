#include <iostream>
#include "QQSystem.h"



QQSystem* QQ = new QQSystem(new QQUser(1, "1", "ÀîÖÇ"));
void test01() {
	QQ->users.push_back(*QQ->currentUser);
	QQ->users.push_back(QQUser(2, "1", "a"));
	QQ->users.push_back(QQUser(3, "1", "b"));
	QQ->users.push_back(QQUser(4, "1", "c"));
	QQ->users.push_back(QQUser(5, "1", "d"));
	QQ->users.push_back(QQUser(6, "1", "e"));
	QQ->users.push_back(QQUser(7, "1", "f"));
	QQ->users.push_back(QQUser(8, "1", "g"));
	utils::saveData<QQUser>("QQUsers.txt", QQ->users);
}

void test02() {
	QQ->friends.push_back({2, "aa"});
	QQ->friends.push_back({3, "bb"});
	QQ->friends.push_back({4, "cc"});
	QQ->tmpFriends.push_back({ 5, "dd", true, 0 });
	QQ->tmpFriends.push_back({ 6, "dd", false, 2 });
	QQ->tmpFriends.push_back({ 7, "dd", false, 0 });
	utils::saveData<Friend>("friends.txt", QQ->friends, QQ->currentUser->_id);
	utils::saveData<Friend>("tmpFriends.txt", QQ->tmpFriends, QQ->currentUser->_id);
}

int main() {
	test01();
	//test02();
	//QQ->users = std::move(utils::readData<QQUser>("QQUsers.txt"));
	QQ->friends = std::move(utils::readData<Friend>("friends.txt", QQ->currentUser->_id));
	QQ->tmpFriends = std::move(utils::readData<Friend>("tmpFriends.txt", QQ->currentUser->_id));
	//QQ->addFriend();
	QQ->newFriend();
	QQ->showFriend();
	system("pause");
	return 0;
}