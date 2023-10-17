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
	std::cout << "--------------欢迎使用QQ----------------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t你的QQ号为:" << currentUser->_id << std::endl;
	std::cout << "\t请选择使用的功能\n";
	std::cout << "\t【1】好友管理\n";
	std::cout << "\t【2】群管理\n";
	std::cout << "\t【3】个人资料\n";
	std::cout << "\t【4】开通服务\n";
	std::cout << "\t【0】切换账号\n";
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
	case 0: showMenu(); break;
	default: menu1(); break;
	}
	menu1();
}

void QQSystem::friendMenu()
{
	system("cls");
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------请选择好友操作----------------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】添加好友\n";
	std::cout << "\t【2】好友列表\n";
	std::cout << "\t【3】查看好友申请\n";
	std::cout << "\t【4】推荐好友\n";
	std::cout << "\t【0】返回\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int select;
	std::cin >> select;
	switch (select) {
	case 1: {
		std::cout << "请输入QQ号" << std::endl;
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
	std::cout << "------------------请选择群操作----------------\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】加入QQ群\n";
	std::cout << "\t【2】创建QQ群\n";
	std::cout << "\t【3】群列表\n";
	std::cout << "\t【4】加入临时讨论组\n";
	std::cout << "\t【0】返回\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------------------------------------------\n" ;
	rgbSet(255, 255, 255, 0, 0, 0);
	std::cout << "请输入您的选择\n";
	int select;
	std::cin >> select;
	switch (select) {
	case 1: {
		int id;
		std::cout << "请输入群号：";
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
	std::cout << "共有" << g.members.size() + 1 << "人\n";
	int num = 1; int flag = 0;
	if (g.owner.id == currentUser->_id) flag = 2;
	std::cout << num++ << "\t群主：" << g.owner.nickname << "(" << g.owner.id << ")\n";
	if (g.members.size()) {
		sort(g.members.begin(), g.members.end(), [](const Friend& a, const Friend& b) {
			return a.admin > b.admin; 
			});
		std::cout << "群成员：\n";
		for (auto& member : g.members) {
			if (member.id == currentUser->_id && member.admin) flag = member.admin;
			std::cout << num++ << "\t" << Friend::getAdmin(member) << "："
				<< member.nickname << "(" << member.id << ")\n";
		}
	}
	std::cout << "---------------------------\n";
	std::cout << "\t请选择操作\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】修改群昵称\n";
	std::cout << "\t【2】退出群聊\n";
	std::cout << "\t【3】邀请入群\n";
	std::cout << "\t【4】添加好友\n";
	if (flag)
		std::cout << "\t【5】群申请\n";
	std::cout << "\t【0】返回\n";
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
			std::cout << "群昵称：" << g.owner.nickname << "\n输入新昵称：";
			std::cin >> group->owner.nickname;
			saveGroups();
		}
		else {
			auto it1 = utils::selectIterator(g.members, currentUser->_id, cmp);
			if (it1 == g.members.end()) break;
			std::cout << "群昵称：" << it1->nickname << "\n输入新昵称：";
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
		std::cout << "输入要添加的成员编号：";
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

void QQSystem::addFriend(int id)
{
	auto user = selectUser(id);
	assert(user != nullptr);
	std::cout << "请输入备注" << std::endl;
	std::string nickname;
	std::cin >> nickname;
	tmpFriends.push_back({ id, nickname });
	//同时也要给对方的好友申请添加一个
	Friend u = { currentUser->_id, nickname, true };
	if (addFriend(id, u))
		if (saveFriends(currentUser->_id, tmpFriends)) {
			std::cout << "成功发送好友申请，等待对方同意" << std::endl;
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
	//对方的好友也要删除
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
	std::cout << "无法删除\n";
	Sleep(1000);
	return false;
}


Friend* QQSystem::showFriends()
{
	if (friends.empty()) {
		std::cout << "没有好友\n";
		Sleep(1000);
		return nullptr;
	}
	system("cls");
	std::cout << "\t好友列表\n--------------------------\n";
	int index = 1, choice = 0;
	for (auto& user : friends) {
		std::cout << index++ << "\t" << user.nickname <<"(" << user.id << ")\n";
	}
	std::cout << "选择好友：";
	std::cin >> choice;
	assert(choice <= friends.size());
	Friend tmp = friends[--choice];
	return &tmp;
}

bool QQSystem::updateFriend(Friend* u)
{
	std::cout << "请输入新备注\n";
	std::string nickname;
	std::cin >> nickname;
	auto item = utils::selectTarget(friends, u->id, [](const Friend& item, int _id) {return _id == item.id;});
	item->nickname = nickname;
	return saveFriends(currentUser->_id, friends);
}

void QQSystem::newFriend()
{
	if (tmpFriends.empty()) {
		std::cout << "没有好友申请\n";
		Sleep(1000);
		return;
	}
	system("cls");
	std::cout << "\t申请列表\n";
	int index = 1, choice1 = 0, choice2 = 0;
	for (auto& item : tmpFriends)
		std::cout << index++ << "\t" << item.nickname << "(" << item.id << ")\t" << Friend::getEnumName(item) << std::endl;
	std::cout << "输入等待申请的申请序号进行处理\n";
	std::cin >> choice1;
	Friend tmp = tmpFriends[--choice1];
	while (tmp.status != wait) {
		std::cout << "请重新输入\n";
		std::cin >> choice1;
		Friend tmp = tmpFriends[--choice1];
	}
	std::cout << "是否同意？\n\t【1】接受\n\t【2】拒绝\n";
	std::cin >> choice2;
	if (choice2 == 1) {
		std::cout << "请输入备注\n";
		std::cin >> tmp.nickname;
		friends.push_back({ tmp.id, tmp.nickname, true, agree });
	}
	tmpFriends[choice1].status = choice2;
	//同时也应该修改对方的好友申请记录，或者说更改
	if (updateApplication(tmp.id, { currentUser->_id, tmp.nickname, false, choice2 }, 2 - choice2)) {
		saveFriends(currentUser->_id, friends);
		saveTmpFriends(currentUser->_id, tmpFriends);
	} else {
		std::cout << "添加失败" << std::endl;
		Sleep(1000);
	}
}

void QQSystem::friendMenu1()
{
	Friend* res = showFriends();
	Friend u = Friend(res);
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "---------------------------\n";
	std::cout << "备注：" << u.nickname << std::endl;
	std::cout << "昵称：" << getUsername(u.id) << std::endl;
	std::cout << "QQ号：" << u.id << std::endl;
	std::cout << "---------------------------\n";
	std::cout << "\t请选择操作\n";
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】修改备注\n";
	std::cout << "\t【2】删除好友\n";
	std::cout << "\t【0】返回\n";
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





void QQSystem::addGroup(int user_id, int group_id)
{
	auto group = utils::selectTarget(allGroups, group_id, [](const QQGroup& item, int _id) {return _id == item.id; });
	assert(group != nullptr);
	std::cout << "请输入群昵称" << std::endl;
	std::string nickname;
	std::cin >> nickname;
	tmpGroups.push_back({ group_id, nickname });
	//同时也要给对应群的申请添加一个
	Friend u = { user_id, nickname, true };
	if (addTmpGroup(group_id, u))
		if (saveTmpGroups(user_id, tmpGroups))
			std::cout << "成功发送入群申请，等待管理员审核" << std::endl;
}

void QQSystem::deleteGroup(QQGroup& group)
{
	auto cmp = [](const Friend& item, int _id) {return _id == item.id; };
	//在我的群中找到要退出的群
	auto it1 = utils::selectIterator(myGroups, group.id, cmp);
	//在群成员中找到我
	auto it2 = utils::selectIterator(group.members, currentUser->_id, cmp);
	
	if (it1 != myGroups.end() && it2 != group.members.end()) {
		myGroups.erase(it1);
		group.members.erase(it2);
		saveGroups(currentUser->_id, myGroups);
		saveMembers(group.id, group.members);
	}
	else {
		std::cout << "退出失败\n";
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
	std::cout << currentUser->_user_name << "的群列表\n";
	int index = 1, choice = 0;
	for (auto& group : myGroups) {
		std::cout << index++  << "\t" << group.nickname << "(" << group.id << ")\n";
	}
	std::cout << "【0】返回\n输入序号选择群：\n";
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
	std::cout << "是否同意入群？\n\t【1】是\t【2】否\n";
	std::cin >> choice2;
	if (choice2 == 1) {
		if (admin == 2) {
			std::cout << "是否设置为管理员？\n\t【1】是\t【2】否\n";
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
