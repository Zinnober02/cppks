#pragma once
#include "User.h"
#include <algorithm>
#include <Windows.h>
#include "QQGroup.h"
#include <filesystem>


class QQSystem
{
public:
	//用户相关
	void createUser();
	User* selectUser(int id);
	void updateUser();
	//好友相关
	void addFriend();
	void deleteFriend();
	void showFriend(); 
	void updateFriend();
	void newFriend();

	bool updateApplication(int id, Friend u, bool flag = true, bool kind = true);//更新被申请对象的申请列表

	//群相关
	void addGroup();
	void deleteGroup();
	void newGroup();
	QQGroup* showGroup();
	void updateGroup();
	void newGroup(QQGroup* group, int admin);
	static QQSystem* getInstance();
	QQSystem(QQSystem const&) = delete;
	void operator=(QQSystem const&) = delete;
	void setUser(User* user);

	void readUsers();
	static bool addFriend(int user_id, Friend newFriend);
	static bool addTmpFriend(int user_id, Friend newFriend);
	static bool addGroup(int user_id, Friend newGroup);
	static bool addTmpGroup(int user_id, Friend newGroup);
	static std::vector<Friend> readGroups(int user_id);
	static std::vector<Friend> readFriends(int user_id);
	static std::vector<Friend> readTmpFriends(int user_id);
	void readGroups();
	static std::vector<Friend> readTmpGroups(int user_id);
	static std::vector<Friend> readMembers(int group_id);
	static std::vector<Friend> readTmpMembers(int group_id);
	static bool saveGroups(int user_id, std::vector<Friend> myGroups);
	static bool saveFriends(int user_id, std::vector<Friend> friends);
	static bool saveTmpFriends(int user_id, std::vector<Friend> tmpFriends);
	static bool saveTmpGroups(int user_id, std::vector<Friend> tmpGroups);
	static bool saveMembers(int group_id, std::vector<Friend> members);
	static bool saveTmpMembers(int group_id, std::vector<Friend> tmpMembers);
private:
	static QQSystem* QQ;
	QQSystem() : currentUser(nullptr){};
public:
	User* currentUser;
	std::vector<User> users;
	std::vector<QQGroup> allGroups;//所有群
	std::vector<Friend> myGroups;//个人加入的群
	std::vector<Friend> tmpGroups;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};
