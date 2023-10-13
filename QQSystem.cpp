#include "QQSystem.h"
#include <cassert>
QQUser* QQSystem::selectUser(int id)
{
	auto it = find_if(users.begin(), users.end(), [&id](const QQUser& user) {
		return id == user._id;
		});
	if (it != users.end()) return &*it;
	else return nullptr;
}

void QQSystem::addFriend()
{
	std::cout << "请输入QQ号" << std::endl;
	int id;
	std::cin >> id;
	auto user = selectUser(id);
	assert(user != nullptr);
	std::cout << "请输入备注" << std::endl;
	std::string nickname;
	std::cin >> nickname;
	tmpFriends.push_back({ id, nickname });
	//同时也要给对方的好友申请添加一个
	Friend u = { currentUser->_id, nickname, true };
	if (utils::addObj(2, 1, id, u))
		if (utils::saveData<Friend>(2, 1, tmpFriends, currentUser->_id))
			std::cout << "成功发送好友申请，等待对方同意" << std::endl;
}

void QQSystem::deleteFriend()
{
	showFriend();
	std::cout << "请输入QQ号" << std::endl;
	int id;
	std::cin >> id;
	auto cmp = [](const Friend& item, int _id) {return _id == item.id; };
	auto it1 = utils::selectIterator(friends, id, cmp);
	//对方的好友也要删除
	auto targetFriends = utils::readData<Friend>(1, 1, id);
	auto it2 = utils::selectIterator(targetFriends, id, cmp);
	if (it1 != friends.end() && it2 != targetFriends.end()) {
		friends.erase(it1);
		targetFriends.erase(it2);
		utils::saveData<Friend>(1, 1, friends, currentUser->_id);
		utils::saveData<Friend>(1, 1, targetFriends, id);
	}
	else std::cout << "无法删除\n";
}


void QQSystem::showFriend()
{
	std::cout << "好友列表" << std::endl;
	int index = 1, choice = 0;
	for (auto& user : friends) {
		std::cout << index++ << "\t" << user.nickname <<"\t" << user.id << std::endl;
	}
	std::cout << "输入序号查看详细信息" << std::endl;
	std::cin >> choice;
	assert(choice <= friends.size());
	Friend tmp = friends[--choice];
	auto user = selectUser(tmp.id);
	std::cout << tmp.nickname << "\t" << user->_user_name << std::endl;
}

void QQSystem::updateFriend()
{
	showFriend();
	std::cout << "请输入要修改的好友账号\n";
	int id;
	std::cin >> id;
	std::cout << "请输入新备注\n";
	std::string nickname;
	std::cin >> nickname;
	auto item = utils::selectTarget(friends, id, [id](const Friend& item, int _id) {return _id == item.id;});
	item->nickname = nickname;
	utils::saveData<Friend>(1, 1, friends, currentUser->_id);
}

void QQSystem::newFriend()
{
	if (tmpFriends.empty()) {
		std::cout << "没有好友申请" << std::endl;
		Sleep(1000);
		return;
	}

	std::cout << "申请列表" << std::endl;
	int index = 1, choice1 = 0, choice2 = 0;
	for (auto& item : tmpFriends)
		std::cout << index++ << "\t" << item.id << "\t" << item.nickname << "\t" << Friend::getEnumName(item) << std::endl;
	std::cout << "输入序号进行处理" << std::endl;
	std::cin >> choice1;
	Friend tmp = tmpFriends[--choice1];
	std::cout << "1yes/2no" << std::endl;
	std::cin >> choice2;
	if (choice2 == 1) {
		std::cout << "请输入备注" << std::endl;
		std::cin >> tmp.nickname;
		friends.push_back({ tmp.id, tmp.nickname, true, agree });
	}
	tmpFriends[choice1].status = choice2;
	//同时也应该修改对方的好友申请记录，或者说更改
	if (updateApplication(tmp.id, { currentUser->_id, tmp.nickname, false, choice2 }, 2 - choice2)) {
		utils::saveData<Friend>(1, 1, friends, currentUser->_id);
		utils::saveData<Friend>(2, 1, tmpFriends, currentUser->_id);
	}
	else std::cout << "添加失败" << std::endl;
}


bool QQSystem::updateApplication(int id, Friend u, bool flag, bool kind)
{
	//修改申请状态
	std::vector<Friend> tmp = 
		std::move(kind ? utils::readData<Friend>(2, 1, id) : utils::readData<Friend>(5, 1, id));
	if (tmp.empty()) return false;
	std::string nickname;
	for (auto& item : tmp) {
		if (item.id == u.id) {
			item.status = flag ? agree : reject;
			break;
		}
	}
	if(!(kind ? utils::saveData<Friend>(2, 1, tmp, id) : utils::saveData<Friend>(5, 1, tmp, id)))
		return false;
	//添加
	if (u.status == reject || flag == false) return true;//被拒绝就不添加
	return kind ? utils::addObj(1, 1, id, u) : utils::addObj(4, 1, id, u);
}





