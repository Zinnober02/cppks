#pragma once
#include "QQUser.h"
#include <algorithm>
#include <Windows.h>
#include "utils.h"
#include <filesystem>
const int wait = 0;
const int reject = 2;
const int agree = 1;



struct Friend {
	int id;
	std::string nickname;
	bool flag = false;//发送为false，接收为true
	int status = wait;

	friend std::ostream& operator<<(std::ostream& os, const Friend& obj) {
		os << obj.id << " " << obj.nickname << " " << obj.flag << " " << obj.status;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Friend& obj) {
		is >> obj.id >> obj.nickname >> obj.flag >> obj.status;
		return is;
	}
};

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
	Friend* selectFriend(int id);
	
	void showFriend(); 
	void updateFriend();
	void newFriend();
	bool updateApplication(int id, Friend u, bool flag = true);//更新被申请对象的申请列表
	std::string getEnumName(const Friend& a);
//private:
	QQSystem(QQUser* user) : currentUser(user) {};
	QQUser* currentUser;
	std::vector<QQUser> users;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};
