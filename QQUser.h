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
	//жиди<<
	friend std::ostream& operator<<(std::ostream& os, const QQUser& obj) {
		os << obj._id << " " << obj._password << " " << obj._user_name;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, QQUser& obj) {
		is >> obj._id >> obj._password >> obj._user_name;
		return is;
	}
};


