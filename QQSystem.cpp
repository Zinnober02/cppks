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
	if (utils::addObj(2, id, u))
		if (utils::saveData<Friend>(2, tmpFriends, currentUser->_id))
			std::cout << "成功发送好友申请，等待对方同意" << std::endl;
}

void QQSystem::deleteFriend()
{
	showFriend();
	std::cout << "请输入QQ号" << std::endl;
	int id;
	std::cin >> id;
	QQSystem::deleteFriend(this->friends, id);
	utils::saveData<Friend>(1, friends, currentUser->_id);
	//对方的好友也要删除
	auto targetFriends = utils::readData<Friend>(1, id);
	QQSystem::deleteFriend(targetFriends, currentUser->_id);
	utils::saveData<Friend>(1, targetFriends, id);
}

bool QQSystem::deleteFriend(std::vector<Friend>& friends, int id)
{
	auto it = find_if(friends.begin(), friends.end(), [&id](const Friend& item) {
		return id == item.id;
		});
	if (it == friends.end()) return false;
	friends.erase(it);
	return true;
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
	utils::saveData<Friend>(1, friends, currentUser->_id);
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
		std::cout << index++ << "\t" << item.id << "\t" << item.nickname << "\t" << getEnumName(item) << std::endl;
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
	if (updateApplication(tmp.id, { currentUser->_id, tmp.nickname, false, choice2 }, static_cast<bool>(2 - choice2))) {
		utils::saveData<Friend>(1, friends, currentUser->_id);
		utils::saveData<Friend>(2, tmpFriends, currentUser->_id);
	}
	else std::cout << "添加失败" << std::endl;
}


bool QQSystem::updateApplication(int id, Friend u, bool flag)
{
	//修改好友申请状态
	std::vector<Friend> tmp = std::move(utils::readData<Friend>(2, id));
	if (tmp.empty()) return false;
	std::string nickname;
	for (auto& item : tmp) {
		if (item.id == u.id) {
			item.status = flag ? agree : reject;
			break;
		}
	}
	if(!utils::saveData<Friend>(2, tmp, id))
		return false;
	//添加好友
	if (u.status == reject || flag == false) return true;//被拒绝就不添加
	return utils::addObj(1, id, u);
}



std::string QQSystem::getEnumName(const Friend& a)
{
	if (a.status == wait) return a.flag ? "等待同意" : "等待对方同意";
	if (a.status == reject) return a.flag ? "已拒绝" :  "已被拒绝";
	return "已同意";
}
