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
	//�û����
	void createUser();
	void deleteUser();
	QQUser* selectUser(int id);
	void updateUser();
	void saveUsers();
	void readUsers();
	//�������
	void addFriend();
	void deleteFriend();
	void selectFriend();
	void showFriend();
	void updateFriend();
	void newFriend();
	void readFriends();
	void saveFriends();//���浱ǰid�ĺ����б�
	void updateApplication(int id, Friend u);//���±��������������б�
	std::string getEnumName(int a);
//private:
	QQSystem(QQUser* user) : currentUser(user) {};
	QQUser* currentUser;
	std::vector<QQUser> users;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};

