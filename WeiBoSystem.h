#pragma once
#include "User.h"
#include "blog.h"
class WeiBoSystem
{
private:
	static WeiBoSystem* Weibo;
	WeiBoSystem() {};
public:
	WeiBoSystem(WeiBoSystem const&) = delete;
	void operator=(WeiBoSystem const&) = delete;
	WeiBoSystem* getInstance();

	std::vector<User> users;
	User* currentUser;
	std::vector<blog> allBlogs;
	std::vector<blog*> myBlogs;
	std::vector<commit> commits;
	blog* currentBlog;

	void init();
	void addBlog();
	void addCommit();
	void showBlog();
	void like();
};

