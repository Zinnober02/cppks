#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <sstream> 
#include <iostream>
#include <fstream>

const int wait = 0;
const int reject = 2;
const int agree = 1;
struct Friend {
	int id;
	std::string nickname;
	bool flag = false;//发送为 false，接收为 true
	int status = wait;

	friend std::ostream& operator<<(std::ostream& os, const Friend& obj) {
		os << obj.id << " " << obj.nickname << " " << obj.flag << " " << obj.status;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Friend& obj) {
		is >> obj.id >> obj.nickname >> obj.flag >> obj.status;
		return is;
	}
};

namespace utils {
	const std::string filename[6] =
	{"QQUsers.txt", "friends.txt", "tmpFriends.txt",  "QQGroups.txt", "groups.txt", "tmpGroups.txt"};


	template<class T>
	bool saveData(int index, const std::vector<T>& data, int id = 0)
	{
		//相对路径  ./账号
		std::string path = index < 6 ? "QQ" : "WeChat";
		std::filesystem::path current_dir = std::filesystem::current_path();
		std::filesystem::path dir_path = 
			id ? current_dir / "files" / path / std::to_string(id) : current_dir / "files" / path;
		if (!std::filesystem::exists(dir_path))
			std::filesystem::create_directories(dir_path);
		std::ofstream file(dir_path / filename[index], std::ios::out);

		if (file.is_open()) {
			for (const auto& item : data)
				file << item << std::endl;
			file.close();
		}
		else {
			std::cerr << "无法打开文件进行写入: " << dir_path / filename[index] << std::endl;
			return false;
		}
		return true;
	}

	template <class T>
	std::vector<T> readData(int index, int id = 0) {
		//相对路径  ./账号
		std::string path = index < 6 ? "QQ" : "WeChat";
		std::filesystem::path current_dir = std::filesystem::current_path();
		std::filesystem::path dir_path = 
			id ? current_dir / "files" / path / std::to_string(id) : current_dir / "files" / path;
		if (!std::filesystem::exists(dir_path)) {
			std::filesystem::create_directories(dir_path);
			std::cout << "成功创建目录" << std::endl;
		}
		std::vector<T> list;
		std::ofstream tmpFile(dir_path / filename[index], std::ios::app);
		tmpFile.close();
		std::ifstream file(dir_path / filename[index], std::ios::in);
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
			std::cerr << "无法打开文件进行读取: " << dir_path / filename[index] << std::endl;
			return std::vector<T>();
		}
		return list;
	}


	template<class T>
	bool addObj(int index, int id, T& u) {
		//相对路径  ./账号
		std::string path = index < 6 ? "QQ" : "WeChat";
		std::filesystem::path current_dir = std::filesystem::current_path();
		std::filesystem::path dir_path = current_dir / "files" / path / std::to_string(id);
		if (!std::filesystem::exists(dir_path)) {
			std::filesystem::create_directories(dir_path);
			std::cout << "成功创建目录" << std::endl;
		}
		std::ofstream file(dir_path / filename[index], std::ios::app);
		if (file.is_open()) {
			file << u << std::endl;
			file.close();
		}
		else {
			std::cerr << "无法打开文件进行写入: " << dir_path / filename[index] << std::endl;
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
}