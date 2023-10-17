#include "QQSystem.h"

QQSystem::QQSystem() {
	readUsers();
}


bool QQSystem::login()
{
	system("cls");
	int ID;
	std::string PassWord;
	std::cout << "����Ҫ��½��QQ:" << std::endl;
	std::cin >> ID;
	auto it = utils::selectIterator(users, ID, [](const User& u, int _id) {
		return u._id == _id;
		});
	if (it == users.end()) {
		std::cout << "δ��ѯ����QQ�ţ��������룬�����������" << std::endl;
		if (getchar() != EOF)
			return false;
	}
	std::cout << "�������QQ������" << std::endl;
	std::cin >> PassWord;
	// [����]fe_flush(stdin);
	while (PassWord != it->_password) {
		std::cout << "�����������,��������������" << std::endl;
		std::cin >> PassWord;
	}
	rgbSet(124, 252, 0, 0, 0, 0);
	std::cout << "��½�ɹ������������ʼʹ��QQ" << std::endl;
	rgbSet(255, 255, 255, 0, 0, 0);
	currentUser = &*it;
	init();
	if (getchar() != EOF)
		return true;
}

void QQSystem::createUser()
{
}

void QQSystem::showMenu()
{
	//User* user = new User(1, "1", "����");
	//setUser(user);
	system("cls");
	int select, key = 1;
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------��ӭʹ��QQ-----------" << std::endl;
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t��1����¼\n";
	std::cout << "\t��2��ע��\n";
	std::cout << "\t��0���˳�ϵͳ\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "--------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	std::cout << "���������ĵ�ѡ��:\n";
	int choice;

	std::cin >> choice;
	switch (choice) {
		case 1:if (login()) menu1(); break;
		case 2:createUser(); break;
		case 0:exit(0); break;
		default: showMenu();
	}
	showMenu();
}

void QQSystem::init()
{
	
	friends = QQSystem::readFriends(currentUser->_id);
	tmpFriends = QQSystem::readTmpFriends(currentUser->_id);
	readGroups();
	myGroups = QQSystem::readGroups(currentUser->_id);
}

User* QQSystem::selectUser(int id)
{
	auto it = find_if(users.begin(), users.end(), [&id](const User& user) {
		return id == user._id;
		});
	if (it != users.end()) return &*it;
	else return nullptr;
}

void QQSystem::menu1()
{
	system("cls");
	int select;
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "--------------��ӭʹ��QQ----------------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t���QQ��Ϊ:" << currentUser->_id << std::endl;
	std::cout << "\t��ѡ��ʹ�õĹ���\n";
	std::cout << "\t��1�����ѹ���\n";
	std::cout << "\t��2��Ⱥ����\n";
	std::cout << "\t��3����������\n";
	std::cout << "\t��4����ͨ����\n";
	std::cout << "\t��0���л��˺�\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	std::cout << "���������ѡ��\n";
	std::cin >> select;
	switch (select) {
	case 1: friendMenu(); break;
	case 2: groupMenu(); break;
	case 3: selfMenu(); break;
	case 4: serviceMenu(); break;
	case 0: showMenu(); break;
	default: menu1(); break;
	}
	menu1();
}

void QQSystem::friendMenu()
{
	system("cls");
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------��ѡ����Ѳ���----------------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t��1����Ӻ���\n";
	std::cout << "\t��2�������б�\n";
	std::cout << "\t��3���鿴��������\n";
	std::cout << "\t��4���Ƽ�����\n";
	std::cout << "\t��0������\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int select;
	std::cin >> select;
	switch (select) {
	case 1: {
		std::cout << "������QQ��" << std::endl;
		int id;
		std::cin >> id;
		addFriend(id);
		break;
	}
	case 2: 
		friendMenu1();
		break;
	case 3:
		newFriend();
		break;
	case 4:
		
		break;
	default:
		menu1();
		return;
	}
	menu1();
}

void QQSystem::groupMenu()
{
	system("cls");
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "------------------��ѡ��Ⱥ����----------------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t��1������QQȺ\n";
	std::cout << "\t��2������QQȺ\n";
	std::cout << "\t��3��Ⱥ�б�\n";
	std::cout << "\t��4��������ʱ������\n";
	std::cout << "\t��0������\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------------------------------------------\n" ;
	rgbSet(255, 255, 255, 0, 0, 0);
	std::cout << "����������ѡ��\n";
	int select;
	std::cin >> select;
	switch (select) {
	case 1: {
		int id;
		std::cout << "������Ⱥ�ţ�";
		std::cin >> id;
		addGroup(currentUser->_id, id);
		break;
	}
	case 2:
		//createGroup();
		break;
	case 3:
		groupMenu1();
		break;
	case 4:

		break;
	default:
		groupMenu();
		break;
	}
	groupMenu();
}


