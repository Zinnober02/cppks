#include "WeiBoSystem.h"

WeiBoSystem* WeiBoSystem::Weibo = new WeiBoSystem();

WeiBoSystem* WeiBoSystem::getInstance()
{
	return Weibo;
}

void WeiBoSystem::init()
{
	//std::move(utils::readData<User>(0, 1));
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
	myBlogs.push_back(&newBlog);
}

void WeiBoSystem::addCommit()
{
	std::cout << "0评论，输入id回复\n";
	int choice = 0;
	std::cin >> choice;
	auto newCommit = commit(currentBlog->id, currentUser->_id, choice);
	std::cout << "请输入内容\n";
	std::cin >> newCommit.content;

	
}
