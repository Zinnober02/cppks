#pragma once
#include "CommunicationPlatform.h"
#include "QQGroup.h"


class QQSystem : public CommunicationPlatform
{
public:
	QQSystem();
	void showMenu() override;
	void init() override;
	void readUsers() override;
	//�û����
	void createUser();
	User* selectUser(int id);
	void updateUser();
	//�������
	void addFriend();
	void deleteFriend();
	void showFriend(); 
	void updateFriend();
	void newFriend();

	bool updateApplication(int id, Friend u, bool flag = true, bool kind = true);//���±��������������б�

	//Ⱥ���
	void addGroup();
	void deleteGroup();
	void newGroup();
	QQGroup* showGroup();
	void updateGroup();
	void newGroup(QQGroup* group, int admin);
	QQSystem(QQSystem const&) = delete;
	void operator=(QQSystem const&) = delete;
	void setUser(User* user);

	
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
	bool saveGroups();
	bool saveUsers() override;
	static bool saveGroups(int user_id, std::vector<Friend> myGroups);
	static bool saveFriends(int user_id, std::vector<Friend> friends);
	static bool saveTmpFriends(int user_id, std::vector<Friend> tmpFriends);
	static bool saveTmpGroups(int user_id, std::vector<Friend> tmpGroups);
	static bool saveMembers(int group_id, std::vector<Friend> members);
	static bool saveTmpMembers(int group_id, std::vector<Friend> tmpMembers);
private:
public:
	std::vector<QQGroup> allGroups;//����Ⱥ
	std::vector<Friend> myGroups;//���˼����Ⱥ
	std::vector<Friend> tmpGroups;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};
