#pragma once
#include "CommunicationPlatform.h"
#include "blog.h"
class WeiBoSystem : public CommunicationPlatform
{
private:
	
public:
	WeiBoSystem();
	WeiBoSystem(WeiBoSystem const&) = delete;
	void operator=(WeiBoSystem const&) = delete;

	std::vector<User> users;
	User* currentUser;
	std::vector<blog> allBlogs;
	std::vector<commit> allCommits;

	void showMenu() override;
	void readUsers() override;
	void init() override;
	bool saveUsers() override;
	bool login() override;
	void createUser() override;
	std::string getUsername(int id);
	void menu1();


	void addBlog();
	void addCommit(int blog_id);
	bool showBlog(User* user = nullptr);
	blog* selectBlog();
	bool detail(blog& b);
	bool updateBlog();
	void like(blog& b);
	void printBlog(blog& b);
	bool saveCommits();
	bool saveBlogs();
	bool readAllBlogs();
	static std::vector<commit> readCommits(int blog_id);

};

