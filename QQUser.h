#pragma once
#include <iostream>
#include <string>
#include <vector>


class QQUser
{
//private:
public:
	int _id;
	std::string _password;
	std::string _user_name;
	
public:
	QQUser() {};
	QQUser(int id, std::string password, std::string user_name) : _id(id), _password(password), _user_name(user_name) {};
};