void QQSystem::groupMenu1()
{
	auto res = showGroups();
	if (!res) return;
	auto g = QQGroup(res);
	system("cls");
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------------------\n";
	std::cout << g.name << std::endl;
	std::cout << g.id << std::endl;
	std::cout << "����" << g.members.size() + 1 << "��\n";
	int num = 1; int flag = 0;
	if (g.owner.id == currentUser->_id) flag = 2;
	std::cout << num++ << "\tȺ����" << g.owner.nickname << "(" << g.owner.id << ")\n";
	if (g.members.size()) {
		sort(g.members.begin(), g.members.end(), [](const Friend& a, const Friend& b) {
			return a.admin > b.admin; 
			});
		std::cout << "Ⱥ��Ա��\n";
		for (auto& member : g.members) {
			if (member.id == currentUser->_id && member.admin) flag = member.admin;
			std::cout << num++ << "\t" << Friend::getAdmin(member) << "��"
				<< member.nickname << "(" << member.id << ")\n";
		}
	}
	std::cout << "---------------------------\n";
	std::cout << "\t��ѡ�����\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t��1���޸�Ⱥ�ǳ�\n";
	std::cout << "\t��2���˳�Ⱥ��\n";
	std::cout << "\t��3��������Ⱥ\n";
	std::cout << "\t��4����Ӻ���\n";
	if (flag)
		std::cout << "\t��5��Ⱥ����\n";
	std::cout << "\t��0������\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int select;
	std::cin >> select;
	auto group = utils::selectIterator(allGroups, g.id, [](const QQGroup& g, int id) {
		return g.id == id;
		});
	switch (select) {
	case 1: {
		auto cmp = [](const Friend& u, int _id) { return u.id == _id; };
		if (currentUser->_id == group->id) {
			std::cout << "Ⱥ�ǳƣ�" << g.owner.nickname << "\n�������ǳƣ�";
			std::cin >> group->owner.nickname;
			saveGroups();
		}
		else {
			auto it1 = utils::selectIterator(g.members, currentUser->_id, cmp);
			if (it1 == g.members.end()) break;
			std::cout << "Ⱥ�ǳƣ�" << it1->nickname << "\n�������ǳƣ�";
			std::cin >> it1->nickname;
			saveMembers(g.id, g.members);
		}
		break;
	}
	case 2:
		deleteGroup(g);
		break;
	case 3: {
		auto u = showFriends();
		if (!u) break;
		addGroup(u->id, g.id);
		break;
	}
	case 4: {
		int choice = 1, id = 1;
		std::cout << "����Ҫ��ӵĳ�Ա��ţ�";
		std::cin >> choice;
		if (choice == 1) id = g.owner.id;
		else id = g.members[choice - 2].id;
		addFriend(id);
		break;
	}
	case 5: {
		if (!flag) groupMenu();
		newGroup(&g, flag);
		break;
	}
	default :
		groupMenu();
		break;
	}
	groupMenu1();
}

void QQSystem::selfMenu()
{
	system("cls");
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "-------��ѡ����������Ϲ���-------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t��1���鿴��������\n";
	std::cout << "\t��2���޸�����\n";
	std::cout << "\t��3���޸�����\n";
	std::cout << "\t��4���޸�ǩ��\n";
	std::cout << "\t��5���޸����ڵ�\n";
	std::cout << "\t��0��������һ���˵�\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int select;
	std::cin >> select;
	switch (select) {
	case 1:
		//addGroup();
		break;
	case 0:
		menu1();
		return;
	default:
		showMenu();
		return;
	}
}

void QQSystem::serviceMenu()
{
	system("cls");
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------��ѡ�����----------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t��1����ͨ΢��\n";
	std::cout << "\t��2����΢��\n";
	std::cout << "\t��0��������һ��\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int select;
	std::cin >> select;
	switch (select) {
	case 1:
		//CreateWeiBo();
		break;
	case 2:
		//LinkWeChat();
		break;
	case 0:
		menu1();
		break;
	default:
		showMenu();
		return;
	}
}

