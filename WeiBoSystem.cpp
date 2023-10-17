#include "WeiBoSystem.h"



WeiBoSystem::WeiBoSystem()
{
	readUsers();
}

void WeiBoSystem::showMenu()
{
	User* user = new User(1, "1", "李智");
	currentUser = user;
	init();
	allBlogs.push_back({ "微博1", "正文", 1, { 2, 3, 5, 6 } });
	allBlogs.push_back({ "微博2", "正文", 1, { 3, 5, 6 } });
	allBlogs.push_back({ "微博3", "正文", 1, { 2, 5, 6 , 7, 8} });
	allBlogs.push_back({ "微博4", "正文", 1, { 3, 6 } });
	allBlogs.push_back({ "微博5", "正文", 1});
	allBlogs.push_back({ "微博6", "正文", 1, { 2, 3, 5, 6, 7, 8, 4 } });
	allBlogs.push_back({ "微博7", "正文", 1, { 2, 3, 5, 6 } });
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
	std::cout << "请输入标题：\n";
	std::cin >> newBlog.title;
	std::cout << "请输入内容：\n";
	std::cin >> newBlog.content;
	newBlog.author_id = this->currentUser->_id;

	allBlogs.push_back(newBlog);
}

void WeiBoSystem::addCommit()
{
	std::cout << "0评论，输入id回复\n";
	int choice = 0;
	std::cin >> choice;
	auto newCommit = commit(currentBlog->id, currentUser->_id, choice);
	std::cout << "请输入内容\n";
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
		std::cout << "微博榜单" << std::endl;
		for (auto& b : allBlogs)
			std::cout << b << std::endl;
	}
	else {
		std::cout << user->_user_name + "的微博榜单" << std::endl;
		for (auto& b : allBlogs)
			if (b.author_id == user->_id)
				std::cout << b << std::endl;
	}
	return true;
}


blog* WeiBoSystem::selectBlog()
{
	if (!showBlog()) return nullptr;

	std::cout << "选择：0按热度\n序号查看详情\n-1返回\n";
	int choice1, choice2;
	std::cin >> choice1;
	switch (choice1) {
		case 0: {
			sort(allBlogs.begin(), allBlogs.end(), [](const blog& a, const blog& b) {
				return a.likes.size() > b.likes.size();
				});
			showBlog();
			std::cout << "输入序号查看详细信息" << std::endl;
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
	std::cout << "1点赞 2评论 3转发\n";
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
		std::cout << "取消点赞\n";
	}
	else {
		b.likes.emplace(id);
		std::cout << "点赞成功\n";
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
