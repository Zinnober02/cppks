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
	//ͬʱҲҪ���Է��ĺ����������һ��
	Friend u = { currentUser->_id, nickname, true };
	if (utils::addObj(2, 1, id, u))
		if (utils::saveData<Friend>(2, 1, tmpFriends, currentUser->_id))
			std::cout << "�ɹ����ͺ������룬�ȴ��Է�ͬ��" << std::endl;
}

void QQSystem::deleteFriend()
{
	showFriend();
	std::cout << "������QQ��" << std::endl;
	int id;
	std::cin >> id;
	auto cmp = [](const Friend& item, int _id) {return _id == item.id; };
	auto it1 = utils::selectIterator(friends, id, cmp);
	//�Է��ĺ���ҲҪɾ��
	auto targetFriends = utils::readData<Friend>(1, 1, id);
	auto it2 = utils::selectIterator(targetFriends, id, cmp);
	if (it1 != friends.end() && it2 != targetFriends.end()) {
		friends.erase(it1);
		targetFriends.erase(it2);
		utils::saveData<Friend>(1, 1, friends, currentUser->_id);
		utils::saveData<Friend>(1, 1, targetFriends, id);
	}
	else std::cout << "�޷�ɾ��\n";
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
	utils::saveData<Friend>(1, 1, friends, currentUser->_id);
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
		std::cout << index++ << "\t" << item.id << "\t" << item.nickname << "\t" << Friend::getEnumName(item) << std::endl;
	std::cout << "������Ž��д���" << std::endl;
	std::cin >> choice1;
	Friend tmp = tmpFriends[--choice1];
	std::cout << "1yes/2no" << std::endl;
	std::cin >> choice2;
	if (choice2 == 1) {
		std::cout << "�����뱸ע" << std::endl;
		std::cin >> tmp.nickname;
		friends.push_back({ tmp.id, tmp.nickname, true, agree });
	}
	tmpFriends[choice1].status = choice2;
	//ͬʱҲӦ���޸ĶԷ��ĺ��������¼������˵����
	if (updateApplication(tmp.id, { currentUser->_id, tmp.nickname, false, choice2 }, 2 - choice2)) {
		utils::saveData<Friend>(1, 1, friends, currentUser->_id);
		utils::saveData<Friend>(2, 1, tmpFriends, currentUser->_id);
	}
	else std::cout << "���ʧ��" << std::endl;
}


bool QQSystem::updateApplication(int id, Friend u, bool flag, bool kind)
{
	//�޸�����״̬
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
	//���
	if (u.status == reject || flag == false) return true;//���ܾ��Ͳ����
	return kind ? utils::addObj(1, 1, id, u) : utils::addObj(4, 1, id, u);
}





void QQSystem::addGroup()
{
	std::cout << "������Ⱥ��" << std::endl;
	int id;
	std::cin >> id;
	auto group = utils::selectTarget(allGroups, id, [id](const QQGroup& item, int _id) {return _id == item.id; });
	assert(group != nullptr);
	std::cout << "������Ⱥ�ǳ�" << std::endl;
	std::string nickname;
	std::cin >> nickname;
	tmpGroups.push_back({ id, nickname });
	//ͬʱҲҪ����ӦȺ���������һ��
	Friend u = { currentUser->_id, nickname, true };
	if (utils::addObj(7, 0, id, u))
		if (utils::saveData<Friend>(5, 1, tmpGroups, currentUser->_id))
			std::cout << "�ɹ�������Ⱥ���룬�ȴ�����Ա���" << std::endl;
}

