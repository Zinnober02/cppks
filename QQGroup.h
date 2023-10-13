#pragma once
#include <string>
#include "utils.h"
class QQGroup
{
public:
	int id;
	std::string name;
	Friend owner;//������QQGroups.txt��
	std::vector<Friend> members;//������ members.txt��

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