void QQSystem::addFriend(int id)
{
	auto user = selectUser(id);
	assert(user != nullptr);
	std::cout << "�����뱸ע" << std::endl;
	std::string nickname;
	std::cin >> nickname;
	tmpFriends.push_back({ id, nickname });
	//ͬʱҲҪ���Է��ĺ����������һ��
	Friend u = { currentUser->_id, nickname, true };
	if (addFriend(id, u))
		if (saveFriends(currentUser->_id, tmpFriends)) {
			std::cout << "�ɹ����ͺ������룬�ȴ��Է�ͬ��" << std::endl;
			Sleep(1000);
		}
}

bool QQSystem::deleteFriend(Friend u)
{
	system("cls");
	int id = u.id;
	Friend copy = u;
	auto cmp = [](const Friend& item, int _id) {return _id == item.id; };
	auto it1 = utils::selectIterator(friends, id, cmp);
	//�Է��ĺ���ҲҪɾ��
	auto targetFriends = readFriends(id);
	auto it2 = utils::selectIterator(targetFriends, currentUser->_id, cmp);
	if (it1 != friends.end() && it2 != targetFriends.end()) {
		friends.erase(it1);
		targetFriends.erase(it2);
		if (saveFriends(currentUser->_id, friends) && saveFriends(id, targetFriends))
			return true;
		else {
			friends.push_back(copy);
			friends.push_back(copy);
		}
	}
	std::cout << "�޷�ɾ��\n";
	Sleep(1000);
	return false;
}


Friend* QQSystem::showFriends()
{
	if (friends.empty()) {
		std::cout << "û�к���\n";
		Sleep(1000);
		return nullptr;
	}
	system("cls");
	std::cout << "\t�����б�\n--------------------------\n";
	int index = 1, choice = 0;
	for (auto& user : friends) {
		std::cout << index++ << "\t" << user.nickname <<"(" << user.id << ")\n";
	}
	std::cout << "ѡ����ѣ�";
	std::cin >> choice;
	assert(choice <= friends.size());
	Friend tmp = friends[--choice];
	return &tmp;
}

bool QQSystem::updateFriend(Friend* u)
{
	std::cout << "�������±�ע\n";
	std::string nickname;
	std::cin >> nickname;
	auto item = utils::selectTarget(friends, u->id, [](const Friend& item, int _id) {return _id == item.id;});
	item->nickname = nickname;
	return saveFriends(currentUser->_id, friends);
}

void QQSystem::newFriend()
{
	if (tmpFriends.empty()) {
		std::cout << "û�к�������\n";
		Sleep(1000);
		return;
	}
	system("cls");
	std::cout << "\t�����б�\n";
	int index = 1, choice1 = 0, choice2 = 0;
	for (auto& item : tmpFriends)
		std::cout << index++ << "\t" << item.nickname << "(" << item.id << ")\t" << Friend::getEnumName(item) << std::endl;
	std::cout << "����ȴ������������Ž��д���\n";
	std::cin >> choice1;
	Friend tmp = tmpFriends[--choice1];
	while (tmp.status != wait) {
		std::cout << "����������\n";
		std::cin >> choice1;
		Friend tmp = tmpFriends[--choice1];
	}
	std::cout << "�Ƿ�ͬ�⣿\n\t��1������\n\t��2���ܾ�\n";
	std::cin >> choice2;
	if (choice2 == 1) {
		std::cout << "�����뱸ע\n";
		std::cin >> tmp.nickname;
		friends.push_back({ tmp.id, tmp.nickname, true, agree });
	}
	tmpFriends[choice1].status = choice2;
	//ͬʱҲӦ���޸ĶԷ��ĺ��������¼������˵����
	if (updateApplication(tmp.id, { currentUser->_id, tmp.nickname, false, choice2 }, 2 - choice2)) {
		saveFriends(currentUser->_id, friends);
		saveTmpFriends(currentUser->_id, tmpFriends);
	} else {
		std::cout << "���ʧ��" << std::endl;
		Sleep(1000);
	}
}