void QQSystem::addGroup()
{
	std::cout << "请输入群号" << std::endl;
	int id;
	std::cin >> id;
	auto group = utils::selectTarget(allGroups, id, [id](const QQGroup& item, int _id) {return _id == item.id; });
	assert(group != nullptr);
	std::cout << "请输入群昵称" << std::endl;
	std::string nickname;
	std::cin >> nickname;
	tmpGroups.push_back({ id, nickname });
	//同时也要给对应群的申请添加一个
	Friend u = { currentUser->_id, nickname, true };
	if (utils::addObj(7, 0, id, u))
		if (utils::saveData<Friend>(5, 1, tmpGroups, currentUser->_id))
			std::cout << "成功发送入群申请，等待管理员审核" << std::endl;
}

void QQSystem::deleteGroup()
{
	if (myGroups.empty()) return;
	std::cout << currentUser->_user_name << "的群列表" << std::endl;
	int index = 1, choice = 0;
	for (auto& group : myGroups) {
		std::cout << index++ << "\t" << group.id << "\t" << group.nickname << std::endl;
	}
	std::cout << "输入要退出的群序号" << std::endl;
	std::cin >> choice;
	assert(choice <= myGroups.size());
	//在我的群中找到要退出的群
	auto it1 = std::next(myGroups.begin(), --choice);
	//通过id读取该群信息和成员
	auto group = utils::selectTarget(allGroups, it1->id, [](const QQGroup& item, int _id) {return _id == item.id; });
	group->members = std::move(utils::readData<Friend>(6, 0, it1->id));
	
	//在要退出的群成员中找到我
	auto it2 = utils::selectIterator(group->members, currentUser->_id, [](const Friend& item, int _id) {return _id == item.id; });
	
	if (it1 != myGroups.end() && it2 != group->members.end()) {
		myGroups.erase(it1);
		group->members.erase(it2);
		utils::saveData<Friend>(4, 1, myGroups, currentUser->_id);
		utils::saveData<Friend>(6, 0, group->members, group->id);
	}
	else std::cout << "退出失败\n";
}

void QQSystem::newGroup()
{
	auto group = showGroup();
	if (!group) return;
	std::cout << *group << std::endl;
	for (auto member : group->members) {
		std::cout << member << std::endl;
	}
	auto g = utils::selectIterator(myGroups, group->id, [](const Friend& item, int _id) {return item.id == _id; });
	newGroup(group, g->admin);
}

QQGroup* QQSystem::showGroup()
{
	if (myGroups.empty()) return nullptr;
	std::cout << currentUser->_user_name << "的群列表" << std::endl;
	int index = 1, choice = 0;
	for (auto& group : myGroups) {
		std::cout << index++ << "\t" << group.id << "\t" << group.nickname << std::endl;
	}
	std::cout << "输入序号查看详细信息" << std::endl;
	std::cin >> choice;
	assert(choice <= myGroups.size());
	auto g = myGroups[--choice];
	//通过id读取该群信息和成员
	auto group = utils::selectTarget(allGroups, g.id, [](const QQGroup& item, int _id) {return _id == item.id; });
	group->members = std::move(utils::readData<Friend>(6, 0, g.id));
	return group;
}

void QQSystem::newGroup(QQGroup* group, int admin)
{
	std::vector<Friend> tmpMembers;
	if (admin) {
		std::cout << "你是该群管理员\n";
		tmpMembers = utils::readData<Friend>(7, 0, group->id);
	}
	if (tmpMembers.empty()) {
		std::cout << "没有入群申请" << std::endl;
		Sleep(1000);
		return;
	}

	std::cout << "申请列表" << std::endl;
	int index = 1, choice1 = 0, choice2 = 0, choice3 = 0;
	std::cout << "序号\t" << "QQ号\t" << "状态\n";
	for (auto& item : tmpMembers)
		std::cout << index++ << "\t" << item.id  << "\t" << Friend::getEnumName(item) << std::endl;
	std::cout << "输入序号进行处理" << std::endl;
	std::cin >> choice1;
	Friend* tmp = &tmpMembers[--choice1];
	std::cout << "1yes/2no" << std::endl;
	std::cin >> choice2;
	if (choice2 == 1) {
		if (admin == 2) {
			std::cout << "是否设置为管理员？1yes/2no\n";
			std::cin >> choice3;
		}
		group->members.push_back({ tmp->id, tmp->nickname, true, agree, 2 - choice3 });
	}
	tmp->status = choice2;
	//同时也应该修改对方的申请记录
	if (updateApplication(tmp->id, { currentUser->_id, tmp->nickname, false, choice2, choice3 }, 2 - choice2, false)) {
		utils::saveData<Friend>(6, 0, group->members, group->id);
		utils::saveData<Friend>(7, 0, tmpMembers, group->id);
	}
	else std::cout << "添加失败" << std::endl;
}

void QQSystem::readGroups()
{
	allGroups = utils::readData<QQGroup>(3, 0);
	for (auto& group : allGroups) {
		group.members = std::move(utils::readData<Friend>(6, 0, group.id));
	}
}
