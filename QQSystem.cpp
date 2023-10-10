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

void QQSystem::saveUsers()
{
	//相对路径  ./账号
	std::filesystem::path current_dir = std::filesystem::current_path();
	std::filesystem::path dir_path = current_dir / "flies";
	if (!std::filesystem::exists(dir_path))
		std::filesystem::create_directories(dir_path);
	std::ofstream file(dir_path / "QQUsers.txt", std::ios::out);
	if (file.is_open()) {
		for (const auto& user : users)
			file << user._id << " " << user._user_name << " " << user._password << std::endl;
		file.close();
	}
	else std::cerr << "无法打开文件进行写入: " << dir_path / "flies" / "QQUsers.txt" << std::endl;
}

void QQSystem::readUsers()
{
	//相对路径  ./账号
	std::filesystem::path current_dir = std::filesystem::current_path();
	std::filesystem::path dir_path = current_dir / "flies";
	if (!std::filesystem::exists(dir_path))
		std::filesystem::create_directories(dir_path);
	std::ifstream file(dir_path / "QQUsers.txt");
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			std::stringstream ss(line);
			QQUser tmp;
			ss >> tmp._id >> tmp._user_name >> tmp._password;
			users.push_back(tmp);
		}
		file.close();
	}
	else std::cerr << "无法打开文件进行读取: " << dir_path / "flies" / "QQUsers.txt" << std::endl;
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
	tmpFriends.push_back({ id, nickname});
	std::cout << "成功发送好友申请，等待对方同意" << std::endl;
}



void QQSystem::showFriend()
{
	std::cout << "好友列表" << std::endl;
	int index = 1, choice = 0;
	for (auto& user : friends) {
		std::cout << index++ << "\t" << user.nickname << std::endl;
	}
	std::cout << "输入序号查看详细信息" << std::endl;
	std::cin >> choice;
	assert(choice < friends.size());
	Friend tmp = friends[choice];
	auto user = selectUser(tmp.id);
	std::cout << tmp.nickname << "\t" << user->_user_name << std::endl;
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
		std::cout << index++ << "\t" << item.nickname << "\t" << getEnumName(item.status) << std::endl;
	std::cout << "输入序号进行处理" << std::endl;
	std::cin >> choice1;
	Friend tmp = tmpFriends[--choice1];
	std::cout << "1yes/2no" << std::endl;
	std::cin >> choice2;
	if (choice2 == 1) {
		std::string nickname;
		std::cout << "请输入备注" << std::endl;
		std::cin >> nickname;
		friends.push_back({ tmp.id, nickname, agree });
	}
	tmpFriends[choice1].status == choice2;
	//同时也应该修改对方的好友申请记录，或者说更改
	updateApplication(tmp.id, { currentUser->_id, tmp.nickname, choice2 });
	
}

void QQSystem::readFriends()
{
	//相对路径  ./账号
	std::filesystem::path current_dir = std::filesystem::current_path();
	std::filesystem::path dir_path = current_dir / "flies" / std::to_string(currentUser->_id);
	try {
		if (!std::filesystem::exists(dir_path)) {
			std::filesystem::create_directories(dir_path);
			std::cout << "成功创建目录" << std::endl;
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "创建失败： " << e.what() << std::endl;
	}
	for (int i = 0; i < 2; ++i) {
		std::string filename = i ? "friends.txt" : "tmpFriends.txt";
		std::ifstream file(dir_path / filename);
		if (file.is_open()) {
			std::string line;
			while (getline(file, line)) {
				std::stringstream ss(line);
				Friend tmp;
				ss >> tmp.id >> tmp.nickname >> tmp.status;
				i ? friends.push_back(tmp) : tmpFriends.push_back(tmp);
			}
			file.close();
		}
		else std::cerr << "无法打开文件进行读取: " << dir_path / "flies" / "friends.txt" << std::endl;
	}
}

void QQSystem::saveFriends()
{
	//相对路径  ./账号
	std::filesystem::path current_dir = std::filesystem::current_path();
	std::filesystem::path dir_path = current_dir / "flies" / std::to_string(currentUser->_id);
	if (!std::filesystem::exists(dir_path))
		std::filesystem::create_directories(dir_path);
	for (int i = 0; i < 2; ++i) {
		std::string filename = i ? "friends.txt" : "tmpFriends.txt";
		std::ofstream file(dir_path / filename, std::ios::out);
		if (file.is_open()) {
			auto& tmp = i ? friends : tmpFriends;
			for (const auto& item :tmp)
				file << item.id << " " << item.nickname << " " << item.status << std::endl;
			file.close();
		}
		else std::cerr << "无法打开文件进行写入: " << dir_path / "flies" / filename << std::endl;
	}
}

void QQSystem::updateApplication(int id, Friend u)
{
	std::filesystem::path current_dir = std::filesystem::current_path();
	std::filesystem::path dir_path = current_dir / "flies" / std::to_string(id);
	if (!std::filesystem::exists(dir_path))
		std::filesystem::create_directories(dir_path);
	//修改好友申请状态
	std::vector<Friend> tmp;
	std::ifstream fin(dir_path / "tmpFriends.txt");
	if (fin.fail()) std::ofstream outfile(dir_path / "tmpFriends.txt");
	if (fin.is_open()) {
		std::string line;
		while (getline(fin, line)) {
			Friend i;
			std::stringstream ss(line);
			ss >> i.id >> i.nickname >> i.status;
			if (i.id == u.id)
				i.status = agree;
			tmp.push_back(i);
		}
		fin.close();
	}
	else std::cerr << "无法打开文件进行读取: " << dir_path / "flies" / "tmpFriends.txt" << std::endl;

	std::ofstream fout(dir_path / "tmpFriends.txt", std::ios::out);
	if (fout.is_open()) {
		for (const auto& i : tmp)
			fout << i.id << " " << i.nickname << " " << i.status << std::endl;
		fout.close();
	}
	else std::cerr << "无法打开文件进行写入: " << dir_path / "flies" / "tmpFriends.txt" << std::endl;
	//添加好友
	if (u.status == reject) return;//被拒绝就不添加
	std::ofstream file(dir_path / "friends.txt", std::ios::app);
	if (file.is_open()) {
		file << u.id << " " << u.nickname << " " << u.status << std::endl;
		file.close();
	}
	else std::cerr << "无法打开文件进行写入: " << dir_path / "flies" / "tmpFriends.txt" << std::endl;
}



std::string QQSystem::getEnumName(int a)
{
	if (a == wait) return "等待同意";
	if (a == reject) return "已被拒绝";
	return "已同意";
}