void QQSystem::friendMenu1()
{
	Friend* res = showFriends();
	Friend u = Friend(res);
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------------------\n";
	std::cout << "��ע��" << u.nickname << std::endl;
	std::cout << "�ǳƣ�" << getUsername(u.id) << std::endl;
	std::cout << "QQ�ţ�" << u.id << std::endl;
	std::cout << "---------------------------\n";
	std::cout << "\t��ѡ�����\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t��1���޸ı�ע\n";
	std::cout << "\t��2��ɾ������\n";
	std::cout << "\t��0������\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int select;
	std::cin >> select;
	switch (select) {
	case 1:
		updateFriend(&u);
		break;
	case 2:
		deleteFriend(u);
		break;
	default:
		friendMenu();
		break;
	}
	friendMenu1();
}

std::string QQSystem::getUsername(int user_id)
{
	auto it = utils::selectIterator(users, user_id, [](const User& u, int _id) {
		return _id == u._id;
		});
	return it->_user_name;
}


bool QQSystem::updateApplication(int id, Friend u, bool flag, bool kind)
{
	//�޸�����״̬
	std::vector<Friend> tmp = kind ? readTmpFriends(id) : readTmpGroups(id);
	if (tmp.empty()) return false;
	std::string nickname;
	for (auto& item : tmp) {
		if (item.id == u.id) {
			item.status = flag ? agree : reject;
			break;
		}
	}
	if(!(kind ? saveTmpFriends(id, tmp) : saveTmpGroups(id, tmp)))
		return false;
	//���
	if (u.status == reject || flag == false) return true;//���ܾ��Ͳ����
	return kind ? addFriend(id, u) : addGroup(id, u);
}





void QQSystem::addGroup(int user_id, int group_id)
{
	auto group = utils::selectTarget(allGroups, group_id, [](const QQGroup& item, int _id) {return _id == item.id; });
	assert(group != nullptr);
	std::cout << "������Ⱥ�ǳ�" << std::endl;
	std::string nickname;
	std::cin >> nickname;
	tmpGroups.push_back({ group_id, nickname });
	//ͬʱҲҪ����ӦȺ���������һ��
	Friend u = { user_id, nickname, true };
	if (addTmpGroup(group_id, u))
		if (saveTmpGroups(user_id, tmpGroups))
			std::cout << "�ɹ�������Ⱥ���룬�ȴ�����Ա���" << std::endl;
}

void QQSystem::deleteGroup(QQGroup& group)
{
	auto cmp = [](const Friend& item, int _id) {return _id == item.id; };
	//���ҵ�Ⱥ���ҵ�Ҫ�˳���Ⱥ
	auto it1 = utils::selectIterator(myGroups, group.id, cmp);
	//��Ⱥ��Ա���ҵ���
	auto it2 = utils::selectIterator(group.members, currentUser->_id, cmp);
	
	if (it1 != myGroups.end() && it2 != group.members.end()) {
		myGroups.erase(it1);
		group.members.erase(it2);
		saveGroups(currentUser->_id, myGroups);
		saveMembers(group.id, group.members);
	}
	else {
		std::cout << "�˳�ʧ��\n";
		Sleep(1000);
	}
}

void QQSystem::newGroup()
{
	auto group = showGroups();
	if (!group) return;
	std::cout << *group << std::endl;
	for (auto& member : group->members) {
		std::cout << member << std::endl;
	}
	auto g = utils::selectIterator(myGroups, group->id, [](const Friend& item, int _id) {return item.id == _id; });
	newGroup(group, g->admin);
}

QQGroup* QQSystem::showGroups()
{
	if (myGroups.empty()) return nullptr;
	system("cls");
	std::cout << currentUser->_user_name << "��Ⱥ�б�\n";
	int index = 1, choice = 0;
	for (auto& group : myGroups) {
		std::cout << index++  << "\t" << group.nickname << "(" << group.id << ")\n";
	}
	std::cout << "��0������\n�������ѡ��Ⱥ��\n";
	std::cin >> choice;
	assert(choice <= myGroups.size());
	auto& g = myGroups[--choice];
	//ͨ��id��ȡ��Ⱥ��Ϣ�ͳ�Ա
	auto group = utils::selectTarget(allGroups, g.id, [](const QQGroup& item, int _id) {return _id == item.id; });
	group->members = readMembers(g.id);
	return group;
}

