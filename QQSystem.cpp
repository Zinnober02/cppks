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
	tmpFriends.push_back({ id, nickname});
	std::cout << "�ɹ����ͺ������룬�ȴ��Է�ͬ��" << std::endl;
}



void QQSystem::showFriend()
{
	std::cout << "�����б�" << std::endl;
	int index = 1, choice = 0;
	for (auto& user : friends) {
		std::cout << index++ << "\t" << user.nickname << std::endl;
	}
	std::cout << "������Ų鿴��ϸ��Ϣ" << std::endl;
	std::cin >> choice;
	assert(choice < friends.size());
	Friend tmp = friends[choice];
	auto user = selectUser(tmp.id);
	std::cout << tmp.nickname << "\t" << user->_user_name << std::endl;
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
	for (auto& item : tmpFriends) {
		std::cout << index++ << "\t" << item.nickname << "\t" << getEnumName(item.status) << std::endl;
	}
	std::cout << "������Ž��д���" << std::endl;
	std::cin >> choice1;
	Friend tmp = tmpFriends[--choice1];
	std::cout << "1yes/2no" << std::endl;
	std::cin >> choice2;
	if (choice2 == 1) {
		std::string nickname;
		std::cout << "�����뱸ע" << std::endl;
		std::cin >> nickname;
		friends.push_back({ tmp.id, nickname, agree });
	}
	tmpFriends[choice1].status == choice2;
	//ͬʱҲӦ���޸ĶԷ��ĺ��������¼������˵����
	updateApplication(tmp.id, { currentUser->_id, tmp.nickname, choice2 });
	
}

void QQSystem::readFriend(std::string filename)
{
	//���·��  ./�˺�
	std::filesystem::path current_dir = std::filesystem::current_path();
	std::filesystem::path dir_path = current_dir / std::to_string(currentUser->_id);
	if (!std::filesystem::exists(dir_path)) {
		std::filesystem::create_directory(dir_path);
	}
	std::ifstream file(dir_path / filename);
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			std::stringstream ss(line);
			Friend tmp;
			ss >> tmp.id >> tmp.nickname >> tmp.status;
			friends.push_back(tmp);
		}
		file.close();
	}
	else std::cerr << "�޷����ļ����ж�ȡ: " << dir_path / "friends.txt" << std::endl;
}

void QQSystem::saveFriends(std::string filename)
{
	//���·��  ./�˺�
	std::filesystem::path current_dir = std::filesystem::current_path();
	std::filesystem::path dir_path = current_dir / std::to_string(currentUser->_id);
	if (!std::filesystem::exists(dir_path)) {
		std::filesystem::create_directory(dir_path);
	}
    //���� friends
	std::ofstream file(dir_path / filename, std::ios::out);
	if (file.is_open()) {
		for (auto& item : friends)
			file <<  item.id << " " << item.nickname << " " << item.status << std::endl;
		file.close();
	}
	else std::cerr << "�޷����ļ�����д��: " << dir_path / filename << std::endl;
	
}

void QQSystem::updateApplication(int id, Friend u)
{
	std::filesystem::path current_dir = std::filesystem::current_path();
	std::filesystem::path dir_path = current_dir / std::to_string(id);
	if (!std::filesystem::exists(dir_path)) {
		std::filesystem::create_directory(dir_path);
	}
	//�޸ĺ�������״̬
	std::vector<Friend> tmp;
	std::ifstream fin(dir_path / "tmpFriends.txt");
	if (fin.is_open()) {
		std::string line;
		while (getline(fin, line)) {
			Friend i;
			std::stringstream ss(line);
			ss >> i.id >> i.nickname >> i.status;
			if (i.id == id)
				i.status == agree;
			tmp.push_back(i);
		}
		fin.close();
	}
	else std::cerr << "�޷����ļ����ж�ȡ: " << dir_path / "tmpFriends.txt" << std::endl;

	std::ofstream fout(dir_path / "tmpFriends.txt", std::ios::out);
	if (fout.is_open()) {
		for (const auto& i : tmp)
			fout << i.id << " " << i.nickname << " " << i.status << std::endl;
		fout.close();
	}
	else std::cerr << "�޷����ļ�����д��: " << dir_path / "tmpFriends.txt" << std::endl;
	//���Ӻ���
	if (u.status == reject) return;//���ܾ��Ͳ�����
	std::ofstream file(dir_path / "friends.txt", std::ios::app);
	if (file.is_open()) {
		file << u.id << " " << u.nickname << " " << u.status << std::endl;
		file.close();
	}
	else std::cerr << "�޷����ļ�����д��: " << dir_path / "tmpFriends.txt" << std::endl;
}



std::string QQSystem::getEnumName(int a)
{
	if (a == wait) return "�ȴ�ͬ��";
	if (a == reject) return "�ѱ��ܾ�";
	return "��ͬ��";
}