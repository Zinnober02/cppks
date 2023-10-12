#pragma once
#include "QQUser.h"
#include <algorithm>
#include <Windows.h>
#include "QQGroup.h"
#include <filesystem>






class QQSystem
{
public:
	//�û����
	void createUser();
	QQUser* selectUser(int id);
	void updateUser();
	//�������
	void addFriend();
	void deleteFriend();
	static bool deleteFriend(std::vector<Friend>& friends, int id);
	void showFriend(); 
	void updateFriend();
	void newFriend();
	bool updateApplication(int id, Friend u, bool flag = true);//���±��������������б�
	std::string getEnumName(const Friend& a);
//private:
	QQSystem(QQUser* user) : currentUser(user) {};
	QQUser* currentUser;
	std::vector<QQUser> users;
	std::vector<QQGroup> addGroups;//����Ⱥ
	std::vector<QQGroup> myGroups;//���˼����Ⱥ
	std::vector<QQGroup> tmpGroups;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};
