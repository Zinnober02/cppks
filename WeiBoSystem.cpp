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
	std::cout << "----------欢迎使用微博-----------" << std::endl;
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】登录\n";
	std::cout << "\t【2】注册\n";
	std::cout << "\t【0】退出\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "--------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int choice;
	std::cout << "请输入您的的选择:\n";
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
	std::cout << "输入要登陆的微博:" << std::endl;
	std::cin >> ID;
	auto it = utils::selectIterator(users, ID, [](const User& u, int _id) {
		return u._id == _id;
		});
	if (it == users.end()) {
		std::cout << "未查询到该微博号，请先申请，按任意键返回" << std::endl;
		if (getchar() != EOF)
			return false;
	}
	std::cout << "请输入密码" << std::endl;
	std::cin >> PassWord;
	while (PassWord != it->_password) {
		std::cout << "密码输入错误,请重新输入密码" << std::endl;
		std::cin >> PassWord;
	}
	rgbSet(124, 252, 0, 0, 0, 0);
	std::cout << "登陆成功，按任意键开始使用微博" << std::endl;
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
	std::cout << "----------欢迎使用微博-----------" << std::endl;
	rgbSet(135, 206, 235, 0, 0, 0);
	std::cout << "\t【1】热搜\n";
	std::cout << "\t【2】发布微博\n";
	std::cout << "\t【3】搜索微博\n";
	std::cout << "\t【0】退出\n";
	rgbSet(255, 215, 0, 0, 0, 0);
	std::cout << "--------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);
	int choice;
	std::cout << "请输入您的的选择:\n";
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
		std::cout << "请输入用户名\n";
		std::string name;
		getchar();
		getline(std::cin, name);
		auto it = utils::selectIterator(users, name, [](const User& u, std::string _name) {
			return u._user_name == _name;
			});
		if (it == users.end()) {
			std::cout << "用户不存在\n";
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
	std::cout << "请输入标题：\n";
	std::cin >> newBlog.title;
	std::cout << "请输入内容：\n";
	std::cin >> newBlog.content;
	newBlog.author_id = this->currentUser->_id;

	allBlogs.push_back(newBlog);
}

void WeiBoSystem::addCommit(int blog_id)
{
	std::cout << "【0】评论，输入id回复:";
	int choice = 0;
	std::cin >> choice;
	std::string content;
	std::cout << "请输入内容：\n";
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
	rgbSet(227, 23, 13, 0, 0, 0);//红色
	if (user)
		std::cout << "\t用户" << currentUser->_user_name << "的微博\n";
	else std::cout << "\t\t\t微博榜单\n";
	int n = 1;
	rgbSet(30, 144, 255, 0, 0, 0);//浅蓝
	std::cout << "---------------------------------------------------------------\n";
	for (auto& b : allBlogs)
		printBlog(b);
	return true;
}


blog* WeiBoSystem::selectBlog()
{
	int select;
	std::cout << "选项：\n\t【0】按热度\n\t【-1】返回\n\t【编号】查看详情\n";
	int choice1, choice2;
	std::cin >> choice1;
	switch (choice1) {
	case 0: {
		sort(allBlogs.begin(), allBlogs.end(), [](const blog& a, const blog& b) {
			return a.likes.size() > b.likes.size();
			});
		showBlog();
		std::cout << "输入编号查看详情，0退出" << std::endl;
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
	rgbSet(30, 144, 255, 0, 0, 0);//浅蓝
	std::cout << "---------------------------------------------------------------\n";
	rgbSet(255, 215, 0, 0, 0, 0);//黄色
	printBlog(b);

	auto c = readCommits(b.id);
	for (auto& i : c) {
		std::cout << i.user_id << ":" << i.content << "\t" << i.date << std::endl;
	}
	std::cout << "\t【1】点赞\n\t【2】评论\n\t【3】转发\n\t【0】返回\n";
	int choice; bool flag = true;
	while (flag) {
		std::cin >> choice;
		switch (choice) {
		case 1: {
			like(b);
			system("cls");
			rgbSet(30, 144, 255, 0, 0, 0);//浅蓝
			std::cout << "---------------------------------------------------------------\n";
			rgbSet(255, 215, 0, 0, 0, 0);//黄色
			printBlog(b);
			std::cout << "\t【1】点赞\n\t【2】评论\n\t【3】转发\n\t【0】返回\n";
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
		std::cout << "取消点赞\n";
	}
	else {
		b.likes.emplace(id);
		std::cout << "点赞成功\n";
	}
	Sleep(1000);
}

void WeiBoSystem::printBlog(blog& b)
{
	rgbSet(255, 215, 0, 0, 0, 0);//黄色
	std::cout << "博主: " << getUsername(b.author_id) << "(" << b.author_id << ")\n";
	rgbSet(135, 206, 235, 0, 0, 0);//蓝色
	std::cout << "微博标题: " << b.title << "\t编号" << b.id << std::endl;
	rgbSet(124, 252, 0, 0, 0, 0);//绿色
	std::cout << "发帖时间: " << b.date.year() << "年" << static_cast<unsigned>(b.date.month())
		<< "月" << b.date.day() << "日" << "\t" << b.likes.size() << "赞\n";
	rgbSet(30, 144, 255, 0, 0, 0);//浅蓝
	std::cout << "---------------------------------------------------------------\n";
	rgbSet(255, 255, 255, 0, 0, 0);//白色
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
