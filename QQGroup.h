#pragma once
#include <string>
#include "utils.h"
class QQGroup
{
public:
	int id;
	std::string name;
	Friend owner;//保存在QQGroups.txt中
	std::vector<Friend> members;//保存在 members.txt中

	QQGroup() {};
	QQGroup(int id, std::string name, Friend owner, std::vector<Friend> members)
		: id(id), name(name), owner(owner), members(members) {};

	friend std::ostream& operator<<(std::ostream& os, const QQGroup& obj) {
		os << obj.id << " " << obj.name << " " << obj.owner;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, QQGroup& obj) {
		is >> obj.id >> obj.name  >> obj.owner;
		return is;
	}
};

