#include "QQSystem.h"

QQSystem::QQSystem() {
	readUsers();
}


bool QQSystem::login()
{
	system("cls");
	int ID;
	std::string PassWord;
	std::cout << "输入要登陆的QQ:" << std::endl;
	std::cin >> ID;
	auto it = utils::selectIterator(users, ID, [](const User& u, int _id) {
		return u._id == _id;
		});
	if (it == users.end()) {
		std::cout << "未查询到该QQ号，请先申请，按任意键返回" << std::endl;
		if (getchar() != EOF)
			return false;
	}
	std::cout << "请输入该QQ的密码" << std::endl;
	std::cin >> PassWord;
	// [表情]fe_flush(stdin);
	while (PassWord != it->_password) {
		std::cout << "密码输入错误,请重新输入密码" << std::endl;
		std::cin >> PassWord;
	}
	rgbSet(124, 252, 0, 0, 0, 0);
	std::cout << "登陆成功，按任意键开始使用QQ" << std::endl;
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
	//User* user = new User(1, "1", "李智");
	//setUser(user);
	system("cls");
	int select, key = 1;
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------欢迎使用QQ-----------" << std::endl;
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】登录\n";
	std::cout << "\t【2】注册\n";
	std::cout << "\t【0】退出系统\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "--------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	std::cout << "请输入您的的选择:\n";
	int choice;
	//更新
	std::cin >> choice;
	switch (choice) {
		case 1:login() ? menu1() : showMenu(); break;
		case 2:createUser(); showMenu(); break;
		case 0:exit(0); break;
	}
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
	std::cout << "--------------欢迎使用QQ----------------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t你的QQ号为:" << currentUser->_id << std::endl;
	std::cout << "\t请选择使用的功能\n";
	std::cout << "\t【1】好友管理\n";
	std::cout << "\t【2】群管理\n";
	std::cout << "\t【3】个人资料\n";
	std::cout << "\t【4】开通服务\n";
	std::cout << "\t【0】返回主菜单\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	std::cout << "请输入你的选择\n";
	std::cin >> select;
	switch (select) {
	case 1: friendMenu(); break;
	case 2: groupMenu(); break;
	case 3: selfMenu(); break;
	case 4: serviceMenu(); break;
	case 0: menu1(); break;
	default: showMenu(); break;
	}
}

void QQSystem::friendMenu()
{
	system("cls");
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------请选择好友操作----------------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】添加好友\n";
	std::cout << "\t【2】显示所有好友\n";
	std::cout << "\t【3】删除好友\n";
	std::cout << "\t【4】查看好友申请\n";
	std::cout << "\t【5】查看好友资料\n";
	std::cout << "\t【6】修改好友备注\n";
	std::cout << "\t【7】查看微信共同好友\n";
	std::cout << "\t【8】添加微信共同好友\n";
	std::cout << "\t【0】返回QQ主菜单\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int select;
	std::cin >> select;
	switch (select) {
	case 1:
		addFriend();
		break;
	case 2:
		showFriend();
		break;
	case 3:
		deleteFriend();
		break;
	case 4:
		newFriend();
		break;
	case 5:
		//ShowFriendInformation();
		break;
	case 6:
		//ChangeFriendRemarks();
		break;
	case 7:
		//ShowWeChatCommonFriends();
		break;
	case 8:
		//AddWeChatCommonFriend();
		break;
	case 0:
		menu1();
		return;
	default:
		showMenu();
		return;
	}
}

