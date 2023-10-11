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
	std::cout << "������QQ��" << std::endl;
	int id;
	std::cin >> id;
	auto user = selectUser(id);
	assert(user != nullptr);
	std::cout << "�����뱸ע" << std::endl;
	std::string nickname;
	std::cin >> nickname;
	tmpFriends.push_back({ id, nickname });
	std::cout << "�ɹ����ͺ������룬�ȴ��Է�ͬ��" << std::endl;
	//ͬʱҲҪ���Է��ĺ����������һ��
	updateApplication(id, { currentUser->_id, currentUser->_user_name, true }, false);
	//QQSystem::saveFriends(currentUser->_id, tmpFriends, false);
	utils::saveData<Friend>("tmpFriends.txt", tmpFriends, currentUser->_id);
}

void QQSystem::deleteFriend()
{
	showFriend();
	std::cout << "������QQ��" << std::endl;
	int id;
	std::cin >> id;
	QQSystem::deleteFriend(this->friends, id);
	utils::saveData<Friend>("friends.txt", friends, currentUser->_id);
	//�Է��ĺ���ҲҪɾ��
	auto targetFriends = utils::readData<Friend>("friends.txt", id);
	QQSystem::deleteFriend(targetFriends, currentUser->_id);
	utils::saveData<Friend>("friends.txt", targetFriends, id);
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

Friend* QQSystem::selectFriend(int id)
{
	auto it = find_if(friends.begin(), friends.end(), [&id](const Friend& item) {
		return id == item.id;
		});
	if (it != friends.end()) return &*it;
	else return nullptr;
}




void QQSystem::showFriend()
{
	std::cout << "�����б�" << std::endl;
	int index = 1, choice = 0;
	for (auto& user : friends) {
		std::cout << index++ << "\t" << user.nickname <<"\t" << user.id << std::endl;
	}
	std::cout << "������Ų鿴��ϸ��Ϣ" << std::endl;
	std::cin >> choice;
	assert(choice <= friends.size());
	Friend tmp = friends[--choice];
	auto user = selectUser(tmp.id);
	std::cout << tmp.nickname << "\t" << user->_user_name << std::endl;
}

void QQSystem::updateFriend()
{
	showFriend();
	std::cout << "������Ҫ�޸ĵĺ����˺�\n";
	int id;
	std::cin >> id;
	std::cout << "�������±�ע\n";
	std::string nickname;
	std::cin >> nickname;
	auto item = utils::selectTarget(friends, id, [id](const Friend& item, int _id) {return _id == item.id;});
	item->nickname = nickname;
	utils::saveData<Friend>("friends.txt", friends, currentUser->_id);
}

void QQSystem::newFriend()
{
	if (tmpFriends.empty()) {
		std::cout << "û�к�������" << std::endl;
		Sleep(1000);
		return;
	}

	std::cout << "�����б�" << std::endl;
	int index = 1, choice1 = 0, choice2 = 0;
	for (auto& item : tmpFriends)
		std::cout << index++ << "\t" << item.nickname << "\t" << getEnumName(item) << std::endl;
	std::cout << "������Ž��д���" << std::endl;
	std::cin >> choice1;
	Friend tmp = tmpFriends[--choice1];
	std::cout << "1yes/2no" << std::endl;
	std::cin >> choice2;
	if (choice2 == 1) {
		std::string nickname;
		std::cout << "�����뱸ע" << std::endl;
		std::cin >> nickname;
		friends.push_back({ tmp.id, nickname, true, agree });
	}
	tmpFriends[choice1].status == choice2;
	//ͬʱҲӦ���޸ĶԷ��ĺ��������¼������˵����
	if (updateApplication(tmp.id, { currentUser->_id, tmp.nickname, false, choice2 }, static_cast<bool>(2 - choice2))) {
		utils::saveData<Friend>("friends.txt", friends, currentUser->_id);
		utils::saveData<Friend>("tmpFriends.txt", tmpFriends, currentUser->_id);
	}
	else std::cout << "���ʧ��" << std::endl;
}


bool QQSystem::updateApplication(int id, Friend u, bool flag)
{
	//�޸ĺ�������״̬
	std::vector<Friend> tmp = std::move(utils::readData<Friend>(utils::fn2, id));
	if (tmp.empty()) return false;
	std::string nickname;
	for (auto& item : tmp) {
		if (item.id == u.id) {
			item.status = flag ? agree : reject;
			break;
		}
	}
	if(!utils::saveData<Friend>(utils::fn2, tmp, id))
		return false;
	//��Ӻ���
	if (u.status == reject || flag == false) return true;//���ܾ��Ͳ����
	return utils::addObj(utils::fn1, id, u);
}



std::string QQSystem::getEnumName(const Friend& a)
{
	if (a.status == wait) return a.flag ? "�ȴ�ͬ��" : "�ȴ��Է�ͬ��";
	if (a.status == reject) return a.flag ? "�Ѿܾ�" :  "�ѱ��ܾ�";
	return "��ͬ��";
}