void QQSystem::newGroup(QQGroup* group, int admin)
{
	std::vector<Friend> tmpMembers;
	if (admin) {
		std::cout << "���Ǹ�Ⱥ����Ա\n";
		tmpMembers = readTmpMembers(group->id);
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
	std::cout << "�Ƿ�ͬ����Ⱥ��\n\t��1����\t��2����\n";
	std::cin >> choice2;
	if (choice2 == 1) {
		if (admin == 2) {
			std::cout << "�Ƿ�����Ϊ����Ա��\n\t��1����\t��2����\n";
			std::cin >> choice3;
		}
		group->members.push_back({ tmp->id, tmp->nickname, true, agree, 2 - choice3 });
	}
	tmp->status = choice2;
	//ͬʱҲӦ���޸ĶԷ��������¼
	if (updateApplication(tmp->id, { currentUser->_id, tmp->nickname, false, choice2, choice3 }, 2 - choice2, false)) {
		saveMembers(group->id, group->members);
		saveTmpMembers(group->id, tmpMembers);
	}
	else std::cout << "���ʧ��" << std::endl;
}



void QQSystem::readGroups()
{
	allGroups = utils::readData<QQGroup>(utils::QQ, utils::groups, 3);
	/*for (auto& group : allGroups) {
		group.members = readMembers(group.id);
	}*/
}

std::vector<Friend> QQSystem::readTmpGroups(int user_id)
{
	return utils::readData<Friend>(utils::QQ, utils::users, 5, user_id);
}

std::vector<Friend> QQSystem::readMembers(int group_id)
{
	return utils::readData<Friend>(utils::QQ, utils::groups, 6, group_id);
}

std::vector<Friend> QQSystem::readTmpMembers(int group_id)
{
	return utils::readData<Friend>(utils::QQ, utils::groups, 7, group_id);
}

bool QQSystem::saveGroups() {
	return utils::saveData<QQGroup>(allGroups, utils::QQ, utils::groups, 3);
}

bool QQSystem::saveUsers()
{
	return utils::saveData<User>(users, utils::QQ, utils::users, 0);
}

bool QQSystem::saveGroups(int user_id, std::vector<Friend> myGroups)
{
	return utils::saveData<Friend>(myGroups, utils::QQ, utils::users, 4, user_id);
}

bool QQSystem::saveFriends(int user_id, std::vector<Friend> friends)
{
	return utils::saveData<Friend>(friends, utils::QQ, utils::users, 1, user_id);
}

bool QQSystem::saveTmpFriends(int user_id, std::vector<Friend> tmpFriends)
{
	return utils::saveData<Friend>(tmpFriends, utils::QQ, utils::users, 2, user_id);
}

bool QQSystem::saveTmpGroups(int user_id, std::vector<Friend> tmpGroups)
{
	return utils::saveData<Friend>(tmpGroups, utils::QQ, utils::users, 5, user_id);
}

bool QQSystem::saveMembers(int group_id, std::vector<Friend> members)
{
	return utils::saveData<Friend>(members, utils::QQ, utils::groups, 6, group_id);
}

bool QQSystem::saveTmpMembers(int group_id, std::vector<Friend> tmpMembers)
{
	return utils::saveData<Friend>(tmpMembers, utils::QQ, utils::groups, 7, group_id);
}



void QQSystem::setUser(User* user)
{
	currentUser = user;
}


void QQSystem::readUsers()
{
	users = utils::readData<User>(utils::QQ, utils::users, 0);
}

bool QQSystem::addFriend(int user_id, Friend newFriend)
{
	return utils::addObj(newFriend, utils::QQ, utils::users, 1, user_id);
}

bool QQSystem::addTmpFriend(int user_id, Friend newFriend)
{
	return utils::addObj(newFriend, utils::QQ, utils::users, 2, user_id);
}

bool QQSystem::addGroup(int user_id, Friend newGroup)
{
	return utils::addObj(newGroup, utils::QQ, utils::users, 4, user_id);
}

bool QQSystem::addTmpGroup(int user_id, Friend newGroup)
{
	return utils::addObj(newGroup, utils::QQ, utils::users, 7, user_id);
}

std::vector<Friend> QQSystem::readGroups(int user_id)
{
	return utils::readData<Friend>(utils::QQ, utils::users, 4, user_id);
}

std::vector<Friend> QQSystem::readFriends(int user_id)
{
	return utils::readData<Friend>(utils::QQ, utils::users, 1, user_id);
}

std::vector<Friend> QQSystem::readTmpFriends(int user_id)
{
	return utils::readData<Friend>(utils::QQ, utils::users, 2, user_id);
}
