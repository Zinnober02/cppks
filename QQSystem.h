#pragma once
#include "QQUser.h"
#include <algorithm>
#include <Windows.h>
#include "QQGroup.h"
#include <filesystem>






class QQSystem
{
public:
	//用户相关
	void createUser();
	QQUser* selectUser(int id);
	void updateUser();
	//好友相关
	void addFriend();
	void deleteFriend();
	void showFriend(); 
	void updateFriend();
	void newFriend();

	static bool updateApplication(int id, Friend u, bool flag = true, bool kind = true);//更新被申请对象的申请列表

	//群相关
	void addGroup();
	void deleteGroup();
	void newGroup();
	QQGroup* showGroup();
	void updateGroup();
	void newGroup(QQGroup* group, int admin);
	void readGroups();
//private:
	QQSystem(QQUser* user) : currentUser(user) {};
	QQUser* currentUser;
	std::vector<QQUser> users;
	std::vector<QQGroup> allGroups;//所有群
	std::vector<Friend> myGroups;//个人加入的群
	std::vector<Friend> tmpGroups;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};
