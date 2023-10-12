#pragma once
#include <string>
#include "utils.h"
class QQGroup
{
public:
	int id;
	std::string name;
	Friend owner;
	std::vector<Friend> members;

	QQGroup() {};
	QQGroup(int id, std::string name, Friend owner, std::vector<Friend> members)
		: id(id), name(name), owner(owner), members(members) {};
};