void QQSystem::deleteGroup()
{
	if (myGroups.empty()) return;
	std::cout << currentUser->_user_name << "��Ⱥ�б�" << std::endl;
	int index = 1, choice = 0;
	for (auto& group : myGroups) {
		std::cout << index++ << "\t" << group.id << "\t" << group.nickname << std::endl;
	}
	std::cout << "����Ҫ�˳���Ⱥ���" << std::endl;
	std::cin >> choice;
	assert(choice <= myGroups.size());
	//���ҵ�Ⱥ���ҵ�Ҫ�˳���Ⱥ
	auto it1 = std::next(myGroups.begin(), --choice);
	//ͨ��id��ȡ��Ⱥ��Ϣ�ͳ�Ա
	auto group = utils::selectTarget(allGroups, it1->id, [](const QQGroup& item, int _id) {return _id == item.id; });
	group->members = std::move(utils::readData<Friend>(6, 0, it1->id));
	
	//��Ҫ�˳���Ⱥ��Ա���ҵ���
	auto it2 = utils::selectIterator(group->members, currentUser->_id, [](const Friend& item, int _id) {return _id == item.id; });
	
	if (it1 != myGroups.end() && it2 != group->members.end()) {
		myGroups.erase(it1);
		group->members.erase(it2);
		utils::saveData<Friend>(4, 1, myGroups, currentUser->_id);
		utils::saveData<Friend>(6, 0, group->members, group->id);
	}
	else std::cout << "�˳�ʧ��\n";
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
	std::cout << currentUser->_user_name << "��Ⱥ�б�" << std::endl;
	int index = 1, choice = 0;
	for (auto& group : myGroups) {
		std::cout << index++ << "\t" << group.id << "\t" << group.nickname << std::endl;
	}
	std::cout << "������Ų鿴��ϸ��Ϣ" << std::endl;
	std::cin >> choice;
	assert(choice <= myGroups.size());
	auto g = myGroups[--choice];
	//ͨ��id��ȡ��Ⱥ��Ϣ�ͳ�Ա
	auto group = utils::selectTarget(allGroups, g.id, [](const QQGroup& item, int _id) {return _id == item.id; });
	group->members = std::move(utils::readData<Friend>(6, 0, g.id));
	return group;
}

void QQSystem::newGroup(QQGroup* group, int admin)
{
	std::vector<Friend> tmpMembers;
	if (admin) {
		std::cout << "���Ǹ�Ⱥ����Ա\n";
		tmpMembers = utils::readData<Friend>(7, 0, group->id);
	}
	if (tmpMembers.empty()) {
		std::cout << "û����Ⱥ����" << std::endl;
		Sleep(1000);
		return;
	}

	std::cout << "�����б�" << std::endl;
	int index = 1, choice1 = 0, choice2 = 0, choice3 = 0;
	std::cout << "���\t" << "QQ��\t" << "״̬\n";
	for (auto& item : tmpMembers)
		std::cout << index++ << "\t" << item.id  << "\t" << Friend::getEnumName(item) << std::endl;
	std::cout << "������Ž��д���" << std::endl;
	std::cin >> choice1;
	Friend* tmp = &tmpMembers[--choice1];
	std::cout << "1yes/2no" << std::endl;
	std::cin >> choice2;
	if (choice2 == 1) {
		if (admin == 2) {
			std::cout << "�Ƿ�����Ϊ����Ա��1yes/2no\n";
			std::cin >> choice3;
		}
		group->members.push_back({ tmp->id, tmp->nickname, true, agree, 2 - choice3 });
	}
	tmp->status = choice2;
	//ͬʱҲӦ���޸ĶԷ��������¼
	if (updateApplication(tmp->id, { currentUser->_id, tmp->nickname, false, choice2, choice3 }, 2 - choice2, false)) {
		utils::saveData<Friend>(6, 0, group->members, group->id);
		utils::saveData<Friend>(7, 0, tmpMembers, group->id);
	}
	else std::cout << "���ʧ��" << std::endl;
}

void QQSystem::readGroups()
{
	allGroups = utils::readData<QQGroup>(3, 0);
	for (auto& group : allGroups) {
		group.members = std::move(utils::readData<Friend>(6, 0, group.id));
	}
}
