#include <iostream>
#include "QQSystem.h"
#include "WeiBoSystem.h"


//void test01() {
//	QQSystem::getInstance()->users.push_back(QQUser(1, "1", "李智"));
//	QQSystem::getInstance()->users.push_back(QQUser(2, "1", "a"));
//	QQSystem::getInstance()->users.push_back(QQUser(3, "1", "b"));
//	QQSystem::getInstance()->users.push_back(QQUser(4, "1", "c"));
//	QQSystem::getInstance()->users.push_back(QQUser(5, "1", "d"));
//	QQSystem::getInstance()->users.push_back(QQUser(6, "1", "e"));
//	QQSystem::getInstance()->users.push_back(QQUser(7, "1", "f"));
//	QQSystem::getInstance()->users.push_back(QQUser(8, "1", "g"));
//	utils::saveData<QQUser>(0, 1, QQ->users);
//}
//
//void test02() {
//	QQSystem::getInstance()->friends.push_back({2, "aa"});
//	QQSystem::getInstance()->friends.push_back({3, "bb"});
//	QQSystem::getInstance()->friends.push_back({4, "cc"});
//	QQSystem::getInstance()->tmpFriends.push_back({ 5, "dd", true, 0 });
//	QQSystem::getInstance()->tmpFriends.push_back({ 6, "dd", false, 2 });
//	QQSystem::getInstance()->tmpFriends.push_back({ 7, "dd", false, 0 });
//	utils::saveData<Friend>(1, 1, QQSystem::getInstance()->friends, QQSystem::getInstance()->currentUser->_id);
//	utils::saveData<Friend>(2, 1, QQSystem::getInstance()->tmpFriends, QQSystem::getInstance()->currentUser->_id);
//}

//void test03() {
//	QQSystem::getInstance()->allGroups.push_back(QQGroup(111, "q1", { 2, "aa" }, QQSystem::getInstance()->friends));
//	QQSystem::getInstance()->allGroups[0].members.push_back({ 1, "1加入的群", 0, 1, 0 });
//	utils::saveData<QQGroup>(3, 0, QQ->allGroups);
//	for (auto& group : QQSystem::getInstance()->allGroups) {
//		utils::saveData<Friend>(6, 0, group.members, group.id);
//	}
//}

int main() {
	//test01();
	//test02();
	User* user = new User(2, "1", "李智");
	QQSystem::getInstance()->setUser(user);
	QQSystem::getInstance()->readUsers();
	QQSystem::getInstance()->friends = QQSystem::readFriends(user->_id);
	QQSystem::getInstance()->tmpFriends = QQSystem::readTmpFriends(user->_id);
	//test03();
	QQSystem::getInstance()->readGroups();
	
	QQSystem::getInstance()->myGroups = QQSystem::readGroups(user->_id);
	//QQSystem::getInstance()->newFriend();
	//QQSystem::getInstance()->deleteFriend();
	//QQSystem::getInstance()->showFriend();
	QQSystem::getInstance()->newGroup();
	//QQSystem::getInstance()->deleteGroup();
	//QQSystem::getInstance()->addGroup();
	std::cout << "-----------\n";
	//blog b = { 1, "标题", "内容", 1};
	//std::cout << b << std::endl;
	//QQSystem::getInstance()->updateFriend();
	//QQSystem::getInstance()->showFriend();
	system("pause");
	return 0;
}