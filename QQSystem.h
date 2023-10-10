#pragma once
#include <string>
#include <vector>
#include "QQUser.h"
#include <algorithm>
#include <Windows.h>
#include <fstream>
#include <filesystem>
#include <sstream> 

const int wait = 0;
const int reject = 2;
const int agree = 1;



struct Friend {
	int id;
	std::string nickname;
	int status = wait;
};

class QQSystem
{
public:
	//用户相关
	void createUser();
	void deleteUser();
	QQUser* selectUser(int id);
	void updateUser();
	void saveUsers();
	void readUsers();
	//好友相关
	void addFriend();
	void deleteFriend();
	void selectFriend();
	void showFriend();
	void updateFriend();
	void newFriend();
	void readFriends();
	void saveFriends();//保存当前id的好友列表
	void updateApplication(int id, Friend u);//更新被申请对象的申请列表
	std::string getEnumName(int a);
//private:
	QQSystem(QQUser* user) : currentUser(user) {};
	QQUser* currentUser;
	std::vector<QQUser> users;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};

