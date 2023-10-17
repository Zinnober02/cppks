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
	//用户相关
	bool login() override;
	void createUser() override;
	User* selectUser(int id);
	void updateUser();

	void menu1();
	void friendMenu();
	void groupMenu();
	void selfMenu();
	void serviceMenu();
	//好友相关
	void addFriend(int id);
	static bool addFriend(int user_id, Friend newFriend);
	bool deleteFriend(Friend u);
	Friend* showFriends(); 
	bool updateFriend(Friend* u);
	void newFriend();
	void friendMenu1();
	void groupMenu1();
	std::string getUsername(int user_id);

	bool updateApplication(int id, Friend u, bool flag = true, bool kind = true);//更新被申请对象的申请列表

	//群相关
	void addGroup(int user_id, int group_id);
	void deleteGroup(QQGroup& group);
	void newGroup();
	QQGroup* showGroups();
	void updateGroup();
	void newGroup(QQGroup* group, int admin);
	
	
	
	
	
	
	
	QQSystem(QQSystem const&) = delete;
	void operator=(QQSystem const&) = delete;
	void setUser(User* user);
	
	
	
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
	std::vector<QQGroup> allGroups;//所有群
	std::vector<Friend> myGroups;//个人加入的群
	std::vector<Friend> tmpGroups;
	std::vector<Friend> friends;
	std::vector<Friend> tmpFriends;
};
