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
	void showFriend(); 
	void updateFriend();
	void newFriend();

	static bool updateApplication(int id, Friend u, bool flag = true, bool kind = true);//���±��������������б�

	//Ⱥ���
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
	std::vector<QQGroup> allGroups;//����Ⱥ
	std::vector<Friend> myGroups;//���˼����Ⱥ
	std::vector<Friend> tmpGroups;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};