void QQSystem::groupMenu()
{
	system("cls");
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "------------------请选择群操作----------------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】加入QQ群\n";
	std::cout << "\t【2】退出QQ群\n";
	std::cout << "\t【3】创建QQ群\n";
	std::cout << "\t【4】查看已加入的QQ群\n";
	std::cout << "\t【5】查看入群申请\n";
	std::cout << "\t【6】添加QQ群管理员\n";
	std::cout << "\t【7】踢出群成员\n"; 
	std::cout << "\t【8】查看群成员信息\n"; 
	std::cout << "\t【9】创建临时讨论组\n";
	std::cout << "\t【10】加入临时讨论组\n";
	std::cout << "\t【11】邀请好友进群\n";
	std::cout << "\t【0】返回\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------------------------------------------\n" ;
	rgbSet(255, 255, 255, 0, 0, 0);
	std::cout << "请输入您的选择\n";
	int select;
	std::cin >> select;
	switch (select) {
	case 1:
		addGroup();
		break;
	case 2:
		deleteGroup();
		break;
	case 3:
		//createGroup();
		break;
	case 4:
		showGroup();
		break;
	case 5:
		newGroup();
		break;
	case 6:
		//ChangeFriendRemarks();
		break;
	case 7:
		//ShowWeChatCommonFriends();
		break;
	case 8:
		//AddWeChatCommonFriend();
		break;
	case 0:
		menu1();
		return;
	default:
		showMenu();
		return;
	}
}

void QQSystem::selfMenu()
{
	system("cls");
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "-------请选择所需的资料功能-------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】查看个人资料\n";
	std::cout << "\t【2】修改密码\n";
	std::cout << "\t【3】修改名称\n";
	std::cout << "\t【4】修改签名\n";
	std::cout << "\t【5】修改所在地\n";
	std::cout << "\t【0】返回上一级菜单\n";
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
	std::cout << "----------请选择服务----------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】开通微博\n";
	std::cout << "\t【2】绑定微信\n";
	std::cout << "\t【0】返回上一级\n";
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
	if (addFriend(id, u))
		if (saveFriends(currentUser->_id, tmpFriends))
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
	//auto targetFriends = utils::readData<Friend>(1, 1, id);
	auto targetFriends = readFriends(id);
	auto it2 = utils::selectIterator(targetFriends, id, cmp);
	if (it1 != friends.end() && it2 != targetFriends.end()) {
		friends.erase(it1);
		targetFriends.erase(it2);
		saveFriends(currentUser->_id, friends);
		saveFriends(id, targetFriends);
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
	saveFriends(currentUser->_id, friends);
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
		saveFriends(currentUser->_id, friends);
		saveTmpFriends(currentUser->_id, tmpFriends);
	}
	else std::cout << "添加失败" << std::endl;
}


bool QQSystem::updateApplication(int id, Friend u, bool flag, bool kind)
{
	//修改申请状态
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
	//添加
	if (u.status == reject || flag == false) return true;//被拒绝就不添加
	return kind ? addFriend(id, u) : addGroup(id, u);
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
	if (addTmpGroup(id, u))
		if (saveTmpGroups(currentUser->_id, tmpGroups))
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
	group->members = readMembers(it1->id);
	
	//在要退出的群成员中找到我
	auto it2 = utils::selectIterator(group->members, currentUser->_id, [](const Friend& item, int _id) {return _id == item.id; });
	
	if (it1 != myGroups.end() && it2 != group->members.end()) {
		myGroups.erase(it1);
		group->members.erase(it2);
		saveGroups(currentUser->_id, myGroups);
		saveMembers(group->id, group->members);
	}
	else std::cout << "退出失败\n";
}

void QQSystem::newGroup()
{
	auto group = showGroup();
	if (!group) return;
	std::cout << *group << std::endl;
	for (auto& member : group->members) {
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
	auto& g = myGroups[--choice];
	//通过id读取该群信息和成员
	auto group = utils::selectTarget(allGroups, g.id, [](const QQGroup& item, int _id) {return _id == item.id; });
	group->members = readMembers(g.id);
	return group;
}

void QQSystem::newGroup(QQGroup* group, int admin)
{
	std::vector<Friend> tmpMembers;
	if (admin) {
		std::cout << "你是该群管理员\n";
		tmpMembers = readTmpMembers(group->id);
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
		saveMembers(group->id, group->members);
		saveTmpMembers(group->id, tmpMembers);
	}
	else std::cout << "添加失败" << std::endl;
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
