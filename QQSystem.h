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
	static bool deleteFriend(std::vector<Friend>& friends, int id);
	void showFriend(); 
	void updateFriend();
	void newFriend();
	bool updateApplication(int id, Friend u, bool flag = true);//更新被申请对象的申请列表
	std::string getEnumName(const Friend& a);
//private:
	QQSystem(QQUser* user) : currentUser(user) {};
	QQUser* currentUser;
	std::vector<QQUser> users;
	std::vector<QQGroup> addGroups;//所有群
	std::vector<QQGroup> myGroups;//个人加入的群
	std::vector<QQGroup> tmpGroups;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};
