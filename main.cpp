#include <iostream>
#include "QQSystem.h"



//QQSystem* QQ = new QQSystem(new QQUser(1, "1", "李智"));
QQSystem* QQ = new QQSystem(new QQUser(2, "1", "aa"));
void test01() {
	QQ->users.push_back(QQUser(1, "1", "李智"));
	QQ->users.push_back(QQUser(2, "1", "a"));
	QQ->users.push_back(QQUser(3, "1", "b"));
	QQ->users.push_back(QQUser(4, "1", "c"));
	QQ->users.push_back(QQUser(5, "1", "d"));
	QQ->users.push_back(QQUser(6, "1", "e"));
	QQ->users.push_back(QQUser(7, "1", "f"));
	QQ->users.push_back(QQUser(8, "1", "g"));
	utils::saveData<QQUser>(0, 1, QQ->users);
}

void test02() {
	QQ->friends.push_back({2, "aa"});
	QQ->friends.push_back({3, "bb"});
	QQ->friends.push_back({4, "cc"});
	QQ->tmpFriends.push_back({ 5, "dd", true, 0 });
	QQ->tmpFriends.push_back({ 6, "dd", false, 2 });
	QQ->tmpFriends.push_back({ 7, "dd", false, 0 });
	utils::saveData<Friend>(1, 1, QQ->friends, QQ->currentUser->_id);
	utils::saveData<Friend>(2, 1, QQ->tmpFriends, QQ->currentUser->_id);
}

void test03() {
	QQ->allGroups.push_back(QQGroup(111, "q1", { 2, "aa" }, QQ->friends));
	QQ->allGroups[0].members.push_back({ 1, "1加入的群", 0, 1, 0 });
	utils::saveData<QQGroup>(3, 0, QQ->allGroups);
	for (auto& group : QQ->allGroups) {
		utils::saveData<Friend>(6, 0, group.members, group.id);
	}
}

int main() {
	//test01();
	//test02();
	QQ->users = std::move(utils::readData<QQUser>(0, 1));
	QQ->friends = std::move(utils::readData<Friend>(1, 1, QQ->currentUser->_id));
	QQ->tmpFriends = std::move(utils::readData<Friend>(2, 1, QQ->currentUser->_id));
	//test03();
	QQ->readGroups();
	
	QQ->myGroups = std::move(utils::readData<Friend>(4, 1, QQ->currentUser->_id));
	//QQ->addFriend();
	//QQ->newFriend();
	//QQ->deleteFriend();
	//QQ->showFriend();
	QQ->showGroup();
	//QQ->addGroup();
	std::cout << "-----------\n";
	//QQ->currentUser = new QQUser(7, "1", "f");
	//QQ->users = std::move(utils::readData<QQUser>(0));
	//QQ->friends = std::move(utils::readData<Friend>(1, QQ->currentUser->_id));
	//QQ->tmpFriends = std::move(utils::readData<Friend>(2, QQ->currentUser->_id));
	//QQ->newFriend();

	//QQ->updateFriend();
	//QQ->showFriend();
	system("pause");
	return 0;
}