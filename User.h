#pragma once
#include "utils.h"
class User
{
//private:

public:
	int _id;
	std::string _password;
	std::string _user_name;
	
public:
	User() {};
	User(int id, std::string password, std::string user_name) : _id(id), _password(password), _user_name(user_name) {};
	//жиди<<
	friend std::ostream& operator<<(std::ostream& os, const User& obj) {
		os << obj._id << " " << obj._password << " " << obj._user_name;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, User& obj) {
		is >> obj._id >> obj._password >> obj._user_name;
		return is;
	}
};


