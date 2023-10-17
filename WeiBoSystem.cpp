#include "WeiBoSystem.h"



WeiBoSystem::WeiBoSystem()
{
	readUsers();
}

void WeiBoSystem::showMenu()
{
	system("cls");
	int select, key = 1;
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------��ӭʹ��΢��-----------" << std::endl;
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t��1����¼\n";
	std::cout << "\t��2��ע��\n";
	std::cout << "\t��0���˳�\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "--------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int choice;
	std::cout << "���������ĵ�ѡ��:\n";
	std::cin >> choice;
	switch (choice) {
	case 1: {
		if (login())
			//showBlog(); 
			menu1();
		showMenu();
		break;
	}
	case 2:createUser(); showMenu(); break;
	case 0:exit(0); break;
	}
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

bool WeiBoSystem::login()
{
	system("cls");
	int ID;
	std::string PassWord;
	std::cout << "����Ҫ��½��΢��:" << std::endl;
	std::cin >> ID;
	auto it = utils::selectIterator(users, ID, [](const User& u, int _id) {
		return u._id == _id;
		});
	if (it == users.end()) {
		std::cout << "δ��ѯ����΢���ţ��������룬�����������" << std::endl;
		if (getchar() != EOF)
			return false;
	}
	std::cout << "����������" << std::endl;
	std::cin >> PassWord;
	while (PassWord != it->_password) {
		std::cout << "�����������,��������������" << std::endl;
		std::cin >> PassWord;
	}
	rgbSet(124, 252, 0, 0, 0, 0);
	std::cout << "��½�ɹ������������ʼʹ��΢��" << std::endl;
	rgbSet(255, 255, 255, 0, 0, 0);
	currentUser = &*it;
	init();
	if (getchar() != EOF)
		return true;
}

void WeiBoSystem::createUser()
{
}

std::string WeiBoSystem::getUsername(int id)
{
	auto it = utils::selectIterator(users, id, [](const User& u, int _id) {
		return _id == u._id;
		});
	return it->_user_name;
}

void WeiBoSystem::menu1()
{
	system("cls");
	int select, key = 1;
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "----------��ӭʹ��΢��-----------" << std::endl;
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t��1������\n";
	std::cout << "\t��2������΢��\n";
	std::cout << "\t��3������΢��\n";
	std::cout << "\t��0���˳�\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "--------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int choice;
	std::cout << "���������ĵ�ѡ��:\n";
	std::cin >> choice;
	switch (choice) {
	case 1: {
		auto& b = *(selectBlog());
		detail(b);
		break;
	}
	case 2:addBlog(); break;
	case 3: {
		system("cls");
		std::cout << "�������û���\n";
		std::string name;
		getchar();
		getline(std::cin, name);
		auto it = utils::selectIterator(users, name, [](const User& u, std::string _name) {
			return u._user_name == _name;
			});
		if (it == users.end()) {
			std::cout << "�û�������\n";
		}
		else {
			showBlog(&*it);
			auto& b = *selectBlog();
			detail(b);
		}
		menu1();
		break;
	}
	case 0:exit(0); break;
	}
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

void WeiBoSystem::addCommit(int blog_id)
{
	std::cout << "��0�����ۣ�����id�ظ�:";
	int choice = 0;
	std::cin >> choice;
	std::string content;
	std::cout << "���������ݣ�\n";
	do {
		getchar();
		getline(std::cin, content);
	} while (content.empty());
	allCommits.push_back({ blog_id, currentUser->_id, choice, content });
	saveCommits();
}



bool WeiBoSystem::showBlog(User* user)
{
	if (allBlogs.empty()) return false;
	sort(allBlogs.begin(), allBlogs.end(), [](const blog& a, const blog& b) {
		return a.date > b.date;
		});
	system("cls");
	rgbSet(227, 23, 13, 0, 0, 0);//��ɫ
	if (user)
		std::cout << "\t�û�" << currentUser->_user_name << "��΢��\n";
	else std::cout << "\t\t\t΢����\n";
	int n = 1;
	rgbSet(30, 144, 255, 0, 0, 0);//ǳ��
	std::cout << "---------------------------------------------------------------\n";
	for (auto& b : allBlogs)
		printBlog(b);
	return true;
}


blog* WeiBoSystem::selectBlog()
{
	int select;
	std::cout << "ѡ�\n\t��0�����ȶ�\n\t��-1������\n\t����š��鿴����\n";
	int choice1, choice2;
	std::cin >> choice1;
	switch (choice1) {
	case 0: {
		sort(allBlogs.begin(), allBlogs.end(), [](const blog& a, const blog& b) {
			return a.likes.size() > b.likes.size();
			});
		showBlog();
		std::cout << "�����Ų鿴���飬0�˳�" << std::endl;
		std::cin >> choice2;
		break;
	}
	case -1: return nullptr;
	default: choice2 = choice1; break;
	}
	if (choice2 == 0) return nullptr;
	assert(choice2 <= allBlogs.size());
	auto b = utils::selectIterator(allBlogs, choice2, [](const blog& b, int _id) {return _id == b.id; });
	return &*b;
}

bool WeiBoSystem::detail(blog& b)
{
	if (!&b) return false;
	system("cls");
	rgbSet(30, 144, 255, 0, 0, 0);//ǳ��
	std::cout << "---------------------------------------------------------------\n";
	rgbSet(255, 215, 0, 0, 0, 0);//��ɫ
	printBlog(b);

	auto c = readCommits(b.id);
	for (auto& i : c) {
		std::cout << i.user_id << ":" << i.content << "\t" << i.date << std::endl;
	}
	std::cout << "\t��1������\n\t��2������\n\t��3��ת��\n\t��0������\n";
	int choice; bool flag = true;
	while (flag) {
		std::cin >> choice;
		switch (choice) {
		case 1: {
			like(b);
			system("cls");
			rgbSet(30, 144, 255, 0, 0, 0);//ǳ��
			std::cout << "---------------------------------------------------------------\n";
			rgbSet(255, 215, 0, 0, 0, 0);//��ɫ
			printBlog(b);
			std::cout << "\t��1������\n\t��2������\n\t��3��ת��\n\t��0������\n";
			break;
		}
		case 2: addCommit(b.id); break;
		case 3: break;
		case 0: flag = false; break;
		}
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
	Sleep(1000);
}

void WeiBoSystem::printBlog(blog& b)
{
	rgbSet(255, 215, 0, 0, 0, 0);//��ɫ
	std::cout << "����: " << getUsername(b.author_id) << "(" << b.author_id << ")\n";
	rgbSet(135, 206, 235, 0, 0, 0);//��ɫ
	std::cout << "΢������: " << b.title << "\t���" << b.id << std::endl;
	rgbSet(124, 252, 0, 0, 0, 0);//��ɫ
	std::cout << "����ʱ��: " << b.date.year() << "��" << static_cast<unsigned>(b.date.month())
		<< "��" << b.date.day() << "��" << "\t" << b.likes.size() << "��\n";
	rgbSet(30, 144, 255, 0, 0, 0);//ǳ��
	std::cout << "---------------------------------------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);//��ɫ
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
