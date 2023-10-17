#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <sstream> 
#include <iostream>
#include <fstream>
#include <algorithm>
#include <Windows.h>
#include <cassert>

constexpr int wait = 0;
constexpr int reject = 2;
constexpr int agree = 1;

struct Friend {
	int id;
	std::string nickname;//备注或者群昵称
	bool flag = false;//发送为 false，接收为 true
	int status = wait;
	int admin = 0;//管理员权限， 0成员 1管理员，2群主

	friend std::ostream& operator<<(std::ostream& os, const Friend& obj) {
		os << obj.id << " " << obj.nickname << " " << obj.flag << " " << obj.status << " " << obj.admin;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Friend& obj) {
		is >> obj.id >> obj.nickname >> obj.flag >> obj.status >> obj.admin;
		return is;
	}
	static std::string getEnumName(const Friend& a)
	{
		if (a.status == wait) return a.flag ? "等待同意" : "等待对方同意";
		if (a.status == reject) return a.flag ? "已拒绝" : "已被拒绝";
		return "已同意";
	}
};

namespace utils {
	using namespace std::filesystem;
	constexpr int null = -1;
	constexpr int QQ = 0;
	constexpr int WeChat = 1;
	constexpr int WeiBo = 2;
	constexpr int users = 3;
	constexpr int groups = 4;
	constexpr int blogs = 5;
	const std::string selection[6] = { "QQ", "WeChat", "WeiBo", "users", "groups", "likes"};

	const std::string filename[11] =
	{"Users.txt", "friends.txt", "tmpFriends.txt",  
		//     0                        1                    2               
		"allGroups.txt", "groups.txt", "tmpGroups.txt", "members.txt", "tmpMembers.txt",
		//           3                       4                     5                           6                        7
		"blogs.txt", "commits.txt", "likes.txt"
		//         8                     9          10
	};
	
	path getDirPath(int index1, int index2, int id);

	template<class T>
	bool saveData(const std::vector<T>& data, int index1, int index2, int fId, int id = 0)
	{
		auto dir_path = getDirPath(index1, index2, id);
		auto name = fId == -1 ? std::to_string(id) + ".txt" : filename[fId];
		std::ofstream file(dir_path / name, std::ios::out);

		if (file.is_open()) {
			for (const auto& item : data)
				file << item << std::endl;
			file.close();
		}
		else {
			std::cerr << "无法打开文件进行写入: " << dir_path / name << std::endl;
			return false;
		}
		return true;
	}


	template <class T>
	std::vector<T> readData(int index1, int index2, int fId, int id = 0) {
		auto dir_path = getDirPath(index1, index2, id);
		auto name = fId == -1 ? std::to_string(id) + ".txt" : filename[fId];
		std::vector<T> list;
		std::ofstream tmpFile(dir_path / name, std::ios::app);
		tmpFile.close();
		std::ifstream file(dir_path / name, std::ios::in);
		if (file.is_open()) {
			std::string line;
			while (getline(file, line)) {
				std::stringstream ss(line);
				T tmp;
				ss >> tmp;
				list.push_back(tmp);
			}
			file.close();
		}
		else {
			std::cerr << "无法打开文件进行读取: " << dir_path / name << std::endl;
			return std::vector<T>();
		}
		return list;
	}

	

	template<class T>
	bool addObj(T& u, int index1, int index2, int fId, int id = 0) {
		auto dir_path = getDirPath(index1, index2, id);
		auto name = fId == -1 ? std::to_string(id) + ".txt" : filename[fId];
		std::ofstream file(dir_path / name, std::ios::app);
		if (file.is_open()) {
			file << u << std::endl;
			file.close();
		}
		else {
			std::cerr << "无法打开文件进行写入: " << dir_path / name << std::endl;
			return false;
		}
		return true;
	}

	template<class T, typename Cmp>
	T* selectTarget(std::vector<T>& list, int id, Cmp cmp)
	{
		auto it = find_if(list.begin(), list.end(), [&id, &cmp](const T& item) {
			return cmp(item, id);
			});
		if (it != list.end()) return &*it;
		else return nullptr;
	}
	template<class T, typename Cmp>
	std::vector<T>::iterator selectIterator(std::vector<T>& list, int id, Cmp cmp)
	{
		auto it = find_if(list.begin(), list.end(), [&id, &cmp](const T& item) {
			return cmp(item, id);
			});
		return it;
	}

	namespace document {

	}
}