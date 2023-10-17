#pragma once
#include "User.h"
class CommunicationPlatform
{
public:
	CommunicationPlatform() {};
	//~CommunicationPlatform();


	std::vector<User> users;
	User* currentUser;

	virtual void showMenu() = 0;
	virtual void init() = 0;
	virtual void readUsers() = 0;
	virtual bool saveUsers() = 0;

	CommunicationPlatform(CommunicationPlatform const&) = delete;
	void operator=(CommunicationPlatform const&) = delete;
private:

	
	
};

