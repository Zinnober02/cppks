#include "WeiBoSystem.h"



WeiBoSystem::WeiBoSystem()
{
	readUsers();
}

void WeiBoSystem::showMenu()
{
	User* user = new User(1, "1", "����");
	currentUser = user;
	init();
	allBlogs.push_back({ "΢��1", "����", 1, { 2, 3, 5, 6 } });
	allBlogs.push_back({ "΢��2", "����", 1, { 3, 5, 6 } });
	allBlogs.push_back({ "΢��3", "����", 1, { 2, 5, 6 , 7, 8} });
	allBlogs.push_back({ "΢��4", "����", 1, { 3, 6 } });
	allBlogs.push_back({ "΢��5", "����", 1});
	allBlogs.push_back({ "΢��6", "����", 1, { 2, 3, 5, 6, 7, 8, 4 } });
	allBlogs.push_back({ "΢��7", "����", 1, { 2, 3, 5, 6 } });
	saveBlogs();
	showBlog();
	//addBlog();
	detail();
}

void WeiBoSystem::readUsers()
{
	users = utils::readData<User>(utils::WeiBo, utils::null, 0);
}

void WeiBoSystem::init()
{
	readAllBlogs();
}

bool WeiBoSystem::saveUsers()
{
	return utils::saveData<User>(users, utils::WeiBo, utils::null, 0);
}

void WeiBoSystem::addBlog()
{
	auto newBlog = blog();
	std::cout << "��������⣺\n";
	std::cin >> newBlog.title;
	std::cout << "���������ݣ�\n";
	std::cin >> newBlog.content;
	newBlog.author_id = this->currentUser->_id;

	allBlogs.push_back(newBlog);
}

void WeiBoSystem::addCommit()
{
	std::cout << "0���ۣ�����id�ظ�\n";
	int choice = 0;
	std::cin >> choice;
	auto newCommit = commit(currentBlog->id, currentUser->_id, choice);
	std::cout << "����������\n";
	std::cin >> newCommit.content;
	allCommits.push_back(newCommit);
	saveCommits();
}



bool WeiBoSystem::showBlog(User* user)
{
	if (allBlogs.empty()) {
		return false;
	}
	system("cls");
	sort(allBlogs.begin(), allBlogs.end(), [](const blog& a, const blog& b) {
		return a.date > b.date;
		});
	if (!user) {
		std::cout << "΢����" << std::endl;
		for (auto& b : allBlogs)
			std::cout << b << std::endl;
	}
	else {
		std::cout << user->_user_name + "��΢����" << std::endl;
		for (auto& b : allBlogs)
			if (b.author_id == user->_id)
				std::cout << b << std::endl;
	}
	return true;
}


blog* WeiBoSystem::selectBlog()
{
	if (!showBlog()) return nullptr;

	std::cout << "ѡ��0���ȶ�\n��Ų鿴����\n-1����\n";
	int choice1, choice2;
	std::cin >> choice1;
	switch (choice1) {
		case 0: {
			sort(allBlogs.begin(), allBlogs.end(), [](const blog& a, const blog& b) {
				return a.likes.size() > b.likes.size();
				});
			showBlog();
			std::cout << "������Ų鿴��ϸ��Ϣ" << std::endl;
			std::cin >> choice2;
			break;
		}
		case -1: return nullptr;
		default: choice2 = choice1; break;
	}
	assert(choice2 <= allBlogs.size());
	auto& b = allBlogs[--choice2];
	return &b;
}

bool WeiBoSystem::detail()
{
	auto& b = *(selectBlog());
	printBlog(b);
	auto c = readCommits(b.id);
	for (auto& i : c) {
		std::cout << i.user_id << ":" << i.content << "\t" << i.date << std::endl;
	}
	std::cout << "1���� 2���� 3ת��\n";
	int choice;
	std::cin >> choice;
	switch (choice) {
		case 1: {
			like(b); 
			printBlog(b); 
			break;
		}
		case 2: addCommit(); break;
		case 3: break;
	}
	return saveBlogs();
}

//bool WeiBoSystem::updateBlog()
//{
//	auto b = selectBlog();
//
//}

void WeiBoSystem::like(blog& b)
{
	int id = currentUser->_id;
	auto it = b.likes.find(id);
	if (it != b.likes.end()) {
		b.likes.erase(it);
		std::cout << "ȡ������\n";
	}
	else {
		b.likes.emplace(id);
		std::cout << "���޳ɹ�\n";
	}
}

void WeiBoSystem::printBlog(blog& b)
{
	system("cls");
	std::cout << b.title << "\t" << b.date << std::endl;
	std::cout << b.content << std::endl;
	std::cout << b.likes.size();
	std::cout << "-----------------\n";
}

bool WeiBoSystem::saveCommits()
{
	return utils::saveData<commit>(allCommits, utils::WeiBo, utils::null, 9);
}



bool WeiBoSystem::saveBlogs()
{
	return utils::saveData<blog>(allBlogs, utils::WeiBo, utils::null, 8);
}

bool WeiBoSystem::readAllBlogs()
{
	allBlogs = utils::readData<blog>(utils::WeiBo, utils::null, 8);
	return !allBlogs.empty();
}

std::vector<commit> WeiBoSystem::readCommits(int blog_id)
{
	return utils::readData<commit>(utils::WeiBo, utils::null, 9);
}
